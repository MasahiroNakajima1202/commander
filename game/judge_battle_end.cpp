//*****************************************************************************
//  終了判定クラス
//  author: 中島将浩
//  update: 2015/11/30
//*****************************************************************************
#include "judge_battle_end.h"
#include "battle_object_accessor.h"
#include "battle_actor.h"

JudgeBattleEnd::JudgeBattleEnd(BattleObjectAccessor* accessor):
_accessor(accessor),
_battle_end(false),
_event_end(false),
_win(false),
_lose(false){
}

JudgeBattleEnd::~JudgeBattleEnd(){
}

void JudgeBattleEnd::Update(void){
	//プレイヤーの全滅
	int player_count(_accessor->GetPlayerCount());
	bool player_alive(false);
	for(int i=0; i<player_count; i++){
		BattleActor* player(_accessor->GetPlayer(i));
		player_alive |= (!player->IsDead());
	}
	_battle_end |= (!player_alive);
	_lose = (!player_alive);

	//敵の全滅
	int enemy_count(_accessor->GetEnemyCount());
	bool enemy_alive(false);
	for(int i=0; i<enemy_count; i++){
		BattleActor* enemy(_accessor->GetEnemy(i));
		enemy_alive |= (!enemy->IsDead());
	}
	_battle_end |= (!enemy_alive);
	_win = (!enemy_alive);
}

bool JudgeBattleEnd::End(void){
	return _battle_end || _event_end;
}

bool JudgeBattleEnd::Win(void){
	return _win;
}

bool JudgeBattleEnd::Lose(void){
	return _lose;
}
