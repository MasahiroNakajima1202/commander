//*****************************************************************************
//  ìGAI ãﬂÇ≠Ç…Ç¢ÇÈìzÇçUåÇ
//  author: íÜìáè´ç_
//  update: 2016/04/11
//*****************************************************************************
#ifndef _ENEMY_AI_ATTACK_NEIGHBOR_H_
#define _ENEMY_AI_ATTACK_NEIGHBOR_H_

#include "enemy_ai.h"
//*****************************************************************************
//  constant
//*****************************************************************************

//*****************************************************************************
//  class
//*****************************************************************************
class EnemyAIAttackNeighbor : public EnemyAI{
public:

	EnemyAIAttackNeighbor(BattleObjectAccessor* accessor, Renderer* renderer, BattleActor* owner);

	virtual ~EnemyAIAttackNeighbor();

	virtual void Update(void);

	//accessor
protected:
};



#endif//_NUMBER_H_