//*****************************************************************************
//  �GAI�]���N���X
//  author: �������_
//  update: 2016/09/23
//*****************************************************************************
#include "ai_scorer.h"
AIScorer::AIScorer(BattleObjectAccessor* accessor) :
	_accessor(accessor),
	_next(nullptr) {
}

AIScorer::~AIScorer() {}

void AIScorer::Apply(AIState::POINT* src_array, int src_length) {
	return;
}

