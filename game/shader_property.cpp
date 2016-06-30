//*****************************************************************************
//  シェーダ用の変数保持クラス
//  author: 中島将浩
//  update: 2015/06/08
//*****************************************************************************
#include "shader_property.h"


D3DXMATRIX ShaderProperty::_world(	1.0f, 0.0f, 0.0f, 0.0f,
									0.0f, 1.0f, 0.0f, 0.0f,
									0.0f, 0.0f, 1.0f, 0.0f,
									0.0f, 0.0f, 0.0f, 1.0f);

D3DXMATRIX ShaderProperty::_view(	1.0f, 0.0f, 0.0f, 0.0f,
									0.0f, 1.0f, 0.0f, 0.0f,
									0.0f, 0.0f, 1.0f, 0.0f,
									0.0f, 0.0f, 0.0f, 1.0f);

D3DXMATRIX ShaderProperty::_projection(	1.0f, 0.0f, 0.0f, 0.0f,
										0.0f, 1.0f, 0.0f, 0.0f,
										0.0f, 0.0f, 1.0f, 0.0f,
										0.0f, 0.0f, 0.0f, 1.0f);

D3DXVECTOR3 ShaderProperty::_light_direction(0.0f, -1.0f, 0.0f);
D3DXVECTOR4 ShaderProperty::_light_diffuse(0.0f, 0.0f, 0.0f, 0.0f);
D3DXVECTOR4 ShaderProperty::_material_diffuse(0.0f, 0.0f, 0.0f, 0.0f);
