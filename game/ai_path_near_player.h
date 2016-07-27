//*****************************************************************************
//  敵AI状態移行クラス プレイヤーが一定以上近くにいる
//  author: 中島将浩
//  update: 2016/07/28
//*****************************************************************************
#ifndef _AI_PATH_NEAR_PLAYER_H_
#define _AI_PATH_NEAR_PLAYER_H_

#include "ai_path.h"

//*****************************************************************************
//  constant
//*****************************************************************************

//*****************************************************************************
//  class
//*****************************************************************************
class BattleActor;
class BattleObjectAccessor;
class Renderer;
class EnemyAI;
class AIPathNearPlayer : public AIPath{

public:

	AIPathNearPlayer(BattleObjectAccessor* accessor, Renderer* renderer, EnemyAI* from, EnemyAI* to, BattleActor* owner, int threshold, float range = 20.0f);

	virtual ~AIPathNearPlayer();

	virtual void Update(void);

	virtual bool CheckToPassThrough(void);

	//accessor
protected:
	BattleActor* _owner;
	int _threthold;
	float _range;
};



#endif//_NUMBER_H_