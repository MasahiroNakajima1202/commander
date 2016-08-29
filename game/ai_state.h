//*****************************************************************************
//  敵AI
//  author: 中島将浩
//  update: 2016/04/11
//*****************************************************************************
#ifndef _ENEMY_AI_H_
#define _ENEMY_AI_H_

#include "main.h"
#include <d3dx9.h>

//*****************************************************************************
//  constant
//*****************************************************************************

//*****************************************************************************
//  class
//*****************************************************************************
class BattleActor;
class BattleObjectAccessor;
class Renderer;
class AIPath;
class AIState{
private:
	AIState():X_POINT_NUM(1),Y_POINT_NUM(1),Z_POINT_NUM(1){}
public:

	AIState(BattleObjectAccessor* accessor, Renderer* renderer, BattleActor* owner, int x_num, int y_num, int z_num = 1);

	virtual ~AIState();

	virtual void Update(void);

	//accessor
protected:
	BattleObjectAccessor* _accessor;
	BattleActor* _owner;
	Renderer* _renderer;

	struct POINT {
		D3DXVECTOR3 position;
		float value;
		//D3DCOLOR debug_color;
		bool enable;

		POINT():
		position(0.0f, 0.0f, 0.0f),
		value(0.0f),
		enable(false){}
	};
	const int X_POINT_NUM;
	const int Y_POINT_NUM;
	const int Z_POINT_NUM;
	POINT* _point_table;

	D3DXVECTOR3 _target_position;
};

// TODO: フィルタクラス、評価関数クラス、カーブの作成

#endif//_NUMBER_H_