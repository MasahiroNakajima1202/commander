//*****************************************************************************
//  選択中のキャラを指すカーソル
//  author: 中島将浩
//  update: 2015/12/27
//*****************************************************************************
#include "actor_cursor.h"
#include "battle_actor.h"
#include "renderer.h"
#include "object_effect.h"

//*****************************************************************************
//  constant
//*****************************************************************************

ActorCursor::ActorCursor(Renderer* renderer, BattleActor* owner):
_renderer(renderer),
_owner(owner),
_image(nullptr),
_active(false){
	_image = new ObjectEffect(renderer);
	_image->SetUp(ObjectEffect::EFFECT_TYPE::TEST);
	_image->Play(true);
}

ActorCursor::~ActorCursor(){
	if(_image != nullptr){
		_image->Destroy();
		_image = nullptr;
	}
}

void ActorCursor::Update(void){
	if(_image != nullptr){
		//update position
		D3DXVECTOR3 position(_owner->GetPosition());
		position.y += 1.0f;
		_image->SetPosition(position);

		_image->SetVisible(_active);
	}
}

void ActorCursor::Activate(void){
	_active = true;
	
	if(_image != nullptr){
		_image->SetVisible(_active);
	}
}
void ActorCursor::Inactivate(void){
	_active = false;

	if(_image != nullptr){
		_image->SetVisible(_active);
	}
}
bool ActorCursor::IsActive(void){
	return _active;
}
