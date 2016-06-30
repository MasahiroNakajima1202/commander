//*****************************************************************************
//  モデルによる地形
//  author: 中島将浩
//  update: 2015/10/24
//*****************************************************************************
#include "model_field.h"
#include "object_x.h"
#include "renderer.h"

ModelField::ModelField(Renderer *renderer, char* filename):
_renderer(renderer),
_image(nullptr){
	_image = new ObjectX(renderer);
	_image->SetUp(filename);
	//_image->SetVisible(false);
}

ModelField::~ModelField(){
	if(_image != nullptr){
		_image->Destroy();
		_image = nullptr;
	}
}

void ModelField::Update(void){
	if(_image != nullptr){
		_image->Update();
	}
}

float ModelField::GetHeight(float x, float z){
	if(_image == nullptr){return 0.0f;}

	int mesh_id(_image->GetMeshId());
	Renderer::MESH_SET *mesh(_renderer->GetMesh(mesh_id));
	if(mesh == nullptr){return false;}

	float top(1000.0f);
	D3DXVECTOR3 lay_begin(x, top, z);
	D3DXVECTOR3 lay(0.0f, -1.0f, 0.0f);
	float length(0.0f);
	BOOL hit(FALSE);
	
	D3DXIntersect(mesh->mesh, &lay_begin, &lay, &hit, nullptr, nullptr, nullptr, &length, nullptr, nullptr);

	if(!hit){
		return 0.0f;
	}

	float height = top - length;

	return height;
}

bool ModelField::FixLay(D3DXVECTOR3 &dst, D3DXVECTOR3 src, D3DXVECTOR3 begin){
	if(_image == nullptr){return false;}
	
	int mesh_id(_image->GetMeshId());
	Renderer::MESH_SET *mesh(_renderer->GetMesh(mesh_id));
	if(mesh == nullptr){return false;}

	D3DXVECTOR3 lay_begin(begin), lay_direction(src);
	float length(0.0f);
	D3DXVec3Normalize(&lay_direction, &lay_direction);
	BOOL hit(FALSE);
	//注意 ModelField自体がワールド変換を想定してないからいいものの、この関数自体はローカル空間上での計算です
	D3DXIntersect(mesh->mesh, &lay_begin, &lay_direction, &hit, nullptr, nullptr, nullptr, &length, nullptr, nullptr);

	bool ret(false);
	if(hit){
		dst = lay_direction * length;
		ret = true;
	}

	return ret;
}
