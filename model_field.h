//*****************************************************************************
//  ÉÇÉfÉãÇ…ÇÊÇÈínå`
//  author: íÜìáè´ç_
//  update: 2015/10/24
//*****************************************************************************
#ifndef _MODEL_FIELD_H_
#define _MODEL_FIELD_H_

#include "main.h"

#include <d3dx9.h>


//*****************************************************************************
//  constant
//*****************************************************************************

//*****************************************************************************
//  class
//*****************************************************************************
class Renderer;
class ObjectX;
class ModelField{
public:


	ModelField(Renderer *renderer, char* filename);

	virtual ~ModelField();

	virtual void Update(void);

	virtual float GetHeight(float x, float z);

	virtual bool FixLay(D3DXVECTOR3 &dst, D3DXVECTOR3 src, D3DXVECTOR3 begin);

	//accessor
protected:
	Renderer *_renderer;
	ObjectX* _image;
};


#endif//_NUMBER_H_