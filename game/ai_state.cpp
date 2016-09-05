//*****************************************************************************
//  “GAI
//  author: ’†“‡«_
//  update: 2016/04/11
//*****************************************************************************
#include "ai_state.h"
#include "ai_path.h"
#include "battle_actor.h"
#include "ai_filter.h"
//*****************************************************************************
//  constant
//*****************************************************************************


AIState::AIState(BattleObjectAccessor* accessor, Renderer* renderer, BattleActor* owner, int x_num, int y_num, int z_num):
_accessor(accessor),
_renderer(renderer),
_owner(owner),
X_POINT_NUM(x_num),
Y_POINT_NUM(y_num),
Z_POINT_NUM(z_num),
_point_table(nullptr),
_target_position(0.0f, 0.0f, 0.0f),
_filter_list(nullptr){
	_point_table = new POINT[x_num*y_num*z_num];
}

AIState::~AIState(){
	if (_point_table != nullptr) {
		delete [] _point_table;
		_point_table = nullptr;
	}
}

void AIState::Update(void) {
	int length(X_POINT_NUM * Y_POINT_NUM * Z_POINT_NUM);

	//generating phase

	//filtering phase
	AIFilter* cur_filter(_filter_list);
	while (cur_filter != nullptr) {
		cur_filter->Apply(_point_table, length);
	}

	//scoring phase
}
