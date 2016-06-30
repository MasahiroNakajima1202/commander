//*****************************************************************************
//  フィールド描画用クラス
//  とりあえず片っ端から描画するけど、のちにインスタンシングに切り替える
//  author: 中島将浩
//  update: 2016/02/26
//*****************************************************************************
#include "tile_field_image.h"
#include "object_x.h"
#include "renderer.h"
#include "tile_field.h"

//*****************************************************************************
//【コンストラクタ】
//*****************************************************************************
TileFieldImage::TileFieldImage(Renderer *master_renderer, int layer_no):
Object(master_renderer, layer_no),
_transparent(false),
_wire_frame(false),
_owner(nullptr),
_world_buffer(nullptr),
_world_decl(nullptr),
_attribute(nullptr){
	for(int i=0; i<IMAGE_MAX; i++){
		_image_id[i] = -1;
	}
}

//*****************************************************************************
//【デス様】
//*****************************************************************************
TileFieldImage::~TileFieldImage(){
	Release();
}

//*****************************************************************************
//【初期化】
//*****************************************************************************
HRESULT TileFieldImage::SetUp(TileField* owner){
	if(owner == nullptr){return E_FAIL;}

	_image_id[0] = _renderer->LoadMesh("data/MODEL/field_block.x");
	Renderer::MESH_SET *mesh = _renderer->GetMesh(_image_id[0]);
	if (mesh == nullptr){ return E_FAIL; }
	DWORD att_size(0);
	mesh->mesh->GetAttributeTable(nullptr, &att_size);
	_attribute = new D3DXATTRIBUTERANGE[att_size];
	mesh->mesh->GetAttributeTable(_attribute, &att_size);
	_owner = owner;
	LPDIRECT3DDEVICE9 device(_renderer->GetDevice());

	int tile_num(owner->GetWidth() * owner->GetDepth() * TileField::GetTileStackLimit());
	if (FAILED(device->CreateVertexBuffer(sizeof(D3DXMATRIX) * tile_num,
		D3DUSAGE_WRITEONLY,
		0,
		D3DPOOL_MANAGED,
		&_world_buffer,
		nullptr))){
		_world_buffer = nullptr;
		return E_FAIL;
	}

	//bufferの初期化
	D3DXMATRIX *work_matrix(nullptr);
	_world_buffer->Lock(0, 0, (void**)&work_matrix, 0);

	for(int i=0; i<tile_num; i++){
		//画面に出ない状態を0スケーリングで実装する
		D3DXMatrixScaling(&work_matrix[i], 0.0f, 0.0f, 0.0f);
	}

	_world_buffer->Unlock();

	//decleration
	D3DVERTEXELEMENT9 element[] = {
		{0,  0, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0},
		{0, 12, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_NORMAL, 0},
		{0, 24, D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 0},
		{1,  0, D3DDECLTYPE_FLOAT4, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 1},  //world1行目
		{1, 16, D3DDECLTYPE_FLOAT4, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 2},  //world2行目
		{1, 32, D3DDECLTYPE_FLOAT4, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 3},  //world3行目
		{1, 48, D3DDECLTYPE_FLOAT4, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 4},  //world4行目
		D3DDECL_END()
	};
	if (FAILED(device->CreateVertexDeclaration(element, &_world_decl))){
		return E_FAIL;
	}

	return S_OK;
}

//*****************************************************************************
//【終了】
//*****************************************************************************
void TileFieldImage::Release(void){
	if(_world_buffer != nullptr){
		_world_buffer->Release();
		_world_buffer = nullptr;
	}
	if(_world_decl != nullptr){
		_world_decl->Release();
		_world_decl = nullptr;
	}
	if(_attribute != nullptr){
		delete [] _attribute;
		_attribute = nullptr;
	}
}

//*****************************************************************************
//【更新】
//*****************************************************************************
void TileFieldImage::Update(void){
}

