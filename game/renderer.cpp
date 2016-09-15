//*****************************************************************************
//  rebdererモジュール
//  author: 中島将浩
//  update: 2014/04/15
//*****************************************************************************

#include "renderer.h"
//#include "fade.h"
//#include "game_input.h"

#include "debug.h"
#include "render_texture.h"
#include "vertex_shader.h"
#include "pixel_shader.h"
#include "vs2d.h"
#include "ps2d.h"
#include "render_texture.h"
#include "vs_skin_mesh.h"
#include "vs_instancing.h"
//*****************************************************************************
//  constant
//*****************************************************************************


//*****************************************************************************
//  library link
//*****************************************************************************

//*****************************************************************************
//【初期化】
//  DirectX9の初期化処理
//  返り値: 初期化に成功したかどうか
//  第1引数: HINSTANCE
//  第2引数: ウィンドウハンドラ
//  第3引数: ウィンドウモードのフラグ FALSEでフルスクリーン
//*****************************************************************************
HRESULT Renderer::SetUp(HINSTANCE hInstance, HWND hWnd, BOOL bWindow){
	D3DPRESENT_PARAMETERS d3dpp;
    D3DDISPLAYMODE d3ddm;
	HRESULT hr = S_OK;
	int i = 0;					//loop index

	// Direct3Dオブジェクトの生成
	_D3D = Direct3DCreate9(D3D_SDK_VERSION);

	if(_D3D == nullptr)
	{
		return E_FAIL;
	}

	// 現在のディスプレイモードを取得
    if(FAILED(_D3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
	{
		return E_FAIL;
	}

	// デバイスのプレゼンテーションパラメータの設定
	ZeroMemory(&d3dpp, sizeof(d3dpp));							// ワークをゼロクリア
	d3dpp.BackBufferCount			= 1;						// バックバッファの数
	d3dpp.BackBufferWidth			= SCREEN_WIDTH;				// ゲーム画面サイズ(幅)
	d3dpp.BackBufferHeight			= SCREEN_HEIGHT;			// ゲーム画面サイズ(高さ)
	d3dpp.BackBufferFormat			= D3DFMT_UNKNOWN;			// バックバッファのフォーマットは現在設定されているものを使う
	d3dpp.SwapEffect				= D3DSWAPEFFECT_DISCARD;	// 映像信号に同期してフリップする
	d3dpp.Windowed					= bWindow;					// ウィンドウモード
	d3dpp.EnableAutoDepthStencil	= TRUE;						// デプスバッファ（Ｚバッファ）とステンシルバッファを作成
	d3dpp.AutoDepthStencilFormat	= D3DFMT_D24S8;				// デプスバッファとして16bitを使う

	if(bWindow)
	{// ウィンドウモード
		d3dpp.BackBufferFormat           = D3DFMT_UNKNOWN;					// バックバッファ
		d3dpp.FullScreen_RefreshRateInHz = 0;								// リフレッシュレート
		d3dpp.PresentationInterval       = D3DPRESENT_INTERVAL_IMMEDIATE;	// インターバル
	}
	else
	{// フルスクリーンモード
		d3dpp.BackBufferFormat           = D3DFMT_R5G6B5;					// バックバッファ
		d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;			// リフレッシュレート
		d3dpp.PresentationInterval       = D3DPRESENT_INTERVAL_DEFAULT;		// インターバル
	}

	// デバイスオブジェクトの生成
	// [デバイス作成制御]<描画>と<頂点処理>をハードウェアで行なう
	if(FAILED(_D3D->CreateDevice(D3DADAPTER_DEFAULT,						// ディスプレイアダプタ
									D3DDEVTYPE_HAL,							// ディスプレイタイプ
									hWnd,									// フォーカスするウインドウへのハンドル
									D3DCREATE_HARDWARE_VERTEXPROCESSING,		// デバイス作成制御の組み合わせ(ほんとはハードでやりたいけどスキンメッシュのために)
									&d3dpp,									// デバイスのプレゼンテーションパラメータ
									&_device)))						// デバイスインターフェースへのポインタ
	{
		// 上記の設定が失敗したら
		// [デバイス作成制御]<描画>をハードウェアで行い、<頂点処理>はCPUで行なう
		if(FAILED(_D3D->CreateDevice(D3DADAPTER_DEFAULT, 
										D3DDEVTYPE_HAL, 
										hWnd, 
										D3DCREATE_SOFTWARE_VERTEXPROCESSING, 
										&d3dpp,
										&_device)))
		{
			// 上記の設定が失敗したら
			// [デバイス作成制御]<描画>と<頂点処理>をCPUで行なう
			if(FAILED(_D3D->CreateDevice(D3DADAPTER_DEFAULT, 
											D3DDEVTYPE_REF,
											hWnd, 
											D3DCREATE_SOFTWARE_VERTEXPROCESSING, 
											&d3dpp,
											&_device)))
			{
				// 初期化失敗
				return E_FAIL;
			}
		}
	}

	

	ResetSamplerState();

	//フォグの設定
	float fog_start = 200.0f;
	float fog_end = 40000.0f;
	//D3DDevice->SetRenderState(D3DRS_FOGENABLE, TRUE);						//フォグをONに
	_device->SetRenderState(D3DRS_FOGCOLOR, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));	//フォグの色
	_device->SetRenderState(D3DRS_FOGVERTEXMODE, D3DFOG_LINEAR);			//頂点フォグ
	_device->SetRenderState(D3DRS_FOGTABLEMODE, D3DFOG_NONE);				//ピクセルフォグ
	_device->SetRenderState(D3DRS_FOGSTART, *(DWORD*)&fog_start);			//フォグ開始位置
	_device->SetRenderState(D3DRS_FOGEND, *(DWORD*)&fog_end);				//フォグ終了位置

	//D3DXCOLOR color(1.0f, 0.75f, 0.5f, 1.0f);
	D3DXCOLOR color(1.0f, 1.0f, 1.0f, 1.0f);

	for(i=0; i<TEXTURE_MAX; i++){
		_texture[i] = nullptr;
		memset(_texture_name[i], '\0', 64);
	}

	D3DXMatrixIdentity(&_view);
	D3DXMatrixIdentity(&_world);
	D3DXMatrixIdentity(&_projection);

	_light_position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);;
	_point_light_ratio = 0.0f;

	//テクスチャなしのときの白色テクスチャ
	D3DXCreateTextureFromFile(_device, "data/TEXTURE/white.png", &_white_texture);


	_rendering_vs[Object::DRAW_LAYER_FIELD]				= new VertexShader(this, "data/SHADER/half_lambert.hlsl", "VSHalfLambert");
	_rendering_ps[Object::DRAW_LAYER_FIELD]				= new PixelShader (this, "data/SHADER/half_lambert.hlsl", "PSLightTexture");
	_rendering_vs[Object::DRAW_LAYER_SHADOW]			= new VertexShader(this, "data/SHADER/half_lambert.hlsl", "VSHalfLambert");
	_rendering_ps[Object::DRAW_LAYER_SHADOW]			= new PixelShader (this, "data/SHADER/half_lambert.hlsl", "PSLightTexture");
	_rendering_vs[Object::DRAW_LAYER_SKIN_MESH]			= new VSSkinMesh  (this);
	_rendering_ps[Object::DRAW_LAYER_SKIN_MESH]			= new PixelShader (this, "data/SHADER/half_lambert.hlsl", "PSLightTexture");
	_rendering_vs[Object::DRAW_LAYER_MESH]				= new VertexShader(this, "data/SHADER/half_lambert.hlsl", "VSHalfLambert");
	_rendering_ps[Object::DRAW_LAYER_MESH]				= new PixelShader (this, "data/SHADER/half_lambert.hlsl", "PSLightTexture");
	_rendering_vs[Object::DRAW_LAYER_INSTANCING_MESH]	= new VSInstancing(this);
	_rendering_ps[Object::DRAW_LAYER_INSTANCING_MESH]	= new PixelShader (this, "data/SHADER/half_lambert.hlsl", "PSLightTexture");
	_rendering_vs[Object::DRAW_LAYER_ALPHA]				= new VertexShader(this, "data/SHADER/half_lambert.hlsl", "VSHalfLambert");
	_rendering_ps[Object::DRAW_LAYER_ALPHA]				= new PixelShader (this, "data/SHADER/half_lambert.hlsl", "PSLightTexture");
	_rendering_vs[Object::DRAW_LAYER_BILLBOARD]			= new VertexShader(this, "data/SHADER/billboard.hlsl", "VSBillboard");
	_rendering_ps[Object::DRAW_LAYER_BILLBOARD]			= new PixelShader (this, "data/SHADER/billboard.hlsl", "PSTexture");
	_rendering_vs[Object::DRAW_LAYER_2D]				= new VS2D(this);
	_rendering_ps[Object::DRAW_LAYER_2D]				= new PS2D(this);
	_rendering_vs[Object::DRAW_LAYER_FADE]				= new VS2D(this);
	_rendering_ps[Object::DRAW_LAYER_FADE]				= new PS2D(this);
	_rendering_vs[Object::DRAW_LAYER_SCREEN]			= new VS2D(this);
	_rendering_ps[Object::DRAW_LAYER_SCREEN]			= new PS2D(this);
	_rendering_vs[Object::DRAW_LAYER_EFFEKSEER]			= new VS2D(this);//effekseer先生の前にはシェーダーなどｺﾞﾐｸｽﾞ同然
	_rendering_ps[Object::DRAW_LAYER_EFFEKSEER]			= new PS2D(this);//これはただのダミーです
	_rendering_vs[Object::DRAW_LAYER_EFFEKSEER_2D]		= new VS2D(this);
	_rendering_ps[Object::DRAW_LAYER_EFFEKSEER_2D]		= new PS2D(this);


	//effekseer関連
	//_effekseer_renderer = nullptr;
	//_effekseer_manager = nullptr;
	//_effekseer_renderer = EffekseerRendererDX9::Renderer::Create(_device, EFFEKSEER_SPRITE_MAX);
	//_effekseer_manager = Effekseer::Manager::Create(EFFEKSEER_SPRITE_MAX);

	// 描画方法の指定、独自に拡張しない限り定形文です。
	//_effekseer_manager->SetSpriteRenderer(_effekseer_renderer->CreateSpriteRenderer());
	//_effekseer_manager->SetRibbonRenderer(_effekseer_renderer->CreateRibbonRenderer());
	//_effekseer_manager->SetRingRenderer(_effekseer_renderer->CreateRingRenderer());
	// テクスチャ画像の読込方法の指定(パッケージ等から読み込む場合拡張する必要があります。)
	//_effekseer_manager->SetTextureLoader(_effekseer_renderer->CreateTextureLoader() );
	// 座標系の指定(RHで右手系、LHで左手系)
	//_effekseer_manager->SetCoordinateSystem(Effekseer::CoordinateSystem::LH);

	//Effekseer::Matrix44 effekseer_proj;
	//Effekseer::Matrix44 effekseer_view;
	//for(int i = 0; i<16; i++){
	//	int row(i/4), line(i%4);
	//	effekseer_proj.Values[row][line] = _projection.m[row][line];
	//}
	//effekseer_view.Indentity();

	// 投影行列の更新
	//_effekseer_renderer->SetProjectionMatrix(effekseer_proj);
	// カメラ行列の更新
	//_effekseer_renderer->SetCameraMatrix(effekseer_view);

	
	return S_OK;
}

