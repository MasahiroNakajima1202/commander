//*****************************************************************************
//  レンダーターゲット用のテクスチャクラス
//  author: 中島将浩
//  update: 2015/06/08
//*****************************************************************************

#include "render_texture.h"
#include "renderer.h"

//*****************************************************************************
//  constant
//*****************************************************************************

//*****************************************************************************
//【コンストラクタ】
//  頂点バッファNULL詰めなど
//  引数: なし
//*****************************************************************************
RenderTexture::RenderTexture(Renderer *master_renderer, int width, int height):
	_renderer(master_renderer),
	_texture(NULL),
	_surface(NULL),
	_zstencil(NULL),
	_def_surface(NULL),
	_def_zstencil(NULL),
	_width(width),
	_height(height){
	LPDIRECT3DDEVICE9 device = _renderer->GetDevice();

	//レンダーターゲット変更用テクスチャ
	device->CreateTexture(width, height, 1,
							 D3DUSAGE_RENDERTARGET,
							 D3DFMT_A8R8G8B8,
							 D3DPOOL_DEFAULT,
							 &_texture, NULL);
	_texture->GetSurfaceLevel(0, &_surface);
	device->CreateDepthStencilSurface(width, height,
										 D3DFMT_D24S8,
										 D3DMULTISAMPLE_NONE,
										 0,
										 TRUE,
										 &_zstencil,
										 NULL);

	_viewport.X = 0;
	_viewport.Y = 0;
	_viewport.Width = width;
	_viewport.Height = height;
	_viewport.MinZ = 0.0f;
	_viewport.MaxZ = 1.0f;
}

//*****************************************************************************
//【デス様】
//  あとかたづけ
//  引数: なし
//*****************************************************************************
RenderTexture::~RenderTexture(){
	if(_texture != NULL){
		_texture->Release();
		_texture = NULL;
	}
	if(_surface != NULL){
		_surface->Release();
		_surface = NULL;
	}
	if(_zstencil != NULL){
		_zstencil->Release();
		_zstencil = NULL;
	}
	if(_def_surface != NULL){
		_def_surface->Release();
		_def_surface = NULL;
	}
	if(_def_zstencil != NULL){
		_def_zstencil->Release();
		_def_zstencil = NULL;
	}
}

void RenderTexture::Set(void){
	LPDIRECT3DDEVICE9 device = _renderer->GetDevice();

	//バックバッファ退避
	device->GetRenderTarget(0, &_def_surface);
	device->GetDepthStencilSurface(&_def_zstencil);
	device->GetViewport(&_def_viewport);

	device->SetRenderTarget(0, _surface);
	device->SetDepthStencilSurface(_zstencil);
	device->SetViewport(&_viewport);
}
void RenderTexture::Reposit(void){
	LPDIRECT3DDEVICE9 device = _renderer->GetDevice();

	device->SetViewport(&_def_viewport);

	if(_def_surface != NULL){
		device->SetRenderTarget(0, _def_surface);
		_def_surface->Release();
		_def_surface = NULL;
	}
	if(_def_zstencil != NULL){
		device->SetDepthStencilSurface(_def_zstencil);
		_def_zstencil->Release();
		_def_zstencil = NULL;
	}
}

