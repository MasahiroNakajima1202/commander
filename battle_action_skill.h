//*****************************************************************************
//  �A�N�V�����N���X �ݒ肳��Ă���X�L���̎g�p
//  �L�����N�^�[�̍s���̎w��
//  author: �������_
//  update: 2015/10/24
//*****************************************************************************
#ifndef _BATTLE_ACTION_SKILL_H_
#define _BATTLE_ACTION_SKILL_H_

#include "battle_action.h"

//*****************************************************************************
//  constant
//*****************************************************************************

//*****************************************************************************
//  class
//*****************************************************************************
class BattleActor;
class BattleActionSkill : public BattleAction{
public:

	BattleActionSkill(BattleActor* owner);
	virtual ~BattleActionSkill();

	virtual void Update(void);
	virtual void OnBegin(void);
	virtual void OnEnd(void);
	virtual bool Finished(void);

	//accessor
private:
};



#endif//_NUMBER_H_