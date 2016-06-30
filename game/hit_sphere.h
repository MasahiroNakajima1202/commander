//*****************************************************************************
//  ìñÇΩÇËîªíËÉNÉâÉX
//  author: íÜìáè´ç_
//  update: 2015/10/25
//*****************************************************************************
#ifndef _HIT_SPHERE_H_
#define _HIT_SPHERE_H_

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
class HitCube;
class HitSphere : public Hit{
public:

	HitSphere(Renderer* renderer, D3DXVECTOR3 position, float radius);

	virtual ~HitSphere();

	virtual void Update(void);

	virtual bool InnerHitCheck(HitSphere* sphere);

	virtual bool HitCheck(Hit* hit);
	virtual bool InnerHitCheck(HitCube* cube);

	//accessor
	virtual void SetPosition(D3DXVECTOR3 position);
	float GetRadius(void){return _radius;}
protected:
	
	Object* _debug_image;
	float _radius;
};



#endif//_NUMBER_H_