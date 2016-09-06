//*****************************************************************************
//  ìGAIì_óÒê∂ê¨Ç≠ÇÁÇ∑ÉNÉâÉX
//  author: íÜìáè´ç_
//  update: 2016/09/06
//*****************************************************************************
#include "ai_generator.h"
#include "ai_state.h"
#include "battle_actor.h"

AIGenerator::AIGenerator(BattleObjectAccessor* accessor, BattleActor* owner, int x_num, int y_num, int z_num, float x_padding, float y_padding, float z_padding) :
	_accessor(accessor),
	_owner(owner),
	X_POINT_NUM(x_num),
	Y_POINT_NUM(y_num),
	Z_POINT_NUM(z_num),
	X_PADDING(x_padding),
	Y_PADDING(y_padding),
	Z_PADDING(z_padding),
	_point_table(nullptr),
	_table_length(x_num*y_num*z_num){
	_point_table = new AIState::POINT[x_num*y_num*z_num];
}

AIGenerator::~AIGenerator() {
	if (_point_table != nullptr) {
		delete[] _point_table;
		_point_table = nullptr;
	}
}

void AIGenerator::AlignmentPoints(void) {
}
