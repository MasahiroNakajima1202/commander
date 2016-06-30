//=============================================================================
//  fade機能のモジュール
//  author: 中島将浩
//  update: 2014/03/16
//=============================================================================

#include "fade.h"

//*****************************************************************************
//  constant def
//*****************************************************************************
#define FADE_LENGTH (8)								//フェードの増減値

//*****************************************************************************
//  static variables
//*****************************************************************************
LPDIRECT3DTEXTURE9 Fade::_texture = NULL;			//フェードのテクスチャ
LPDIRECT3DVERTEXBUFFER9 Fade::_vtx = NULL;
Fade::FADE Fade::_state = FADE_NON;
int Fade::_value = 0;
Renderer *Fade::_renderer = NULL;
LPDIRECT3DVERTEXDECLARATION9 Fade::_decl;

//=============================================================================
// フェードの初期化
//=============================================================================
bool Fade::SetUp(Renderer *master_renderer){
	LPDIRECT3DDEVICE9 device = NULL;		//デバイス取得用
	VERTEX_2D *work_vtx = NULL;					//頂点情報先頭アドレス格納用

	_renderer = master_renderer;

	//フェードの状態初期化
	_state = FADE_NON;
	_value = 255;

	//デバイスの取得
	device = _renderer->GetDevice();

	//頂点要素の定義
	D3DVERTEXELEMENT9 v_ele[] = {
		{ 0, 0, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0 },
		{ 0, 16, D3DDECLTYPE_D3DCOLOR, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_COLOR, 0 },
		{ 0, 20, D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 0 },
		D3DDECL_END()
	};

	//declaration初期化
	if (FAILED(device->CreateVertexDeclaration(v_ele, &_decl))){
		return false;
	}

	//頂点バッファの確保
	if(FAILED(device->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
										  D3DUSAGE_WRITEONLY,
										  0,
										  D3DPOOL_MANAGED,
										  &_vtx,
										  NULL))){
		return false;
	}

	//頂点情報の取得
	_vtx->Lock(0, 0, (void**)&work_vtx, 0);					//他者からのアクセスやメモリ再配置をロックする

	//頂点情報の初期化
	work_vtx[0].vtx = D3DXVECTOR3(0, 0, 0.0f);
	work_vtx[1].vtx = D3DXVECTOR3(SCREEN_WIDTH, 0, 0.0f);
	work_vtx[2].vtx = D3DXVECTOR3(0, SCREEN_HEIGHT, 0.0f);
	work_vtx[3].vtx = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);
	work_vtx[0].rhw = 1.0f;
	work_vtx[1].rhw = 1.0f;
	work_vtx[2].rhw = 1.0f;
	work_vtx[3].rhw = 1.0f;
	work_vtx[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	work_vtx[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	work_vtx[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	work_vtx[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	work_vtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	work_vtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	work_vtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	work_vtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	_vtx->Unlock();

	return S_OK;
}

//=============================================================================
// フェードの更新
//=============================================================================
void Fade::Update(void){

	if(_state == FADE_OUT){
		_value += FADE_LENGTH;
		if(_value >= 255){
			_value = 255;
			_state = FADE_NON;
		}
	}

	if(_state == FADE_IN){
		_value -= FADE_LENGTH;
		if(_value <= 0){
			_value = 0;
			_state = FADE_NON;
		}
	}

}

//=============================================================================
// フェードの描画
//=============================================================================
void Fade::Draw(void){
	VERTEX_2D *work_vtx = NULL;					//頂点情報先頭アドレス格納用
	LPDIRECT3DDEVICE9 device = NULL;

	if(_renderer == NULL || _vtx == NULL){return;}

	//頂点情報の取得
	_vtx->Lock(0, 0, (void**)&work_vtx, 0);					//他者からのアクセスやメモリ再配置をロックする

	//頂点情報の初期化
	work_vtx[0].diffuse = D3DCOLOR_RGBA(0, 0, 0, _value);
	work_vtx[1].diffuse = D3DCOLOR_RGBA(0, 0, 0, _value);
	work_vtx[2].diffuse = D3DCOLOR_RGBA(0, 0, 0, _value);
	work_vtx[3].diffuse = D3DCOLOR_RGBA(0, 0, 0, _value);

	_vtx->Unlock();


	//デバイスの取得
	device = _renderer->GetDevice();

	//フォグの状態取得
	DWORD def_fog = 0;
	device->GetRenderState(D3DRS_FOGENABLE, &def_fog);

	//フォグを消す
	device->SetRenderState(D3DRS_FOGENABLE, FALSE);

	device->SetVertexDeclaration(_decl);

	device->SetStreamSource(0, _vtx, 0, sizeof(VERTEX_2D));

	device->SetTexture(0, _texture);

	device->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

	device->SetRenderState(D3DRS_FOGENABLE, def_fog);
}

//=============================================================================
// フェードの終了処理
//=============================================================================
void Fade::Release(void){
	if(_texture != NULL){
		_texture->Release();
		_texture = NULL;
	}
	if(_vtx != NULL){
		_vtx->Release();
		_vtx = NULL;
	}
	if(_decl != NULL){
		_decl->Release();
		_decl = NULL;
	}
}


//=============================================================================
// フェードイン開始
//=============================================================================
void Fade::FadeIn(void){
	_state = FADE_IN;
}

//=============================================================================
// フェードアウト開始
//=============================================================================
void Fade::FadeOut(void){
	_state = FADE_OUT;
}

bool Fade::IsBlackOut(void){
	return (_value >= 255);
}