//*****************************************************************************
//  頂点シェーダ基底クラス 単純なランバートをサポートします
//  author: 中島将浩
//  update: 2015/06/08
//*****************************************************************************

#include "pixel_shader.h"
#include "renderer.h"

//*****************************************************************************
//  constant
//*****************************************************************************


//*****************************************************************************
//【コンストラクタ】
//  頂点バッファNULL詰めなど
//  引数: なし
//*****************************************************************************
PixelShader::PixelShader(Renderer *master_renderer, const char *filename, const char *name) :
_renderer(master_renderer),
_shader(NULL),
_constant(NULL),
_texture(NULL),
_light_direction(0.0f, 0.0f, 0.0f),
_light_diffuse(1.0f, 1.0f, 1.0f, 1.0f),
_light_position(0.0f, 0.0f, 0.0f),
_point_light_ratio(0.0f){
	LPDIRECT3DDEVICE9 device = _renderer->GetDevice();

	//シェーダの読み込み
	LPD3DXBUFFER code = NULL;
	LPD3DXBUFFER error = NULL;

	HRESULT hr = D3DXCompileShaderFromFile(filename, NULL, NULL, name, "ps_3_0", 0, &code, &error, &_constant);

	if(FAILED(hr)){
		MessageBox(NULL, (LPSTR)error->GetBufferPointer(), "error", MB_OK);
	}

	device->CreatePixelShader((DWORD*)code->GetBufferPointer(), &_shader);

	if(error != NULL){
		error->Release();
		error = NULL;
	}
	if(code != NULL){
		code->Release();
		code = NULL;
	}
}

//*****************************************************************************
//【デス様】
//  あとかたづけ
//  引数: なし
//*****************************************************************************
PixelShader::~PixelShader(){
	if(_shader != NULL){
		_shader->Release();
		_shader = NULL;
	}
	if(_constant != NULL){
		_constant->Release();
		_constant = NULL;
	}
}

void PixelShader::Set(void){
	LPDIRECT3DDEVICE9 device = _renderer->GetDevice();

	device->SetPixelShader(_shader);

	//テクスチャを設定
	int index(_constant->GetSamplerIndex("_tex_sampler1"));
	if(0 <= index && index < 32){
		device->SetTexture(index, _texture);
	}

	_constant->SetFloatArray(device, "_light_direction", (float*)&_light_direction, 3);
	_constant->SetFloatArray(device, "_light_diffuse", (float*)&_light_diffuse, 4);
	_constant->SetFloatArray(device, "_light_position", (float*)&_light_position, 3);
	_constant->SetFloat(device, "_point_light_ratio", _point_light_ratio);

}


void PixelShader::SetLightDirection(D3DXVECTOR3 value){
	_light_direction = value;
}
void PixelShader::SetLightDiffuse(D3DXVECTOR4 value){
	_light_diffuse = value;
}
void PixelShader::SetLightPosition(D3DXVECTOR3 value){
	_light_position = value;
}
void PixelShader::SetPointLightRatio(float value){
	_point_light_ratio = value;
}
