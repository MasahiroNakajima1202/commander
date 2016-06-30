//*****************************************************************************
//  攻撃判定クラス
//  author: 中島将浩
//  update: 2015/10/25
//*****************************************************************************
#ifndef _ATTACK_H_
#define _ATTACK_H_

#include "main.h"

#include <d3dx9.h>

//*****************************************************************************
//  constant
//*****************************************************************************

//*****************************************************************************
//  class
//*****************************************************************************
class AttackAccessor;
class Hit;
class BattleActor;
class Attack{
public:

	//scope指定無しで生成すると、全員をscopeに含めます
	Attack(int hit_count, BattleActor* owner, int power, D3DXVECTOR3 direction);

	virtual ~Attack();

	virtual void Update(void) = 0;
	virtual bool Finished(void) = 0;

	bool IsScopingPlayer(void){return _player_scope;}
	bool IsScopingEnemy(void){return _enemy_scope;}

	int GetPower(void);

	//accessor
	int GetHitCount(void){return _hit_count;}
	Hit* GetHit(int index);
	int GetId(void){return _id;}
	static void SetAccessor(AttackAccessor* accessor){_accessor = accessor;}
	void SetPlayerScope(bool value){_player_scope = value;}
	void SetEnemyScope(bool value){_enemy_scope = value;}
	BattleActor* GetOwner(void){return _owner;}
	D3DXVECTOR3 GetDirection(void){return _direction;}

protected:
	int _id;
	BattleActor* _owner;
	Hit** _hit_array;
	int _hit_count;
	int _power;

	//scopes
	bool  _player_scope;
	bool _enemy_scope;

	D3DXVECTOR3 _direction;

	static const int ID_LIMIT = 65536;
	static int _next_id;
	static AttackAccessor* _accessor;
};



#endif//_NUMBER_H_