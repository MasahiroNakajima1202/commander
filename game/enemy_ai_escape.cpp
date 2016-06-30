//*****************************************************************************
//  “GAI “¦–S
//  author: ’†“‡«_
//  update: 2016/06/30
//*****************************************************************************
#include "enemy_ai_escape.h"
#include "constant.h"
#include "battle_object_accessor.h"
#include "battle_actor.h"

//*****************************************************************************
//  constant
//*****************************************************************************


EnemyAIEscape::EnemyAIEscape(BattleObjectAccessor* accessor, Renderer* renderer, BattleActor* owner):
EnemyAI(accessor, renderer, owner){
}

EnemyAIEscape::~EnemyAIEscape(){
	
}

void EnemyAIEscape::Update(void){
	if(_accessor == nullptr){return;}
	if(_owner == nullptr){return;}

	//ˆê”Ô‹ß‚¢ƒ^[ƒQƒbƒg‚Ìõ“G
	float min_length(1000000.0f);
	BattleActor* target_player(nullptr);
	for(int i = 0; i<PLAYER_MAX; i++){
		BattleActor* player(_accessor->GetPlayer(i));
		if(player == nullptr){continue;}

		D3DXVECTOR3 player_position(player->GetPosition());
		D3DXVECTOR3 enemy_position(_owner->GetPosition());
		D3DXVECTOR3 enemy_to_player(player_position - enemy_position);
		D3DXVECTOR3 h_enemy_to_player(enemy_to_player);
		h_enemy_to_player.y = 0.0f;

		float h_sq_length(D3DXVec3LengthSq(&h_enemy_to_player));
		if(h_sq_length < min_length){
			min_length = h_sq_length;
			target_player = player;
		}
	}

	min_length = sqrt(min_length);

	const float SEARCH_RANGE(200.0f);
	if(target_player == nullptr){return;}
	
	//\•ª‹ß‚©‚Á‚½‚ç“¦‚°‚é
	if(min_length < SEARCH_RANGE){
		D3DXVECTOR3 direction(_owner->GetPosition() - target_player->GetPosition());
		if(D3DXVec3LengthSq(&direction) > 0.0f){
			D3DXVec3Normalize(&direction, &direction);
		}
		else{
			direction = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
		}

		float length(10.0f);
		_owner->WalkTo(_owner->GetPosition() + direction * length);

		//Œü‚«‡‚í‚¹
	}


}
