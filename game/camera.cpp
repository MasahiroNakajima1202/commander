//*****************************************************************************
//  cameraモジュール
//  author: 中島将浩
//  update: 2014/04/23
//*****************************************************************************


#include "camera.h"
#include "renderer.h"
//#include "game_input.h"

//*****************************************************************************
//  constant
//*****************************************************************************
//カメラ位置
#define CAMERA_INIT_X (0)
#define CAMERA_INIT_Y (0)
#define CAMERA_INIT_Z (-200)


//*****************************************************************************
//  class
//*****************************************************************************

//*****************************************************************************
//【初期化】
//  返り値: 初期化に成功したかどうか
//  引数: なし
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
//【終了】
//  返り値: なし
//  引数: なし
//*****************************************************************************
void Camera::Release(void){}

//*****************************************************************************
//【更新】
//  返り値: なし
//  引数: なし
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
//【セット】
//  返り値: なし
//  引数: なし
//*****************************************************************************
void Camera::Set(void){
	LPDIRECT3DDEVICE9 device = NULL;		//デバイス取得用

	device = _renderer->GetDevice();

	D3DXMatrixIdentity(&_view);					//ビュー行列をとりあえずEにする
	D3DXMatrixLookAtLH(&_view,					//ビュー行列の作成
					   &_eye,
					   &_at,
					   &_up);
	_renderer->SetView(_view);

	D3DXMatrixIdentity(&_proj);					//射影行列をとりあえずEにする
	D3DXMatrixPerspectiveFovLH(&_proj,			//射影行列の作成
							   D3DX_PI * 0.45f,		//視野角
							   (float)SCREEN_WIDTH/(float)SCREEN_HEIGHT,	//アスペクト比
							   10.0f,				//near値
							   1000.0f);				//far値
	_renderer->SetProjection(_proj);
}