//*****************************************************************************
//【描画】
//*****************************************************************************
void TileFieldImage::Draw(void){
	if(_owner == nullptr){return;}
	if (_renderer == nullptr){ return; }
	if (!_visible){ return; }

	LPDIRECT3DDEVICE9 device = nullptr;		//デバイス取得用

	device = _renderer->GetDevice();

	if (_wire_frame){
		device->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
	}

	//メッシュの取得
	Renderer::MESH_SET *mesh = _renderer->GetMesh(_image_id[0]);
	if (mesh == nullptr){ return; }
	D3DXMATERIAL *mat((D3DXMATERIAL*)mesh->mat_buff->GetBufferPointer());

	LPDIRECT3DVERTEXBUFFER9 vertex;
	LPDIRECT3DINDEXBUFFER9 index;
	mesh->mesh->GetIndexBuffer(&index);
	mesh->mesh->GetVertexBuffer(&vertex);
	device->SetStreamSource(0, vertex, 0, sizeof(VERTEX_MESH));
	device->SetIndices(index);

	//instancing bufferの設定
	int tile_num(_owner->GetWidth() * _owner->GetDepth() * TileField::GetTileStackLimit());
	device->SetStreamSource(1, _world_buffer, 0, sizeof(D3DXMATRIX));
	UINT def_freq0, def_freq1;
	device->GetStreamSourceFreq(0, &def_freq0);
	device->GetStreamSourceFreq(1, &def_freq1);
	device->SetStreamSourceFreq(0, D3DSTREAMSOURCE_INDEXEDDATA  | tile_num);
	device->SetStreamSourceFreq(1, D3DSTREAMSOURCE_INSTANCEDATA | 1);
	device->SetVertexDeclaration(_world_decl);

	for (int i = 0; i<(int)mesh->mat_num; i++){
		D3DMATERIAL9 work_mat = mat[i].MatD3D;
		if (_transparent){
			work_mat.Diffuse.a *= 0.5f;
		}
		D3DXVECTOR4 diffuse(work_mat.Diffuse.r,
			work_mat.Diffuse.g,
			work_mat.Diffuse.b,
			work_mat.Diffuse.a);

		_renderer->SetTextureToShader(mesh->texture[i]);
		_renderer->SetMaterialDiffuse(diffuse);

		_renderer->SetCurrentShader();

		int index_offset(_attribute[i].FaceStart * 3);
		int face_count(_attribute[i].FaceCount);
		int vertex_num(_attribute[i].VertexCount);
		int vertex_offset(_attribute[i].VertexStart);
		device->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, vertex_offset, vertex_num, index_offset, face_count);					//描画

	}

	device->SetStreamSourceFreq(0, def_freq0);
	device->SetStreamSourceFreq(1, def_freq1);
	device->SetStreamSource(1, nullptr, 0, 0);
	device->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);

}

void TileFieldImage::CommitImage(void){
	if(_owner == nullptr){return;}

	int width(_owner->GetWidth()), depth(_owner->GetDepth());
	float  tile_size(TileField::GetTileSize());
	float tile_height(TileField::GetTileHeight());
	float x(static_cast<float>(width) * tile_size * -0.5f + tile_size * 0.5f), z(static_cast<float>(depth) * tile_size * -0.5f + tile_size * 0.5f);

	int tile_num(width * depth * TileField::GetTileStackLimit());
	int xz_offset(0);
	D3DXMATRIX *work_matrix(nullptr);
	_world_buffer->Lock(0, 0, (void**)&work_matrix, 0);

	for(int z_index=0; z_index<depth; z_index++){
		x = static_cast<float>(width)* tile_size * -0.5f + tile_size * 0.5f;
		for(int x_index = 0; x_index<width; x_index++){

			int field_height(_owner->GetIndexHeight(x_index, z_index));
			float height(0.0f);

			for(int y_index=0; y_index<=field_height; y_index++){
				D3DXMATRIX *matrix(&work_matrix[xz_offset + y_index]);

				D3DXVECTOR3 position(x, height - tile_height, z);
				D3DXVECTOR3 size(tile_size, tile_height, tile_size);
				D3DXMatrixTranslation(matrix, position.x, position.y, position.z);

				height += tile_height;
			}

			xz_offset += TileField::GetTileStackLimit();
			x += tile_size;
		}
		z += tile_size;
	}

	_world_buffer->Unlock();
}


void TileFieldImage::DrawImage(D3DXVECTOR3 position, D3DXVECTOR3 size){
	D3DXMATRIX scl_mtx, rot_mtx, translate_mtx, world_mtx;
	LPDIRECT3DDEVICE9 device = nullptr;		//デバイス取得用

	D3DXMATERIAL *mat = nullptr;
	unsigned int i = 0, j = 0;								//loop index

	if (_renderer == nullptr){ return; }

	device = _renderer->GetDevice();

	//メッシュの取得
	Renderer::MESH_SET *mesh = _renderer->GetMesh(_image_id[0]);
	if (mesh == nullptr){ return; }

	D3DXMatrixIdentity(&world_mtx);					//ワールド行列をとりあえずEにする

	//最初はscalingで形を作っていたけど、TILEの大きさが決まったのでscalingなしで
	//変わる可能性もなくはないので一応残し
	//D3DXMatrixScaling(&scl_mtx, size.x, size.y, size.z);
	//D3DXMatrixMultiply(&world_mtx, &world_mtx, &scl_mtx);

	D3DXMatrixTranslation(&translate_mtx, position.x, position.y, position.z);
	D3DXMatrixMultiply(&world_mtx, &world_mtx, &translate_mtx);

	_renderer->SetWorld(world_mtx);

	mat = (D3DXMATERIAL*)mesh->mat_buff->GetBufferPointer();
	for (j = 0; j<mesh->mat_num; j++){
		D3DMATERIAL9 work_mat = mat[j].MatD3D;
		if (_transparent){
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

	
}
