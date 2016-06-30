//*****************************************************************************
//  マウスカーソルクラス
//  author: 中島将浩
//  update: 2015/10/24
//*****************************************************************************
#ifndef _MOUSE_CURSOR_H_
#define _MOUSE_CURSOR_H_

#include "main.h"

#include <d3dx9.h>


//*****************************************************************************
//  constant
//*****************************************************************************

//*****************************************************************************
//  class
//*****************************************************************************
class Renderer;
class Object;
class MouseCursor{
public:

	MouseCursor(Renderer *renderer);

	virtual ~MouseCursor();

	void Update(void);

	//accessor
	D3DXVECTOR2 GetPosition(void){return _position;}
	bool GetLeftPress(void){return _left_press;}
	bool GetLeftTrigger(void){return _left_trigger;}
	bool GetLeftRelease(void){return _left_release;}
	bool GetRightPress(void){return _right_press;}
	bool GetRightTrigger(void){return _right_trigger;}
	bool GetRightRelease(void){return _right_release;}
	static void LeftDown(void){_left_down = true;}
	static void RightDown(void){_right_down = true;}
	static void LeftUp(void){_left_down = false;}
	static void RightUp(void){_right_down = false;}
private:
	Renderer *_renderer;
	Object* _image;

	D3DXVECTOR2 _position;
	bool _visible;

	bool _left_trigger;
	bool _left_press;
	bool _left_release;
	bool _pre_left_press;
	bool _right_trigger;
	bool _right_press;
	bool _right_release;
	bool _pre_right_press;

	static bool _left_down;
	static bool _right_down;
};


#endif//_NUMBER_H_