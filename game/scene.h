//****************************************************************
//  scenewb_
//  SΜΜV[Η
//  author: «_
//  update: 2013/6/10
//****************************************************************

#ifndef _SCENE_H_
#define _SCENE_H_

//*****************************************************************************
//  include
//*****************************************************************************
#include "main.h"

//*****************************************************************************
//  class definition
//*****************************************************************************
//Ηl ιΎΜέ
class SceneChanger;
class Renderer;
class Input;
class Joypad;

//V[
class Scene{
public:
	Scene(Renderer *master_renderer, Input *input){
		_renderer = master_renderer;
		this->_input = input;
	}
	~Scene(){}
	//ΌzΦ
	virtual void SetUp() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;
	virtual void Release() = 0;

protected:
	Renderer *_renderer;
	Input *_input;
};


#endif//_SCENE_H_