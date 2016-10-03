//*****************************************************************************
//  敵AIフィルタクラス
//  author: 中島将浩
//  update: 2016/09/05
//*****************************************************************************
#ifndef _AI_FILTER_H_
#define _AI_FILTER_H_

#include "main.h"
#include <d3dx9.h>

#include "ai_state.h"

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
class AIFilter {
private:
	AIFilter() {}
public:

	AIFilter(BattleObjectAccessor* accessor, BattleActor* owner);

	virtual ~AIFilter();

	virtual void Apply(AIState::POINT* point_array, int array_length);

	virtual void Judge(AIState::POINT* point) = 0;

	//accessor
	void SetNextFilter(AIFilter* value) { _next = value; }
	AIFilter* GetNextFilter(void) { return _next; }
protected:
	AIFilter* _next;
	BattleObjectAccessor* _accessor;
	BattleActor* _owner;
};



#endif//_NUMBER_H_