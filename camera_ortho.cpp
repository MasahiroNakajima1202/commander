//*****************************************************************************
//  cameraモジュール
//  author: 中島将浩
//  update: 2014/04/23
//*****************************************************************************

#include "camera_ortho.h"
#include "renderer.h"

//*****************************************************************************
//  constant
//*****************************************************************************

//*****************************************************************************
//  class
//*****************************************************************************


//*****************************************************************************
//【セット】
//  返り値: なし
//  引数: なし
//*****************************************************************************
void CameraOrtho::Set(void){
	LPDIRECT3DDEVICE9 device = NULL;		//デバイス取得用

	device = _renderer->GetDevice();

	D3DXMatrixIdentity(&_view);					//ビュー行列をとりあえずEにする
	D3DXMatrixLookAtLH(&_view,					//ビュー行列の作成
					   &_eye,
					   &_at,
					   &_up);
	//device->SetTransform(D3DTS_VIEW, &view_mtx);	//ビュー行列の設定

	D3DXMatrixIdentity(&_proj);					//射影行列をとりあえずEにする
	D3DXMatrixOrthoLH(&_proj,			//射影行列の作成
							   150.0f,		//たて
							   150.0f,		//よこ
							   10.0f,				//near値
							   500.0f);			//far値
	device->SetTransform(D3DTS_PROJECTION, &_proj);	//射影行列の設定
}
