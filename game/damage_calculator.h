//*****************************************************************************
//  ダメージ計算クラス
//  author: 中島将浩
//  update: 2015/11/29
//*****************************************************************************
#ifndef _DAMAGE_CALCULATOR_H_
#define _DAMAGE_CALCULATOR_H_

#include "main.h"
#include <d3dx9.h>

//*****************************************************************************
//  constant
//*****************************************************************************

//*****************************************************************************
//  class
//*****************************************************************************
class BattleObjectAccessor;
class BattleActor;
class Attack;
class DamageCalculator{
private:
	DamageCalculator(){}
public:

	DamageCalculator(BattleObjectAccessor* accessor, Attack* attack, BattleActor* defender);

	virtual ~DamageCalculator(){}

	int GetDamage(void){return _damage;}
	bool IsValid(void){return _valid;}

	//accessor
protected:
	BattleObjectAccessor* _accessor;
	Attack* _attack;
	BattleActor* _defender;
	int _damage;
	bool _valid;

	float GetDirectionEffect(D3DXVECTOR3 attack_direction, D3DXVECTOR3 diffence_direction);
};



#endif//_NUMBER_H_