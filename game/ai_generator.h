//*****************************************************************************
//  GAI_ñ¶¬­ç·NX
//  author: «_
//  update: 2016/09/06
//*****************************************************************************
#ifndef _AI_GENERATOR_H_
#define _AI_GENERATOR_H_

#include "main.h"
#include <d3dx9.h>

#include "ai_state.h"

//*****************************************************************************
//  constant
//*****************************************************************************

//*****************************************************************************
//  class
//*****************************************************************************
class BattleActor;
class BattleObjectAccessor;
class Renderer;
class AIState;
class AIGenerator {
private:
	AIGenerator(){}
public:

	AIGenerator(BattleObjectAccessor* accessor, BattleActor* owner);

	virtual ~AIGenerator();

	virtual void AlignmentPoints(void) = 0;

	//accessor
	virtual AIState::POINT* GetPointTable(void) = 0;
	virtual int GetTableLength(void) = 0;

protected:
	BattleObjectAccessor* _accessor;
	BattleActor* _owner;
};



#endif//_NUMBER_H_