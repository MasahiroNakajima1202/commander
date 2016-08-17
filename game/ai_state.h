//*****************************************************************************
//  ìGAI
//  author: íÜìáè´ç_
//  update: 2016/04/11
//*****************************************************************************
#ifndef _ENEMY_AI_H_
#define _ENEMY_AI_H_

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
class AIPath;
class AIState{
private:
	AIState(){}
public:

	AIState(BattleObjectAccessor* accessor, Renderer* renderer, BattleActor* owner);

	virtual ~AIState();

	virtual void Update(void) = 0;

	AIState* CheckPath(void);
	//accessor
protected:


	BattleObjectAccessor* _accessor;
	BattleActor* _owner;
	Renderer* _renderer;

	static const int PATH_MAX = 1;
	AIPath* _path_array[PATH_MAX];
};



#endif//_NUMBER_H_