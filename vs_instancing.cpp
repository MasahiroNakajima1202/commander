//*****************************************************************************
//  �C���X�^���V���O�p���_�V�F�[�_
//  author: �������_
//  update: 2016/03/09
//*****************************************************************************
#include "vs_instancing.h"

VSInstancing::VSInstancing(Renderer *master_renderer):
VertexShader(master_renderer, "data/SHADER/instancing.hlsl", "VSInstancing"){
}

VSInstancing::~VSInstancing(){
}

void VSInstancing::Set(void){
	VertexShader::Set();

	LPDIRECT3DDEVICE9 device = _renderer->GetDevice();

	D3DXMATRIX vp(_view * _projection);
	_constant->SetMatrix(device, "_vp", &vp);
}
