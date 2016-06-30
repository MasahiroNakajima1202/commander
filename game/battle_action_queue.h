//*****************************************************************************
//  çsìÆó\ñÒ
//  author: íÜìáè´ç_
//  update: 2015/10/25
//*****************************************************************************
#ifndef _BATTLE_ACTION_QUEUE_H_
#define _BATTLE_ACTION_QUEUE_H_

#include "main.h"

#include <d3dx9.h>

//*****************************************************************************
//  constant
//*****************************************************************************

//*****************************************************************************
//  class
//*****************************************************************************
class BattleAction;
class BattleActionQueue{
public:

	BattleActionQueue();

	virtual ~BattleActionQueue();

	void Enqueue(BattleAction* value);
	BattleAction* Dequeue(void);
	bool IsEmpty(void);
	void Clear(void);

	//accessor
protected:
	static const int BUFFER_MAX = 64;

	int _read_cursor;
	int _write_cursor;
	BattleAction* _buffer[BUFFER_MAX];
};



#endif//_NUMBER_H_