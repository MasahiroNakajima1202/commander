//*****************************************************************************
//  �X�e�[�g�p�^�[���퓬�s�\
//  author: �������_
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