//*****************************************************************************
//【終了】
//  DirectX9の終了処理
//  返り値: なし
//  引数: なし
//*****************************************************************************
void Renderer::Release(void){
	//effekseer関連
	//if(_effekseer_manager != nullptr){
	//	_effekseer_manager->StopAllEffects();
	//	_effekseer_manager->Destroy();
	//	_effekseer_manager = nullptr;
	//}

	//if(_effekseer_renderer != nullptr){
	//	_effekseer_renderer->Destory();
	//	_effekseer_renderer = nullptr;
	//}
	
	//テクスチャ解放
	ReleaseAllTexture();
	ReleaseAllMesh();

	if(_D3D != nullptr){
		_D3D->Release();
		_D3D = nullptr;
	}
	if(_device != nullptr){
		_device->Release();
		_device = nullptr;
	}

	if(_white_texture != nullptr){
		_white_texture->Release();
		_white_texture = nullptr;
	}

	for (int i=0; i<Object::DRAW_LAYER_MAX; i++){
		if (_rendering_vs[i] != nullptr){
			delete _rendering_vs[i];
			_rendering_vs[i] = nullptr;
		}
		if (_rendering_ps[i] != nullptr){
			delete _rendering_ps[i];
			_rendering_ps[i] = nullptr;
		}
	}
}

