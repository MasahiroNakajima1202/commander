//*****************************************************************************
//  歩きアクションクラス
//  キャラクターの行動の指定
//  author: 中島将浩
//  update: 2015/10/24
//*****************************************************************************
#include "battle_action_skill.h"
#include "battle_actor.h"

#include "battle_skill.h"

//*****************************************************************************
//  class
//*****************************************************************************
BattleActionSkill::BattleActionSkill(BattleActor* owner):
BattleAction(owner){
}

BattleActionSkill::~BattleActionSkill(){
}

void BattleActionSkill::Update(void){
	if(_owner == nullptr){return;}

	_owner->UpdateSkill();
}
bool BattleActionSkill::Finished(void){
	if(_owner == nullptr){return true;}

	BattleSkill* skill(_owner->GetSkill());
	if(skill == nullptr){return true;}

	return skill->Finished();
}

void BattleActionSkill::OnBegin(void){
}
void BattleActionSkill::OnEnd(void){
}


