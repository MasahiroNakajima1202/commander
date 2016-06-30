//*****************************************************************************
//  当たり判定クラス
//  author: 中島将浩
//  update: 2015/10/25
//*****************************************************************************
#ifndef _HIT_H_
#define _HIT_H_

#include "main.h"
#include <d3dx9.h>

//*****************************************************************************
//  constant
//*****************************************************************************

//*****************************************************************************
//  class
//*****************************************************************************
class HitSphere;
class HitCube;
class Renderer;
class Hit{
private:
	Hit(){}
public:

	Hit(Renderer* renderer, D3DXVECTOR3 position):
	_renderer(renderer),
	_position(position){
	}

	virtual ~Hit(){}

	virtual void Update(void) = 0;

	virtual bool HitCheck(Hit* hit) = 0;

	virtual bool InnerHitCheck(HitSphere* sphere) = 0;				//内部的に使用しています
	virtual bool InnerHitCheck(HitCube* cube) = 0;

	//accessor
	D3DXVECTOR3 GetPosition(void){return _position;}
	virtual void SetPosition(D3DXVECTOR3 position){_position = position;}
	D3DXVECTOR3 GetRotation(void){return _rotation;}
	virtual void SetRotation(D3DXVECTOR3 rotation){_rotation = rotation;}
protected:

	Renderer* _renderer;
	D3DXVECTOR3 _position;
	D3DXVECTOR3 _rotation;
};



#endif//_NUMBER_H_