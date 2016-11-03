//*****************************************************************************
//  “GAI•]‰¿ƒNƒ‰ƒX
//  ‹——£ˆË‘¶
//  author: ’†“‡«_
//  update: 2016/11/03
//*****************************************************************************
#include "ai_scorer_near_ally.h"
#include "battle_actor.h"
#include "battle_object_accessor.h"

AIScorerNearAlly::AIScorerNearAlly(BattleObjectAccessor* accessor, BattleActor* owner) :
AIScorer(accessor, owner) {
}

AIScorerNearAlly::~AIScorerNearAlly() {
}

float AIScorerNearAlly::Score(AIState::POINT* point) {
	if (_owner == nullptr) { return 0.0f; }

	float min_length(_range);
	int ally_count(_accessor->GetPlayerCount());
	for (int i = 0; i < ally_count; i++) {
		BattleActor* ally(_accessor->GetPlayer(i));

		D3DXVECTOR3 v(point->position - ally->GetPosition());
		float sq_length(D3DXVec3Dot(&v, &v));
		if (min_length * min_length > sq_length) {
			min_length = sqrtf(sq_length);
		}
	}

	float value(max((_range - min_length) / _range, 0.0f));

	return value;
}
