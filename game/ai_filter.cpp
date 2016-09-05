//*****************************************************************************
//  敵AIフィルタクラス
//  author: 中島将浩
//  update: 2016/09/05
//*****************************************************************************
#include "ai_filter.h"
AIFilter::AIFilter(BattleObjectAccessor* accessor) :
_accessor(accessor),
_next(nullptr){
}

AIFilter::~AIFilter() {}

void AIFilter::Apply(AIState::POINT* src_array, int src_length) {
	return;
}

