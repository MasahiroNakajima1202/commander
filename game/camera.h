//*****************************************************************************
//  cameraモジュール
//  author: 中島将浩
//  update: 2014/04/23
//*****************************************************************************
#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "main.h"

#include <d3dx9.h>
//*****************************************************************************
//  constant
//*****************************************************************************

//*****************************************************************************
//  class
//*****************************************************************************
class Renderer;
class GameInput;

class Camera{
public:
	//*****************************************************************************
	//【コンストラクタ】
	//  第1引数: れんだらー
	//*****************************************************************************
	Camera(Renderer *master_renderer){_renderer = master_renderer;}

	//*****************************************************************************
	//【デス様】
	//  あとかたづけ
	//  引数: なし
	//*****************************************************************************
	virtual ~Camera(){_renderer = NULL;}

	//*****************************************************************************
	//【初期化】
	//  返り値: 初期化に成功したかどうか
	//  引数: なし
	//*****************************************************************************
	HRESULT SetUp(void);

	//*****************************************************************************
	//【終了】
	//  返り値: なし
	//  引数: なし
	//*****************************************************************************
	void Release(void);

	//*****************************************************************************
	//【更新】
	//  返り値: なし
	//  引数: なし
	//*****************************************************************************
	void Update(GameInput *input = NULL);

	//*****************************************************************************
	//【セット】
	//  返り値: なし
	//  引数: なし
	//*****************************************************************************
	virtual void Set(void);

	//accessor
	D3DXMATRIX *GetView(void){ return &_view; }
	D3DXMATRIX *GetProjection(void){ return &_proj; }
	D3DXVECTOR3 GetPosition(void){return _eye;}
	D3DXVECTOR3 GetAtPosition(void){return _at;}

	void SetEyePosition(D3DXVECTOR3 value){_eye = _dst_eye = value;}
	void SetAtPosition(D3DXVECTOR3 value){_at = _dst_at = value;}
	void SetDestEyePosition(D3DXVECTOR3 value){_dst_eye = value;}
	void SetDestAtPosition(D3DXVECTOR3 value){_dst_at = value;}
	void SetUpVector(D3DXVECTOR3 value){_up = value;}
	D3DXVECTOR3 GetRight(void){return _right;}
	void SetRight(D3DXVECTOR3 value){_right = value;}
protected:
	Renderer *_renderer;

	D3DXVECTOR3 _eye;										//カメラ視点
	D3DXVECTOR3 _at;										//カメラ注視点
	D3DXVECTOR3 _up;										//カメラ上方向ベクトル

	D3DXVECTOR3 _dst_eye;									//カメラ始点目的地
	D3DXVECTOR3 _dst_at;									//カメラ注視点目的地

	D3DXVECTOR3 _front;
	D3DXVECTOR3 _right;

	float _length;											//注視点までの長さ

	D3DXMATRIX _view;									//ビュー行列
	D3DXMATRIX _proj;									//射影行列


};

//accessor

#endif//_CAMERA_H_