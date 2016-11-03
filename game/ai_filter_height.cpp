//*****************************************************************************
//  “GAIƒtƒBƒ‹ƒ^ƒNƒ‰ƒX ‚‚³
//  author: ’†“‡«_
//  update: 2016/11/03
//*****************************************************************************
#include "ai_filter_height.h"
#include "battle_actor.h"


AIFilterHeight::AIFilterHeight(BattleObjectAccessor* accessor, BattleActor* owner, float range):
AIFilter(accessor, owner),
_range(range){
}

AIFilterHeight::~AIFilterHeight() {
}

void AIFilterHeight::Judge(AIState::POINT* point) {
	if (_owner == nullptr) { return; }

	float dy(fabsf(_owner->GetPosition().y - point->position.y));

	point->enable = dy < _range;
}
