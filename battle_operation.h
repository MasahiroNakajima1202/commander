//*****************************************************************************
//  作戦行動クラス
//  author: 中島将浩
//  update: 2015/10/31
//*****************************************************************************
#ifndef _BATTLE_OPERATION_H_
#define _BATTLE_OPERATION_H_

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
class Renderer;						//skillがエフェクトを出したりするときに必要になる
class BattleOperation{
private:
	BattleOperation(){}
public:

	BattleOperation(BattleActor* owner, BattleObjectAccessor* accessor, Renderer* renderer):
	_owner(owner),
	_accessor(accessor),
	_renderer(renderer){
	}

	virtual ~BattleOperation(){}

	virtual void Update(void) = 0;

	virtual bool Finished(void) = 0;

	//accessor
protected:
	BattleActor* _owner;
	BattleObjectAccessor* _accessor;
	Renderer* _renderer;
};



#endif//_NUMBER_H_