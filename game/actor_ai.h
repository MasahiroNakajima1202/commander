//*****************************************************************************
//  ìGAI
//  author: íÜìáè´ç_
//  update: 2016/08/16
//*****************************************************************************
#ifndef _ACTOR_AI_H_
#define _ACTOR_AI_H_

#include "main.h"
#include <d3dx9.h>

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
class AIPath;
class ActorAI {
private:
	ActorAI() {}
public:

	ActorAI(BattleObjectAccessor* accessor, Renderer* renderer, BattleActor* owner);

	virtual ~ActorAI();

	void Update(void);

	void SetCurrentState(AIState* value);

	ActorAI* AddState(AIState* state);
	ActorAI* AddPath(AIPath* path);

	//accessor
protected:
	BattleObjectAccessor* _accessor;
	BattleActor* _owner;
	Renderer* _renderer;

	static const int PATH_MAX = 16;
	AIPath* _path_array[PATH_MAX];

	static const int STATE_MAX = 16;
	AIState* _state_array[STATE_MAX];

	AIState* _current_state;
};



#endif//_NUMBER_H_