//*****************************************************************************
//  スキンメッシュ用頂点シェーダ
//  author: 中島将浩
//  update: 2015/12/03
//*****************************************************************************
#include "vs_skin_mesh.h"
//*****************************************************************************
//【コンストラクタ】
//  頂点バッファNULL詰めなど
//  引数: なし
//*****************************************************************************
VSSkinMesh::VSSkinMesh(Renderer *master_renderer):
VertexShader(master_renderer, "data/SHADER/skinmesh.hlsl", "VSSkinMesh"){
}

//*****************************************************************************
//【デス様】
//  あとかたづけ
//  引数: なし
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
