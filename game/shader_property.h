//*****************************************************************************
//  シェーダ用の変数保持クラス
//  author: 中島将浩
//  update: 2015/06/08
//*****************************************************************************
#ifndef _SHADER_PROPERTY_H_
#define _SHADER_PROPERTY_H_

#include "main.h"
#include <d3dx9.h>

//*****************************************************************************
//  constant
//*****************************************************************************

//*****************************************************************************
//  class
//*****************************************************************************
class Renderer;
class ShaderProperty{
private:
	ShaderProperty(){}
public:

	//*****************************************************************************
	//【デス様】
	//  あとかたづけ
	//  引数: なし
	//*****************************************************************************
	virtual ~ShaderProperty();

	//accessor
	static void SetWorld(D3DXMATRIX* value){_world = *value;}
	static void SetView(D3DXMATRIX* value){_view = *value;}
	static void SetProjection(D3DXMATRIX* value){_projection = *value;}
	static void SetLightDirection(D3DXVECTOR3 value){_light_direction = value;}
	static void SetLightDiffuse(D3DXVECTOR4 value){_light_diffuse = value;}
	static void SetMaterialDiffuse(D3DXVECTOR4 value){_material_diffuse = value;}


	static D3DXMATRIX* GetWorld(void){return &_world;}
	static D3DXMATRIX* GetView(void){return &_view;}
	static D3DXMATRIX* GetProjection(void){return &_projection;}
	static D3DXVECTOR3 GetLightDirection(void){return _light_direction;}
	static D3DXVECTOR4 GetLightDiffuse(void){return _light_diffuse;}
	static D3DXVECTOR4 GetMaterialDiffuse(void){return _material_diffuse;}

private:
	static D3DXMATRIX _world;
	static D3DXMATRIX _view;
	static D3DXMATRIX _projection;
	static D3DXVECTOR3 _light_direction;
	static D3DXVECTOR4 _light_diffuse;
	static D3DXVECTOR4 _material_diffuse;
};

//accessor

#endif//_VERTEX_SHADER_H_