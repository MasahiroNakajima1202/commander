//*****************************************************************************
//  ダメージ表示クラス
//  author: 中島将浩
//  update: 2015/11/29
//*****************************************************************************
#ifndef _DAMAGE_POPUP_H_
#define _DAMAGE_POPUP_H_

#include "main.h"
#include <d3dx9.h>

//*****************************************************************************
//  constant
//*****************************************************************************

//*****************************************************************************
//  class
//*****************************************************************************
class ObjectBillboard;
class BattleActor;
class Renderer;
class DamagePopup{
private:
	DamagePopup(){}
public:

	DamagePopup(Renderer* renderer, int damage, BattleActor* owner, float offset_radius);

	virtual ~DamagePopup();

	virtual void Update(void);

	bool Finished(void){return _time_count >= TIME_LIMIT;}
	//accessor
	D3DXVECTOR3 GetPosition(void){return _position;}
	void SetPosition(D3DXVECTOR3 position){_position = position;}
protected:

	Renderer* _renderer;
	int _damage;
	BattleActor* _owner;
	D3DXVECTOR3 _position;
	float _offset_radius;
	static const int DIGIT_MAX = 4;
	ObjectBillboard* _image[DIGIT_MAX];			//little endian
	int _digit_count;
	static const int TIME_LIMIT = 60;
	int _time_count;
	float _total_width;

};



#endif//_NUMBER_H_