//*****************************************************************************
//  ステートパターン歩き中
//  author: 中島将浩
//  update: 2015/11/14
//*****************************************************************************
#ifndef _BATTLE_ACTOR_STATE_WALK_H_
#define _BATTLE_ACTOR_STATE_WALK_H_

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
class BattleActorStateWalk : public BattleActorState{
public:

	BattleActorStateWalk(BattleActor* owner):
	BattleActorState(owner){
	}

	virtual ~BattleActorStateWalk(){}

	virtual void Update(void);

	virtual void StateIn(void);

	virtual void StateOut(void);

protected:
};



#endif//_NUMBER_H_