//*****************************************************************************
//  ステートパターン待機中
//  author: 中島将浩
//  update: 2015/11/14
//*****************************************************************************
#ifndef _BATTLE_ACTOR_STATE_IDLE_H_
#define _BATTLE_ACTOR_STATE_IDLE_H_

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
class BattleActorStateIdle : public BattleActorState{
public:

	BattleActorStateIdle(BattleActor* owner):
	BattleActorState(owner){
	}

	virtual ~BattleActorStateIdle(){}

	virtual void Update(void);

	virtual void StateIn(void);

	virtual void StateOut(void);

protected:
};



#endif//_NUMBER_H_