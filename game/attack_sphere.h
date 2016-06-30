//*****************************************************************************
//  çUåÇîªíËÉNÉâÉX ãÖ
//  author: íÜìáè´ç_
//  update: 2015/10/25
//*****************************************************************************
#ifndef _ATTACK_SPHERE_H_
#define _ATTACK_SPHERE_H_

#include "main.h"
#include <d3dx9.h>

#include "attack.h"

//*****************************************************************************
//  constant
//*****************************************************************************

//*****************************************************************************
//  class
//*****************************************************************************
class Object;
class Renderer;
class AttackSphere : public Attack{
public:
	AttackSphere(D3DXVECTOR3 position, float radius, int life_count, Renderer* renderer, BattleActor* owner, int power, D3DXVECTOR3 direction);

	virtual ~AttackSphere();

	virtual void Update(void);
	virtual bool Finished(void);

	//accessor
protected:
	D3DXVECTOR3 _position;
	float _radius;
	int _life_count;
	Renderer* _renderer;
};



#endif//_NUMBER_H_