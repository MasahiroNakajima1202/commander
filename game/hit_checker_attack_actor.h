//*****************************************************************************
//  攻撃判定とキャラクター間の当たり判定クラス
//  author: 中島将浩
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
class Renderer;					//ダメージ表示のために必要になりました
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
	
	//当たったときの処理
	void HitActor(BattleActor* actor, Attack* attack);

	//当たったかどうかのチェック
	bool HitCheck(BattleActor* actor, Attack* attack);
};



#endif//_NUMBER_H_