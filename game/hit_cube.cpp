//*****************************************************************************
//  当たり判定クラス
//  author: 中島将浩
//  update: 2015/10/25
//*****************************************************************************
#include "hit_cube.h"
#include "hit_sphere.h"
#include "object_x.h"

HitCube::HitCube(Renderer* renderer, D3DXVECTOR3 position, D3DXVECTOR3 size):
Hit(renderer, position),
_debug_image(nullptr),
_size(size){
#ifdef _DEBUG
	if(renderer != nullptr){
		ObjectX* image(new ObjectX(renderer));
		image->SetUp("data/MODEL/cube.x");
		image->SetSize(size);
		image->SetWireFrameFlag(true);
		image->SetPosition(position);

		_debug_image = image;
	}
#endif
}

HitCube::~HitCube(){
	if(_debug_image != nullptr){
		_debug_image->Destroy();
		_debug_image = nullptr;
	}
}
void HitCube::Update(void){
	if(_debug_image != nullptr){
		_debug_image->SetPosition(_position);
		_debug_image->SetRotation(_rotation);
	}
}

bool HitCube::HitCheck(Hit* hit){
	return hit->InnerHitCheck(this);
}

bool HitCube::InnerHitCheck(HitSphere* sphere){
	if(sphere == nullptr){return false;}

	D3DXMATRIX world, world_inv, rotation, translation;
	D3DXMatrixTranslation(&translation, _position.x, _position.y, _position.z);
	D3DXMatrixRotationYawPitchRoll(&rotation, _rotation.y, _rotation.x, _rotation.z);
	D3DXMatrixMultiply(&world, &rotation, &translation);
	D3DXMatrixInverse(&world_inv, nullptr, &world);

	//sphereを、box上のローカル座標に変換
	D3DXVECTOR3 sphere_position(sphere->GetPosition());
	D3DXVec3TransformCoord(&sphere_position, &sphere_position, &world_inv);

	//各方向のはみ出し距離を測定
	
	float x_out( max(0.0f, fabsf(sphere_position.x) - _size.x * 0.5f) );
	float y_out( max(0.0f, fabsf(sphere_position.y) - _size.y * 0.5f) );
	float z_out( max(0.0f, fabsf(sphere_position.z) - _size.z * 0.5f) );

	//はみ出しの長さを測定
	D3DXVECTOR3 ext(x_out, y_out, z_out);
	float length(D3DXVec3Length(&ext));
	float radius(sphere->GetRadius());

	bool hit(length < radius);

	return hit;
}

bool HitCube::InnerHitCheck(HitCube* cube){
	if(cube == nullptr){return false;}

	//各成分ごとに距離比較

	//まるペケ見てがんばって
	//あとまわし

	bool hit(false);

	return hit;
}

void HitCube::SetPosition(D3DXVECTOR3 position){
	_position = position;
	if(_debug_image != nullptr){
		_debug_image->SetPosition(_position);
	}
}

void HitCube::SetRotation(D3DXVECTOR3 rotation){
	_rotation = rotation;
	if(_debug_image != nullptr){
		_debug_image->SetRotation(_rotation);
	}
}
