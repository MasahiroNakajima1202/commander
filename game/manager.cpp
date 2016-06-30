//*****************************************************************************
//  managerモジュール
//  author: 中島将浩
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
SceneFactory *Manager::_factory;//ファクトリー
Input *Manager::_input;

//*****************************************************************************
//【初期化】
//  返り値: 初期化に成功したかどうか
//  引数: なし
//*****************************************************************************
HRESULT Manager::SetUp(HINSTANCE hInstance, HWND hWnd, BOOL bWindow){
	//れんだらーの生成
	_renderer = new Renderer();
	_renderer->SetUp(hInstance, hWnd, bWindow);

	//入力インスタンス生成
	_input = new Input(hInstance, hWnd);
	_input->SetUp(hInstance, hWnd);

	//最初のシーンのファクトリーを生成
	_factory = new BattleFactory();

	//フェードの初期化
	Fade::SetUp(_renderer);

	//デバッグ表示の初期化
	Debug::SetRenderer(_renderer);
	Debug::SetUp();

	return S_OK;
}

//*****************************************************************************
//【終了】
//  返り値: なし
//  引数: なし
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

	////デバッグ表示の解放
	Debug::Release();
}

//*****************************************************************************
//【更新】
//  返り値: なし
//  引数: なし
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
//【描画】
//  返り値: なし
//  引数: なし
//*****************************************************************************
void Manager::Draw(void){
	if(_cur_scene != NULL){
		_cur_scene->Draw();
	}
}

//private func
void Manager::Change(void){
	if(_cur_scene != NULL){
		_cur_scene->Release();					//現在のシーンの破棄
		delete _cur_scene;
		_cur_scene = NULL;
	}
	_cur_scene = _factory->Make(_renderer, _input);			//シーン移し替え
	delete _factory;
	_factory = NULL;
	_cur_scene->SetUp();							//生成したシーンの初期化
}
