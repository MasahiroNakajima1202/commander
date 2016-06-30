//*****************************************************************************
//  “GAI ‹ß‚­‚É‚¢‚é“z‚ğUŒ‚
//  author: ’†“‡«_
//  update: 2016/04/11
//*****************************************************************************
#include "enemy_ai_attack_neighbor.h"
#include "constant.h"
#include "battle_object_accessor.h"
#include "battle_actor.h"

#include "battle_skill_attack.h"
#include "battle_action_skill.h"
//*****************************************************************************
//  constant
//*****************************************************************************


EnemyAIAttackNeighbor::EnemyAIAttackNeighbor(BattleObjectAccessor* accessor, Renderer* renderer, BattleActor* owner):
EnemyAI(accessor, renderer, owner){
}

EnemyAIAttackNeighbor::~EnemyAIAttackNeighbor(){
	
}

void EnemyAIAttackNeighbor::Update(void){
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

	const float SEARCH_RANGE(50.0f);
	const float ATTACK_RANGE(10.0f);
	if(target_player == nullptr || min_length > SEARCH_RANGE){return;}
	
	//ˆê’èˆÈã‚È‚çŒü‚©‚¤
	if(min_length > ATTACK_RANGE){
		_owner->WalkTo(target_player->GetPosition());
	}
	//\•ª‹ß‚©‚Á‚½‚ç‚»‚¢‚Â‚Ì•ûŒü‚¢‚ÄUŒ‚
	else{
		//Œü‚«ƒ`ƒFƒbƒN
		
		if(_owner->GetSkill() == nullptr){
			_owner->SetSkill(new BattleSkillAttack(_owner, _renderer, _accessor));
			_owner->SetAction(new BattleActionSkill(_owner));
		}
	}
}
