//*****************************************************************************
//  敵AIフィルタクラス 高さ
//  author: 中島将浩
//  update: 2016/11/03
//*****************************************************************************
#ifndef _AI_FILTER_HEIGHT_H_
#define _AI_FILTER_HEIGHT_H_


#include "ai_filter.h"

//*****************************************************************************
//  constant
//*****************************************************************************

//*****************************************************************************
//  class
//*****************************************************************************
class BattleActor;
class BattleObjectAccessor;
class Renderer;
class AIState;
class AIFilterHeight : public AIFilter {
public:

	AIFilterHeight(BattleObjectAccessor* accessor, BattleActor* owner, float range);

	virtual ~AIFilterHeight();

	virtual void Judge(AIState::POINT* point);
protected:
	float _range;
};



#endif//_NUMBER_H_