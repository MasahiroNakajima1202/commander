//*****************************************************************************
//  í“¬’†‚Ì‹ZƒNƒ‰ƒX@’Êí‹ßÚUŒ‚
//  author: ’†“‡«_
//  update: 2015/10/31
//*****************************************************************************
#ifndef _BATTLE_SKILL_ATTACK_H_
#define _BATTLE_SKILL_ATTACK_H_

#include "main.h"
#include <d3dx9.h>

#include "battle_skill.h"
//*****************************************************************************
//  constant
//*****************************************************************************

//*****************************************************************************
//  class
//*****************************************************************************
class BattleActor;
class Renderer;
class BattleObjectAccessor;
class BattleSkillAttack : public BattleSkill{
private:
public:

	BattleSkillAttack(BattleActor* owner, Renderer* renderer, BattleObjectAccessor* accessor);

	virtual ~BattleSkillAttack();

	virtual void Update(void);

	virtual bool Finished(void);

	//accessor
protected:
	int _frame_count;
};

#endif//_NUMBER_H_