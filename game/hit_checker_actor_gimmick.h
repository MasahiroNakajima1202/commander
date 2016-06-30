//*****************************************************************************
//  �M�~�b�N�ƃL�����N�^�[�Ԃ̓����蔻��N���X
//  author: �������_
//  update: 2016/03/13
//*****************************************************************************
#ifndef _HIT_CHECKER_ACTOR_GIMMICK_H_
#define _HIT_CHECKER_ACTOR_GIMMICK_H_

#include "main.h"
#include <d3dx9.h>

//*****************************************************************************
//  constant
//*****************************************************************************

//*****************************************************************************
//  class
//*****************************************************************************
class Renderer;					//�_���[�W�\���̂��߂ɕK�v�ɂȂ�܂���
class BattleObjectAccessor;
class BattleActor;
class Gimmick;
class HitCheckerkActorGimmick{
private:
	HitCheckerkActorGimmick(){}
public:

	HitCheckerkActorGimmick(BattleObjectAccessor* accessor):
	_accessor(accessor){
	}

	virtual ~HitCheckerkActorGimmick(){}

	void Update(void);

	//accessor
protected:
	BattleObjectAccessor* _accessor;
	
	//���������Ƃ��̏���
	void HitActor(BattleActor* actor, Gimmick* gimmick);

	//�����������ǂ����̃`�F�b�N
	bool HitCheck(BattleActor* actor, Gimmick* gimmick);
};



#endif//_NUMBER_H_