//*****************************************************************************
//【更新】
//  DirectX9の更新処理
//  返り値: なし
//  引数: なし
//*****************************************************************************
void Renderer::Update(void){

	//effekseerにviewを通知
	//Effekseer::Matrix44 effekseer_proj;
	//Effekseer::Matrix44 effekseer_view;
	//for(int i = 0; i<16; i++){
	//	int row(i/4), line(i%4);
	//	effekseer_view.Values[row][line] = _view.m[row][line];
	//	effekseer_proj.Values[row][line] = _projection.m[row][line];
	//}

	// 投影行列の更新
	//_effekseer_renderer->SetProjectionMatrix(effekseer_proj);
	// カメラ行列の更新
	//_effekseer_renderer->SetCameraMatrix(effekseer_view);

	//_effekseer_manager->Update(1.0f);
}

//*****************************************************************************
//【描画】
//  DirectX9の描画処理 DXに関する描画マスター
//  DirectXの描画機能を必要とするモジュールの描画メソッドはこの中で呼び出すことになる
//  返り値: 初期化に成功したかどうか
//  引数: なし
//*****************************************************************************
void Renderer::Draw(bool swap, D3DCOLOR clear_color){

	_device->Clear(0, nullptr,
						(D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL),
						clear_color,
						1.0f, 0);
	if(SUCCEEDED(_device->BeginScene())){

		VertexShader* def_vs(_cur_vs);
		PixelShader* def_ps(_cur_ps);

		for (int i = 0; i<Object::DRAW_LAYER_SCREEN; i++){
			SetCurrentVertexShader(_rendering_vs[i]);
			SetCurrentPixelShader(_rendering_ps[i]);

			Object::DrawLayer(static_cast<Object::DRAW_LAYER>(i));
		}

		//_effekseer_renderer->BeginRendering();
		//Object::DrawLayer(Object::DRAW_LAYER::DRAW_LAYER_EFFEKSEER);
		//_effekseer_manager->Draw();
		//_effekseer_renderer->EndRendering();
		ResetSamplerState();

		SetCurrentVertexShader(_rendering_vs[Object::DRAW_LAYER_MESH]);
		SetCurrentPixelShader(_rendering_ps[Object::DRAW_LAYER_MESH]);
		Debug::Draw();

		_cur_vs = def_vs;
		_cur_ps = def_ps;
		
		_device->EndScene();
	}

	//バッファのスワップ
	if(swap){
		_device->Present(nullptr, nullptr, 0, nullptr);
	}
}
void Renderer::DrawScreen(D3DCOLOR clear_color){
	_device->Clear(0, nullptr,
		(D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL),
		clear_color,
		1.0f, 0);
	if (SUCCEEDED(_device->BeginScene())){

		VertexShader* def_vs(_cur_vs);
		PixelShader* def_ps(_cur_ps);

		SetCurrentVertexShader(_rendering_vs[Object::DRAW_LAYER_SCREEN]);
		SetCurrentPixelShader(_rendering_ps[Object::DRAW_LAYER_SCREEN]);

		_device->SetRenderState(D3DRS_ZENABLE, FALSE);						//Zバッファの設定

		Object::DrawLayer(static_cast<Object::DRAW_LAYER>(Object::DRAW_LAYER_SCREEN));
		
		_device->SetRenderState(D3DRS_ZENABLE, TRUE);						//Zバッファの設定

		//_effekseer_renderer->BeginRendering();
		//Object::DrawLayer(Object::DRAW_LAYER::DRAW_LAYER_EFFEKSEER_2D);
		//_effekseer_renderer->EndRendering();
		ResetSamplerState();

		_cur_vs = def_vs;
		_cur_ps = def_ps;

		_device->EndScene();
	}

	//バッファのスワップ
	_device->Present(nullptr, nullptr, 0, nullptr);
}


