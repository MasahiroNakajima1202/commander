//*****************************************************************************
//  ìGAIèÛë‘à⁄çsÉNÉâÉX
//  author: íÜìáè´ç_
//  update: 2016/07/05
//*****************************************************************************
#ifndef _AI_PATH_H_
#define _AI_PATH_H_

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
class EnemyAI;
class AIPath{
private:
	AIPath(){}
public:

	AIPath(BattleObjectAccessor* accessor, Renderer* renderer, EnemyAI* from, EnemyAI* to);

	virtual ~AIPath();

	virtual void Update(void);

	virtual bool CheckToPassThrough(void) = 0;

	//accessor
protected:
	BattleObjectAccessor* _accessor;
	Renderer* _renderer;
	EnemyAI* _from;
	EnemyAI* _to;
};



#endif//_NUMBER_H_