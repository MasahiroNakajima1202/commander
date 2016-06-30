//*****************************************************************************
//  作戦行動指示クラス
//  author: 中島将浩
//  update: 2015/10/31
//*****************************************************************************
#ifndef _BATTLE_COMMANDER_H_
#define _BATTLE_COMMANDER_H_

#include "main.h"
#include <d3dx9.h>

//*****************************************************************************
//  constant
//*****************************************************************************

//*****************************************************************************
//  class
//*****************************************************************************
class BattleActor;
class BattleObjectAccessor;
class Renderer;
class BattleCommanderState;
class BattleCommander{
private:
	BattleCommander(){}
public:

	BattleCommander(BattleObjectAccessor* accessor, Renderer* renderer);

	virtual ~BattleCommander();

	virtual void Update(void);

	enum STATE{
		FREE = 0,
		DIRECTION,
		MAX
	};
	void ChangeState(STATE state);

	//accessor
protected:
	BattleObjectAccessor* _accessor;
	Renderer* _renderer;

	BattleCommanderState* _state[STATE::MAX];
	BattleCommanderState* _cur_state;
};



#endif//_NUMBER_H_