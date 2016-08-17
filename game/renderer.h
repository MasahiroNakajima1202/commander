//*****************************************************************************
//  rebdererモジュール
//  DXの初期化や描画などを請け負う
//  author: 中島将浩
//  update: 2014/04/15
//*****************************************************************************
#ifndef _RENDERER_H_
#define _RENDERER_H_

#include "main.h"
#include "object.h"
#include "camera.h"


#include <d3dx9.h>
#define DIRECTINPUT_VERSION (0x0800)			//警告つぶし
#include "dinput.h"

//effekseer関連
//#include <Effekseer.h>
//#include <EffekseerRendererDX9.h>

//#define FVF_VERTEX_2D (D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)	//2Dテクスチャ設定
//#define	FVF_VERTEX_3D	(D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1)
//スキンメッシュ用の頂点フォーマット (頂点 / 3 weight / mtx index / normal / diffuse / tex coord)
//#define FVF_VERTEX_BLEND_3D (D3DFVF_XYZB4 | D3DFVF_LASTBETA_UBYTE4 | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1)

//*****************************************************************************
// struct
//*****************************************************************************
typedef struct
{
	D3DXVECTOR3 vtx;		// 頂点座標
	float rhw;				// テクスチャのパースペクティブコレクト用
	D3DCOLOR diffuse;		// 反射光
	D3DXVECTOR2 tex;		// テクスチャ座標
} VERTEX_2D;

typedef struct
{
	D3DXVECTOR3 vtx;		// 頂点座標
	D3DXVECTOR3 nor;		// 法線ベクトル
	D3DCOLOR diffuse;		// 反射光
	D3DXVECTOR2 tex;		// テクスチャ座標
} VERTEX_3D;

typedef struct
{
	D3DXVECTOR3 vtx;		// 頂点座標
	D3DXVECTOR3 nor;		// 法線ベクトル
	D3DXVECTOR2 tex;		// テクスチャ座標
} VERTEX_MESH;

struct VERTEX_BLEND_3D
{
    D3DXVECTOR3 vtx;		// 頂点座標
    float weight[3];		// 重み
    DWORD mtx_index;		// 頂点インデックス(下位バイトが若番)
    D3DXVECTOR3 nor;		// 法線ベクトル
	D3DCOLOR diffuse;		// 反射光
	D3DXVECTOR2 tex;		// テクスチャ座標
};

//*****************************************************************************
// ライブラリのリンク
//*****************************************************************************
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "dxguid.lib")


#if defined(DEBUG) || defined(_DEBUG)
#pragma comment(lib, "d3dx9d.lib")
#else
#pragma comment(lib, "d3dx9.lib")
#endif//_DEBUG

#pragma comment(lib, "dinput8.lib")

//effekseer関連
#pragma comment(lib, "Effekseer.lib")
#pragma comment(lib, "EffekseerRendererDX9.lib")

//*****************************************************************************
//  class
//*****************************************************************************
class GameInput;
class Light;
class Object;
class RenderTexture;
class VertexShader;
class PixelShader;
class Renderer{
public:
	//*****************************************************************************
	//【コンストラクタ】
	//  なにもしない。
	//  引数: なし
	//*****************************************************************************
	Renderer() :
		_cur_vs(nullptr),
		_cur_ps(nullptr),
		_light_direction(0.0f, 0.0f, 0.0f),
		_light_diffuse(0.0f, 0.0f, 0.0f, 0.0f),
		_light_position(0.0f, 0.0f, 0.0f),
		_point_light_ratio(0.0f){
		int i = 0;
		_D3D = nullptr;
		_device = nullptr;
		for(i=0; i<TEXTURE_MAX; i++){
			_texture[i] = nullptr;
			memset(_texture_name[i], '\0', 64);
		}
		memset(_mesh, 0, sizeof(MESH_SET) * MESH_MAX);
		for(i=0; i<MESH_MAX; i++){
			memset(_mesh[i].texture, -1, sizeof(int) * MAT_MAX);
		}

		for(i=0; i<Object::DRAW_LAYER_MAX; i++){
			_rendering_vs[i] = nullptr;
			_rendering_ps[i] = nullptr;
		}
	}

	//*****************************************************************************
	//【デス様】
	//  あとかたづけ
	//  引数: なし
	//*****************************************************************************
	virtual ~Renderer(){Release();}

	//*****************************************************************************
	//【初期化】
	//  DirectX9の初期化処理
	//  返り値: 初期化に成功したかどうか
	//  第1引数: HINSTANCE
	//  第2引数: ウィンドウハンドラ
	//  第3引数: ウィンドウモードのフラグ FALSEでフルスクリーン
	//*****************************************************************************
	HRESULT SetUp(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);

	//*****************************************************************************
	//【終了】
	//  DirectX9の終了処理
	//  返り値: なし
	//  引数: なし
	//*****************************************************************************
	void Release(void);

	//*****************************************************************************
	//【更新】
	//  DirectX9の更新処理
	//  返り値: なし
	//  引数: なし
	//*****************************************************************************
	void Update(void);

