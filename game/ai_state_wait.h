//*****************************************************************************
//  �GAI �ҋ@
//  author: �������_
//  update: 2016/06/30
//*****************************************************************************
#ifndef _ENEMY_AI_WAIT_H_
#define _ENEMY_AI_WAIT_H_

#include "ai_state.h"
//*****************************************************************************
//  constant
//*****************************************************************************

//*****************************************************************************
//  class
//*****************************************************************************
class AIStateWait : public AIState{
public:

	AIStateWait(BattleObjectAccessor* accessor, Renderer* renderer, BattleActor* owner);

	virtual ~AIStateWait();

	virtual void Update(void);

	//accessor
protected:
};



#endif//_NUMBER_H_