//*****************************************************************************
//【テクスチャの読み込み】
//  テクスチャ読み込み依頼 すでに存在している場合はそれを返す
//  失敗時には-1を返す
//  返り値: テクスチャID
//  引数: ファイル名
//*****************************************************************************
int Renderer::LoadTexture(const char *filename){
	int i = 0;						//loop index

	//null check
	if(filename == nullptr){return -1;}

	//同じ名前の奴がいないかどうかチェック
	for(i=0; i<TEXTURE_MAX; i++){
		if(strcmp(filename, _texture_name[i]) == 0){
			if(_texture[i] == nullptr){
				i = -1;
			}
			return i;
		}
	}

	//いないので、空きを探す
	for(i=0; i<TEXTURE_MAX; i++){
		if(_texture_name[i][0] == '\0'){
			break;
		}
	}

	strcpy(_texture_name[i], filename);
	D3DXCreateTextureFromFile(_device, filename, &_texture[i]);

	if(_texture[i] == nullptr){
		strcpy(_texture_name[i], "");
		i = -1;
	}

	return i;
}

//*****************************************************************************
//【テクスチャの取得】
//  テクスチャIDからテクスチャを返す
//  返り値: テクスチャのアドレス
//  引数: テクスチャID
//*****************************************************************************
LPDIRECT3DTEXTURE9 Renderer::GetTexture(int texture_id){
	//section check
	if(texture_id < 0 || TEXTURE_MAX <= texture_id){return nullptr;}

	return _texture[texture_id];
}

