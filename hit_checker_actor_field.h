//*****************************************************************************
//  �n�ʂƃL�����N�^�[�Ԃ̓����蔻��N���X
//  author: �������_
//  update: 2015/10/31
//*****************************************************************************
#ifndef _HIT_CHECKER_ACTOR_FIELD_H_
#define _HIT_CHECKER_ACTOR_FIELD_H_

#include "main.h"
#include <d3dx9.h>

//*****************************************************************************
//  constant
//*****************************************************************************

//*****************************************************************************
//  class
//*****************************************************************************
class BattleObjectAccessor;
class HitCheckerActorField{
private:
	HitCheckerActorField(){}
public:

	HitCheckerActorField(BattleObjectAccessor* accessor):
	_accessor(accessor){
	}

	virtual ~HitCheckerActorField(){}

	virtual void Update(void);

	//accessor
protected:
	BattleObjectAccessor* _accessor;
};



#endif//_NUMBER_H_