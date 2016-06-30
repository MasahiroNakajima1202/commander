//*****************************************************************************
//  UŒ‚”»’èƒNƒ‰ƒX ‹…
//  author: ’†“‡«_
//  update: 2015/10/25
//*****************************************************************************
#include "attack_sphere.h"
#include "hit_sphere.h"
#include "object_x.h"
#include "object.h"
//*****************************************************************************
//  constant
//*****************************************************************************

//*****************************************************************************
//  class
//*****************************************************************************
AttackSphere::AttackSphere(D3DXVECTOR3 position, float radius, int life_count, Renderer* renderer, BattleActor* owner, int power, D3DXVECTOR3 direction):
Attack(1, owner, power, direction),
_position(position),
_radius(radius),
_life_count(life_count),
_renderer(renderer){
	_hit_array[0] = new HitSphere(renderer, position, radius);
}

AttackSphere::~AttackSphere(){
	if(_hit_array[0] != nullptr){
		delete _hit_array[0];
		_hit_array[0] = nullptr;
	}

	
}

void AttackSphere::Update(void){
	_life_count--;
	_life_count = max(_life_count, 0);

	_hit_array[0]->Update();
}

bool AttackSphere::Finished(void){
	return _life_count <= 0;
}