//*****************************************************************************
//【全テクスチャの破棄】
//  返り値: なし
//  引数: なし
//*****************************************************************************
void Renderer::ReleaseAllTexture(void){
	int i = 0;					//loop index

	for(i=0; i<TEXTURE_MAX; i++){
		if(_texture[i] != nullptr){
			_texture[i]->Release();
			_texture[i] = nullptr;
		}

		memset(_texture_name[i], '\0', 64);
	}
}

//*****************************************************************************
//【メッシュの読み込み】
//  メッシュ読み込み依頼 すでに存在している場合はそれを返す
//  失敗時には-1を返す
//  返り値: メッシュID
//  引数: ファイル名
//*****************************************************************************
int Renderer::LoadMesh(const char *filename){
	int i = 0, j = 0;						//loop index
	HRESULT hr = S_OK;

	LPD3DXBUFFER adjacency_buff = nullptr;								//隣接情報


	//null check
	if(filename == nullptr){return -1;}

	//同じ名前の奴がいないかどうかチェック
	for(i=0; i<MESH_MAX; i++){
		if(strcmp(filename, _mesh[i].filename) == 0){
			if(_mesh[i].mesh == nullptr){
				i = -1;
			}
			return i;
		}
	}

	//いないので、空きを探す
	for(i=0; i<MESH_MAX; i++){
		if(_mesh[i].filename[0] == '\0'){
			break;
		}
	}

	strcpy(_mesh[i].filename, filename);
	if(FAILED(D3DXLoadMeshFromX(filename,
								D3DXMESH_SYSTEMMEM,
								_device,
								&adjacency_buff,
								&_mesh[i].mat_buff,
								nullptr,
								&_mesh[i].mat_num,
								&_mesh[i].mesh))){
		return -1;
	}
	D3DXMATERIAL *mat = nullptr;
	mat = (D3DXMATERIAL*)_mesh[i].mat_buff->GetBufferPointer();
	int mut_num = _mesh[i].mat_num;
	for(j=0; j<mut_num; j++){
		//マテリアルに対応するテクスチャの読み込み
		_mesh[i].texture[j] = LoadTexture(mat[j].pTextureFilename);
	}

	if(_mesh[i].mesh == nullptr){
		strcpy(_mesh[i].filename, "");
		i = -1;
	}

	//optimaize
	hr = _mesh[i].mesh->OptimizeInplace(
		D3DXMESHOPT_COMPACT | D3DXMESHOPT_ATTRSORT | D3DXMESHOPT_VERTEXCACHE,
		(DWORD*)adjacency_buff->GetBufferPointer(),
		nullptr,
		nullptr,
		nullptr);

	if(adjacency_buff != nullptr){
		adjacency_buff->Release();
	}

	if(FAILED(hr)){
		return -1;
	}

	//頂点要素の定義
	D3DVERTEXELEMENT9 v_ele[] = {
		{0,  0, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0},
		{0, 12, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_NORMAL, 0},
		{0, 24, D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 0},
		D3DDECL_END()
	};

	//コンバート
	LPD3DXMESH old_mesh = _mesh[i].mesh;
	hr = old_mesh->CloneMesh(D3DXMESH_MANAGED, v_ele, _device, &_mesh[i].mesh);

	//コンバート前のやつを潰す
	old_mesh->Release();

	if(FAILED(hr)){
		return -1;
	}

	//いちおうこんなのもあるよ！FVFでも参照して読んでみてもいい
	//D3DXComputeNormals(mesh[i].mesh, nullptr);


	return i;
}

