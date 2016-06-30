//*****************************************************************************
//  戦闘指示クラス用ステートパターン 通常時
//  author: 中島将浩
//  update: 2015/12/29
//*****************************************************************************
#ifndef _BATTLE_COMMANDER_STATE_FREE_H_
#define _BATTLE_COMMANDER_STATE_FREE_H_

#include "main.h"
#include <d3dx9.h>

#include "battle_commander_state.h"

//*****************************************************************************
//  constant
//*****************************************************************************

//*****************************************************************************
//  class
//*****************************************************************************
class BattleActor;
class BattleCommanderStateFree : public BattleCommanderState{
public:

	BattleCommanderStateFree(BattleCommander* owner, BattleObjectAccessor* accessor, Renderer* renderer);

	virtual ~BattleCommanderStateFree();

	virtual void Update(void);

	virtual void StateIn(void);

	virtual void StateOut(void);

	virtual void MouseLeftDown(void);

	virtual void MouseLeftUp(void);

	virtual void MouseRightDown(void);

	virtual void MouseRightUp(void);

protected:
	BattleActor* _pointing_actor;

	void CheckPointingActor(void);

};



#endif//_NUMBER_H_