//*****************************************************************************
//  地面とキャラクター間の当たり判定クラス
//  author: 中島将浩
//  update: 2016/03/11
//*****************************************************************************
#ifndef _HIT_CHECKER_ACTOR_TILE_FIELD_H_
#define _HIT_CHECKER_ACTOR_TILE_FIELD_H_

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
class HitCheckerActorTileField{
private:
	HitCheckerActorTileField(){}
public:

	HitCheckerActorTileField(BattleObjectAccessor* accessor):
	_accessor(accessor){
	}

	virtual ~HitCheckerActorTileField(){}

	virtual void Update(void);

	//accessor
protected:
	BattleObjectAccessor* _accessor;

	//二段以上の高さを移動しようとしていたら止まってもらう
	bool StopActor(D3DXVECTOR3 pre_position, D3DXVECTOR3 cur_position, D3DXVECTOR3 &out_position);
	void HitCheckActor(BattleActor* actor);
};



#endif//_NUMBER_H_