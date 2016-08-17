//*****************************************************************************
//  �퓬���̃L�����N�^�[
//  author: �������_
//  update: 2015/10/24
//*****************************************************************************
#ifndef _BATTLE_ACTOR_H_
#define _BATTLE_ACTOR_H_

#include "main.h"
#include <d3dx9.h>

#include "battle_action_queue.h"

//*****************************************************************************
//  constant
//*****************************************************************************

//*****************************************************************************
//  class
//*****************************************************************************
class Renderer;
class Object;
class BattleAction;
class Hit;
class BattleSkill;
class BattleOperation;
class BattleActorState;
class AIState;
class BattleActor{
public:
	struct PARAMETER{
		int max_hp;
		int hp;
		int attack;
		int defence;

		PARAMETER(int max_hp, int hp, int attack, int defence):
		max_hp(max_hp),
		hp(hp),
		attack(attack),
		defence(defence){}

		PARAMETER(void):
		max_hp(100),
		hp(100),
		attack(0),
		defence(0){}
	};
	BattleActor(Renderer *renderer, PARAMETER &parameter, char* image_filename);

	virtual ~BattleActor();

	void Update(void);

	//action����Ă΂�����
	void UpdateSkill(void);

	void Accel(D3DXVECTOR3 acceleration);
	void WalkTo(D3DXVECTOR3 dest_position);

	//�s������\�� �㏑���ł͂Ȃ��A�ǉ�
	void SetAction(BattleAction* action);

	//�s���L���[��S�ċ�ɂ���
	void ClearAction(void);

	//���ɋZ�����݂��Ă�����A����͍폜����
	void SetSkill(BattleSkill* skill);

	//���ɍ�킪���݂��Ă�����A����͍폜����
	void SetOperation(BattleOperation* operation);

	bool IsActing(void){return _cur_action != nullptr;}

	enum STATE{
		IDLE = 0,
		WALK,
		DEAD,
		MAX
	};
	void ChangeState(STATE state);

	void SetRejection(int attack_id, int time = 60);
	bool IsRejected(int attack_id);

	void Damage(int damage);
	bool IsDead(void);

	int GetAttack(void);
	int GetDefence(void);

	//accessor
	D3DXVECTOR3 GetPrePosition(void){return _pre_position;}
	D3DXVECTOR3 GetPosition(void){ return _position; }
	void SetPosition(D3DXVECTOR3 position);
	D3DXVECTOR3 GetVelocity(void){ return _velocity; }
	void SetVelocity(D3DXVECTOR3 velocity){_velocity = velocity;}
	void SetVisible(bool value);
	Hit* GetHit(void){return _hit;}
	Hit* GetCursorHit(void){ return GetHit(); }		//�K�v�Ȃ�΃J�[�\���ɑ΂��Ă͕ʂ̓����蔻������悤��
	BattleSkill* GetSkill(void){return _skill;}
	void SetDestRotation(D3DXVECTOR3 value){_dest_rotation = value;}
	void SetRotation(D3DXVECTOR3 value){_dest_rotation = _rotation = value;}
	D3DXVECTOR3 GetRotation(void){return _rotation;}
	D3DXVECTOR3 GetDestRotation(void){return _dest_rotation;}
	void SetCurrentAI(AIState* ai);
private:
	static const float DEFAULT_WALK_ACCEL;
	static const float NATURAL_SPEED_DOWN;
	Renderer *_renderer;
	Object* _image;

	D3DXVECTOR3 _position;
	D3DXVECTOR3 _pre_position;
	D3DXVECTOR3 _velocity;
	D3DXVECTOR3 _rotation;
	D3DXVECTOR3 _dest_rotation;
	bool _visible;
	float _walk_accel;

	BattleActionQueue _action_queue;
	BattleAction* _cur_action;
	BattleSkill* _skill;
	BattleOperation* _operation;

	Hit* _hit;

	static const int AI_MAX = 32;
	AIState* _ai_array[AI_MAX];
	AIState* _current_ai;

	struct ATTACK_REJECTION{
		int attack_id;
		int rest_time;
		bool active;
		ATTACK_REJECTION():
		attack_id(-1),
		rest_time(0),
		active(false){}
	};
	static const int REJECTION_MAX = 32;
	ATTACK_REJECTION _rejection[REJECTION_MAX];

	BattleActorState* _state_array[STATE::MAX];
	BattleActorState* _cur_state;

	PARAMETER _parameter;

	void UpdateOperation(void);
	void UpdateAction(void);
	void UpdateRejection(void);
};


#endif