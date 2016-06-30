//*****************************************************************************
//  ステートパターン戦闘不能
//  author: 中島将浩
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
	//アニメーション再生
}

void BattleActorStateDead::StateOut(void){
	if(_owner == nullptr){return;}
	D3DXVECTOR3 rotation(_owner->GetDestRotation());
	rotation.x = 0.0f;
	_owner->SetDestRotation(rotation);
}