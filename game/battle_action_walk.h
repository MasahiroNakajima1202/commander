//*****************************************************************************
//  歩きアクションクラス
//  キャラクターの行動の指定
//  author: 中島将浩
//  update: 2015/10/24
//*****************************************************************************
#ifndef _BATTLE_ACTION_WALK_H_
#define _BATTLE_ACTION_WALK_H_

#include "battle_action.h"

//*****************************************************************************
//  constant
//*****************************************************************************

//*****************************************************************************
//  class
//*****************************************************************************
class BattleActor;
class BattleActionWalk : public BattleAction{
public:

	BattleActionWalk(BattleActor* owner, D3DXVECTOR3 dest_position);
	virtual ~BattleActionWalk();

	virtual void Update(void);
	virtual void OnBegin(void);
	virtual void OnEnd(void);
	virtual bool Finished(void);

	//accessor
private:
	D3DXVECTOR3 _dest_position;
	static const float ZERO_RADIUS;
};



#endif//_NUMBER_H_