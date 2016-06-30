//*****************************************************************************
//  ���s���N���X
//  author: �������_
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
class Renderer;						//skill���G�t�F�N�g���o�����肷��Ƃ��ɕK�v�ɂȂ�
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