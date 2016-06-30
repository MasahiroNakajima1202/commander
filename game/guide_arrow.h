//*****************************************************************************
//  çsÇ´êÊÇé¶Ç∑ñÓàÛ
//  author: íÜìáè´ç_
//  update: 2015/12/30
//*****************************************************************************
#ifndef _GUIDE_ARROW_H_
#define _GUIDE_ARROW_H_

#include "main.h"
#include <d3dx9.h>

//*****************************************************************************
//  constant
//*****************************************************************************

//*****************************************************************************
//  class
//*****************************************************************************
class Renderer;
class Sprite3D;
class GuideArrow{
public:

	GuideArrow(Renderer *renderer);

	virtual ~GuideArrow();

	void Update(void);


	void SetBeginPosition(D3DXVECTOR3 position);
	void SetEndPosition(D3DXVECTOR3 position);

	//accessor
	void SetVisible(bool visible);
private:
	Renderer *_renderer;
	Sprite3D* _arrow;
	Sprite3D* _line;

	D3DXVECTOR3 _begin;
	D3DXVECTOR3 _end;
	bool _visible;

	void CommitImage(void);
};


#endif