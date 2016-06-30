//*****************************************************************************
//  戦闘指示クラス用ステートパターン親クラス
//  author: 中島将浩
//  update: 2015/12/29
//*****************************************************************************
#ifndef _BATTLE_COMMANDER_STATE_H_
#define _BATTLE_COMMANDER_STATE_H_

#include "main.h"
#include <d3dx9.h>

//*****************************************************************************
//  constant
//*****************************************************************************

//*****************************************************************************
//  class
//*****************************************************************************
class BattleCommander;
class BattleObjectAccessor;
class Renderer;
class BattleCommanderState{
private:
	BattleCommanderState(){}
public:

	BattleCommanderState(BattleCommander* owner, BattleObjectAccessor* accessor, Renderer* renderer):
	_owner(owner),
	_accessor(accessor),
	_renderer(renderer){
	}

	virtual ~BattleCommanderState(){}

	virtual void Update(void) = 0;

	virtual void StateIn(void) = 0;

	virtual void StateOut(void) = 0;

	virtual void MouseLeftDown(void) = 0;

	virtual void MouseLeftUp(void) = 0;

	virtual void MouseRightDown(void) = 0;

	virtual void MouseRightUp(void) = 0;

protected:
	BattleCommander* _owner;
	BattleObjectAccessor* _accessor;
	Renderer* _renderer;
};



#endif//_NUMBER_H_