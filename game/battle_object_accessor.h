//*****************************************************************************
//  ゲームオブジェクトの管理
//  author: 中島将浩
//  update: 2015/10/25
//*****************************************************************************
#ifndef _BATTLE_OBJECT_ACCESSOR_H_
#define _BATTLE_OBJECT_ACCESSOR_H_

#include "main.h"
#include "constant.h"
#include <d3dx9.h>

//*****************************************************************************
//  constant
//*****************************************************************************

//*****************************************************************************
//  class
//*****************************************************************************
class Renderer;
class Camera;
class ModelField;
class MouseCursor;
class Cursor3D;
class CursorDirector;
class BattleActor;
class BattleAction;
class AttackAccessor;
class DamagePopup;
class BattleEndDemo;
class ObjectEffect;
class ActorCursor;
class BattleActorGhost;
class CameraDirector;
class Gimmick;
class AIState;
class BattleObjectAccessor{
public:

	BattleObjectAccessor(Renderer* renderer);

	virtual ~BattleObjectAccessor();

	void UpdateAll(void);

	int GetPlayerCount(void);
	BattleActor* GetPlayer(int index);
	int GetEnemyCount(void);
	BattleActor* GetEnemy(int index);
	bool IsPlayer(BattleActor *actor);
	bool IsEnemy(BattleActor *actor);

	int GetGimmickCount(void);
	Gimmick* GetGimmick(int index);

	void InactivateAllPlayerCursor(void);

	//accessor
	Camera* GetCamera(void){return _camera;}
	ModelField* GetModelField(void){return _model_field;}
	MouseCursor* GetMouseCursor(void){return _mouse_cursor;}
	Cursor3D* GetCursor3D(void){return _cursor3d;}
	CursorDirector* GetCursorDirector(void){return _cursor_director;}
	AttackAccessor* GetAttackAccessor(void){return _attack_accessor;}
	void SetDamagePopup(DamagePopup* popup);
	void SetEndDemo(BattleEndDemo* demo){_end_demo = demo;}
	BattleEndDemo* GetEndDemo(void){return _end_demo;}
	ActorCursor* GetPlayerCursor(int index);
	ActorCursor* GetPlayerCursor(BattleActor* owner);
	BattleActorGhost* GetPlayerGhost(int index);
	BattleActorGhost* GetPlayerGhost(BattleActor* owner);
protected:
	Renderer* _renderer;
	Camera *_camera;

	ModelField* _model_field;
	MouseCursor* _mouse_cursor;
	Cursor3D* _cursor3d;
	CursorDirector* _cursor_director;
	AttackAccessor* _attack_accessor;

	BattleActor* _player_array[PLAYER_MAX];
	BattleActor* _enemy_array[ENEMY_MAX];
	AIState* _enemy_ai_array[ENEMY_MAX];

	ActorCursor* _player_cursor_array[PLAYER_MAX];
	BattleActorGhost* _player_ghost_array[PLAYER_MAX];

	BattleEndDemo* _end_demo;
	CameraDirector* _camera_director;

	Gimmick* _gimmick_array[GIMMICK_MAX];
	//test
	DamagePopup* _popup;
};

#endif//_NUMBER_H_