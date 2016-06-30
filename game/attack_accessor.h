//*****************************************************************************
//  çUåÇîªíËä«óùÉNÉâÉX
//  author: íÜìáè´ç_
//  update: 2015/10/25
//*****************************************************************************
#ifndef _ATTACK_MANAGER_H_
#define _ATTACK_MANAGER_H_

#include "main.h"

#include <d3dx9.h>

//*****************************************************************************
//  constant
//*****************************************************************************

//*****************************************************************************
//  class
//*****************************************************************************
class Attack;
class AttackAccessor{
public:

	AttackAccessor();

	virtual ~AttackAccessor();

	//kill time out attack
	void Update(void);

	int Entry(Attack* attack);
	void Leave(int index);
	void Leave(Attack* attack);
	int GetIndex(Attack* attack);

	void Clear(void);
	int GetCount(void);
	Attack* Get(int index);
	//accessor
protected:
	static const int BUFFER_MAX = 256;
	Attack* _buffer[BUFFER_MAX];
	int _count;
	
	int SearchSpace(void);
	
};



#endif//_NUMBER_H_