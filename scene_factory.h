//****************************************************************
//  scene_factory���W���[��
//  �V�[���̃W�F�l���[�^
//  author: �������_
//  update: 2013/7/02
//****************************************************************
#ifndef _SCENE_FACTORY_H_
#define _SCENE_FACTORY_H_
//****************************************************************
//  include
//****************************************************************
#include "scene.h"							//�V�[����m�邽��
#include "battle.h"

#include "renderer.h"
class Input;

//****************************************************************
//  class definition
//****************************************************************
//class SceneChanger;						//�Ǘ��l�̑��݂����͒m���Ă���
class SceneFactory{
public:
	virtual Scene* Make(Renderer *master_renderer, Input *input) = 0;			//�p�����O��̏����p���֐�

private:
};

//�퓬�V�[���N���X�t�@�N�g���[
class BattleFactory : public SceneFactory{
public:
	Scene* Make(Renderer *master_renderer, Input *input){return new Battle(master_renderer, input);}

private:
};

//�^�C�g���N���X�t�@�N�g���[
//class TitleFactory : public SceneFactory{
//public:
//	Scene* Make(Renderer *master_renderer, Input *input){return new Title(master_renderer, input);}
//
//private:
//};
//
////���U���g�N���X�t�@�N�g���[
//class ResultFactory : public SceneFactory{
//public:
//	Scene* Make(Renderer *master_renderer, Input *input){return new Result(master_renderer, input);}
//
//private:
//};

#endif//_SCENE_FACTORY_H_