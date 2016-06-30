//*****************************************************************************
//  �X�L�����b�V���p���_�V�F�[�_
//  author: �������_
//  update: 2015/12/03
//*****************************************************************************
#include "vs_skin_mesh.h"
//*****************************************************************************
//�y�R���X�g���N�^�z
//  ���_�o�b�t�@NULL�l�߂Ȃ�
//  ����: �Ȃ�
//*****************************************************************************
VSSkinMesh::VSSkinMesh(Renderer *master_renderer):
VertexShader(master_renderer, "data/SHADER/skinmesh.hlsl", "VSSkinMesh"){
}

//*****************************************************************************
//�y�f�X�l�z
//  ���Ƃ����Â�
//  ����: �Ȃ�
//*****************************************************************************
VSSkinMesh::~VSSkinMesh(){
}

void VSSkinMesh::Set(void){
	VertexShader::Set();

	LPDIRECT3DDEVICE9 device = _renderer->GetDevice();

	_constant->SetMatrixArray(device, "_world_array", _world_array, Renderer::BONE_TABLE_MAX);

	D3DXMATRIX vp(_view * _projection);

	_constant->SetMatrix(device, "_vp", &vp);
}

//accessor
void VSSkinMesh::SetWorldArray(D3DXMATRIX* value, int length){
	if(value == nullptr){return;}

	memcpy(_world_array, value, sizeof(D3DXMATRIX) * length);
}
