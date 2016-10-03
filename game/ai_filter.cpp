//*****************************************************************************
//  敵AIフィルタクラス
//  author: 中島将浩
//  update: 2016/09/05
//*****************************************************************************
#include "ai_filter.h"
AIFilter::AIFilter(BattleObjectAccessor* accessor, BattleActor* owner) :
_accessor(accessor),
_owner(owner),
_next(nullptr){
}

AIFilter::~AIFilter() {}

void AIFilter::Apply(AIState::POINT* point_array, int array_length) {
	for (int i = 0; i < array_length; i++) {
		Judge(point_array + i);
	}
}

