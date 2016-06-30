//*****************************************************************************
//  êÌì¨éûÇÃÉMÉ~ÉbÉN
//  author: íÜìáè´ç_
//  update: 2016/03/13
//*****************************************************************************
#ifndef _GIMMICK_H_
#define _GIMMICK_H_

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
class Hit;
class BattleActor;
class Gimmick{
private:
	Gimmick(){}
public:
	
	Gimmick(Renderer *renderer, D3DXVECTOR3 position, D3DXVECTOR3 rotation);

	virtual ~Gimmick();

	virtual void Update(void);

	virtual void ReactToActor(BattleActor* actor) = 0;

	//accessor
	D3DXVECTOR3 GetPrePosition(void){return _pre_position;}
	D3DXVECTOR3 GetPosition(void){ return _position; }
	void SetPosition(D3DXVECTOR3 position);
	D3DXVECTOR3 GetVelocity(void){ return _velocity; }
	void SetVelocity(D3DXVECTOR3 velocity){_velocity = velocity;}
	void SetVisible(bool value);
	Hit* GetHit(void){return _hit;}
	void SetDestRotation(D3DXVECTOR3 value){_dest_rotation = value;}
	D3DXVECTOR3 GetRotation(void){return _rotation;}
	D3DXVECTOR3 GetDestRotation(void){return _dest_rotation;}
protected:
	static const float NATURAL_SPEED_DOWN;
	Renderer *_renderer;
	Object* _image;

	D3DXVECTOR3 _position;
	D3DXVECTOR3 _pre_position;
	D3DXVECTOR3 _velocity;
	D3DXVECTOR3 _rotation;
	D3DXVECTOR3 _dest_rotation;
	bool _visible;

	Hit* _hit;

	void CommitPositionRotationToImage(void);
	void CommitPositionRotationToHit(void);
};


#endif