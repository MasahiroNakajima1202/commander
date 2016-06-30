//*****************************************************************************
//  戦闘指示クラス用ステートパターン 通常時
//  author: 中島将浩
//  update: 2015/12/29
//*****************************************************************************
#include "battle_commander_state_direction.h"
#include "battle_commander.h"
#include "battle_object_accessor.h"
#include "battle_actor.h"
#include "actor_cursor.h"
#include "battle_actor_ghost.h"
#include "cursor3d.h"
#include "hit_sphere.h"

#include "battle_operation_attack.h"
#include "battle_action_walk.h"
#include "guide_arrow.h"

BattleCommanderStateDirection::BattleCommanderStateDirection(BattleCommander* owner, BattleObjectAccessor* accessor, Renderer* renderer):
BattleCommanderState(owner, accessor, renderer),
_pointing_actor(nullptr){
	for(int i=0; i<GUIDE_ARROW_MAX; i++){
		_guide_arrow[i] = nullptr;
	}

	for (int i = 0; i<GUIDE_ARROW_MAX; i++){
		_guide_arrow[i] = new GuideArrow(renderer);
		_guide_arrow[i]->SetVisible(false);
	}
}

BattleCommanderStateDirection::~BattleCommanderStateDirection(){
	for(int i=0; i<GUIDE_ARROW_MAX; i++){
		if(_guide_arrow[i] != nullptr){
			delete _guide_arrow[i];
			_guide_arrow[i] = nullptr;
		}
	}
}

void BattleCommanderStateDirection::Update(void){
	if(_accessor == nullptr){return;}
	CheckPointingActor();

	//ghost
	if(_pointing_actor == nullptr){
		SetGhostAsMovement();
	}
	else if(_accessor->IsEnemy(_pointing_actor)){
		SetGhostAsAttack();
	}
	else if (_accessor->IsPlayer(_pointing_actor)){//仮処理　本当は、指揮下に入る指示
		SetGhostAsMovement();
	}

	//guide arrow
	SetGuideArrowToGhost();
	
}

void BattleCommanderStateDirection::StateIn(void){
	CheckPointingActor();
}

void BattleCommanderStateDirection::StateOut(void){
	_pointing_actor = nullptr;

	//make all ghost invisible
	int player_count(_accessor->GetPlayerCount());
	for (int i = 0; i<player_count; i++){
		BattleActorGhost* ghost(_accessor->GetPlayerGhost(i));
		if (ghost == nullptr){ continue; }
		ghost->SetVisible(false);
	}
}

void BattleCommanderStateDirection::MouseLeftDown(void){
}

void BattleCommanderStateDirection::MouseLeftUp(void){
	if(_owner == nullptr){return;}
	if(_accessor == nullptr){
		_owner->ChangeState(BattleCommander::STATE::FREE);
		return;
	}

	bool attack_order(_pointing_actor != nullptr && _accessor->IsEnemy(_pointing_actor));
	bool move_order(_pointing_actor == nullptr || !_accessor->IsEnemy(_pointing_actor));

	if(attack_order){
		
		//attack order, for all selected player
		int player_count(_accessor->GetPlayerCount());
		for(int i = 0; i<player_count; i++){
			BattleActor* player(_accessor->GetPlayer(i));
			ActorCursor* cursor(_accessor->GetPlayerCursor(player));
			if(cursor != nullptr && cursor->IsActive()){
				player->ClearAction();
				player->SetOperation(new BattleOperationAttack(player, _accessor, _renderer, _pointing_actor));
			}
		}

	}
	else if(move_order){

		//move order, for all selected player
		int player_count(_accessor->GetPlayerCount());
		for(int i = 0; i<player_count; i++){
			BattleActor* player(_accessor->GetPlayer(i));
			ActorCursor* cursor(_accessor->GetPlayerCursor(player));
			if(cursor != nullptr && cursor->IsActive()){
				Cursor3D* cursor3d(_accessor->GetCursor3D());
				if(cursor3d != nullptr){
					D3DXVECTOR3 destination(cursor3d->GetPosition());
					player->SetOperation(nullptr);
					player->ClearAction();
					player->SetAction(new BattleActionWalk(player, destination));
				}
			}
		}
		
	}

	for(int i=0; i<GUIDE_ARROW_MAX; i++){
		if(_guide_arrow[i] == nullptr){continue;}
		_guide_arrow[i]->SetVisible(false);
	}

	_owner->ChangeState(BattleCommander::STATE::FREE);
}

void BattleCommanderStateDirection::MouseRightDown(void){
}

void BattleCommanderStateDirection::MouseRightUp(void){
}

void BattleCommanderStateDirection::CheckPointingActor(void){
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

void BattleCommanderStateDirection::SetGhostAsMovement(void){
	int player_count(_accessor->GetPlayerCount());
	for(int i=0; i<player_count; i++){
		ActorCursor* cursor(_accessor->GetPlayerCursor(i));
		BattleActorGhost* ghost(_accessor->GetPlayerGhost(i));
		BattleActor* player(_accessor->GetPlayer(i));
		if(ghost == nullptr || player == nullptr){continue;}
		if(cursor == nullptr || !cursor->IsActive()){
			ghost->SetVisible(false);
			continue;
		}

		//update position
		D3DXVECTOR3 position(0.0f, 0.0f, 0.0f);
		Cursor3D* cursor3d(_accessor->GetCursor3D());
		if(cursor3d != nullptr){
			position = cursor3d->GetPosition();
		}
		ghost->SetPosition(position);

		//update rotation
		D3DXVECTOR3 player_position(0.0f, 0.0f, 0.0f);
		if(player != nullptr){
			player_position = player->GetPosition();
		}
		D3DXVECTOR3 direction(position - player_position);
		if(D3DXVec3Dot(&direction, &direction) > 0.0f){
			D3DXVec3Normalize(&direction, &direction);
		}
		D3DXVECTOR3 rotation(0.0f, 0.0f, 0.0f);
		rotation.y = atan2(direction.x, direction.z);
		ghost->SetRotation(rotation);

		//play animation

		ghost->SetVisible(true);
	}
}
void BattleCommanderStateDirection::SetGhostAsAttack(void){}

void BattleCommanderStateDirection::SetGuideArrowToGhost(void){
	if(_accessor == nullptr){return;}
	int arrow_index(0);
	for(int i=0; i<GUIDE_ARROW_MAX; i++){
		if(_guide_arrow[i] == nullptr){continue;}
		_guide_arrow[i]->SetVisible(false);
	}

	int player_count(_accessor->GetPlayerCount());
	for(int i=0; i<player_count; i++){
		BattleActor* player(_accessor->GetPlayer(i));
		BattleActorGhost* ghost(_accessor->GetPlayerGhost(player));
		ActorCursor* cursor(_accessor->GetPlayerCursor(i));
		if(player == nullptr || ghost == nullptr || cursor == nullptr){continue;}
		if(!cursor->IsActive()){continue;}

		while(arrow_index < GUIDE_ARROW_MAX && _guide_arrow[arrow_index] == nullptr){
			arrow_index++;
			continue;
		}
		if(arrow_index == GUIDE_ARROW_MAX){break;}
		GuideArrow* arrow(_guide_arrow[arrow_index]);

		D3DXVECTOR3 begin(player->GetPosition());
		D3DXVECTOR3 end(ghost->GetPosition());

		arrow->SetBeginPosition(begin);
		arrow->SetEndPosition(end);
		arrow->SetVisible(true);
		arrow->Update();
	}
}
