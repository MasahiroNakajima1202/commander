//*****************************************************************************
//  camera���W���[��
//  author: �������_
//  update: 2014/04/23
//*****************************************************************************


#include "camera.h"
#include "renderer.h"
//#include "game_input.h"

//*****************************************************************************
//  constant
//*****************************************************************************
//�J�����ʒu
#define CAMERA_INIT_X (0)
#define CAMERA_INIT_Y (0)
#define CAMERA_INIT_Z (-200)


//*****************************************************************************
//  class
//*****************************************************************************

//*****************************************************************************
//�y�������z
//  �Ԃ�l: �������ɐ����������ǂ���
//  ����: �Ȃ�
//*****************************************************************************
HRESULT Camera::SetUp(void){
	_eye = D3DXVECTOR3(CAMERA_INIT_X, CAMERA_INIT_Y, CAMERA_INIT_Z);
	_at = D3DXVECTOR3(0, 0, 0);
	_up = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	_dst_eye = _eye;
	_dst_at = _at;

	_front = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	_right = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	D3DXVECTOR3 to_at(_at - _eye);
	_length = D3DXVec3Length(&to_at);
	
	return S_OK;
}

//*****************************************************************************
//�y�I���z
//  �Ԃ�l: �Ȃ�
//  ����: �Ȃ�
//*****************************************************************************
void Camera::Release(void){}

//*****************************************************************************
//�y�X�V�z
//  �Ԃ�l: �Ȃ�
//  ����: �Ȃ�
//*****************************************************************************
void Camera::Update(GameInput *input){
	_eye += (_dst_eye - _eye) * 0.1f;
	_at+= (_dst_at - _at) * 0.1f;

	_front = _at - _eye;
	D3DXVec3Normalize(&_front, &_front);

	D3DXVec3Cross(&_right, &_front, &_up);
	D3DXVec3Normalize(&_right, &_right);

	D3DXVec3Cross(&_up, &_right, &_front);
	D3DXVec3Normalize(&_up, &_up);
}

//*****************************************************************************
//�y�Z�b�g�z
//  �Ԃ�l: �Ȃ�
//  ����: �Ȃ�
//*****************************************************************************
void Camera::Set(void){
	LPDIRECT3DDEVICE9 device = NULL;		//�f�o�C�X�擾�p

	device = _renderer->GetDevice();

	D3DXMatrixIdentity(&_view);					//�r���[�s����Ƃ肠����E�ɂ���
	D3DXMatrixLookAtLH(&_view,					//�r���[�s��̍쐬
					   &_eye,
					   &_at,
					   &_up);
	_renderer->SetView(_view);

	D3DXMatrixIdentity(&_proj);					//�ˉe�s����Ƃ肠����E�ɂ���
	D3DXMatrixPerspectiveFovLH(&_proj,			//�ˉe�s��̍쐬
							   D3DX_PI * 0.45f,		//����p
							   (float)SCREEN_WIDTH/(float)SCREEN_HEIGHT,	//�A�X�y�N�g��
							   10.0f,				//near�l
							   1000.0f);				//far�l
	_renderer->SetProjection(_proj);
}

