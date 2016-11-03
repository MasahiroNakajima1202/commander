//*****************************************************************************
//  “GAI•]‰¿ƒNƒ‰ƒX
//  author: ’†“‡«_
//  update: 2016/09/23
//*****************************************************************************
#include "ai_scorer.h"
AIScorer::AIScorer(BattleObjectAccessor* accessor,BattleActor* owner) :
_accessor(accessor),
_owner(owner),
_next(nullptr){
}

AIScorer::~AIScorer() {}

void AIScorer::Apply(AIState::POINT* src_array, int src_length) {
	if (_accessor == nullptr) { return; }

	for (int i = 0; i < src_length; i++) {
		AIState::POINT* point(src_array + i);
		point->value += Score(point);
	}
}

