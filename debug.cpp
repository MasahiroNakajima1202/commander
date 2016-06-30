//*****************************************************************************
//  debugモジュール
//  author: 中島将浩
//  update: 2014/05/13
//*****************************************************************************

#include "debug.h"
#include "renderer.h"
#include "stdio.h"

//*****************************************************************************
//  sttic variables
//*****************************************************************************
Renderer *Debug::renderer = NULL;
char Debug::buffer[BUFFER_MAX] = {};
LPD3DXFONT Debug::font = NULL;					// フォントへのポインタ

LPDIRECT3DVERTEXBUFFER9 Debug::vtx = NULL;			//頂点バッファのポインタ
int Debug::texture_index = -1;
Debug::HIT_VIEW Debug::hit_view[HIT_VIEW_MAX] = {};
D3DXMATRIX Debug::camera_view;

//*****************************************************************************
//【初期化】
//  バッファクリア
//  返り値: 初期化に成功したかどうか
//  引数: なし
//*****************************************************************************
HRESULT Debug::SetUp(void){
	LPDIRECT3DDEVICE9 device = renderer->GetDevice();
	VERTEX_3D *work_vtx = NULL;
	
	memset(buffer, 0, BUFFER_MAX);

	// 情報表示用フォントを設定
	if(FAILED(D3DXCreateFont(device, 18, 0, 0, 0, FALSE, SHIFTJIS_CHARSET,
		OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, "Terminal", &font))){
			return E_FAIL;
	}

	LoadHitView();




	return S_OK;
}

//*****************************************************************************
//【終了】
//  返り値: なし
//  引数: なし
//*****************************************************************************
void Debug::Release(void){
	memset(buffer, 0, BUFFER_MAX);

	if(font != NULL){
		font->Release();
		font = NULL;
	}

	ReleaseHitView();
}

//*****************************************************************************
//【出力】
//  返り値: なし
//  第1引数: 文字列
//  第2引数: 可変長引数
//*****************************************************************************
void Debug::Print(char* format, ...){
#ifdef _DEBUG
	va_list list;
	char work[256] = {};

	va_start(list, format);

	vsprintf(work, format, list);

	strcat(buffer, work);
	va_end(list);
#endif
}

//*****************************************************************************
//【描画】
//  返り値: なし
//  引数: なし
//*****************************************************************************
void Debug::Draw(void){
#ifdef _DEBUG
	RECT rect = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
	int i = 0;				//loop index
	D3DXMATRIX translate_mtx, scale_mtx;
	LPDIRECT3DDEVICE9 device = NULL;		//デバイス取得用
	D3DXMATRIX view_mtx;					//view inverseを仕込んでおくため
	D3DXMATRIX world;						//格納用ワールド行列

#ifdef _DEBUG_HIT_DRAW_

	device = renderer->GetDevice();

	//ビルボードはライトを切る！！！！！
	device->SetRenderState(D3DRS_LIGHTING, FALSE);

	//レンダーステートでαテストをONに
	device->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	device->SetRenderState(D3DRS_ALPHAREF, 32);
	device->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	//カメラのviewを殺す
	view_mtx = camera_view;
	D3DXMatrixInverse(&view_mtx, NULL, &view_mtx);

	device->SetFVF(FVF_VERTEX_3D);										//頂点描画形式の指定
	device->SetStreamSource(0, vtx, 0, sizeof(VERTEX_3D));				//頂点バッファをデータストリームにバインド
	device->SetTexture(0, renderer->GetTexture(texture_index));			//これから描画するテクスチャのセット


	//hit view
	for(i=0; i<HIT_VIEW_MAX; i++){
		//いないやつは飛ばす
		if(!hit_view[i].flag){continue;}

		//world初期化
		D3DXMatrixIdentity(&world);					//ワールド行列をとりあえずEにする

		//scaling
		D3DXMatrixScaling(&scale_mtx, hit_view[i].radius, hit_view[i].radius, 1.0f);
		D3DXMatrixMultiply(&world, &world, &scale_mtx);

		D3DXMatrixMultiply(&world, &world, &view_mtx);

		world._41 = 0.0f;
		world._42 = 0.0f;
		world._43 = 0.0f;

		//translation
		D3DXMatrixTranslation(&translate_mtx, hit_view[i].position.x, hit_view[i].position.y, hit_view[i].position.z);
		D3DXMatrixMultiply(&world, &world, &translate_mtx);

		device->SetTransform(D3DTS_WORLD, &world);

		device->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);					//描画

		hit_view[i].flag = false;
	}


	//あ、ライトまたつけなきゃ
	device->SetRenderState(D3DRS_LIGHTING, TRUE);

	//レンダーステート復旧
	device->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);

#endif

	if(font != NULL){

		// テキスト描画
		font->DrawText(NULL, buffer, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));

	}
	memset(buffer, 0, BUFFER_MAX);
#endif
}


void Debug::LoadHitView(void){
	LPDIRECT3DDEVICE9 device = NULL;		//デバイス取得用
	VERTEX_3D *work_vtx = NULL;
	int i = 0;								//loop index

	device = renderer->GetDevice();

	//頂点情報の設定
	if(FAILED(device->CreateVertexBuffer(sizeof(VERTEX_3D) * 4,
										 D3DUSAGE_WRITEONLY,
										 0,
										 D3DPOOL_MANAGED,
										 &vtx,
										 NULL))){
		return;
	}

	vtx->Lock(0, 0, (void**)&work_vtx, 0);

	for(i=0; i<4; i++){
		work_vtx[i].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		work_vtx[i].nor = D3DXVECTOR3(0.0f, 0.0f, 1.0f);			//どうせ意味ないし……
	}
	work_vtx[0].vtx = D3DXVECTOR3(-1.0f/2.0f,  1.0f/2.0f, 0.0f);
	work_vtx[1].vtx = D3DXVECTOR3( 1.0f/2.0f,  1.0f/2.0f, 0.0f);
	work_vtx[2].vtx = D3DXVECTOR3(-1.0f/2.0f, -1.0f/2.0f, 0.0f);
	work_vtx[3].vtx = D3DXVECTOR3( 1.0f/2.0f, -1.0f/2.0f, 0.0f);
	work_vtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	work_vtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	work_vtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	work_vtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	vtx->Unlock();

	//テクスチャ登録
	texture_index = renderer->LoadTexture("data/TEXTURE/flare03.png");
}
void Debug::ReleaseHitView(void){
	if(vtx != NULL){
		vtx->Release();
		vtx = NULL;
	}
}

void Debug::EntryHitView(D3DXVECTOR3 pos, float radius){
	int i = 0;				//loop index
#ifdef _DEBUG_HIT_DRAW_

	for(i=0; i<HIT_VIEW_MAX; i++){
		if(!hit_view[i].flag){
			hit_view[i].position = pos;
			hit_view[i].radius = radius;
			hit_view[i].flag = true;
			break;
		}
	}
#endif
}
