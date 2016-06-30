//*****************************************************************************
//  ステートパターン親クラス
//  author: 中島将浩
//  update: 2015/11/14
//*****************************************************************************
#ifndef _BATTLE_ACTOR_STATE_H_
#define _BATTLE_ACTOR_STATE_H_

#include "main.h"
#include <d3dx9.h>

//*****************************************************************************
//  constant
//*****************************************************************************

//*****************************************************************************
//  class
//*****************************************************************************
class BattleActor;
class BattleActorState{
private:
	BattleActorState(){}
public:

	BattleActorState(BattleActor* owner):
	_owner(owner){
	}

	virtual ~BattleActorState(){}

	virtual void Update(void) = 0;

	virtual void StateIn(void) = 0;

	virtual void StateOut(void) = 0;

protected:
	BattleActor* _owner;
};



#endif//_NUMBER_H_