//****************************************************************
//  gameクラス
//  author: 中島将浩
//  update: 2014/3/16
//****************************************************************

//*****************************************************************************
//  include
//*****************************************************************************
#include "battle.h"
#include "fade.h"
#include "scene_factory.h"

#include "manager.h"
#include "camera.h"
#include "object2d.h"
#include "object_x.h"
#include "input.h"
#include "joypad.h"
#include "renderer.h"
#include "vertex_shader.h"
#include "pixel_shader.h"

#include "battle_object_accessor.h"
#include "judge.h"
#include "battle_commander.h"


//test
#include "battle_actor.h"
#include "battle_action_walk.h"
#include "object_billboard.h"
//*****************************************************************************
//  初期化
//*****************************************************************************
void Battle::SetUp(void){
	int i = 0;
	LPDIRECT3DDEVICE9 device = _renderer->GetDevice();


	D3DXVECTOR3 direction(0.5f, -1.0f, 0.5f);
	D3DXVec3Normalize(&direction, &direction);

	_renderer->SetLightDirection(direction);
	_renderer->SetLightDiffuse(D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f));

	_battle_object_accessor = new BattleObjectAccessor(_renderer);

	_judge = new Judge(_battle_object_accessor, _renderer);
	
	_commander = new BattleCommander(_battle_object_accessor, _renderer);

	Fade::FadeIn();
	return;
}

//*****************************************************************************
//  更新
//*****************************************************************************
void Battle::Update(void){
	int i = 0;					//loop index

	//単体で動く連中
	_input->Update();

	_renderer->Update();

	_battle_object_accessor->UpdateAll();

	//関連をもつ連中
	_commander->Update();

	_judge->Update();

	//描画されるオブジェクトの更新
	Object::UpdateAll();

	//洗い流す
	Object::Flush();

}

//*****************************************************************************
//  描画
//*****************************************************************************
void Battle::Draw(void){

	_battle_object_accessor->GetCamera()->Set();
	_renderer->Draw();

}

//*****************************************************************************
//  解放
//*****************************************************************************
void Battle::Release(void){
	int i = 0;					//loop index

	if(_commander != nullptr){
		delete _commander;
		_commander = nullptr;
	}

	if(_judge != nullptr){
		delete _judge;
		_judge = nullptr;
	}

	if(_battle_object_accessor != nullptr){
		delete _battle_object_accessor;
		_battle_object_accessor = nullptr;
	}

	Object::DestroyAll();

	Object::Flush();

}
