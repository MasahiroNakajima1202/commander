//*****************************************************************************
//  “GAI
//  author: ’†“‡«_
//  update: 2016/04/11
//*****************************************************************************
#include "ai_state.h"
#include "ai_path.h"
#include "battle_actor.h"
#include "ai_filter.h"
#include "ai_generator.h"
#include "ai_scorer.h"

#include "debug.h"
//*****************************************************************************
//  constant
//*****************************************************************************


AIState::AIState(BattleObjectAccessor* accessor, Renderer* renderer, BattleActor* owner):
_accessor(accessor),
_renderer(renderer),
_owner(owner),
_target_position(0.0f, 0.0f, 0.0f),
_generator(nullptr),
_filter_list(nullptr),
_scorer_list(nullptr){
	
}

AIState::~AIState(){
	
}

void AIState::Update(void) {
	//generating phase
	_generator->AlignmentPoints();
	POINT* point_table(_generator->GetPointTable());
	int length(_generator->GetTableLength());

	//filtering phase
	AIFilter* cur_filter(_filter_list);
	while (cur_filter != nullptr) {
		cur_filter->Apply(point_table, length);
		cur_filter = cur_filter->GetNextFilter();
	}

	//scoring phase
	AIScorer* cur_scorer(_scorer_list);
	while (cur_scorer != nullptr) {
		cur_scorer->Apply(point_table, length);
		cur_scorer = cur_scorer->GetNextScorer();
	}
	
	//target position
	float target_distance = 9999.0f;
	int index(0);
	float max_score(0.0f);
	for (int i = 0; i < length; i++){
		POINT* point(&point_table[i]);
		if (!point->enable) { continue; }
		if (max_score > point->value) { continue; }

		D3DXVECTOR3 to_owner(_owner->GetPosition() - point->position);
		to_owner.y = 0.0f;
		float sq_distance(D3DXVec3Dot(&to_owner, &to_owner));

		if (max_score < point->value || sq_distance < target_distance * target_distance) {
			index = i;
			target_distance = sqrtf(sq_distance);
			max_score = point->value;
		}
	}

	_target_position = point_table[index].position;
	

	for (int i = 0; i < length; i++) {
		POINT* point(&point_table[i]);
		if (!point->enable) { continue; }
		float gb(1.0f - point->value);
		float size(2.0f);
		if (i == index) { size = 4.0f; }
		Debug::EntryHitView(point->position, size, D3DXVECTOR4(1.0f, gb, gb, 1.0f));
	}
}

void AIState::AddFilter(AIFilter* value) {
	if (_filter_list == nullptr) {
		_filter_list = value;
		return;
	}

	AIFilter* cur(_filter_list->GetNextFilter());
	while (cur->GetNextFilter() != nullptr) {
		cur = cur->GetNextFilter();
	}

	cur->SetNextFilter(value);
}
void AIState::AddScorer(AIScorer* value) {
	if (_scorer_list == nullptr) {
		_scorer_list = value;
		return;
	}

	AIScorer* cur(_scorer_list->GetNextScorer());
	while (cur->GetNextScorer() != nullptr) {
		cur = cur->GetNextScorer();
	}

	cur->SetNextScorer(value);
}