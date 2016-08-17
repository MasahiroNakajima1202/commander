//*****************************************************************************
//  ìGAI ãﬂÇ≠Ç…Ç¢ÇÈìzÇçUåÇ
//  author: íÜìáè´ç_
//  update: 2016/04/11
//*****************************************************************************
#ifndef _ENEMY_AI_ATTACK_NEIGHBOR_H_
#define _ENEMY_AI_ATTACK_NEIGHBOR_H_

#include "ai_state.h"
//*****************************************************************************
//  constant
//*****************************************************************************

//*****************************************************************************
//  class
//*****************************************************************************
class AIStateAttackNeighbor : public AIState{
public:

	AIStateAttackNeighbor(BattleObjectAccessor* accessor, Renderer* renderer, BattleActor* owner, BattleActor* target);

	virtual ~AIStateAttackNeighbor();

	virtual void Update(void);

	//accessor
protected:
	BattleActor* _target;
};



#endif//_NUMBER_H_