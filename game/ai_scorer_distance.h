//*****************************************************************************
//  �GAI�]���N���X
//  �����ˑ�
//  author: �������_
//  update: 2016/11/03
//*****************************************************************************
#ifndef _AI_SCORER_DISTANCE_H_
#define _AI_SCORER_DISTANCE_H_

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
class AIScorerDistance : public AIScorer {
public:

	AIScorerDistance(BattleObjectAccessor* accessor, BattleActor* owner);

	virtual ~AIScorerDistance();

	void SetRange(float value) { _range = value; }

protected:
	virtual float Score(AIState::POINT* point);

	//�ő勗��
	float _range;
};



#endif//_NUMBER_H_