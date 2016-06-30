//*****************************************************************************
//  ìñÇΩÇËîªíËÉNÉâÉX
//  author: íÜìáè´ç_
//  update: 2016/03/13
//*****************************************************************************
#ifndef _HIT_CUBE_H_
#define _HIT_CUBE_H_

#include "main.h"
#include <d3dx9.h>

#include "hit.h"

//*****************************************************************************
//  constant
//*****************************************************************************

//*****************************************************************************
//  class
//*****************************************************************************
class Renderer;
class Object;
class HitSphere;
class HitCube : public Hit{
public:

	HitCube(Renderer* renderer, D3DXVECTOR3 position, D3DXVECTOR3 size);

	virtual ~HitCube();

	virtual void Update(void);

	virtual bool InnerHitCheck(HitSphere* sphere);
	virtual bool InnerHitCheck(HitCube* cube);

	virtual bool HitCheck(Hit* hit);

	//accessor
	virtual void SetPosition(D3DXVECTOR3 position);
	virtual void SetRotation(D3DXVECTOR3 rotation);
	D3DXVECTOR3 GetSize(void){return _size;}
protected:
	
	Object* _debug_image;
	D3DXVECTOR3 _size;
};



#endif//_NUMBER_H_