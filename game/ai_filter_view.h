//*****************************************************************************
//  �GAI�t�B���^�N���X ���E��
//  author: �������_
//  update: 2016/10/03
//*****************************************************************************
#ifndef _AI_FILTER_VIEW_H_
#define _AI_FILTER_VIEW_H_


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
class AIFilterView : public AIFilter{
public:

	AIFilterView(BattleObjectAccessor* accessor, BattleActor* owner, float angel);

	virtual ~AIFilterView();

	virtual void Judge(AIState::POINT* point);
protected:
	float _angle;
};



#endif//_NUMBER_H_