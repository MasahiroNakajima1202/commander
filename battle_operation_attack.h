//*****************************************************************************
//  ìís“®ƒNƒ‰ƒX ’ÊíUŒ‚‚ğ‘Šè‚ª“|‚ê‚é‚Ü‚Å‘±‚¯‚é
//  author: ’†“‡«_
//  update: 2015/10/31
//*****************************************************************************
#ifndef _BATTLE_OPERATION_ATTACK_H_
#define _BATTLE_OPERATION_ATTACK_H_

#include "main.h"
#include <d3dx9.h>

#include "battle_operation.h"

//*****************************************************************************
//  constant
//*****************************************************************************

//*****************************************************************************
//  class
//*****************************************************************************
class BattleActor;
class BattleObjectAccessor;
class BattleOperationAttack : public BattleOperation{
public:

	BattleOperationAttack(BattleActor* owner, BattleObjectAccessor* accessor, Renderer* renderer, BattleActor* target);

	virtual ~BattleOperationAttack();

	virtual void Update(void);

	virtual bool Finished(void);

	//accessor
protected:
	BattleActor* _target;
};



#endif//_NUMBER_H_