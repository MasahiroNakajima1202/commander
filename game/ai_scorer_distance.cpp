//*****************************************************************************
//  “GAI•]‰¿ƒNƒ‰ƒX
//  ‹——£ˆË‘¶
//  author: ’†“‡«_
//  update: 2016/11/03
//*****************************************************************************
#include "ai_scorer_distance.h"
#include "battle_actor.h"

AIScorerDistance::AIScorerDistance(BattleObjectAccessor* accessor, BattleActor* owner):
AIScorer(accessor, owner){
}

AIScorerDistance::~AIScorerDistance() {
}

float AIScorerDistance::Score(AIState::POINT* point) {
	if (_owner == nullptr) { return 0.0f; }

	D3DXVECTOR3 v(_owner->GetPosition() - point->position);
	float d(D3DXVec3Length(&v));

	float value(max((_range - d) / _range, 0.0f));

	return value;
}
