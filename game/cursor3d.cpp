//*****************************************************************************
//  フィールド上のカーソル
//  author: 中島将浩
//  update: 2015/10/24
//*****************************************************************************

#include "cursor3d.h"
#include "object_x.h"


//*****************************************************************************
//  constant
//*****************************************************************************


Cursor3D::Cursor3D(Renderer *renderer):
_renderer(renderer),
_image(nullptr),
_position(0.0f, 0.0f, 0.0f),
_visible(false){
	ObjectX *obj(new ObjectX(renderer));
	obj->SetUp("data/MODEL/head.x");
	_image = obj;
}

Cursor3D::~Cursor3D(){
	if(_image != nullptr){
		_image->Destroy();
		_image = nullptr;
	}
}

void Cursor3D::Update(void){
	if(_image != nullptr){
		_image->SetPosition(_position);
	}
}

void Cursor3D::SetPosition(D3DXVECTOR3 position){
	_position = position;
	if(_image != nullptr){
		_image->SetPosition(position);
	}
}
void Cursor3D::SetVisible(bool value){
	_visible = value;
	if(_image != nullptr){
		_image->SetVisible(value);
	}
}