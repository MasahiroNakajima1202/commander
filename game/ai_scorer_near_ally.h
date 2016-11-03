//*****************************************************************************
//  ìGAIï]âøÉNÉâÉX
//  ãóó£àÀë∂
//  author: íÜìáè´ç_
//  update: 2016/10/12
//*****************************************************************************
#ifndef _AI_SCORER_NEAR_ALLY_H_
#define _AI_SCORER_NEAR_ALLY_H_

#include "main.h"
#include <d3dx9.h>

#include "ai_scorer.h"

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
class AIScorerNearAlly : public AIScorer {
public:

	AIScorerNearAlly(BattleObjectAccessor* accessor, BattleActor* owner);

	virtual ~AIScorerNearAlly();

	void SetRange(float value) { _range = value; }

protected:
	virtual float Score(AIState::POINT* point);

	//ç≈ëÂãóó£
	float _range;
};



#endif//_NUMBER_H_