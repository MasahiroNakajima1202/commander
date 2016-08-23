//*****************************************************************************
//  “GAIó‘ÔˆÚsƒNƒ‰ƒX ˆê’èˆÈãã‚Á‚Ä‚¢‚é
//  author: ’†“‡«_
//  update: 2016/08/24
//*****************************************************************************
#include "ai_path_weaken.h"
#include "battle_actor.h"
#include "battle_object_accessor.h"

AIPathWeaken::AIPathWeaken(BattleObjectAccessor* accessor, Renderer* renderer, AIState* from, AIState* to, BattleActor* owner, float threshold) :
	AIPath(accessor, renderer, from, to),
	_owner(owner),
	_threthold(threshold){
}

AIPathWeaken::~AIPathWeaken() {
}

void AIPathWeaken::Update(void) {
}

bool AIPathWeaken::CheckToPassThrough(void) {
	if (_owner == nullptr) { return false; }
	if (_accessor == nullptr) { return false; }

	// TODO: HP‚ªthresholdˆÈã‚ÌŠ„‡‚ÅŒ¸‚Á‚Ä‚¢‚½‚ç

	return false;
}
