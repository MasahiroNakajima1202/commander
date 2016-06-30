//*****************************************************************************
//  í“¬Žž‚ÌƒMƒ~ƒbƒN
//  author: ’†“‡«_
//  update: 2016/03/13
//*****************************************************************************
#include "gimmick.h"
#include "object.h"
#include "hit.h"
#include "my_math.h"

//*****************************************************************************
//  constant
//*****************************************************************************
const float Gimmick::NATURAL_SPEED_DOWN(0.95f);
//*****************************************************************************
//  class
//*****************************************************************************

Gimmick::Gimmick(Renderer *renderer, D3DXVECTOR3 position, D3DXVECTOR3 rotation):
_renderer(renderer),
_image(nullptr),
_position(position),
_pre_position(position),
_velocity(0.0f, 0.0f, 0.0f),
_rotation(rotation),
_dest_rotation(rotation),
 _visible(true),
_hit(nullptr){
}

Gimmick::~Gimmick(){
	if(_image != nullptr){
		_image->Destroy();
		_image = nullptr;
	}

	if(_hit != nullptr){
		delete _hit;
		_hit = nullptr;
	}
}

void Gimmick::Update(void){
	_pre_position = _position;

	//update velociy
	//_velocity.y -= 0.05f;
	_velocity *= NATURAL_SPEED_DOWN;

	//update position
	_position += _velocity;

	//update angle
	D3DXVECTOR3 omega(_dest_rotation - _rotation);
	PiSectionFix(&omega, &omega);
	omega *= 0.1f;
	_rotation += omega;
	PiSectionFix(&_rotation, &_rotation);

	CommitPositionRotationToImage();

	CommitPositionRotationToHit();
}

void Gimmick::CommitPositionRotationToImage(void){
	//commit position and rotation to image
	if(_image != nullptr){
		_image->SetPosition(_position);
		D3DXVECTOR3 rotation(_rotation.x, _rotation.y + D3DX_PI, _rotation.z);
		_image->SetRotation(rotation);
	}
}
void Gimmick::CommitPositionRotationToHit(void){
	//commit position to hit
	if(_hit != nullptr){
		_hit->SetPosition(_position);
	}
}