//*****************************************************************************
//  戦闘時のキャラクターの分身　ドラッグ時のガイド用
//  author: 中島将浩
//  update: 2015/12/29
//*****************************************************************************
#ifndef _BATTLE_ACTOR_GHOST_H_
#define _BATTLE_ACTOR_GHOST_H_

#include "main.h"
#include <d3dx9.h>

//*****************************************************************************
//  constant
//*****************************************************************************

//*****************************************************************************
//  class
//*****************************************************************************
class Renderer;
class SkinMesh;
class BattleActorGhost{
public:

	BattleActorGhost(Renderer *renderer, char* image_filename);

	virtual ~BattleActorGhost();

	void Update(void);


	//accessor
	D3DXVECTOR3 GetPosition(void){ return _position; }
	void SetPosition(D3DXVECTOR3 position);
	void SetRotation(D3DXVECTOR3 rotation);
	void SetVisible(bool value);
	void SetDestRotation(D3DXVECTOR3 value){_dest_rotation = value;}
	D3DXVECTOR3 GetRotation(void){return _rotation;}
	D3DXVECTOR3 GetDestRotation(void){return _dest_rotation;}
private:
	Renderer *_renderer;
	SkinMesh* _image;

	D3DXVECTOR3 _position;
	D3DXVECTOR3 _velocity;
	D3DXVECTOR3 _rotation;
	D3DXVECTOR3 _dest_rotation;
	bool _visible;

};


#endif