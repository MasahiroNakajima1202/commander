//*****************************************************************************
//  �GAI �߂��ɂ���z���U��
//  author: �������_
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


EnemyAIAttackNeighbor::EnemyAIAttackNeighbor(BattleObjectAccessor* accessor, Renderer* renderer, BattleActor* owner, BattleActor* target):
EnemyAI(accessor, renderer, owner),
_target(target){
}

EnemyAIAttackNeighbor::~EnemyAIAttackNeighbor(){
	
}

void EnemyAIAttackNeighbor::Update(void){
	if(_accessor == nullptr){return;}
	if(_owner == nullptr){return;}

	if(_target == nullptr){return;}

	
	D3DXVECTOR3 to_target(_target->GetPosition() - _owner->GetPosition());
	float length(D3DXVec3Length(&to_target));
	const float SEARCH_RANGE(50.0f);
	const float ATTACK_RANGE(10.0f);
	
	//���ȏ�Ȃ������
	if(length > ATTACK_RANGE){
		_owner->WalkTo(_target->GetPosition());
	}
	//�\���߂������炻���̕������čU��
	else{
		//�����`�F�b�N
		
		if(_owner->GetSkill() == nullptr){
			_owner->SetSkill(new BattleSkillAttack(_owner, _renderer, _accessor));
			_owner->SetAction(new BattleActionSkill(_owner));
		}
	}
}
