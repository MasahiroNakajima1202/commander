//*****************************************************************************
//  �U������ƃL�����N�^�[�Ԃ̓����蔻��N���X
//  author: �������_
//  update: 2015/10/31
//*****************************************************************************
#ifndef _HIT_CHECKER_ATTACK_ACTOR_H_
#define _HIT_CHECKER_ATTACK_ACTOR_H_

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
class Attack;
class HitCheckerAttackActor{
private:
	HitCheckerAttackActor(){}
public:

	HitCheckerAttackActor(BattleObjectAccessor* accessor, Renderer* renderer):
	_accessor(accessor),
	_renderer(renderer){
	}

	virtual ~HitCheckerAttackActor(){}

	void Update(void);

	//accessor
protected:
	BattleObjectAccessor* _accessor;
	Renderer* _renderer;
	
	//���������Ƃ��̏���
	void HitActor(BattleActor* actor, Attack* attack);

	//�����������ǂ����̃`�F�b�N
	bool HitCheck(BattleActor* actor, Attack* attack);
};



#endif//_NUMBER_H_