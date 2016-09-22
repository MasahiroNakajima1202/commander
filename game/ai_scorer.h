//*****************************************************************************
//  ìGAIï]âøÉNÉâÉX
//  author: íÜìáè´ç_
//  update: 2016/09/23
//*****************************************************************************
#ifndef _AI_SCORER_H_
#define _AI_SCORER_H_

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
class AIScorer {
private:
	AIScorer() {}
public:

	AIScorer(BattleObjectAccessor* accessor);

	virtual ~AIScorer();

	virtual void Apply(AIState::POINT* src_array, int src_length);

	//accessor
	void SetNextScorer(AIScorer* value) { _next = value; }
	AIScorer* GetNextScorer(void) { return _next; }
protected:
	AIScorer* _next;
	BattleObjectAccessor* _accessor;

};



#endif//_NUMBER_H_