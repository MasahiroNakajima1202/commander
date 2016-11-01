//*****************************************************************************
//  戦闘時のキャラクター
//  author: 中島将浩
//  update: 2015/10/24
//*****************************************************************************

#include "battle_actor.h"
#include "object_x.h"
#include "skin_mesh.h"
#include "my_math.h"

#include "battle_action.h"
#include "battle_action_queue.h"

#include "hit.h"
#include "hit_sphere.h"
#include "battle_skill.h"

#include "battle_operation.h"

#include "battle_actor_state.h"
#include "battle_actor_state_idle.h"
#include "battle_actor_state_walk.h"
#include "battle_actor_state_dead.h"

#include "actor_ai.h"

#include "debug.h"
//*****************************************************************************
//  constant
//*****************************************************************************
const float BattleActor::DEFAULT_WALK_ACCEL = 0.01f;
const float BattleActor::NATURAL_SPEED_DOWN = 0.95f;

BattleActor::BattleActor(Renderer *renderer, PARAMETER& parameter, char* image_filename) :
_renderer(renderer),
_image(nullptr),
_position(0.0f, 0.0f, 0.0f),
_pre_position(0.0f, 0.0f, 0.0f),
_velocity(0.0f, 0.0f, 0.0f),
_rotation(0.0f, 0.0f, 0.0f),
_dest_rotation(0.0f, 0.0f, 0.0f),
_visible(false),
_walk_accel(DEFAULT_WALK_ACCEL),
_action_queue(),
_cur_action(nullptr),
_skill(nullptr),
_operation(nullptr),
_hit(nullptr),
_cur_state(nullptr),
_parameter(parameter),
_ai(nullptr){
	SkinMesh *obj(new SkinMesh(renderer));
	obj->LoadModelFile(image_filename);
	obj->PlayAnimation(0);
	_image = obj;

	//test
	_hit = new HitSphere(_renderer, _position, 10.0f);

	_state_array[STATE::IDLE] = new BattleActorStateIdle(this);
	_state_array[STATE::WALK] = new BattleActorStateWalk(this);
	_state_array[STATE::DEAD] = new BattleActorStateDead(this);

	_cur_state = _state_array[STATE::IDLE];
}

BattleActor::~BattleActor(){
	if(_image != nullptr){
		_image->Destroy();
		_image = nullptr;
	}

	if(_cur_action != nullptr){
		delete _cur_action;
		_cur_action = nullptr;
	}
	
	if(_hit != nullptr){
		delete _hit;
		_hit = nullptr;
	}

	if(_skill != nullptr){
		delete _skill;
		_skill = nullptr;
	}

	if(_operation != nullptr){
		delete _operation;
		_operation = nullptr;
	}

	for(int i=0; i<STATE::MAX; i++){
		if(_state_array[i] != nullptr){
			delete _state_array[i];
			_state_array[i] = nullptr;
		}
	}

	if (_ai != nullptr) {
		delete _ai;
		_ai = nullptr;
	}
}

void BattleActor::Update(void){
	//本当は当たり判定とかの後で座標がfixされてから行うべき
	if (_ai != nullptr) {
		_ai->Update();
		D3DXVECTOR3 destination(_ai->GetTargetPosition());
		WalkTo(destination);
	}

	_pre_position = _position;

	//update velociy
	_velocity.y -= 0.05f;
	_velocity *= NATURAL_SPEED_DOWN;

	//update position
	_position += _velocity;

	//update angle
	D3DXVECTOR3 omega(_dest_rotation - _rotation);
	PiSectionFix(&omega, &omega);
	omega *= 0.1f;
	_rotation += omega;
	PiSectionFix(&_rotation, &_rotation);
	
	

	_cur_state->Update();

	UpdateOperation();

	UpdateAction();

	if(_cur_state != nullptr){
		_cur_state->Update();
	}

	//commit position and rotation to image
	if(_image != nullptr){
		_image->SetPosition(_position);
		D3DXVECTOR3 rotation(_rotation.x, _rotation.y + D3DX_PI, _rotation.z);
		_image->SetRotation(rotation);
	}

	//commit position to hit
	if(_hit != nullptr){
		D3DXVECTOR3 position(_position);
		position.y += ((HitSphere*)_hit)->GetRadius() * 0.5f;
		_hit->SetPosition(position);
	}
}

void BattleActor::Accel(D3DXVECTOR3 acceleration){
	_velocity += acceleration;
}

