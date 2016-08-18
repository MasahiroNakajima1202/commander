//*****************************************************************************
//  歩きアクションクラス
//  キャラクターの行動の指定
//  author: 中島将浩
//  update: 2015/10/24
//*****************************************************************************
#include "battle_action_walk.h"
#include "battle_actor.h"
#include <math.h>
#include "my_math.h"

//*****************************************************************************
//  constant
//*****************************************************************************
const float BattleActionWalk::ZERO_RADIUS = 0.1f;

//*****************************************************************************
//  class
//*****************************************************************************
BattleActionWalk::BattleActionWalk(BattleActor* owner, D3DXVECTOR3 dest_position):
BattleAction(owner),
_dest_position(dest_position){
}

BattleActionWalk::~BattleActionWalk(){
}

void BattleActionWalk::Update(void){
	if(_owner == nullptr){return;}
	//向き合わせ
	D3DXVECTOR3 position(_owner->GetPosition());
	D3DXVECTOR3 direction(_dest_position - position);

	//わずかすぎる移動では向きを変えない
	if(D3DXVec3Dot(&direction, &direction) > 1.0f * 1.0f){
		float angle(atan2f(direction.x, direction.z));
		PiSectionFix(&angle, &angle);

		D3DXVECTOR3 rotation(_owner->GetRotation());
		rotation.y = angle;

		_owner->SetDestRotation(rotation);
	}
	
	_owner->WalkTo(_dest_position);
}
bool BattleActionWalk::Finished(void){
	if(_owner == nullptr){return true;}

	D3DXVECTOR3 position(_owner->GetPosition());
	D3DXVECTOR3 direction(_dest_position - position);
	direction.y = 0.0f;
	bool ret(ZERO_RADIUS * ZERO_RADIUS > D3DXVec3Dot(&direction, &direction));

	return ret;
}

void BattleActionWalk::OnBegin(void){
	if(_owner == nullptr){return;}

	_owner->ChangeState(BattleActor::STATE::WALK);
}
void BattleActionWalk::OnEnd(void){
	_owner->ChangeState(BattleActor::STATE::IDLE);
}
