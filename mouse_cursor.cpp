//*****************************************************************************
//  マウスカーソルクラス
//  author: 中島将浩
//  update: 2015/10/24
//*****************************************************************************
#include "mouse_cursor.h"
#include "main.h"
#include <Windows.h>
#include "object.h"
#include "object2d.h"

//*****************************************************************************
//  constant
//*****************************************************************************

//*****************************************************************************
//  static variables
//*****************************************************************************
bool MouseCursor::_left_down(false);
bool MouseCursor::_right_down(false);

MouseCursor::MouseCursor(Renderer *renderer):
_renderer(renderer),
_image(nullptr),
_position(0.0f, 0.0f),
_visible(false),
_left_trigger(false),
_left_press(false),
_left_release(false),
_pre_left_press(false),
_right_trigger(false),
_right_press(false),
_right_release(false),
_pre_right_press(false){
	Object2D *image(new Object2D(renderer));
	image->SetUp(0.0f, 0.0f, 10.0f, 10.0f, "data/TEXTURE/flare03.png");

	_image = image;
}

MouseCursor::~MouseCursor(){
	if(_image != nullptr){
		_image->Destroy();
		_image = nullptr;
	}
}

void MouseCursor::Update(void){
	//get mouse state
	_left_press = _left_down;
	_right_press = _right_down;

	//trigger
	_left_trigger = _left_press && (_left_press ^ _pre_left_press);
	_right_trigger = _right_press && (_right_press ^ _pre_right_press);

	//release
	_left_release = !_left_press && (_left_press ^ _pre_left_press);
	_right_release = !_right_press && (_right_press ^ _pre_right_press);

	//save
	_pre_left_press = _left_press;
	_pre_right_press = _right_press;

	//update position
	HWND window(GetMainWindowHandle());
	POINT screen_pos;
	GetCursorPos(&screen_pos);

	POINT client_pos(screen_pos);
	ScreenToClient(window, &client_pos);

	_position.x = static_cast<float>(client_pos.x);
	_position.y = static_cast<float>(client_pos.y);

	float width(static_cast<float>(SCREEN_WIDTH)), height(static_cast<float>(SCREEN_HEIGHT));
	_position.x -= width / 2.0f;
	_position.y -= height / 2.0f;
	_position.x /= width / 2.0f;
	_position.y /= height / 2.0f;
	_position.y = -_position.y;

	if(_image != nullptr){
		D3DXVECTOR3 position(static_cast<float>(client_pos.x), static_cast<float>(client_pos.y), 0.0f);
		_image->SetPosition(position);
	}
}