void BattleActor::WalkTo(D3DXVECTOR3 dest_position){
	D3DXVECTOR3 position(_position);
	D3DXVECTOR3 direction(dest_position - position);
	direction.y = 0.0f;

	D3DXVECTOR3 acceleration(direction);
	float length = D3DXVec3Length(&acceleration);
	if (length <= 2.0f) { return; }
	D3DXVECTOR3 h_velocity(_velocity);
	h_velocity.y = 0.0f;
	float speed(D3DXVec3Length(&h_velocity));

	//目的地を越えない範囲で加速
	D3DXVec3Normalize(&acceleration, &acceleration);
	acceleration *= _walk_accel;
	Accel(acceleration);

	//向き合わせ
	float angle(atan2f(direction.x, direction.z));
	PiSectionFix(&angle, &angle);

	D3DXVECTOR3 dest_rotation(_rotation);
	dest_rotation.y = angle;

	SetDestRotation(dest_rotation);
}

void BattleActor::SetAction(BattleAction* action){
	if(action == nullptr){return;}

	_action_queue.Enqueue(action);
}

void BattleActor::ClearAction(void){
	if(_cur_action != nullptr){
		delete _cur_action;
		_cur_action = nullptr;
	}
	
	_action_queue.Clear();
}


void BattleActor::SetPosition(D3DXVECTOR3 position){
	_position = position;
	if(_image != nullptr){
		_image->SetPosition(position);
	}

	//commit position to hit
	if(_hit != nullptr){
		D3DXVECTOR3 position(_position);
		position.y += ((HitSphere*)_hit)->GetRadius() * 0.5f;
		_hit->SetPosition(position);
	}
}
void BattleActor::SetVisible(bool value){
	_visible = value;
	if(_image != nullptr){
		_image->SetVisible(value);
	}
}

void BattleActor::SetSkill(BattleSkill* skill){
	if(_skill != nullptr){delete _skill;}

	_skill = skill;
}

void BattleActor::SetOperation(BattleOperation* operation){
	if(_operation != nullptr){delete _operation;}

	_operation = operation;
}




void BattleActor::ChangeState(STATE state){
	if(_cur_state != nullptr){
		_cur_state->StateOut();
	}

	_cur_state = _state_array[state];
	_cur_state->StateIn();
}

void BattleActor::SetRejection(int attack_id, int time){
	bool rejecting(false);
	for(int i = 0; i<REJECTION_MAX; i++){
		if(_rejection[i].active && _rejection[i].attack_id == attack_id){
			//既にreject中のものは、時間を上書きして延長
			_rejection[i].rest_time = max(time, _rejection[i].rest_time);
			rejecting = true;
			break;
		}
	}

	//もういた
	if(rejecting){return;}

	for(int i = 0; i<REJECTION_MAX; i++){
		if(_rejection[i].active){
			//上でチェック済みのため、ここには同idは現れない　無条件で飛ばす
			continue;
		}

		//空きがいたので書き込み
		_rejection[i].attack_id = attack_id;
		_rejection[i].rest_time = time;
		_rejection[i].active = true;

		break;
	}
}

bool BattleActor::IsRejected(int attack_id){
	bool ret(false);

	for(int i = 0; i<REJECTION_MAX; i++){
		if(!_rejection[i].active){continue;}

		if(_rejection[i].attack_id == attack_id){
			ret = true;
			break;
		}
	}

	return ret;
}

void BattleActor::Damage(int damage){
	//hp減算
	_parameter.hp -= damage;
	_parameter.hp = max(0, _parameter.hp);

	//死亡判定
	bool dead(_parameter.hp == 0);

	if(dead){
		ChangeState(STATE::DEAD);
	}
}

bool BattleActor::IsDead(void){
	return _cur_state == _state_array[STATE::DEAD];
}

int BattleActor::GetAttack(void){
	return _parameter.attack;
}

int BattleActor::GetDefence(void){
	return _parameter.defence;
}

void BattleActor::UpdateSkill(void){
	if(_skill == nullptr){return;}

	_skill->Update();

	if(_skill->Finished()){
		delete _skill;
		_skill = nullptr;
	}
}

void BattleActor::UpdateAction(void){
	//update current action
	if(_cur_action != nullptr){
		_cur_action->Update();

		if(_cur_action->Finished()){
			_cur_action->OnEnd();
			delete _cur_action;
			_cur_action = nullptr;
		}
	}

	//check action queue
	if(_cur_action == nullptr
	&& !_action_queue.IsEmpty()){
		_cur_action = _action_queue.Dequeue();
		_cur_action->OnBegin();
	}
}

void BattleActor::UpdateOperation(void){
	if(_operation == nullptr){return;}

	_operation->Update();

	if(_operation->Finished()){
		delete _operation;
		_operation = nullptr;
	}
}

void BattleActor::UpdateRejection(void){
	for(int i = 0; i<REJECTION_MAX; i++){
		if(!_rejection[i].active){continue;}

		if(_rejection[i].rest_time <= 0){
			_rejection[i].active = false;
			_rejection[i].attack_id = -1;
			_rejection[i].rest_time = 0;
		}
		else{
			_rejection[i].rest_time--;
		}
	}
}
