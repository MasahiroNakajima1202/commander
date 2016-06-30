//*****************************************************************************
//  フィールド上のカーソル
//  author: 中島将浩
//  update: 2015/10/24
//*****************************************************************************
#ifndef _CURSOR_3D_H_
#define _CURSOR_3D_H_

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
class Cursor3D{
public:

	Cursor3D(Renderer *renderer);

	virtual ~Cursor3D();

	void Update(void);

	//accessor
	D3DXVECTOR3 GetPosition(void){return _position;}
	void SetPosition(D3DXVECTOR3 position);
	void SetVisible(bool value);
	bool GetVisible(void){return _visible;}
private:
	Renderer *_renderer;
	Object* _image;

	D3DXVECTOR3 _position;
	bool _visible;
};


#endif//_NUMBER_H_