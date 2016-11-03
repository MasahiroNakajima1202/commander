//*****************************************************************************
//  “GAI•]‰¿ƒNƒ‰ƒX
//  ‹——£ˆË‘¶
//  author: ’†“‡«_
//  update: 2016/10/12
//*****************************************************************************
#include "ai_scorer_distance_player.h"

#include "battle_object_accessor.h"
#include "battle_actor.h"
//*****************************************************************************
//  constant
//*****************************************************************************
AIScorerDistancePlayer::AIScorerDistancePlayer(BattleObjectAccessor* accessor, BattleActor* owner):
AIScorer(accessor, owner),
_distance(1.0f),
_range(1.0f){
}

AIScorerDistancePlayer::~AIScorerDistancePlayer() {
}

float AIScorerDistancePlayer::Score(AIState::POINT* point) {
	if (point == nullptr) { return 0.0f; }

	D3DXVECTOR3 position(point->position);

	if (_accessor->GetPlayerCount() == 0) { return 0.0f; }
	BattleActor* player(_accessor->GetPlayer(0));
	D3DXVECTOR3 player_position(player->GetPosition());

	if (_range == 0.0f) { return 0.0f; }
	D3DXVECTOR3 horizontal(player_position - position);
	horizontal.y = 0;
	float d(D3DXVec3Length(&horizontal));
	float score(fabsf(d - _distance) / _range);
	score = 1.0f - max(0.0f, min(1.0f, score));

	return score;
}
