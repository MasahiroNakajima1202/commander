//*****************************************************************************
//  ピクセルシェーダ基底クラス
//  保持する定数レジスタはなし、テクスチャ情報のみを保持する
//  author: 中島将浩
//  update: 2015/06/08
//*****************************************************************************
#ifndef _PIXEL_SHADER_H_
#define _PIXEL_SHADER_H_

#include "main.h"
#include <d3dx9.h>

//*****************************************************************************
//  constant
//*****************************************************************************

//*****************************************************************************
//  class
//*****************************************************************************
class Renderer;
class PixelShader{
protected:
	PixelShader(){}
public:

	//*****************************************************************************
	//【コンストラクタ】
	//  頂点バッファNULL詰めなど
	//  引数: なし
	//*****************************************************************************
	PixelShader(Renderer *master_renderer, const char *filename, const char *name);

	//*****************************************************************************
	//【デス様】
	//  あとかたづけ
	//  引数: なし
	//*****************************************************************************
	virtual ~PixelShader();

	virtual void Set(void);

	//accessor
	void SetTexture(LPDIRECT3DTEXTURE9 value){_texture = value;}

	virtual void SetLightDirection(D3DXVECTOR3 value);
	virtual void SetLightDiffuse(D3DXVECTOR4 value);
	virtual void SetLightPosition(D3DXVECTOR3 value);
	virtual void SetPointLightRatio(float value);
protected:
	Renderer *_renderer;
	IDirect3DPixelShader9 *_shader;
	ID3DXConstantTable *_constant;

	//定数レジスタ用データ
	LPDIRECT3DTEXTURE9 _texture;

	D3DXVECTOR3 _light_direction;
	D3DXVECTOR4 _light_diffuse;
	D3DXVECTOR3 _light_position;
	float _point_light_ratio;

};

//accessor

#endif//_PIXEL_SHADER_H_