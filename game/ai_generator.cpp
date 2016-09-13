//*****************************************************************************
//  “GAI“_—ñ¶¬‚­‚ç‚·ƒNƒ‰ƒX
//  author: ’†“‡«_
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
	if (_point_table == nullptr) { return; }
	if (_owner == nullptr) { return; }

	//initialize position
	D3DXVECTOR3 init_position(_owner->GetPosition());
	init_position.x -= (float)(X_POINT_NUM - 1) * 0.5f * X_PADDING;
	init_position.y -= (float)(Y_POINT_NUM - 1) * 0.5f * Y_PADDING;
	init_position.z -= (float)(Z_POINT_NUM - 1) * 0.5f * Z_PADDING;
	D3DXVECTOR3 position(init_position);

	for (int k = 0; k < Z_POINT_NUM; k++){
		position.y = init_position.y;

		for (int j = 0; j < Y_POINT_NUM; j++){
			position.x = init_position.x;
			
			for (int i = 0; i < X_POINT_NUM; i++){
				int index(k * X_POINT_NUM * Y_POINT_NUM + j * X_POINT_NUM + i);
				_point_table[index].position = position;
				position.x += X_PADDING;
			}

			position.y += Y_PADDING;
		}

		position.z += Z_PADDING;
	}
}
