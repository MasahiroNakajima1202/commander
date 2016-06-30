//*****************************************************************************
//  作戦行動クラス 敵の近くまで行って、通常攻撃を相手が倒れるまで続ける
//  author: 中島将浩
//  update: 2015/10/31
//*****************************************************************************
#include "battle_operation_attack.h"
#include "battle_actor.h"
#include "battle_skill_attack.h"
#include "battle_action_walk.h"
#include "battle_action_skill.h"
#include "battle_object_accessor.h"

#include <math.h>

BattleOperationAttack::BattleOperationAttack(BattleActor* owner, BattleObjectAccessor* accessor, Renderer* renderer, BattleActor* target):
BattleOperation(owner, accessor, renderer),
_target(target){
}

BattleOperationAttack::~BattleOperationAttack(){
}

void BattleOperationAttack::Update(void){
	if(_owner == nullptr){return;}

	//target生存確認
	if(_target == nullptr){return;}
	if(!_accessor->IsEnemy(_target)){return;}
	if(_target->IsDead()){return;}

	//owner行動中チェック
	if(_owner->IsActing()){return;}

	//距離チェック
	D3DXVECTOR3 owner_position(_owner->GetPosition());
	D3DXVECTOR3 target_position(_target->GetPosition());
	D3DXVECTOR3 to_target(target_position - owner_position);
	float sq_length(D3DXVec3Dot(&to_target, &to_target));
	const float RANGE(20.0f);
	if(sq_length > RANGE * RANGE){
		//移動命令
		D3DXVECTOR3 direction(to_target);
		D3DXVec3Normalize(&direction, &direction);
		float length(sqrt(sq_length) - RANGE);
		D3DXVECTOR3 dest_position(owner_position + direction * length);
		_owner->SetAction(new BattleActionWalk(_owner, dest_position));
		return;
	}

	//方向チェック

	//攻撃命令
	_owner->SetSkill(new BattleSkillAttack(_owner, _renderer, _accessor));
	_owner->SetAction(new BattleActionSkill(_owner));
}

bool BattleOperationAttack::Finished(void){
	//そもそも不在
	if(_target == nullptr){
		return true;
	}
	//敵じゃなかった
	if(!_accessor->IsEnemy(_target)){
		return true;
	}
	//し、死んでる……！
	if(_target->IsDead()){
		return true;
	}

	return false;
}
