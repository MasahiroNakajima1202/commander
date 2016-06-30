//*****************************************************************************
//  numberモジュール
//  サンプルシーン
//  author: 中島将浩
//  update: 2014/06/18
//*****************************************************************************

#include "number.h"
#include "renderer.h"

//*****************************************************************************
//  static variables
//*****************************************************************************


//*****************************************************************************
//【コンストラクタ】
//  頂点バッファNULL詰めなど
//  引数: なし
//*****************************************************************************
Number::Number(Renderer *master_renderer){
	_renderer = master_renderer;
	_texture_index = -1;
	_vtx = NULL;
	_x = 0.0f;
	_y = 0.0f;
	_align = ALIGN_LEFT;
	_value = 0;
}

//*****************************************************************************
//【デス様】
//  あとかたづけ
//  引数: なし
//*****************************************************************************
Number::~Number(){
	Release();
}

//*****************************************************************************
//【初期化】
//  返り値: 初期化に成功したかどうか
//  引数: なし
//*****************************************************************************
HRESULT Number::SetUp(float x, float y, float width, float height, ALIGN align){
	LPDIRECT3DDEVICE9 device = NULL;			//デバイス取得用
	VERTEX_2D *work_vtx = NULL;					//頂点情報先頭アドレス格納用
	float x_align = 0.0f;

	x_align = -width + (float)align * width * 0.5f;

	//デバイスの取得
	device = _renderer->GetDevice();

	//頂点確保
	if(FAILED(device->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
										  D3DUSAGE_WRITEONLY,
										  0,
										  D3DPOOL_MANAGED,
										  &_vtx,
										  NULL))){
		_vtx = NULL;
		return E_FAIL;
	}

	_vtx->Lock(0, 0, (void**)&work_vtx, 0);					//他者からのアクセスやメモリ再配置をロックする

	//頂点情報の書き換え ここから
	work_vtx[0].vtx = D3DXVECTOR3(x + x_align			, y - height/2.0f, 0.0f);
	work_vtx[1].vtx = D3DXVECTOR3(x + x_align + width	, y - height/2.0f, 0.0f);
	work_vtx[2].vtx = D3DXVECTOR3(x + x_align			, y + height/2.0f, 0.0f);
	work_vtx[3].vtx = D3DXVECTOR3(x + x_align + width	, y + height/2.0f, 0.0f);
	work_vtx[0].rhw = 1.0f;
	work_vtx[1].rhw = 1.0f;
	work_vtx[2].rhw = 1.0f;
	work_vtx[3].rhw = 1.0f;
	work_vtx[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	work_vtx[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	work_vtx[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	work_vtx[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	work_vtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	work_vtx[1].tex = D3DXVECTOR2(0.1f, 0.0f);
	work_vtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	work_vtx[3].tex = D3DXVECTOR2(0.1f, 1.0f);

	_vtx->Unlock();

	_texture_index = _renderer->LoadTexture("data/TEXTURE/number.png");

	this->_x = x;
	this->_y = y;
	this->_align = align;
	this->_width = width;
	this->_height = height;

	return S_OK;
}

//*****************************************************************************
//【終了】
//  返り値: なし
//  引数: なし
//*****************************************************************************
void Number::Release(void){
	_x = 0.0f;
	_y = 0.0f;

	if(_vtx != NULL){
		_vtx->Release();
		_vtx = NULL;
	}
}

//*****************************************************************************
//【更新】
//  返り値: なし
//  引数: なし
//*****************************************************************************
void Number::Update(void){
}

//*****************************************************************************
//【描画】
//  返り値: なし
//  引数: なし
//*****************************************************************************
void Number::Draw(void){
	//renderer null check
	if(_renderer == NULL){return;}

	//LPDIRECT3DDEVICE9 device = _renderer->GetDevice();

	//device->SetFVF(FVF_VERTEX_2D);								//頂点描画形式の指定

	//device->SetStreamSource(0, vtx, 0, sizeof(VERTEX_2D));		//頂点バッファをデータストリームにバインド

	//device->SetTexture(0, renderer->GetTexture(texture_index));								//テクスチャのセット
	//	
	//device->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);			//描画
}
void Number::Draw(float x, float y){
	SetPosition(x, y);
	Draw();
}

//accessor
void Number::SetPosition(float x, float y){
	VERTEX_2D *work_vtx = NULL;					//頂点情報先頭アドレス格納用
	float x_align = 0.0f;

	if(this->_x == x && this->_y == y){return;}

	this->_x = x;
	this->_y = y;

	x_align = -_width + (float)_align * _width * 0.5f;

	_vtx->Lock(0, 0, (void**)&work_vtx, 0);					//他者からのアクセスやメモリ再配置をロックする

	//頂点情報の書き換え ここから
	work_vtx[0].vtx = D3DXVECTOR3(x + x_align			, y - _height/2.0f, 0.0f);
	work_vtx[1].vtx = D3DXVECTOR3(x + x_align + _width	, y - _height/2.0f, 0.0f);
	work_vtx[2].vtx = D3DXVECTOR3(x + x_align			, y + _height/2.0f, 0.0f);
	work_vtx[3].vtx = D3DXVECTOR3(x + x_align + _width	, y + _height/2.0f, 0.0f);

	_vtx->Unlock();
}
void Number::SetValue(int value){
	if(this->_value == value){return;}

	VERTEX_2D *work_vtx = NULL;						//頂点情報先頭アドレス格納用
	float left = 0.0f;

	this->_value = value;

	left = 0.1f * (float)value;

	_vtx->Lock(0, 0, (void**)&work_vtx, 0);			//他者からのアクセスやメモリ再配置をロックする

	//頂点情報の書き換え ここから
	work_vtx[0].tex = D3DXVECTOR2(left			, 0.0f);
	work_vtx[1].tex = D3DXVECTOR2(left + 0.1f	, 0.0f);
	work_vtx[2].tex = D3DXVECTOR2(left			, 1.0f);
	work_vtx[3].tex = D3DXVECTOR2(left + 0.1f	, 1.0f);

	_vtx->Unlock();
}
