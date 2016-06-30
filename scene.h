//****************************************************************
//  scene�w�b�_
//  �S�̂̃V�[���Ǘ�
//  author: �������_
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
//�Ǘ��l �錾�̂�
class SceneChanger;
class Renderer;
class Input;
class Joypad;

//�V�[��
class Scene{
public:
	Scene(Renderer *master_renderer, Input *input){
		_renderer = master_renderer;
		this->_input = input;
	}
	~Scene(){}
	//�������z�֐�
	virtual void SetUp() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;
	virtual void Release() = 0;

protected:
	Renderer *_renderer;
	Input *_input;
};


#endif//_SCENE_H_