//*****************************************************************************
//  戦闘時のギミック 梯子
//  author: 中島将浩
//  update: 2016/03/13
//*****************************************************************************
#ifndef _GIMMICK_LADDER_H_
#define _GIMMICK_LADDER_H_

#include "main.h"
#include <d3dx9.h>

#include "gimmick.h"

//*****************************************************************************
//  constant
//*****************************************************************************

//*****************************************************************************
//  class
//*****************************************************************************
class Renderer;
class ObjectX;
class Hit;
class GimmickLadder : public Gimmick{
public:
	
	GimmickLadder(Renderer *renderer, D3DXVECTOR3 position, D3DXVECTOR3 rotation, int height_num);

	virtual ~GimmickLadder();

	virtual void Update(void);

	virtual void ReactToActor(BattleActor* actor);

protected:
	static const int HEIGHT_MAX = 32;
	ObjectX* _ladder_image[HEIGHT_MAX];
	int _height_num;
};


#endif