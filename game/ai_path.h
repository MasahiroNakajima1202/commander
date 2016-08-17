//*****************************************************************************
//  敵AI状態移行クラス
//  author: 中島将浩
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
class AIState;
class AIPath{
private:
	AIPath(){}
public:

	AIPath(BattleObjectAccessor* accessor, Renderer* renderer, AIState* from, AIState* to);

	virtual ~AIPath();

	virtual void Update(void);

	virtual bool CheckToPassThrough(void) = 0;

	//accessor
	AIState* GetNext(void){return _to;}
protected:
	BattleObjectAccessor* _accessor;
	Renderer* _renderer;
	AIState* _from;
	AIState* _to;
};



#endif//_NUMBER_H_