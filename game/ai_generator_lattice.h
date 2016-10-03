//*****************************************************************************
//  敵AI点列生成クラス　格子点
//  author: 中島将浩
//  update: 2016/10/03
//*****************************************************************************
#ifndef _AI_GENERATOR_LATTICE_H_
#define _AI_GENERATOR_LATTICE_H_

#include "ai_generator.h"

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
class AIGeneratorLattice : public AIGenerator{
public:

	AIGeneratorLattice(BattleObjectAccessor* accessor, BattleActor* owner, int x_num, int y_num, int z_num, float x_padding, float y_padding, float z_padding);

	virtual ~AIGeneratorLattice();

	virtual void AlignmentPoints(void);

	//accessor
	virtual AIState::POINT* GetPointTable(void) { return _point_table; }
	virtual int GetTableLength(void) { return _table_length; }
protected:

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