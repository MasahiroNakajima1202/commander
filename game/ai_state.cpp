//*****************************************************************************
//  �GAI
//  author: �������_
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
	
	for (int i = 0; i < length; i++){
		POINT* point(&point_table[i]);
		if (!point->enable) { continue; }
		Debug::EntryHitView(point->position, 2.0f, D3DXVECTOR4(1.0f, 0.0f, 0.0f, 1.0f));
	}

	//�f�o�b�O�X�t�B�A�ɐF������Ƃ��납��
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