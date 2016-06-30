//*****************************************************************************
//  �퓬���̋Z�N���X
//  author: �������_
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
	//�U��������o���ۂ́A�͈͎w���ʒu�w��̂���
	BattleObjectAccessor* _accessor;
};



#endif//_NUMBER_H_