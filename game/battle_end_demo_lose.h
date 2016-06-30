//*****************************************************************************
//  èIóπîªíËÉNÉâÉX
//  author: íÜìáè´ç_
//  update: 2015/11/30
//*****************************************************************************
#ifndef _BATTLE_END_DEMO_LOSE_H_
#define _BATTLE_END_DEMO_LOSE_H_

#include "main.h"
#include <d3dx9.h>

#include "battle_end_demo.h"

//*****************************************************************************
//  constant
//*****************************************************************************

//*****************************************************************************
//  class
//*****************************************************************************
class Renderer;
class BattleObjectAccessor;
class BattleEndDemoLose : public BattleEndDemo{
public:

	BattleEndDemoLose(BattleObjectAccessor* accessor, Renderer* renderer);

	virtual ~BattleEndDemoLose();

	virtual void Update(void);

	virtual bool Finished(void);

	//accessor
protected:
};



#endif//_NUMBER_H_