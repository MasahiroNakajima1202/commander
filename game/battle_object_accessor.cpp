//*****************************************************************************
//  ゲームオブジェクトの管理
//  author: 中島将浩
//  update: 2015/10/25
//*****************************************************************************
#include "battle_object_accessor.h"

#include "camera.h"
#include "model_field.h"
#include "mouse_cursor.h"
#include "cursor3d.h"
#include "cursor_director.h"
#include "attack.h"
#include "attack_accessor.h"
#include "battle_actor.h"
#include "battle_end_demo.h"
#include "damage_popup.h"
#include "object_effect.h"
#include "actor_cursor.h"
#include "battle_actor_ghost.h"
#include "camera_director.h"
#include "tile_field.h"

#include "actor_ai.h"
#include "ai_state.h"
#include "ai_path_near_player.h"

#include "gimmick.h"
#include "gimmick_ladder.h"
//*****************************************************************************
//  constant
//*****************************************************************************

//*****************************************************************************
//  class
//*****************************************************************************

BattleObjectAccessor::BattleObjectAccessor(Renderer* renderer) :
	_renderer(renderer),
	_camera(nullptr),
	_model_field(nullptr),
	_mouse_cursor(nullptr),
	_cursor3d(nullptr),
	_cursor_director(nullptr),
	_attack_accessor(nullptr),
	_end_demo(nullptr),
	_camera_director(nullptr),
	_popup(nullptr) {
	for (int i = 0; i < PLAYER_MAX; i++) {
		_player_array[i] = nullptr;
		_player_cursor_array[i] = nullptr;
		_player_ghost_array[i] = nullptr;
	}
	for (int i = 0; i < ENEMY_MAX; i++) {
		_enemy_array[i] = nullptr;
	}
	for (int i = 0; i < GIMMICK_MAX; i++) {
		_gimmick_array[i] = nullptr;
	}

	//カメラのインスタンス生成
	_camera = new Camera(_renderer);
	_camera->SetUp();
	_camera->SetEyePosition(D3DXVECTOR3(0.0f, 100.0f, -200.0f));
	_camera->SetAtPosition(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	TileField* field(new TileField(_renderer, 32, 32));
	int height_map[32][32] = {
		//							 7								15								23
		 0,  0,  0,  0,  0,  0,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  0,  0,  0,  0,  0,  0, 15, 10, 10, 10, 10, 15, //00
		 0,  0,  0,  0,  0,  0,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  0,  0,  0,  0,  0,  0, 15, 10, 10, 10, 10, 15, //01
		 0,  0,  0,  0,  0,  0,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  0,  0,  0,  0,  0,  0,  0, 15, 10, 10, 10, 10, 15, //02
		 0,  0,  0,  0,  0,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  0,  0,  0,  0,  0,  1,  1, 15, 10, 10, 10, 10, 15, //03
		 0,  0,  0,  0,  0,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  0,  0,  0,  5,  5,  5,  5,  2,  2, 15, 15, 10, 10, 15, 15, //04
		 0,  0,  0,  0,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  0,  0,  0,  0,  5,  5,  5,  4,  3,  3, 10, 10, 10, 10, 10, 10, //05
		 0,  0,  0,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  0,  0,  0,  0,  0,  5,  5,  5,  4,  3,  3, 10, 10, 10, 10, 10, 10, //06
		 1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  0,  0,  0,  0,  0,  6,  6,  6,  6,  6,  7,  8,  9, 10, 10, 10, 10, //07
		 1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  0,  0,  0,  0,  0,  6,  6,  6,  6,  6,  7,  8,  9, 10, 10, 10, 10, //08
		 2,  2,  2,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, 12, 12,  0,  0,  0,  0,  0,  6,  6,  6,  6,  6,  7,  8,  9, 10, 10, 10, 10, //09
		 3,  3,  3,  2,  1,  1,  1,  1,  1,  1,  1,  1,  1, 12, 12,  0,  0,  0,  0,  0,  6,  6,  6,  6,  6,  7,  8,  9, 10, 10, 10, 10, //10
		 4,  4,  4,  3,  2,  1,  1,  1,  1,  1,  1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  5,  5,  5,  1,  1,  1, 10, 10, 12, 12, 10, 10, //11
		 5,  5,  5,  4,  3,  2,  1,  1,  1,  1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  4,  4,  4,  1,  1,  1, 10, 10, 12, 12, 10, 10, //12
		 6,  6,  6,  5,  4,  3,  2,  1,  1,  1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  3,  3,  3,  1,  1,  1, 10, 10, 10, 10, 10, 10, //13
		 7,  7,  7,  6,  5,  4,  3,  2,  1,  1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  2,  2,  2,  1,  1,  1, 10, 10, 10, 10, 10, 10, //14
		 7,  7,  7,  6,  5,  4,  3,  2,  1,  1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  1,  1,  1,  1,  1, 10, 10, 10, 10, 10, 10, //15
		 7,  7,  7,  6,  5,  4,  4,  2,  1,  1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  1, 16, 16, 16, 16, 16, 16, //00
		 7,  7,  7,  6,  5,  4,  4,  3,  2,  1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  1, 16, 16, 16, 16, 16, 16, //01
		 6,  6,  6,  5,  4,  4,  5,  6,  6,  6,  6,  6,  6,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  1, 16, 10, 10, 10, 10, 10, //02
		 5,  5,  5,  4,  3,  3,  3,  3,  3,  6,  6,  6,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  1, 16, 10, 10, 10, 10, 10, //03
		 4,  4,  4,  3,  3,  3,  3,  2,  1,  0,  0,  0,  0,  0,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  0,  1, 16, 10, 10, 10, 10, 10, //04
		 3,  3,  3,  3,  3,  3,  2,  2,  1,  0,  0,  0,  0,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  0,  1, 16, 10, 10, 10, 10, 10, //05
		 3,  3,  3,  3,  3,  3,  2,  1,  1,  0,  0,  0,  0,  0,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  0,  1, 16, 10, 10, 10, 10, 10, //06
		 3,  3,  3,  3,  3,  3,  2,  1,  0,  0,  0,  0,  0,  0,  0,  6,  6,  6,  6,  6,  6,  6,  6,  6,  0,  1, 16, 10, 10, 10, 10, 10, //07
		 3,  3,  3,  3,  3,  2,  1,  1,  0,  0,  0,  0,  0,  0,  0,  6,  6,  6,  6,  6,  6,  6,  6,  6,  0,  1, 16, 10, 10, 10, 10, 10, //08
		 2,  2,  2,  2,  2,  1,  1,  0,  0,  0,  0,  0,  0,  0,  0,  6,  6,  6, 22, 22, 22, 22, 22, 22, 22, 22, 22, 16, 16, 16, 16, 16, //09
		 1,  1,  1,  1,  1,  1,  0,  0,  0,  0,  0,  0,  0,  0,  6,  6,  6,  6, 10, 10, 10, 10, 10, 10, 10, 22, 22, 16, 16, 16, 16, 16, //10
		 0,  0,  0,  0,  0,  0,  0,  0,  0, 12, 12, 12, 12,  6,  6,  6,  6,  6, 10, 10, 10, 10, 10, 10, 10, 22, 22, 16, 16, 16, 18, 18, //11
		 0,  0,  0,  0,  0,  0,  0,  1, 12, 12, 12, 12, 12, 12,  6,  6,  6,  6, 10, 10, 10, 10, 10, 10, 10, 22, 22, 16, 16, 16, 18, 18, //12
		 0,  0,  0,  0,  0,  0,  0, 12, 12, 12, 12, 12, 12, 12,  6,  6,  6,  6, 10, 10, 10, 10, 10, 10, 10, 22, 22, 16, 16, 16, 16, 16, //13
		 0,  0,  0,  0,  0,  0,  0, 12, 12, 12, 12, 12, 12, 12, 12,  6,  6,  6, 10, 10, 10, 10, 10, 10, 10, 22, 22, 16, 16, 16, 16, 16, //14
		 0,  0,  0,  0,  0,  0,  0, 12, 12, 12, 12, 12, 12, 12, 12,  6,  6,  6, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, //15
	};
	for (int i = 0; i < 32; i++) {
		for (int j = 0; j < 32; j++) {
			field->StackTile(j, i, height_map[31 - i][j]);
		}
	}
	field->CommitImage();

	_model_field = field;

	_mouse_cursor = new MouseCursor(_renderer);

	_cursor3d = new Cursor3D(_renderer);

	_cursor_director = new CursorDirector(_mouse_cursor, _cursor3d, _model_field, _camera);

	_attack_accessor = new AttackAccessor();
	Attack::SetAccessor(_attack_accessor);

	//初期プレイヤーデータ
	const int player_num(5);
	char* player_filename = "data/ModelNdk/seabata.ndk";
	D3DXVECTOR3 player_position[player_num] = {
		//初期メンバー
		D3DXVECTOR3(-240.0f, 0.0f, -310.0f),
		//D3DXVECTOR3(240.0f, 50.0f, -140.0f),
		D3DXVECTOR3(-230.0f, 0.0f, -290.0f),
		D3DXVECTOR3(-270.0f, 0.0f, -290.0f),
		//追い詰められてる二人
		D3DXVECTOR3(-270.0f, 0.0f, 290.0f),
		D3DXVECTOR3(-290.0f, 0.0f, 270.0f),
	};
	float player_rotation[player_num] = {
		//初期メンバー
		0.0f,
		0.0f,
		0.0f,
		//追い詰められてる二人
		D3DX_PI * 0.75f,
		D3DX_PI * 0.75f,
	};

	for (int i = 0; i < player_num; i++) {
		BattleActor::PARAMETER parameter(100, 100, 50, 5);
		_player_array[i] = new BattleActor(_renderer, parameter, player_filename);
		_player_cursor_array[i] = new ActorCursor(_renderer, _player_array[i]);
		_player_ghost_array[i] = new BattleActorGhost(_renderer, player_filename);

		D3DXVECTOR3 position(player_position[i]);
		position.y = _model_field->GetHeight(position.x, position.z);
		_player_array[i]->SetPosition(position);
		_player_array[i]->SetRotation(D3DXVECTOR3(0.0f, player_rotation[i], 0.0f));
	}

	//初期エネミーデータ
	const int enemy_num(22);
	char* enemy_filename = "data/ModelNdk/mitukuri.ndk";
	D3DXVECTOR3 enemy_position[enemy_num] = {
		//最初の斜面
		D3DXVECTOR3(-290.0f, 0.0f, -150.0f),
		D3DXVECTOR3(-270.0f, 0.0f, -210.0f),
		D3DXVECTOR3(-230.0f, 0.0f, -170.0f),
		//丘の上
		D3DXVECTOR3(-290.0f, 0.0f, -70.0f),
		D3DXVECTOR3(-290.0f, 0.0f, -10.0f),
		D3DXVECTOR3(-210.0f, 0.0f, -10.0f),
		//伏兵
		D3DXVECTOR3(-90.0f, 0.0f, -30.0f),
		D3DXVECTOR3(-90.0f, 0.0f, -15.0f),
		//攻囲中
		D3DXVECTOR3(-290.0f, 0.0f, 210.0f),
		D3DXVECTOR3(-260.0f, 0.0f, 210.0f),
		D3DXVECTOR3(-230.0f, 0.0f, 230.0f),
		D3DXVECTOR3(-210.0f, 0.0f, 260.0f),
		D3DXVECTOR3(-210.0f, 0.0f, 290.0f),
		//高台番兵
		D3DXVECTOR3(90.0f, 0.0f, 90.0f),
		D3DXVECTOR3(110.0f, 0.0f, 90.0f),
		D3DXVECTOR3(130.0f, 0.0f, 90.0f),
		//獄卒
		D3DXVECTOR3(260.0f, 0.0f, 210.0f),
		//最初の門兵
		D3DXVECTOR3(220.0f, 0.0f, -20.0f),
		D3DXVECTOR3(300.0f, 0.0f, -20.0f),
		//二番目の門兵
		D3DXVECTOR3(200.0f, 0.0f, -200.0f),
		D3DXVECTOR3(200.0f, 0.0f, -240.0f),
		D3DXVECTOR3(200.0f, 0.0f, -280.0f),
	};
	float enemy_rotation[enemy_num] = {
		//最初の斜面
		D3DX_PI * 1.0f,
		D3DX_PI * 1.0f,
		D3DX_PI * 1.0f,
		//丘の上
		D3DX_PI * 1.0f,
		D3DX_PI * 1.0f,
		D3DX_PI * 1.0f,
		//伏兵
		D3DX_PI * 0.5f,
		D3DX_PI * 0.5f,
		//攻囲中
		D3DX_PI * 0.0f,
		D3DX_PI * 1.75f,
		D3DX_PI * 1.75f,
		D3DX_PI * 1.75f,
		D3DX_PI * 1.5f,
		//高台番兵
		D3DX_PI * 1.0f,
		D3DX_PI * 1.0f,
		D3DX_PI * 1.0f,
		//獄卒
		D3DX_PI * 1.0f,
		//最初の門兵
		D3DX_PI * 0.0f,
		D3DX_PI * 0.0f,
		//二番目の門兵
		D3DX_PI * 0.5f,
		D3DX_PI * 0.5f,
		D3DX_PI * 0.5f,
	};
	for (int i = 0; i < enemy_num; i++) {
		BattleActor::PARAMETER parameter(100, 100, 50, 5);
		_enemy_array[i] = new BattleActor(_renderer, parameter, enemy_filename);

		D3DXVECTOR3 position(enemy_position[i]);
		position.y = _model_field->GetHeight(position.x, position.z);
		_enemy_array[i]->SetPosition(position);
		_enemy_array[i]->SetRotation(D3DXVECTOR3(0.0f, enemy_rotation[i], 0.0f));
	}

	//gimmick test
	_gimmick_array[0] = new GimmickLadder(_renderer, D3DXVECTOR3(-60.0f, 0.0f, 130.0f), D3DXVECTOR3(0.0f, D3DX_PI * 0.5f, 0.0f), 12);
	_gimmick_array[1] = new GimmickLadder(_renderer, D3DXVECTOR3(220.0f, 50.0f, 0.0f), D3DXVECTOR3(0.0f, D3DX_PI * 0.0f, 0.0f), 6);
	_gimmick_array[2] = new GimmickLadder(_renderer, D3DXVECTOR3(260.0f, 50.0f, 0.0f), D3DXVECTOR3(0.0f, D3DX_PI * 0.0f, 0.0f), 6);
	_gimmick_array[3] = new GimmickLadder(_renderer, D3DXVECTOR3(300.0f, 50.0f, 0.0f), D3DXVECTOR3(0.0f, D3DX_PI * 0.0f, 0.0f), 6);
	_gimmick_array[4] = new GimmickLadder(_renderer, D3DXVECTOR3(250.0f, 50.0f, -180.0f), D3DXVECTOR3(0.0f, D3DX_PI * 0.0f, 0.0f), 6);
	_gimmick_array[5] = new GimmickLadder(_renderer, D3DXVECTOR3(290.0f, 50.0f, -180.0f), D3DXVECTOR3(0.0f, D3DX_PI * 0.0f, 0.0f), 6);
	_gimmick_array[6] = new GimmickLadder(_renderer, D3DXVECTOR3(220.0f, 80.0f, -200.0f), D3DXVECTOR3(0.0f, D3DX_PI * 0.5f, 0.0f), 6);
	_gimmick_array[7] = new GimmickLadder(_renderer, D3DXVECTOR3(220.0f, 80.0f, -240.0f), D3DXVECTOR3(0.0f, D3DX_PI * 0.5f, 0.0f), 6);
	_gimmick_array[8] = new GimmickLadder(_renderer, D3DXVECTOR3(220.0f, 80.0f, -280.0f), D3DXVECTOR3(0.0f, D3DX_PI * 0.5f, 0.0f), 6);

	//ai test
	ActorAI* enemy_ai(new ActorAI(this, _renderer, _enemy_array[0]));
	AIState* ai_state(new AIState(this, _renderer, _enemy_array[0]));
	enemy_ai->AddState(ai_state);
	enemy_ai->SetCurrentState(ai_state);
	_enemy_array[0]->SetAI(enemy_ai);

	_camera_director = new CameraDirector(_player_array[0], _camera);

}

BattleObjectAccessor::~BattleObjectAccessor(){
	if(_camera_director != nullptr){
		delete _camera_director;
		_camera_director = nullptr;
	}

	if(_camera != nullptr){
		_camera->Release();
		delete _camera;
		_camera = nullptr;
	}
	
	if(_model_field != nullptr){
		delete _model_field;
		_model_field = nullptr;
	}

	if(_mouse_cursor != nullptr){
		delete _mouse_cursor;
		_mouse_cursor = nullptr;
	}

	if(_cursor3d != nullptr){
		delete _cursor3d;
		_cursor3d = nullptr;
	}

	if(_cursor_director != nullptr){
		delete _cursor_director;
		_cursor_director = nullptr;
	}

	if(_attack_accessor != nullptr){
		_attack_accessor->Clear();
		delete _attack_accessor;
		_attack_accessor = nullptr;
	}
	Attack::SetAccessor(nullptr);

	for(int i = 0; i<PLAYER_MAX; i++){
		if(_player_array[i] != nullptr){
			delete _player_array[i];
			_player_array[i] = nullptr;
		}

		if(_player_cursor_array[i] != nullptr){
			delete _player_cursor_array[i];
			_player_cursor_array[i] = nullptr;
		}

		if(_player_ghost_array[i] != nullptr){
			delete _player_ghost_array[i];
			_player_ghost_array[i] = nullptr;
		}
	}
	for(int i = 0; i<ENEMY_MAX; i++){
		if (_enemy_array[i] != nullptr) {
			delete _enemy_array[i];
			_enemy_array[i] = nullptr;
		}
	}
	for(int i = 0; i<GIMMICK_MAX; i++){
		if(_gimmick_array[i] != nullptr){
			delete _gimmick_array[i];
			_gimmick_array[i] = nullptr;
		}
	}

	if(_end_demo != nullptr){
		delete _end_demo;
		_end_demo = nullptr;
	}

	if(_popup != nullptr){
		delete _popup;
		_popup = nullptr;
	}
}

void BattleObjectAccessor::UpdateAll(void){
	_camera->Update();

	_model_field->Update();

	_mouse_cursor->Update();

	_cursor3d->Update();

	_attack_accessor->Update();
	
	for(int i = 0; i<PLAYER_MAX; i++){
		if(_player_array[i] != nullptr){
			_player_array[i]->Update();
		}

		if(_player_cursor_array[i] != nullptr){
			_player_cursor_array[i]->Update();
		}

		if(_player_ghost_array[i] != nullptr){
			_player_ghost_array[i]->Update();
		}
	}
	for(int i = 0; i<ENEMY_MAX; i++){
		if(_enemy_array[i] != nullptr){
			_enemy_array[i]->Update();
		}
	}
	for(int i = 0; i<GIMMICK_MAX; i++){
		if(_gimmick_array[i] != nullptr){
			_gimmick_array[i]->Update();
		}
	}

	if(_popup != nullptr){
		if(_popup->Finished()){
			delete _popup;
			_popup = nullptr;
		}
		else{
			_popup->Update();
		}
	}

	if(_end_demo != nullptr){
		_end_demo->Update();
	}

	//関連を持つ連中
	_cursor_director->Update();

	_camera_director->Update();

}

int BattleObjectAccessor::GetPlayerCount(void){
	int count(0);

	for(int i=0; i<PLAYER_MAX; i++){
		if(_player_array[i] != nullptr){
			count++;
		}
	}

	return count;
}
BattleActor* BattleObjectAccessor::GetPlayer(int index){
	if(index < 0 || PLAYER_MAX <= index){return nullptr;}
	int count(-1);
	BattleActor* player(nullptr);
	for(int i = 0; i<PLAYER_MAX; i++){
		if(_player_array[i] != nullptr){
			count++;
		}

		if(count == index){
			player = _player_array[i];
			break;
		}
	}

	return player;
}
int BattleObjectAccessor::GetEnemyCount(void){
	int count(0);

	for(int i=0; i<ENEMY_MAX; i++){
		if(_enemy_array[i] != nullptr){
			count++;
		}
	}

	return count;
}
BattleActor* BattleObjectAccessor::GetEnemy(int index){
	if(index < 0 || ENEMY_MAX <= index){return nullptr;}
	int count(-1);
	BattleActor* enemy(nullptr);
	for(int i = 0; i<ENEMY_MAX; i++){
		if(_enemy_array[i] != nullptr){
			count++;
		}

		if(count == index){
			enemy = _enemy_array[i];
			break;
		}
	}

	return enemy;
}

bool BattleObjectAccessor::IsPlayer(BattleActor *actor){
	if(actor == nullptr){return false;}

	bool exist(false);
	for(int i=0; i<PLAYER_MAX; i++){
		if(_player_array[i] == actor){
			exist = true;
			break;
		}
	}

	return exist;
}
bool BattleObjectAccessor::IsEnemy(BattleActor *actor){
	if(actor == nullptr){return false;}

	bool exist(false);
	for(int i=0; i<ENEMY_MAX; i++){
		if(_enemy_array[i] == actor){
			exist = true;
			break;
		}
	}

	return exist;
}

int BattleObjectAccessor::GetGimmickCount(void){
	int count(0);

	return 0;

	for(int i=0; i<GIMMICK_MAX; i++){
		if(_gimmick_array[i] != nullptr){
			count++;
		}
	}

	return count;
}
Gimmick* BattleObjectAccessor::GetGimmick(int index){
	if(index < 0 || GIMMICK_MAX <= index){return nullptr;}
	int count(-1);
	Gimmick* gimmick(nullptr);
	for(int i = 0; i<GIMMICK_MAX; i++){
		if(_gimmick_array[i] != nullptr){
			count++;
		}

		if(count == index){
			gimmick = _gimmick_array[i];
			break;
		}
	}

	return gimmick;
}

void BattleObjectAccessor::SetDamagePopup(DamagePopup* popup){
	if(popup == nullptr){return;}

	if(_popup != nullptr){
		delete _popup;
		_popup = nullptr;
	}

	_popup = popup;
}

ActorCursor* BattleObjectAccessor::GetPlayerCursor(int index){
	if(index < 0 || PLAYER_MAX <= index){return nullptr;}
	int count(-1);
	ActorCursor* cursor(nullptr);
	for(int i = 0; i<PLAYER_MAX; i++){
		if(_player_cursor_array[i] != nullptr){
			count++;
		}

		if(count == index){
			cursor = _player_cursor_array[i];
			break;
		}
	}

	return cursor;
}
ActorCursor* BattleObjectAccessor::GetPlayerCursor(BattleActor* owner){
	ActorCursor* ret(nullptr);
	for(int i = 0; i<PLAYER_MAX; i++){
		if(owner == _player_array[i]){
			ret = _player_cursor_array[i];
		}
	}

	return ret;
}

void BattleObjectAccessor::InactivateAllPlayerCursor(void){
	for(int i = 0; i<PLAYER_MAX; i++){
		if(_player_cursor_array[i] != nullptr){
			_player_cursor_array[i]->Inactivate();
		}
	}
}

BattleActorGhost* BattleObjectAccessor::GetPlayerGhost(int index){
	if(index < 0 || PLAYER_MAX <= index){return nullptr;}
	int count(-1);
	BattleActorGhost* ghost(nullptr);
	for(int i = 0; i<PLAYER_MAX; i++){
		if(_player_ghost_array[i] != nullptr){
			count++;
		}

		if(count == index){
			ghost = _player_ghost_array[i];
			break;
		}
	}

	return ghost;
}
BattleActorGhost* BattleObjectAccessor::GetPlayerGhost(BattleActor* owner){
	BattleActorGhost* ret(nullptr);
	for(int i = 0; i<PLAYER_MAX; i++){
		if(owner == _player_array[i]){
			ret = _player_ghost_array[i];
		}
	}

	return ret;
}