//*****************************************************************************
//  攻撃判定クラス
//  author: 中島将浩
//  update: 2015/10/25
//*****************************************************************************
#include "attack.h"
#include "attack_accessor.h"
int Attack::_next_id(0);
AttackAccessor* Attack::_accessor(nullptr);
//*****************************************************************************
//  constant
//*****************************************************************************

Attack::Attack(int hit_count, BattleActor* owner, int power, D3DXVECTOR3 direction):
_id(-1),
_owner(owner),
_hit_array(nullptr),
_hit_count(hit_count),
_power(power),
_player_scope(true),
_enemy_scope(true),
_direction(direction){
	//子クラス内で用いるポインタ配列の生成
	if(hit_count != 0){
		_hit_array = new Hit*[hit_count];
	}

	_id = _next_id;
	_next_id++;
	_next_id%=ID_LIMIT;

	if(_accessor != nullptr){
		_accessor->Entry(this);
	}
}

Attack::~Attack(){
	if(_hit_array != nullptr){
		delete[] _hit_array;
		_hit_array = nullptr;
	}

	if(_accessor != nullptr){
		_accessor->Leave(this);
	}
}

int Attack::GetPower(void){
	return _power;
}


Hit* Attack::GetHit(int index){
	if(index < 0 || _hit_count <= index){return nullptr;}
	if(_hit_array == nullptr){return nullptr;}

	Hit* hit(_hit_array[index]);

	return hit;
}
