//*****************************************************************************
//  レンダーターゲット用のテクスチャクラス
//  author: 中島将浩
//  update: 2015/06/08
//*****************************************************************************
#ifndef _RENDER_TARGET_H_
#define _RENDER_TARGET_H_

#include "main.h"
#include <d3dx9.h>

//*****************************************************************************
//  constant
//*****************************************************************************

//*****************************************************************************
//  class
//*****************************************************************************
class Renderer;
class RenderTexture{
private:
	RenderTexture(){}
public:

	//*****************************************************************************
	//【コンストラクタ】
	//  頂点バッファNULL詰めなど
	//  引数: なし
	//*****************************************************************************
	RenderTexture(Renderer *master_renderer, int width, int height);

	//*****************************************************************************
	//【デス様】
	//  あとかたづけ
	//  引数: なし
	//*****************************************************************************
	virtual ~RenderTexture();

	//*****************************************************************************
	//【更新】
	//  返り値: なし
	//  引数: なし
	//*****************************************************************************
	//virtual void Update(void);

	void Set(void);				//テクスチャをレンダーターゲットに設定
	void Reposit(void);			//もどす

	LPDIRECT3DTEXTURE9 GetTexture(void){return _texture;}

	//accessor
protected:
	Renderer *_renderer;

	LPDIRECT3DTEXTURE9 _texture;
	IDirect3DSurface9 *_surface;
	IDirect3DSurface9 *_zstencil;

	IDirect3DSurface9 *_def_surface;
	IDirect3DSurface9 *_def_zstencil;

	int _width;
	int _height;

	D3DVIEWPORT9 _viewport;
	D3DVIEWPORT9 _def_viewport;
};

//accessor

#endif//_SCENE_X_H_