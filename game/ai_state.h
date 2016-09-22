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
class AIFilter;
class AIGenerator;
class AIScorer;
class AIState{
private:
	AIState(){}
public:

	AIState(BattleObjectAccessor* accessor, Renderer* renderer, BattleActor* owner);

	virtual ~AIState();

	virtual void Update(void);

	struct POINT {
		D3DXVECTOR3 position;
		float value;
		//D3DCOLOR debug_color;
		bool enable;

		POINT() :
			position(0.0f, 0.0f, 0.0f),
			value(0.0f),
			enable(false) {}
	};

	//accessor
	void SetGenerator(AIGenerator* value) { _generator = value; }
	void AddFilter(AIFilter* value);
	void AddScorer(AIScorer* value);
protected:
	BattleObjectAccessor* _accessor;
	BattleActor* _owner;
	Renderer* _renderer;

	D3DXVECTOR3 _target_position;

	AIGenerator* _generator;
	AIFilter* _filter_list;
	AIScorer* _scorer_list;
};

// TODO: 点列生成クラスのalignment関数の実装、評価関数クラス、カーブの作成

#endif//_NUMBER_H_