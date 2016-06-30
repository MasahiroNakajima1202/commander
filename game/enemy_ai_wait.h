//*****************************************************************************
//  ìGAI ë“ã@
//  author: íÜìáè´ç_
//  update: 2016/06/30
//*****************************************************************************
#ifndef _ENEMY_AI_WAIT_H_
#define _ENEMY_AI_WAIT_H_

#include "enemy_ai.h"
//*****************************************************************************
//  constant
//*****************************************************************************

//*****************************************************************************
//  class
//*****************************************************************************
class EnemyAIWait : public EnemyAI{
public:

	EnemyAIWait(BattleObjectAccessor* accessor, Renderer* renderer, BattleActor* owner);

	virtual ~EnemyAIWait();

	virtual void Update(void);

	//accessor
protected:
};



#endif//_NUMBER_H_