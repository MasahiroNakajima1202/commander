//*****************************************************************************
//  ƒJƒƒ‰‚ð“®‚©‚·l
//  author: ’†“‡«_
//  update: 2016/02/24
//*****************************************************************************
#include "camera_director.h"
#include "camera.h"
#include "battle_actor.h"

CameraDirector::CameraDirector(BattleActor* owner, Camera* camera):
_owner(owner),
_camera(camera){
}

CameraDirector::~CameraDirector(){
}

void CameraDirector::Update(void){
	if(_camera == nullptr || _owner == nullptr){return;}

	D3DXVECTOR3 owner_rotation(_owner->GetRotation());

	//make front vector
	D3DXVECTOR3 front(0.0f, 0.0f, 1.0f);
	D3DXMATRIX rotation_matrix;
	D3DXMatrixRotationY(&rotation_matrix, owner_rotation.y);
	D3DXVec3TransformNormal(&front, &front, &rotation_matrix);

	//eye, at positionŽZo
	D3DXVECTOR3 eye(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 at(0.0f, 0.0f, 0.0f);
	float eye_h_distance(45.0f);
	float eye_v_distance(50.0f);
	float at_h_distance(200.0f);
	float at_v_distance(10.0f);
	D3DXVECTOR3 owner_position(_owner->GetPosition());
	eye = owner_position - front * eye_h_distance;
	eye.y += eye_v_distance;
	at = owner_position + front * at_h_distance;
	at.y += at_v_distance;

	_camera->SetDestEyePosition(eye);
	_camera->SetDestAtPosition(at);
	_camera->SetUpVector(D3DXVECTOR3(0.0f, 1.0f, 0.0f));
}
