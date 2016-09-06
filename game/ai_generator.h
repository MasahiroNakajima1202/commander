//*****************************************************************************
//  ìGAIì_óÒê∂ê¨Ç≠ÇÁÇ∑ÉNÉâÉX
//  author: íÜìáè´ç_
//  update: 2016/09/06
//*****************************************************************************
#ifndef _AI_GENERATOR_H_
#define _AI_GENERATOR_H_

#include "main.h"
#include <d3dx9.h>

#include "ai_state.h"

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
class AIGenerator {
private:
	AIGenerator() :X_POINT_NUM(1), Y_POINT_NUM(1), Z_POINT_NUM(1), X_PADDING(1.0f), Y_PADDING(1.0f), Z_PADDING(1.0f) {}
public:

	AIGenerator(BattleObjectAccessor* accessor, BattleActor* owner, int x_num, int y_num, int z_num, float x_padding, float y_padding, float z_padding);

	virtual ~AIGenerator();

	virtual void AlignmentPoints(void);

	//accessor
	AIState::POINT* GetPointTable(void) { return _point_table; }
	int GetTableLength(void) { return _table_length; }
protected:
	BattleObjectAccessor* _accessor;
	BattleActor* _owner;

	const int X_POINT_NUM;
	const int Y_POINT_NUM;
	const int Z_POINT_NUM;
	const float X_PADDING;
	const float Y_PADDING;
	const float Z_PADDING;
	AIState::POINT* _point_table;
	int _table_length;
};



#endif//_NUMBER_H_