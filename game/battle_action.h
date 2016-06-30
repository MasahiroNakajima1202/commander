//*****************************************************************************
//  アクションクラス
//  キャラクターの行動の指定
//  author: 中島将浩
//  update: 2015/10/24
//*****************************************************************************
#ifndef _BATTLE_ACTION_H_
#define _BATTLE_ACTION_H_

#include "main.h"

#include <d3dx9.h>

//*****************************************************************************
//  constant
//*****************************************************************************

//*****************************************************************************
//  class
//*****************************************************************************
class BattleActor;
class BattleAction{
public:

	BattleAction(BattleActor* owner):
	_owner(owner){
	}

	virtual ~BattleAction(){
	}

	virtual void Update(void) = 0;
	virtual void OnBegin(void) = 0;
	virtual void OnEnd(void) = 0;
	virtual bool Finished(void) = 0;

	//accessor
protected:
	BattleActor* _owner;
};



#endif//_NUMBER_H_