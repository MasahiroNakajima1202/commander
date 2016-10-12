//*****************************************************************************
//  “GAI•]‰¿ƒNƒ‰ƒX
//  ‹——£ˆË‘¶
//  author: ’†“‡«_
//  update: 2016/10/12
//*****************************************************************************
#ifndef _AI_SCORER_DISTANCE_PLAYER_H_
#define _AI_SCORER_DISTANCE_PLAYER_H_

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
class AIScorerDistancePlayer : public AIScorer {
public:

	AIScorerDistancePlayer(BattleObjectAccessor* accessor);

	virtual ~AIScorerDistancePlayer();

	void SetDistance(float value) { _distance = value; }
	void SetRange(float value) { _range = value; }

protected:
	virtual float Score(AIState::POINT* point);

	//’†S‹——£
	float _distance;
	//‹——£‚©‚ç‚Ì”ÍˆÍ
	float _range;
};



#endif//_NUMBER_H_