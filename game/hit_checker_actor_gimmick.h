//*****************************************************************************
//  ギミックとキャラクター間の当たり判定クラス
//  author: 中島将浩
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
class Renderer;					//ダメージ表示のために必要になりました
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
	
	//当たったときの処理
	void HitActor(BattleActor* actor, Gimmick* gimmick);

	//当たったかどうかのチェック
	bool HitCheck(BattleActor* actor, Gimmick* gimmick);
};



#endif//_NUMBER_H_