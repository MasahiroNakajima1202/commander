//*****************************************************************************
//  �X�e�[�g�p�^�[���퓬�s�\
//  author: �������_
//  update: 2015/11/29
//*****************************************************************************
#include "battle_actor_state_dead.h"
#include "battle_actor.h"

void BattleActorStateDead::Update(void){
	if(_owner == nullptr){return;}
	D3DXVECTOR3 rotation(_owner->GetDestRotation());
	rotation.x = D3DX_PI * 0.5f;
	_owner->SetDestRotation(rotation);
}

void BattleActorStateDead::StateIn(void){
	//�A�j���[�V�����Đ�
}

void BattleActorStateDead::StateOut(void){
	if(_owner == nullptr){return;}
	D3DXVECTOR3 rotation(_owner->GetDestRotation());
	rotation.x = 0.0f;
	_owner->SetDestRotation(rotation);
}