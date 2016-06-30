//*****************************************************************************
//  マウスカーソルの位置から、3Dカーソルの位置を設定するクラス
//  author: 中島将浩
//  update: 2015/10/24
//*****************************************************************************
#include "cursor_director.h"

#include "mouse_cursor.h"
#include "cursor3d.h"
#include "model_field.h"
#include "camera.h"

CursorDirector::CursorDirector(MouseCursor* mouse_cursor, Cursor3D* cursor3d, ModelField* model_field, Camera* camera):
_mouse_cursor(mouse_cursor),
_cursor3d(cursor3d),
_model_field(model_field),
_camera(camera){
}

CursorDirector::~CursorDirector(){
}

void CursorDirector::Update(void){
	if(_mouse_cursor == nullptr
		|| _cursor3d == nullptr
		|| _model_field == nullptr
		|| _camera == nullptr){
		return;
	}

	//get screen position
	D3DXVECTOR2 screen_position(_mouse_cursor->GetPosition());
	D3DXVECTOR3 screen_front(screen_position.x, screen_position.y, 0.0f);
	D3DXVECTOR3 screen_depth(screen_position.x, screen_position.y, 1.0f);

	//get view, projection and inverse 
	D3DXMATRIX view( *(_camera->GetView()) );
	D3DXMATRIX proj( *(_camera->GetProjection()) );
	D3DXMATRIX view_proj(view * proj);
	D3DXMATRIX view_proj_inverse(view_proj);
	D3DXMatrixInverse(&view_proj_inverse, nullptr, &view_proj);

	//calculate lay
	D3DXVECTOR3 front(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 depth(0.0f, 0.0f, 0.0f);
	D3DXVec3TransformCoord(&front, &screen_front, &view_proj_inverse);
	D3DXVec3TransformCoord(&depth, &screen_depth, &view_proj_inverse);
	D3DXVECTOR3 lay_begin(front);
	D3DXVECTOR3 lay_direction(depth - front);

	//fix lay
	D3DXVECTOR3 fixed_lay(0.0f, 0.0f, 0.0f);
	bool hit(false);
	hit = _model_field->FixLay(fixed_lay, lay_direction, lay_begin);
	if(hit){
		D3DXVECTOR3 position(lay_begin + fixed_lay);
		_cursor3d->SetPosition(position);
		_cursor3d->SetVisible(true);
	}
	else{
		_cursor3d->SetPosition(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
		_cursor3d->SetVisible(false);
	}
}

