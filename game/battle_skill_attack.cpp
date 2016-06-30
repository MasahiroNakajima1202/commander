//*****************************************************************************
//  í“¬’†‚Ì‹ZƒNƒ‰ƒX@’Êí‹ßÚUŒ‚
//  author: ’†“‡«_
//  update: 2015/10/31
//*****************************************************************************
#include "battle_skill_attack.h"
#include "attack_sphere.h"
#include "battle_actor.h"
#include "battle_object_accessor.h"

BattleSkillAttack::BattleSkillAttack(BattleActor* owner, Renderer* renderer, BattleObjectAccessor* accessor):
BattleSkill(owner, renderer, accessor),
_frame_count(0){
}

BattleSkillAttack::~BattleSkillAttack(){
}

void BattleSkillAttack::Update(void){
	if(_frame_count == 1){
		float angle(_owner->GetRotation().y);
		D3DXVECTOR3 direction(0.0f, 0.0f, 1.0f);
		float reach(20.0f);
		D3DXVECTOR3 position(_owner->GetPosition());

		D3DXMATRIX rotation;
		D3DXMatrixRotationY(&rotation, angle);
		D3DXVec3TransformCoord(&direction, &direction, &rotation);

		position += reach * direction;

		int power(_owner->GetAttack());
		AttackSphere* attack(new AttackSphere(position, 10.0f, 60, _renderer, _owner, power, direction));
		
		//set scope
		attack->SetPlayerScope(false);
		attack->SetEnemyScope(false);
		if(_accessor->IsPlayer(_owner)){
			attack->SetEnemyScope(true);
		}
		if(_accessor->IsEnemy(_owner)){
			attack->SetPlayerScope(true);
		}
	}

	_frame_count++;
}


bool BattleSkillAttack::Finished(void){
	return _frame_count >= 120;
}

