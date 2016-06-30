//*****************************************************************************
//  戦闘指示クラス用ステートパターン プレイヤーへの指示出し
//  author: 中島将浩
//  update: 2015/12/29
//*****************************************************************************
#ifndef _BATTLE_COMMANDER_STATE_DIRECTION_H_
#define _BATTLE_COMMANDER_STATE_DIRECTION_H_

#include "main.h"
#include <d3dx9.h>
#include "constant.h"

#include "battle_commander_state.h"

//*****************************************************************************
//  constant
//*****************************************************************************

//*****************************************************************************
//  class
//*****************************************************************************
class BattleActor;
class GuideArrow;
class BattleCommanderStateDirection : public BattleCommanderState{
public:

	BattleCommanderStateDirection(BattleCommander* owner, BattleObjectAccessor* accessor, Renderer* renderer);

	virtual ~BattleCommanderStateDirection();

	virtual void Update(void);

	virtual void StateIn(void);

	virtual void StateOut(void);

	virtual void MouseLeftDown(void);

	virtual void MouseLeftUp(void);

	virtual void MouseRightDown(void);

	virtual void MouseRightUp(void);

protected:
	BattleActor* _pointing_actor;
	static const int GUIDE_ARROW_MAX = 32;
	GuideArrow* _guide_arrow[GUIDE_ARROW_MAX];

	void CheckPointingActor(void);
	void SetGhostAsMovement(void);//移動指令を示すghost表示
	void SetGhostAsAttack(void);//攻撃指令を示すghost表示

	void SetGuideArrowToGhost(void);//guide arrowをghostに向けて表示させる
};



#endif//_NUMBER_H_