//*****************************************************************************
//  ステートパターン戦闘不能
//  author: 中島将浩
//  update: 2015/11/29
//*****************************************************************************
#ifndef _BATTLE_ACTOR_STATE_DEAD_H_
#define _BATTLE_ACTOR_STATE_DEAD_H_

#include "main.h"
#include <d3dx9.h>

#include "battle_actor_state.h"

//*****************************************************************************
//  constant
//*****************************************************************************

//*****************************************************************************
//  class
//*****************************************************************************
class BattleActor;
class BattleActorStateDead : public BattleActorState{
public:

	BattleActorStateDead(BattleActor* owner):
	BattleActorState(owner){
	}

	virtual ~BattleActorStateDead(){}

	virtual void Update(void);

	virtual void StateIn(void);

	virtual void StateOut(void);

protected:
};



#endif//_NUMBER_H_