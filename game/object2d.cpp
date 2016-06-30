//*****************************************************************************
//  Objectモジュール
//  サンプルシーン
//  author: 中島将浩
//  update: 2014/04/15
//*****************************************************************************

#include "renderer.h"
#include "object2d.h"


//*****************************************************************************
//  constant
//*****************************************************************************
//*****************************************************************************
//【コンストラクタ】
//  頂点バッファNULL詰めなど
//  引数: なし
//*****************************************************************************
Object2D::Object2D(Renderer *master_renderer, int layer_no) : Object(master_renderer, layer_no){
	_vtx = NULL;
	_texture = -1;
	_offset = 0.0f;
	_scale = D3DXVECTOR2(1.0f, 1.0f);
	_pop_from = D3DXVECTOR2(0.0f, 0.0f);
	_pop_to = D3DXVECTOR2(1.0f, 1.0f);
	_pop_up = false;
	_pop_count = 0;
	_pop_length = 1;
}

//*****************************************************************************
//【初期化】
//  引数: なし
//*****************************************************************************
HRESULT Object2D::SetUp(float x, float y, float width, float height, char *filename){
	LPDIRECT3DDEVICE9 device = _renderer->GetDevice();

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

	VERTEX_2D *work_vtx = NULL;

	//頂点情報の初期化
	_vtx->Lock(0, 0, (void**)&work_vtx, 0);					//他者からのアクセスやメモリ再配置をロックする

	//頂点情報の書き換え
	work_vtx[0].vtx = D3DXVECTOR3(-0.5f, -0.5f, 0.0f);
	work_vtx[1].vtx = D3DXVECTOR3( 0.5f, -0.5f, 0.0f);
	work_vtx[2].vtx = D3DXVECTOR3(-0.5f,  0.5f, 0.0f);
	work_vtx[3].vtx = D3DXVECTOR3( 0.5f,  0.5f, 0.0f);
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

	_texture = _renderer->LoadTexture(filename);

	_position.x = x;
	_position.y = y;
	_size.x = width;
	_size.y = height;

	//頂点要素の定義
	D3DVERTEXELEMENT9 v_ele[] = {
		{0,  0, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0},
		{0, 16, D3DDECLTYPE_D3DCOLOR, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_COLOR, 0},
		{0, 20, D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 0},
		D3DDECL_END()
	};

	//declaration初期化
	if(FAILED(device->CreateVertexDeclaration(v_ele, &_decl))){
		return E_FAIL;
	}

	return S_OK;
}

//*****************************************************************************
//【終了】
//  返り値: なし
//  引数: なし
//*****************************************************************************
void Object2D::Release(void){
	if(_vtx != NULL){
		_vtx->Release();
		_vtx = NULL;
	}

	if(_decl != NULL){
		_decl->Release();
		_decl = NULL;
	}
}

//*****************************************************************************
//【更新】
//  返り値: なし
//  引数: なし
//*****************************************************************************
void Object2D::Update(void){
	if(_pop_up){
		float t((float)_pop_count / (float)_pop_length);

		_scale = (1.0f - t) * _pop_from + t * _pop_to;

		_pop_count++;
		if(_pop_count > _pop_length){
			_scale = _pop_to;
			_pop_up = false;
			_pop_count = 0;
		}
	}
}

//*****************************************************************************
//【描画】
//  返り値: なし
//  引数: なし
//*****************************************************************************
void Object2D::Draw(void){
	//renderer null check
	if(_renderer == NULL){return;}
	if(!_visible){return;}

	LPDIRECT3DDEVICE9 device = _renderer->GetDevice();
	D3DXMATRIX world_mtx, scaling_mtx, rotation_mtx, translate_mtx;

	//フォグの状態取得
	DWORD def_fog = 0;
	device->GetRenderState(D3DRS_FOGENABLE, &def_fog);

	device->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);				//背面カリングの設定

	//フォグを消す
	device->SetRenderState(D3DRS_FOGENABLE, FALSE);

	D3DXMatrixIdentity(&world_mtx);					//ワールド行列をとりあえずEにする

	D3DXMatrixScaling(&scaling_mtx, _size.x * _scale.x, _size.y * _scale.y, 0.0f);								//scaling
	D3DXMatrixMultiply(&world_mtx, &world_mtx, &scaling_mtx);

	D3DXMatrixRotationYawPitchRoll(&rotation_mtx, 0.0f, 0.0f, _rotation.z);	//rotation
	D3DXMatrixMultiply(&world_mtx, &world_mtx, &rotation_mtx);

	D3DXMatrixTranslation(&translate_mtx, _position.x, _position.y, 0.0f);				//translation
	D3DXMatrixMultiply(&world_mtx, &world_mtx, &translate_mtx);

	_renderer->SetWorld(world_mtx);

	device->SetVertexDeclaration(_decl);

	device->SetStreamSource(0, _vtx, 0, sizeof(VERTEX_2D));		//頂点バッファをデータストリームにバインド

	_renderer->SetTextureToShader(_texture);

	_renderer->SetCurrentShader();
		
	device->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);			//描画

	//フォグの復旧
	device->SetRenderState(D3DRS_FOGENABLE, def_fog);
}

void Object2D::SetAlpha(int value){
	VERTEX_2D *work_vtx = NULL;

	_vtx->Lock(0, 0, (void**)&work_vtx, 0);
	work_vtx[0].diffuse &= 0x00ffffff;
	work_vtx[1].diffuse &= 0x00ffffff;
	work_vtx[2].diffuse &= 0x00ffffff;
	work_vtx[3].diffuse &= 0x00ffffff;
	work_vtx[0].diffuse |= value << 24;
	work_vtx[1].diffuse |= value << 24;
	work_vtx[2].diffuse |= value << 24;
	work_vtx[3].diffuse |= value << 24;

	_vtx->Unlock();
}


void Object2D::SetV(float v0, float v1, float v2, float v3){
	VERTEX_2D *work_vtx = NULL;

	_vtx->Lock(0, 0, (void**)&work_vtx, 0);
	work_vtx[0].tex.y = v0;
	work_vtx[1].tex.y = v1;
	work_vtx[2].tex.y = v2;
	work_vtx[3].tex.y = v3;

	_vtx->Unlock();
}

void Object2D::PopUp(D3DXVECTOR2 from, D3DXVECTOR2 to, int frame_length){
	_pop_count = 0;
	_pop_length = frame_length;
	_pop_from = from;
	_pop_to = to;
	_pop_up = true;
	_scale = from;
}
