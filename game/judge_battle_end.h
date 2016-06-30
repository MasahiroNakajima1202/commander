//*****************************************************************************
//  èIóπîªíËÉNÉâÉX
//  author: íÜìáè´ç_
//  update: 2015/11/30
//*****************************************************************************
#ifndef _JUDGE_BATTLE_END_H_
#define _JUDGE_BATTLE_END_H_

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
class JudgeBattleEnd{
private:
	JudgeBattleEnd(){}
public:

	JudgeBattleEnd(BattleObjectAccessor* accessor);

	virtual ~JudgeBattleEnd();

	void Update(void);

	bool End(void);
	bool Win(void);
	bool Lose(void);

	//accessor
protected:
	BattleObjectAccessor* _accessor;

	bool _battle_end;
	bool _event_end;
	bool _win;
	bool _lose;
};



#endif//_NUMBER_H_