//*****************************************************************************
//  ギミックとキャラクター間の当たり判定クラス
//  author: 中島将浩
//  update: 2016/03/13
//*****************************************************************************
#include "hit_checker_actor_gimmick.h"
#include "battle_object_accessor.h"
#include "hit.h"
#include "battle_actor.h"
#include "gimmick.h"
//*****************************************************************************
//  constant
//*****************************************************************************


void HitCheckerkActorGimmick::Update(void){
	//hit check battle actor and attack
	int gimmick_count(_accessor->GetGimmickCount());

	int player_count(_accessor->GetPlayerCount());
	for(int i=0; i<player_count; i++){
		BattleActor* player(_accessor->GetPlayer(i));
		for(int j = 0; j<gimmick_count; j++){
			Gimmick* gimmick(_accessor->GetGimmick(j));
			
			bool hit(HitCheck(player, gimmick));

			if(hit){
				HitActor(player, gimmick);
			}
		}
	}

	int enemy_count(_accessor->GetEnemyCount());
	for(int i=0; i<enemy_count; i++){
		BattleActor* enemy(_accessor->GetEnemy(i));
		for(int j = 0; j<gimmick_count; j++){
			Gimmick* gimmick(_accessor->GetGimmick(j));

			bool hit(HitCheck(enemy, gimmick));

			if(hit){
				HitActor(enemy, gimmick);
			}
		}
	}
}

void HitCheckerkActorGimmick::HitActor(BattleActor* actor, Gimmick* gimmick){
	gimmick->ReactToActor(actor);
}

bool HitCheckerkActorGimmick::HitCheck(BattleActor* actor, Gimmick* gimmick){
	Hit* actor_hit(actor->GetHit());
	Hit* gimmick_hit(gimmick->GetHit());
	bool hit(actor_hit->HitCheck(gimmick_hit));

	return hit;
}
