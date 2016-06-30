//*****************************************************************************
//  scene_xモジュール
//  author: 中島将浩
//  update: 2014/04/23
//*****************************************************************************

#include "main.h"
#include "object_x.h"
#include "renderer.h"

//*****************************************************************************
//  constant
//*****************************************************************************

//*****************************************************************************
//【コンストラクタ】
//  頂点バッファNULL詰めなど
//  引数: なし
//*****************************************************************************
ObjectX::ObjectX(Renderer *master_renderer, int layer_no) :
Object(master_renderer, layer_no),
_mesh_id(-1),
_transparent(false),
_wire_frame(false){
}
	
//*****************************************************************************
//【初期化】
//  返り値: 初期化に成功したかどうか
//  引数: なし
//*****************************************************************************
HRESULT ObjectX::SetUp(char *filename){
	LPDIRECT3DDEVICE9 device = _renderer->GetDevice();
	D3DXMATERIAL *mat = NULL;
	unsigned int i = 0;							//loop index

	_position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//位置
	_rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//向き


	_mesh_id = _renderer->LoadMesh(filename);

	return S_OK;
}


//*****************************************************************************
//【終了】
//  返り値: なし
//  引数: なし
//*****************************************************************************
void ObjectX::Release(void){
}

//*****************************************************************************
//【更新】
//  返り値: なし
//  引数: なし
//*****************************************************************************
void ObjectX::Update(void){
	Object::Update();
}

//*****************************************************************************
//【描画】
//  返り値: なし
//  引数: なし
//*****************************************************************************
void ObjectX::Draw(void){
	D3DXMATRIX scl_mtx, rot_mtx, translate_mtx, world_mtx;
	LPDIRECT3DDEVICE9 device = NULL;		//デバイス取得用

	D3DXMATERIAL *mat = NULL;
	unsigned int i = 0, j = 0;								//loop index

	if(_renderer == NULL){return;}
	if(!_visible){return;}

	device = _renderer->GetDevice();
	
	if(_wire_frame){
		device->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
	}

	//メッシュの取得
	Renderer::MESH_SET *mesh = _renderer->GetMesh(_mesh_id);
	if(mesh == NULL){return;}

	D3DXMatrixIdentity(&world_mtx);					//ワールド行列をとりあえずEにする

	D3DXMatrixScaling(&scl_mtx, _size.x, _size.y, _size.z);	//rotation
	D3DXMatrixMultiply(&world_mtx, &world_mtx, &scl_mtx);

	D3DXMatrixRotationYawPitchRoll(&rot_mtx, _rotation.y, _rotation.x, _rotation.z);	//rotation
	D3DXMatrixMultiply(&world_mtx, &world_mtx, &rot_mtx);

	D3DXMatrixTranslation(&translate_mtx, _position.x, _position.y, _position.z);	//translation
	D3DXMatrixMultiply(&world_mtx, &world_mtx, &translate_mtx);

	_renderer->SetWorld(world_mtx);

	mat = (D3DXMATERIAL*)mesh->mat_buff->GetBufferPointer();
	for(j=0; j<mesh->mat_num; j++){
		D3DMATERIAL9 work_mat = mat[j].MatD3D;
		if(_transparent){
			work_mat.Diffuse.a *= 0.5f;
		}
		D3DXVECTOR4 diffuse(work_mat.Diffuse.r,
							work_mat.Diffuse.g,
							work_mat.Diffuse.b,
							work_mat.Diffuse.a);

		_renderer->SetTextureToShader(mesh->texture[j]);
		_renderer->SetMaterialDiffuse(diffuse);

		_renderer->SetCurrentShader();

		mesh->mesh->DrawSubset(j);
	}

	device->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);

}