	//*****************************************************************************
	//【描画】
	//  DirectX9の描画処理 DXに関する描画マスター
	//  DirectXの描画機能を必要とするモジュールの描画メソッドはこの中で呼び出すことになる
	//  返り値: なし
	//  引数: なし
	//*****************************************************************************
	void Draw(bool swap = true, D3DCOLOR clear_color = D3DCOLOR_RGBA(16, 64, 144, 255));
	void DrawScreen(D3DCOLOR clear_color = D3DCOLOR_RGBA(16, 64, 144, 255));

	//*****************************************************************************
	//【テクスチャの読み込み】
	//  テクスチャ読み込み依頼 すでに存在している場合はそれを返す
	//  失敗時には-1を返す
	//  返り値: テクスチャID
	//  引数: ファイル名
	//*****************************************************************************
	int LoadTexture(const char *filename);

	//*****************************************************************************
	//【テクスチャの取得】
	//  テクスチャIDからテクスチャを返す
	//  返り値: テクスチャのアドレス
	//  引数: テクスチャID
	//*****************************************************************************
	LPDIRECT3DTEXTURE9 GetTexture(int texture_id);

	//*****************************************************************************
	//【全テクスチャの破棄】
	//  返り値: なし
	//  引数: なし
	//*****************************************************************************
	void ReleaseAllTexture(void);

	//メッシュ情報格納用
	static const int MAT_MAX = 32;
	struct MESH_SET{
		LPD3DXMESH mesh;									//メッシュ情報アドレス
		LPD3DXBUFFER mat_buff;								//マテリアル情報アドレス
		DWORD mat_num;										//マテリアルの数
		char filename[64];
		int texture[MAT_MAX];
	};
	//*****************************************************************************
	//【メッシュの読み込み】
	//  メッシュ読み込み依頼 すでに存在している場合はそれを返す
	//  失敗時には-1を返す
	//  返り値: メッシュID
	//  引数: ファイル名
	//*****************************************************************************
	int LoadMesh(const char *filename);

	//*****************************************************************************
	//【メッシュの取得】
	//  メッシュIDからテクスチャを返す
	//  返り値: メッシュセットのアドレス
	//  引数: メッシュID
	//*****************************************************************************
	MESH_SET *GetMesh(int mesh_id);

	//*****************************************************************************
	//【全メッシュの破棄】
	//  返り値: なし
	//  引数: なし
	//*****************************************************************************
	void ReleaseAllMesh(void);

	void DestroyLight(int index);							//ライトを潰す
	void DestroyAllLight(void);								//ライトをぜんぶ潰す

	void SetCurrentVertexShader(VertexShader* vs);
	void SetCurrentPixelShader(PixelShader* ps);
	void SetTextureToShader(int texture_id);
	void SetRenderTextureToShader(RenderTexture* texture);

	void SetCurrentShader(void);

	//シェーダープロパティ
	void SetMaterialDiffuse(D3DXVECTOR4 value);
	void SetWorld(D3DXMATRIX& value);
	void SetWorldArray(D3DXMATRIX* value, int length);
	void SetView(D3DXMATRIX& value);
	void SetProjection(D3DXMATRIX& value);
	void SetLightDirection(D3DXVECTOR3 direction);
	void SetLightDiffuse(D3DXVECTOR4 diffuse);
	void SetLightPosition(D3DXVECTOR3 position);
	void SetPointLightRatio(float ratio);

	D3DXMATRIX& GetView(void){return _view;}

	static const int BONE_TABLE_MAX = 52;

	//accessor
	LPDIRECT3DDEVICE9 GetDevice(void){return _device;}
	//Effekseer::Manager* GetEffekseerManager(void){return _effekseer_manager;}
	//EffekseerRenderer::Renderer* GetEffekseerRenderer(void){return _effekseer_renderer;}
private:
	int SearchFreeLightIndex(void);

	LPDIRECT3D9			_D3D;			// Direct3Dオブジェクト
	LPDIRECT3DDEVICE9	_device;		// Deviceオブジェクト(描画に必要)


	static const int TEXTURE_MAX = 64;
	LPDIRECT3DTEXTURE9 _texture[TEXTURE_MAX];
	char _texture_name[TEXTURE_MAX][64];

	LPDIRECT3DTEXTURE9 _white_texture;			//NULL時のテクスチャ
	
	static const int MESH_MAX = 64;
	MESH_SET _mesh[MESH_MAX];

	D3DXMATRIX _projection;
	D3DXMATRIX _view;
	D3DXMATRIX _world;
	D3DXVECTOR3 _light_direction;
	D3DXVECTOR4 _light_diffuse;
	D3DXVECTOR3 _light_position;
	float _point_light_ratio;

	//レンダーターゲット変更用テクスチャ

	VertexShader* _cur_vs;
	PixelShader* _cur_ps;

	VertexShader* _rendering_vs[Object::DRAW_LAYER_MAX];
	PixelShader* _rendering_ps[Object::DRAW_LAYER_MAX];

	static const int EFFEKSEER_SPRITE_MAX = 256;
	//EffekseerRenderer::Renderer* _effekseer_renderer;
	//Effekseer::Manager* _effekseer_manager;

	void ResetSamplerState(void);
};

#endif//_RENDERER_H_