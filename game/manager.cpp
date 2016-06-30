//*****************************************************************************
//  manager���W���[��
//  author: �������_
//  update: 2014/05/07
//*****************************************************************************
#include "manager.h"
#include "renderer.h"
#include "scene.h"
#include "scene_factory.h"
#include "fade.h"
#include "input.h"
#include "joypad.h"
#include "debug.h"

Renderer *Manager::_renderer;
Scene *Manager::_cur_scene;
SceneFactory *Manager::_factory;//�t�@�N�g���[
Input *Manager::_input;

//*****************************************************************************
//�y�������z
//  �Ԃ�l: �������ɐ����������ǂ���
//  ����: �Ȃ�
//*****************************************************************************
HRESULT Manager::SetUp(HINSTANCE hInstance, HWND hWnd, BOOL bWindow){
	//��񂾂�[�̐���
	_renderer = new Renderer();
	_renderer->SetUp(hInstance, hWnd, bWindow);

	//���̓C���X�^���X����
	_input = new Input(hInstance, hWnd);
	_input->SetUp(hInstance, hWnd);

	//�ŏ��̃V�[���̃t�@�N�g���[�𐶐�
	_factory = new BattleFactory();

	//�t�F�[�h�̏�����
	Fade::SetUp(_renderer);

	//�f�o�b�O�\���̏�����
	Debug::SetRenderer(_renderer);
	Debug::SetUp();

	return S_OK;
}

//*****************************************************************************
//�y�I���z
//  �Ԃ�l: �Ȃ�
//  ����: �Ȃ�
//*****************************************************************************
void Manager::Release(void){
	if(_cur_scene != NULL){
		_cur_scene->Release();
		delete _cur_scene;
		_cur_scene = NULL;
	}
	if(_factory != NULL){
		delete _factory;
		_factory = NULL;
	}

	if(_renderer != NULL){
		_renderer->Release();
		delete _renderer;
		_renderer = NULL;
	}

	if(_input != NULL){
		_input->Release();
		delete _input;
		_input = NULL;
	}


	Fade::Release();

	////�f�o�b�O�\���̉��
	Debug::Release();
}

//*****************************************************************************
//�y�X�V�z
//  �Ԃ�l: �Ȃ�
//  ����: �Ȃ�
//*****************************************************************************
void Manager::Update(void){
	if(_factory != NULL && Fade::IsBlackOut()){
		Change();
	}
	if(_cur_scene != NULL){
		_cur_scene->Update();
	}

	if(_renderer != NULL){
		_renderer->Update();
	}

	Fade::Update();
}

//*****************************************************************************
//�y�`��z
//  �Ԃ�l: �Ȃ�
//  ����: �Ȃ�
//*****************************************************************************
void Manager::Draw(void){
	if(_cur_scene != NULL){
		_cur_scene->Draw();
	}
}

//private func
void Manager::Change(void){
	if(_cur_scene != NULL){
		_cur_scene->Release();					//���݂̃V�[���̔j��
		delete _cur_scene;
		_cur_scene = NULL;
	}
	_cur_scene = _factory->Make(_renderer, _input);			//�V�[���ڂ��ւ�
	delete _factory;
	_factory = NULL;
	_cur_scene->SetUp();							//���������V�[���̏�����
}
