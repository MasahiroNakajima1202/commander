//*****************************************************************************
//  攻撃判定とキャラクター間の当たり判定クラス
//  author: 中島将浩
//  update: 2015/10/31
//*****************************************************************************
#include "hit_checker_actor_field.h"

#include "battle_object_accessor.h"
#include "battle_actor.h"
#include "model_field.h"

void HitCheckerActorField::Update(void){
	ModelField* field(_accessor->GetModelField());

	int player_count(_accessor->GetPlayerCount());
	for(int i=0; i<player_count; i++){
		BattleActor* player(_accessor->GetPlayer(i));

		D3DXVECTOR3 position(player->GetPosition());
		position.y = max(field->GetHeight(position.x, position.z), position.y);
		player->SetPosition(position);
	}

	int enemy_count(_accessor->GetEnemyCount());
	for(int i=0; i<enemy_count; i++){
		BattleActor* enemy(_accessor->GetEnemy(i));

		D3DXVECTOR3 position(enemy->GetPosition());
		position.y = max(field->GetHeight(position.x, position.z), position.y);
		enemy->SetPosition(position);
	}
}

