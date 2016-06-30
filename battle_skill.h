//*****************************************************************************
//  戦闘中の技クラス
//  author: 中島将浩
//  update: 2015/10/31
//*****************************************************************************
#ifndef _BATTLE_SKILL_H_
#define _BATTLE_SKILL_H_

#include "main.h"
#include <d3dx9.h>

//*****************************************************************************
//  constant
//*****************************************************************************

//*****************************************************************************
//  class
//*****************************************************************************
class BattleActor;
class Renderer;
class BattleObjectAccessor;
class BattleSkill{
private:
	BattleSkill(){}
public:

	BattleSkill(BattleActor* owner, Renderer* renderer, BattleObjectAccessor* accessor):
	_owner(owner),
	_renderer(renderer),
	_accessor(accessor){
	}

	virtual ~BattleSkill(){}

	virtual void Update(void) = 0;

	virtual bool Finished(void) = 0;

	//accessor
protected:
	BattleActor* _owner;
	Renderer* _renderer;
	//攻撃判定を出す際の、範囲指定や位置指定のため
	BattleObjectAccessor* _accessor;
};



#endif//_NUMBER_H_