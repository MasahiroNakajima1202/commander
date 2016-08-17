//*****************************************************************************
//  ìGAI ë“ã@
//  author: íÜìáè´ç_
//  update: 2016/06/30
//*****************************************************************************
#include "ai_state_wait.h"
#include "constant.h"
#include "battle_object_accessor.h"
#include "battle_actor.h"

//*****************************************************************************
//  constant
//*****************************************************************************


AIStateWait::AIStateWait(BattleObjectAccessor* accessor, Renderer* renderer, BattleActor* owner):
AIState(accessor, renderer, owner){
}

AIStateWait::~AIStateWait(){
	
}

void AIStateWait::Update(void){
	if(AIState::CheckPath() != nullptr){
		return;
	}
}
