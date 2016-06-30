//*****************************************************************************
//  scene_billboardモジュール
//  author: 中島将浩
//  update: 2014/05/07
//*****************************************************************************


#include "object_billboard.h"
#include "renderer.h"

//*****************************************************************************
//  constant
//*****************************************************************************

//*****************************************************************************
//【コンストラクタ】
//  頂点バッファNULLつめつめなど
//  引数: なし
//*****************************************************************************
ObjectBillboard::ObjectBillboard(Renderer *master_renderer, int layer_no):
Object(master_renderer, layer_no),
_vtx(nullptr),
_texture_id(-1),
_decl(nullptr),
_scale(1.0f, 1.0f),
_offset(0.0f, 0.0f, 0.0f){
}


//*****************************************************************************
//【初期設定】
//  返り値: 設定に成功したかどうか
//  第1引数: 中心位置
//  第2引数: 横幅
//  第3引数: 縦幅
//  第4引数: テクスチャパス
//*****************************************************************************
HRESULT ObjectBillboard::SetUp(D3DXVECTOR3 pos, float width, float height, char *texture_filename){
	LPDIRECT3DDEVICE9 device = nullptr;		//デバイス取得用
	VERTEX_3D *work_vtx = nullptr;
	int i = 0;								//loop index

	device = _renderer->GetDevice();

	//頂点情報の設定
	if(FAILED(device->CreateVertexBuffer(sizeof(VERTEX_3D) * 4,
										 D3DUSAGE_WRITEONLY,
										 0,
										 D3DPOOL_MANAGED,
										 &_vtx,
										 nullptr))){
		return E_FAIL;
	}

	_vtx->Lock(0, 0, (void**)&work_vtx, 0);

	for(i=0; i<4; i++){
		work_vtx[i].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		work_vtx[i].nor = D3DXVECTOR3(0.0f, 0.0f, 1.0f);			//どうせ意味ないし……
	}
	work_vtx[0].vtx = D3DXVECTOR3(-0.5f,  0.5f, 0.0f);
	work_vtx[1].vtx = D3DXVECTOR3( 0.5f,  0.5f, 0.0f);
	work_vtx[2].vtx = D3DXVECTOR3(-0.5f, -0.5f, 0.0f);
	work_vtx[3].vtx = D3DXVECTOR3( 0.5f, -0.5f, 0.0f);
	work_vtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	work_vtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	work_vtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	work_vtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	_vtx->Unlock();

	_position = pos;
	_size.x = width;
	_size.y = height;
	_size.z = 0.0f;

	//テクスチャ登録
	_texture_id = _renderer->LoadTexture(texture_filename);

	//頂点要素の定義
	D3DVERTEXELEMENT9 v_ele[] = {
		{ 0, 0, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0 },
		{ 0, 12, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_NORMAL, 0 },
		{ 0, 24, D3DDECLTYPE_D3DCOLOR, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_COLOR, 0 },
		{ 0, 28, D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 0 },
		D3DDECL_END()
	};

	//declaration初期化
	if (FAILED(device->CreateVertexDeclaration(v_ele, &_decl))){
		return E_FAIL;
	}

	return S_OK;
}

//*****************************************************************************
//【終了】
//  返り値: なし
//  引数: なし
//*****************************************************************************
void ObjectBillboard::Release(void){
	if(_vtx != nullptr){
		_vtx->Release();
		_vtx = nullptr;
	}

	if (_decl != nullptr){
		_decl->Release();
		_decl = nullptr;
	}
}

//*****************************************************************************
//【更新】
//  返り値: なし
//  引数: なし
//*****************************************************************************
void ObjectBillboard::Update(void){
	Object::Update();
}

//*****************************************************************************
//【描画】
//  返り値: なし
//  引数: なし
//*****************************************************************************
void ObjectBillboard::Draw(void){
	D3DXMATRIX translate_mtx, scaling_mtx;
	LPDIRECT3DDEVICE9 device = nullptr;		//デバイス取得用
	D3DXMATRIX view_mtx;					//view inverseを仕込んでおくため
	D3DXMATRIX world;						//格納用ワールド行列
	int i = 0;								//loop index

	device = _renderer->GetDevice();

	D3DXMatrixIdentity(&world);					//ワールド行列をとりあえずEにする

	//scaling
	D3DXMatrixScaling(&scaling_mtx, _size.x * _scale.x, _size.y * _scale.y, 0.0f);
	D3DXMatrixMultiply(&world, &world, &scaling_mtx);

	//offset
	D3DXMatrixTranslation(&translate_mtx, _offset.x, _offset.y, _offset.z);
	D3DXMatrixMultiply(&world, &world, &translate_mtx);

	//カメラのviewの角度成分を殺す
	view_mtx = _renderer->GetView();
	D3DXMatrixInverse(&view_mtx, nullptr, &view_mtx);
	view_mtx._41 = 0.0f;
	view_mtx._42 = 0.0f;
	view_mtx._43 = 0.0f;
	D3DXMatrixMultiply(&world, &world, &view_mtx);

	//world._41 = 0.0f;
	//world._42 = 0.0f;
	//world._43 = 0.0f;

	//translation
	D3DXMatrixTranslation(&translate_mtx, _position.x, _position.y, _position.z);
	D3DXMatrixMultiply(&world, &world, &translate_mtx);

	_renderer->SetWorld(world);

	D3DXVECTOR4 diffuse(1.0f, 0.0f, 0.0f, 0.5f);
	_renderer->SetMaterialDiffuse(diffuse);

	device->SetVertexDeclaration(_decl);

	_renderer->SetTextureToShader(_texture_id);

	device->SetStreamSource(0, _vtx, 0, sizeof(VERTEX_3D));					//頂点バッファをデータストリームにバインド

	_renderer->SetCurrentShader();

	device->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);						//描画
}

//*****************************************************************************
//【頂点バッファのUV値設定】
//  返り値: なし
//  引数: なし
//*****************************************************************************
void ObjectBillboard::SetUV(float left, float top, float right, float bottom){
	VERTEX_3D *work_vtx = nullptr;

	_vtx->Lock(0, 0, (void**)&work_vtx, 0);

	work_vtx[0].tex = D3DXVECTOR2(left, top);
	work_vtx[1].tex = D3DXVECTOR2(right, top);
	work_vtx[2].tex = D3DXVECTOR2(left, bottom);
	work_vtx[3].tex = D3DXVECTOR2(right, bottom);

	_vtx->Unlock();
}

//accessor