//*****************************************************************************
//【メッシュの取得】
//  メッシュIDからテクスチャを返す
//  返り値: メッシュセットのアドレス
//  引数: メッシュID
//*****************************************************************************
Renderer::MESH_SET* Renderer::GetMesh(int mesh_id){
	//section check
	if(mesh_id < 0 || MESH_MAX <= mesh_id){return nullptr;}

	return &_mesh[mesh_id];
}

//*****************************************************************************
//【全メッシュの破棄】
//  返り値: なし
//  引数: なし
//*****************************************************************************
void Renderer::ReleaseAllMesh(void){
	int i = 0;					//loop index

	for(i=0; i<MESH_MAX; i++){
		if(_mesh[i].mesh != nullptr){
			_mesh[i].mesh->Release();
			_mesh[i].mesh = nullptr;
		}

		if(_mesh[i].mat_buff != nullptr){
			_mesh[i].mat_buff->Release();
			_mesh[i].mat_buff = nullptr;
		}

		memset(_mesh[i].filename, '\0', 64);
		memset(_mesh[i].texture, -1, MAT_MAX);
		_mesh[i].mat_num = 0;
	}
}




void Renderer::SetCurrentVertexShader(VertexShader* vs){
	_cur_vs = vs;
}
void Renderer::SetCurrentPixelShader(PixelShader* ps){
	_cur_ps = ps;
}


void Renderer::SetTextureToShader(int texture_id){
	if(_cur_ps == nullptr){return;}
	LPDIRECT3DTEXTURE9 work(nullptr);
	if(texture_id < 0 || TEXTURE_MAX <= texture_id){
		work = nullptr;
	}
	else{
		work = _texture[texture_id];
	}

	if(work == nullptr){
		work = _white_texture;
	}

	_cur_ps->SetTexture(work);
}

