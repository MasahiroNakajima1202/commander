//*****************************************************************************
//  “–‚½‚è”»’èƒNƒ‰ƒX
//  author: ’†“‡«_
//  update: 2015/10/25
//*****************************************************************************
#include "hit_sphere.h"
#include "hit_cube.h"
#include "object_x.h"

HitSphere::HitSphere(Renderer* renderer, D3DXVECTOR3 position, float radius):
Hit(renderer, position),
_debug_image(nullptr),
_radius(radius){
#ifdef _DEBUG
	if(renderer != nullptr){
		ObjectX* image(new ObjectX(renderer));
		image->SetUp("data/MODEL/sphere.x");
		image->SetSize(D3DXVECTOR3(radius, radius, radius));
		image->SetWireFrameFlag(true);
		image->SetPosition(position);

		_debug_image = image;
	}
#endif
}

HitSphere::~HitSphere(){
	if(_debug_image != nullptr){
		_debug_image->Destroy();
		_debug_image = nullptr;
	}
}
void HitSphere::Update(void){
	if(_debug_image != nullptr){
		_debug_image->SetPosition(_position);
	}
}

bool HitSphere::HitCheck(Hit* hit){
	return hit->InnerHitCheck(this);
}

bool HitSphere::InnerHitCheck(HitSphere* sphere){
	if(sphere == nullptr){return false;}

	float sum_radius(_radius + sphere->GetRadius());
	D3DXVECTOR3 v(_position - sphere->GetPosition());
	float sq_distance(D3DXVec3Dot(&v, &v));

	bool hit(sum_radius * sum_radius > sq_distance);

	return hit;
}

bool HitSphere::InnerHitCheck(HitCube* cube){
	if(cube == nullptr){return false;}

	return cube->InnerHitCheck(this);
}

void HitSphere::SetPosition(D3DXVECTOR3 position){
	_position = position;
	if(_debug_image != nullptr){
		_debug_image->SetPosition(_position);
	}
}
