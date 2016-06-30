//****************************************************************
//  sceneヘッダ
//  全体のシーン管理
//  author: 中島将浩
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
//管理人 宣言のみ
class SceneChanger;
class Renderer;
class Input;
class Joypad;

//シーン
class Scene{
public:
	Scene(Renderer *master_renderer, Input *input){
		_renderer = master_renderer;
		this->_input = input;
	}
	~Scene(){}
	//純粋仮想関数
	virtual void SetUp() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;
	virtual void Release() = 0;

protected:
	Renderer *_renderer;
	Input *_input;
};


#endif//_SCENE_H_