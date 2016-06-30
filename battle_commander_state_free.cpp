//*****************************************************************************
//  戦闘指示クラス用ステートパターン 通常時
//  author: 中島将浩
//  update: 2015/12/29
//*****************************************************************************
#include "battle_commander_state_free.h"
#include "battle_commander.h"
#include "battle_object_accessor.h"
#include "battle_actor.h"
#include "actor_cursor.h"
#include "cursor3d.h"
#include "hit_sphere.h"

BattleCommanderStateFree::BattleCommanderStateFree(BattleCommander* owner, BattleObjectAccessor* accessor, Renderer* renderer):
BattleCommanderState(owner, accessor, renderer),
_pointing_actor(nullptr){
}

BattleCommanderStateFree::~BattleCommanderStateFree(){}

void BattleCommanderStateFree::Update(void){
	CheckPointingActor();
}

void BattleCommanderStateFree::StateIn(void){
	CheckPointingActor();
}

void BattleCommanderStateFree::StateOut(void){
	_pointing_actor = nullptr;
}

void BattleCommanderStateFree::MouseLeftDown(void){
	if(_pointing_actor != nullptr && _accessor != nullptr){
		//reset unless ctrl is pushed
		_accessor->InactivateAllPlayerCursor();

		//activate
		ActorCursor* cursor(_accessor->GetPlayerCursor(_pointing_actor));
		if(cursor != nullptr){
			cursor->Activate();
		}

		_owner->ChangeState(BattleCommander::STATE::DIRECTION);
	}
}

void BattleCommanderStateFree::MouseLeftUp(void){
	if(_pointing_actor == nullptr){
		_accessor->InactivateAllPlayerCursor();
	}
}

void BattleCommanderStateFree::MouseRightDown(void){
}

void BattleCommanderStateFree::MouseRightUp(void){
}

void BattleCommanderStateFree::CheckPointingActor(void){
	Cursor3D* cursor3d(_accessor->GetCursor3D());
	if(!cursor3d->GetVisible()){
		_pointing_actor = nullptr;
		return;
	}

	D3DXVECTOR3 cursor_position(cursor3d->GetPosition());
	HitSphere cursor_hit(nullptr, cursor_position, 5.0f);
	
	//敵と味方を全部辿って、当たっている奴の中で一番近いやつを指す
	_pointing_actor = nullptr;
	float min_length(1000.0f);

	int player_count(_accessor->GetPlayerCount());
	for(int i=0; i<player_count; i++){
		BattleActor* player(_accessor->GetPlayer(i));
		Hit* player_hit(player->GetCursorHit());

		bool hit(player_hit->HitCheck(&cursor_hit));
		if(hit){
			D3DXVECTOR3 player_position(player->GetPosition());
			D3DXVECTOR3 v(player_position - cursor_position);
			float length(D3DXVec3Length(&v));
			if(min_length > length){
				min_length = length;
				_pointing_actor = player;
			}
		}
	}

	int enemy_count(_accessor->GetEnemyCount());
	for(int i=0; i<enemy_count; i++){
		BattleActor* enemy(_accessor->GetEnemy(i));
		Hit* enemy_hit(enemy->GetCursorHit());

		bool hit(enemy_hit->HitCheck(&cursor_hit));
		if(hit){
			D3DXVECTOR3 enemy_position(enemy->GetPosition());
			D3DXVECTOR3 v(enemy_position - cursor_position);
			float length(D3DXVec3Length(&v));
			if(min_length > length){
				min_length = length;
				_pointing_actor = enemy;
			}
		}
	}
}