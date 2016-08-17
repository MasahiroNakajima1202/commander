//*****************************************************************************
//  ìGAI ì¶ñS
//  author: íÜìáè´ç_
//  update: 2016/06/30
//*****************************************************************************
#ifndef _ENEMY_AI_ESCAPE_H_
#define _ENEMY_AI_ESCAPE_H_

#include "ai_state.h"
//*****************************************************************************
//  constant
//*****************************************************************************

//*****************************************************************************
//  class
//*****************************************************************************
class AIStateEscape : public AIState{
public:

	AIStateEscape(BattleObjectAccessor* accessor, Renderer* renderer, BattleActor* owner);

	virtual ~AIStateEscape();

	virtual void Update(void);

	//accessor
protected:
};



#endif//_NUMBER_H_