void Renderer::SetRenderTextureToShader(RenderTexture* texture){
	if (_cur_ps == nullptr){ return; }
	LPDIRECT3DTEXTURE9 work(texture->GetTexture());

	if (work == nullptr){
		work = _white_texture;
	}

	_cur_ps->SetTexture(work);
}

void Renderer::SetCurrentShader(void){
	if(_cur_vs != nullptr){
		_cur_vs->SetWorld(&_world);
		_cur_vs->SetView(&_view);
		_cur_vs->SetProjection(&_projection);
		_cur_vs->SetLightDirection(_light_direction);
		_cur_vs->SetLightDiffuse(_light_diffuse);
		_cur_vs->Set();
	}

	if(_cur_ps != nullptr){
		_cur_ps->SetLightDirection(_light_direction);
		_cur_ps->SetLightDiffuse(_light_diffuse);
		_cur_ps->SetLightPosition(_light_position);
		_cur_ps->SetPointLightRatio(_point_light_ratio);
		_cur_ps->Set();
	}
}

void Renderer::SetMaterialDiffuse(D3DXVECTOR4 value){
	if(_cur_vs == nullptr){return;}

	_cur_vs->SetMaterialDiffuse(value);
}


void Renderer::SetWorld(D3DXMATRIX& value){
	_world = value;

	if(_cur_vs == nullptr){ return; }
	_cur_vs->SetWorld(&value);
}

void Renderer::SetWorldArray(D3DXMATRIX* value, int length){
	if (_cur_vs == nullptr){ return; }
	_cur_vs->SetWorldArray(value, length);
}


void Renderer::SetView(D3DXMATRIX& value){
	_view = value;

	if(_cur_vs == nullptr){ return; }
	_cur_vs->SetView(&value);
}

void Renderer::SetProjection(D3DXMATRIX& value){
	_projection = value;

	if(_cur_vs == nullptr){ return; }
	_cur_vs->SetProjection(&value);
}

void Renderer::SetLightDiffuse(D3DXVECTOR4 diffuse){
	_light_diffuse = diffuse;

	if (_cur_vs != nullptr){
		_cur_vs->SetLightDiffuse(diffuse);
	}

	if (_cur_ps != nullptr){
		_cur_ps->SetLightDiffuse(diffuse);
	}
}

void Renderer::SetLightDirection(D3DXVECTOR3 direction){
	_light_direction = direction;

	if (_cur_vs != nullptr){
		_cur_vs->SetLightDirection(direction);
	}

	if (_cur_ps != nullptr){
		_cur_ps->SetLightDirection(direction);
	}
}

void Renderer::SetLightPosition(D3DXVECTOR3 position){
	_light_position = position;

	if (_cur_ps == nullptr){ return; }
	_cur_ps->SetLightPosition(position);
}
void Renderer::SetPointLightRatio(float ratio){
	_point_light_ratio = ratio;

	if (_cur_ps == nullptr){ return; }
	_cur_ps->SetPointLightRatio(ratio);
}

void Renderer::ResetSamplerState(void){
	//レンダーステートの設定
	_device->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);				//背面カリングの設定
	_device->SetRenderState(D3DRS_ZENABLE, TRUE);						//Zバッファの設定
	_device->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);			//αブレンドの設定
	_device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);		//描画元のα値の設定
	_device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);	//描画先のα値の設定

	for(int i=0; i<4; i++){
		//サンプラーステートの設定
		_device->SetSamplerState(i, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);	//テクスチャの繰り返し設定
		_device->SetSamplerState(i, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);
		_device->SetSamplerState(i, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);		//テクスチャ拡縮時の補完設定
		_device->SetSamplerState(i, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
		_device->SetSamplerState(i, D3DSAMP_MIPFILTER, D3DTEXF_NONE);

	}

	_device->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);	//αオペレーション 混ぜ合わせの設定
	_device->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);	//テクスチャから
	_device->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_CURRENT);	//現在描画されているものから

}
