//*****************************************************************************
//  選択中のキャラを指すカーソル
//  author: 中島将浩
//  update: 2015/12/27
//*****************************************************************************
#ifndef _ACTOR_CURSOR_H_
#define _ACTOR_CURSOR_H_

#include "main.h"
#include <d3dx9.h>

//*****************************************************************************
//  constant
//*****************************************************************************

//*****************************************************************************
//  class
//*****************************************************************************
class BattleActor;
class Renderer;
class ObjectEffect;
class ActorCursor{
private:
	ActorCursor(){}
public:

	ActorCursor(Renderer* renderer, BattleActor* owner);

	virtual ~ActorCursor();

	virtual void Update(void);

	void Activate(void);
	void Inactivate(void);
	bool IsActive(void);

	//accessor

protected:
	Renderer* _renderer;
	BattleActor* _owner;
	ObjectEffect* _image;
	bool _active;
};



#endif//_NUMBER_H_