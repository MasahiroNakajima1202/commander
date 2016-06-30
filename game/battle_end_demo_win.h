//*****************************************************************************
//  èIóπîªíËÉNÉâÉX
//  author: íÜìáè´ç_
//  update: 2015/11/30
//*****************************************************************************
#ifndef _BATTLE_END_DEMO_WIN_H_
#define _BATTLE_END_DEMO_WIN_H_

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
class Object2D;
class BattleEndDemoWin : public BattleEndDemo{
public:

	BattleEndDemoWin(BattleObjectAccessor* accessor, Renderer* renderer);

	virtual ~BattleEndDemoWin();

	virtual void Update(void);

	virtual bool Finished(void);

	//accessor
protected:
	//test
	Object2D* _logo;
	int _frame_count;
};



#endif//_NUMBER_H_