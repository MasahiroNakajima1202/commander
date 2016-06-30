//*****************************************************************************
//  2D用頂点シェーダ
//  author: 中島将浩
//  update: 2015/06/08
//*****************************************************************************
#include "vs2d.h"
#include "renderer.h"
//*****************************************************************************
//【コンストラクタ】
//  頂点バッファNULL詰めなど
//  引数: なし
//*****************************************************************************
VS2D::VS2D(Renderer *master_renderer):
VertexShader(master_renderer, "data/SHADER/shader2d.hlsl", "VS2D"){
	D3DXMatrixOrthoLH(&_projection,
		static_cast<float>(SCREEN_WIDTH),		//たて
		static_cast<float>(SCREEN_HEIGHT),		//よこ
		0.0f,									//near値
		1.0f);									//far値

	D3DXMATRIX offset;
	D3DXMatrixIdentity(&offset);
	offset._22 = -1.0f;
	offset._41 -= static_cast<float>(SCREEN_WIDTH / 2);
	offset._42 += static_cast<float>(SCREEN_HEIGHT / 2);

	D3DXMatrixMultiply(&_projection, &offset, &_projection);
}

//*****************************************************************************
//【デス様】
//  あとかたづけ
//  引数: なし
//*****************************************************************************
VS2D::~VS2D(){}

void VS2D::Set(void){
	LPDIRECT3DDEVICE9 device = _renderer->GetDevice();

	device->SetVertexShader(_shader);

	D3DXMATRIX wvp(_world * _projection);

	//wvpを設定
	_constant->SetMatrix(device, "_wvp", &wvp);

	//worldを設定
	_constant->SetMatrix(device, "_world", &_world);

}
