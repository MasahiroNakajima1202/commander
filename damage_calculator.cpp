//*****************************************************************************
//  ダメージ計算クラス
//  author: 中島将浩
//  update: 2015/11/29
//*****************************************************************************
#include "damage_calculator.h"
#include "attack.h"
#include "battle_actor.h"

DamageCalculator::DamageCalculator(BattleObjectAccessor* accessor, Attack* attack, BattleActor* defender):
_accessor(accessor),
_attack(attack),
_defender(defender),
_damage(0),
_valid(false){
	if(attack == nullptr || defender == nullptr){
		_valid = false;
		_damage = 0;
		return;
	}

	//死んでいたら無効で
	if(defender->IsDead()){
		_damage = 0;
		_valid = false;
		return;
	}

	int attack_power(attack->GetPower());
	int defence(defender->GetDefence());
	_damage = max(attack_power - defence, 0);
	_valid = (_damage > 0);

	//direction check
	D3DXVECTOR3 attack_direction(attack->GetDirection());
	D3DXVECTOR3 diffence_direction(0.0f, 0.0f, 1.0f);
	D3DXVECTOR3 rotation(defender->GetRotation());
	D3DXMATRIX rotation_matrix;
	D3DXMatrixRotationY(&rotation_matrix, rotation.y);
	D3DXVec3TransformCoord(&diffence_direction, &diffence_direction, &rotation_matrix);
	float direction_effect(GetDirectionEffect(attack_direction, diffence_direction));
	_damage = static_cast<int>((static_cast<float>(_damage) * direction_effect));
}

float DamageCalculator::GetDirectionEffect(D3DXVECTOR3 attack_direction, D3DXVECTOR3 diffence_direction){
	//不正値チェック
	if(D3DXVec3Dot(&attack_direction, &attack_direction) < 0.5f){return 1.0f;}
	if(D3DXVec3Dot(&diffence_direction, &diffence_direction) < 0.5f){return 1.0f;}

	float dot(D3DXVec3Dot(&attack_direction, &diffence_direction));
	float ret(max(dot, 0.0f) + 1.0f);

	return ret;
}

