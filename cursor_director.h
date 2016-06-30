//*****************************************************************************
//  マウスカーソルの位置から、3Dカーソルの位置を設定するクラス
//  author: 中島将浩
//  update: 2015/10/24
//*****************************************************************************
#ifndef _CURSOR_DIRECTOR_H_
#define _CURSOR_DIRECTOR_H_

#include "main.h"

#include <d3dx9.h>


//*****************************************************************************
//  constant
//*****************************************************************************

//*****************************************************************************
//  class
//*****************************************************************************
class MouseCursor;
class Cursor3D;
class ModelField;
class Camera;
class CursorDirector{
public:

	CursorDirector(MouseCursor* mouse_cursor, Cursor3D* cursor3d, ModelField* model_field, Camera* camera);

	virtual ~CursorDirector();

	void Update(void);

	//accessor
private:
	MouseCursor* _mouse_cursor;
	Cursor3D* _cursor3d;
	ModelField* _model_field;
	Camera* _camera;
};



#endif//_NUMBER_H_