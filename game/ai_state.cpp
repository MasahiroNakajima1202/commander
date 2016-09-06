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
//*****************************************************************************
//  constant
//*****************************************************************************


AIState::AIState(BattleObjectAccessor* accessor, Renderer* renderer, BattleActor* owner):
_accessor(accessor),
_renderer(renderer),
_owner(owner),
_target_position(0.0f, 0.0f, 0.0f),
_generator(nullptr),
_filter_list(nullptr){
	//hack
	_generator = new AIGenerator(accessor, owner, 5, 1, 5, 10.0f, 0.0f, 10.0f);
	_filter_list = new AIFilter(accessor);
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
	}

	//scoring phase
}
