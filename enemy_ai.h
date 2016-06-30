//*****************************************************************************
//  ìGAI
//  author: íÜìáè´ç_
//  update: 2016/04/11
//*****************************************************************************
#ifndef _ENEMY_AI_H_
#define _ENEMY_AI_H_

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
class EnemyAI{
private:
	EnemyAI(){}
public:

	EnemyAI(BattleObjectAccessor* accessor, Renderer* renderer, BattleActor* owner);

	virtual ~EnemyAI();

	virtual void Update(void) = 0;

	//accessor
protected:
	BattleObjectAccessor* _accessor;
	BattleActor* _owner;
	Renderer* _renderer;
};



#endif//_NUMBER_H_