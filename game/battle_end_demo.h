//*****************************************************************************
//  èIóπîªíËÉNÉâÉX
//  author: íÜìáè´ç_
//  update: 2015/11/30
//*****************************************************************************
#ifndef _BATTLE_END_DEMO_H_
#define _BATTLE_END_DEMO_H_

#include "main.h"
#include <d3dx9.h>

//*****************************************************************************
//  constant
//*****************************************************************************

//*****************************************************************************
//  class
//*****************************************************************************
class Renderer;
class BattleObjectAccessor;
class BattleEndDemo{
private:
	BattleEndDemo(){}
public:

	BattleEndDemo(BattleObjectAccessor* accessor, Renderer* renderer);

	virtual ~BattleEndDemo();

	virtual void Update(void) = 0;

	virtual bool Finished(void) = 0;

	//accessor
protected:
	BattleObjectAccessor* _accessor;
	Renderer* _renderer;
};



#endif//_NUMBER_H_