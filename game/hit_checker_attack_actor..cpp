//*****************************************************************************
//  攻撃判定とキャラクター間の当たり判定クラス
//  author: 中島将浩
//  update: 2015/10/31
//*****************************************************************************
#include "hit_checker_attack_actor.h"

#include "battle_object_accessor.h"
#include "battle_actor.h"
#include "attack.h"
#include "attack_sphere.h"
#include "attack_accessor.h"
#include "hit.h"
#include "hit_sphere.h"
#include "damage_popup.h"
#include "damage_calculator.h"

void HitCheckerAttackActor::Update(void){
	//hit check battle actor and attack
	AttackAccessor* attack_accessor(_accessor->GetAttackAccessor());
	int attack_count(attack_accessor->GetCount());

	int player_count(_accessor->GetPlayerCount());
	for(int i=0; i<player_count; i++){
		BattleActor* player(_accessor->GetPlayer(i));
		for(int j = 0; j<attack_count; j++){
			Attack* attack(attack_accessor->Get(j));
			//scope check
			if(!attack->IsScopingPlayer()){
				continue;
			}

			bool hit(HitCheck(player, attack));

			if(hit){
				HitActor(player, attack);
			}
		}
	}

	int enemy_count(_accessor->GetEnemyCount());
	for(int i=0; i<enemy_count; i++){
		BattleActor* enemy(_accessor->GetEnemy(i));
		for(int j = 0; j<attack_count; j++){
			Attack* attack(attack_accessor->Get(j));
			//scope check
			if(!attack->IsScopingEnemy()){
				continue;
			}

			bool hit(HitCheck(enemy, attack));

			if(hit){
				HitActor(enemy, attack);
			}
		}
	}
}


void HitCheckerAttackActor::HitActor(BattleActor* actor, Attack* attack){
	//当たった弾のIDを設定
	int attack_id(attack->GetId());
	actor->SetRejection(attack_id);
	
	//ダメージ計算
	DamageCalculator calc(_accessor, attack, actor);
	int damage(calc.GetDamage());
	bool valid(calc.IsValid());
	if(valid){
		//ダメージを与える
		actor->Damage(damage);

		//ダメージの表示
		float radius(20.0f);
		DamagePopup* popup(new DamagePopup(_renderer, damage, actor, radius));
		_accessor->SetDamagePopup(popup);

		//わかりやすくするために浮かせています そのうち消します
		D3DXVECTOR3 accel(actor->GetVelocity());
		accel.x = accel.z = 0.0f;
		accel.y = -accel.y + 1.0f;
		actor->Accel(accel);
	}

}

bool HitCheckerAttackActor::HitCheck(BattleActor* actor, Attack* attack){
	//rejection check
	int attack_id(attack->GetId());
	if(actor->IsRejected(attack_id)){
		return false;
	}

	int hit_count(attack->GetHitCount());
	Hit* actor_hit(actor->GetHit());
	bool hit(false);

	for(int i = 0; i < hit_count; i++){
		Hit* attack_hit(attack->GetHit(i));

		hit |= actor_hit->HitCheck(attack_hit);
			
		if(hit){break;}
	}

	return hit;
}
