//*****************************************************************************
//  戦闘時のキャラクターの分身　ドラッグ時のガイド用
//  author: 中島将浩
//  update: 2015/12/29
//*****************************************************************************
#include "battle_actor_ghost.h"
#include "renderer.h"
#include "skin_mesh.h"
#include "my_math.h"

BattleActorGhost::BattleActorGhost(Renderer *renderer, char* image_filename):
_renderer(renderer),
_image(nullptr),
_position(0.0f, 0.0f, 0.0f),
_rotation(0.0f, 0.0f, 0.0f),
_dest_rotation(0.0f, 0.0f, 0.0f),
_visible(false){
	SkinMesh* image(new SkinMesh(renderer));
	image->LoadModelFile(image_filename);
	image->SetVisible(false);
	image->SetTransparent(true);

	_image = image;
}

BattleActorGhost::~BattleActorGhost(){
	if(_image != nullptr){
		_image->Destroy();
		_image = nullptr;
	}
}

void BattleActorGhost::Update(void){
	//update angle
	//D3DXVECTOR3 omega(_dest_rotation - _rotation);
	//PiSectionFix(&omega, &omega);
	//omega *= 0.1f;
	//_rotation += omega;
	//PiSectionFix(&_rotation, &_rotation);

	//commit position and rotation to image
	if(_image != nullptr){
		SetPosition(_position);
		D3DXVECTOR3 rotation(_rotation.x, _rotation.y + D3DX_PI, _rotation.z);
		SetRotation(rotation);
		SetVisible(_visible);
	}
}

void BattleActorGhost::SetPosition(D3DXVECTOR3 position){
	_position = position;
	//commit position and rotation to image
	if(_image != nullptr){
		_image->SetPosition(_position);
	}
}
void BattleActorGhost::SetRotation(D3DXVECTOR3 rotation){
	_rotation = rotation;
	_rotation.y += D3DX_PI;
	PiSectionFix(&_rotation.y, &_rotation.y);
	if (_image != nullptr){
		_image->SetRotation(_rotation);
	}
}
void BattleActorGhost::SetVisible(bool value){
	_visible = value;
	//commit position and rotation to image
	if(_image != nullptr){
		_image->SetVisible(value);
	}
}
