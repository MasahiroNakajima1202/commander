//*****************************************************************************
//  “GAIó‘ÔˆÚsƒNƒ‰ƒX ˆê’èˆÈãã‚Á‚Ä‚¢‚é
//  author: ’†“‡«_
//  update: 2016/08/24
//*****************************************************************************
#ifndef _AI_PATH_WEAKEN_H_
#define _AI_PATH_WEAKEN_H_

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
class AIState;
class AIPathWeaken : public AIPath {

public:

	AIPathWeaken(BattleObjectAccessor* accessor, Renderer* renderer, AIState* from, AIState* to, BattleActor* owner, float threshold);

	virtual ~AIPathWeaken();

	virtual void Update(void);

	virtual bool CheckToPassThrough(void);

	//accessor
protected:
	BattleActor* _owner;
	float _threthold;
};



#endif//_NUMBER_H_