//*****************************************************************************
//  ìGAI ì¶ñS
//  author: íÜìáè´ç_
//  update: 2016/06/30
//*****************************************************************************
#ifndef _ENEMY_AI_ESCAPE_H_
#define _ENEMY_AI_ESCAPE_H_

#include "enemy_ai.h"
//*****************************************************************************
//  constant
//*****************************************************************************

//*****************************************************************************
//  class
//*****************************************************************************
class EnemyAIEscape : public EnemyAI{
public:

	EnemyAIEscape(BattleObjectAccessor* accessor, Renderer* renderer, BattleActor* owner);

	virtual ~EnemyAIEscape();

	virtual void Update(void);

	//accessor
protected:
};



#endif//_NUMBER_H_