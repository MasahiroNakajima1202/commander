//*****************************************************************************
//  ダメージ表示クラス
//  author: 中島将浩
//  update: 2015/11/29
//*****************************************************************************
#include "damage_popup.h"
#include "battle_actor.h"
#include "renderer.h"
#include "object_billboard.h"

DamagePopup::DamagePopup(Renderer* renderer, int damage, BattleActor* owner, float offset_radius):
_renderer(renderer),
_damage(damage),
_owner(owner),
_position(0.0f, 0.0f, 0.0f),
_offset_radius(offset_radius),
_digit_count(0),
_time_count(0),
_total_width(0.0f){
	if(owner != nullptr){
		_position = owner->GetPosition();
	}

	for(int i=0; i<DIGIT_MAX; i++){
		_image[i] = nullptr;
	}

	int value(damage);
	float width(10.0f), height(20.0f);

	for(int i=0; i<DIGIT_MAX; i++){
		if(value <= 0){
			break;
		}

		int digit_value(value % 10);
		value /= 10;

		_image[i] = new ObjectBillboard(renderer);
		_image[i]->SetUp(_position, width, height, "data/TEXTURE/number.png");

		float u(static_cast<float>(digit_value) / 10.0f);
		_image[i]->SetUV(u, 0.0f, u + 0.1f, 1.0f);

		_image[i]->SetOffsetZ(-offset_radius);

		_total_width += width;
		_digit_count++;
	}

	float right(_total_width * 0.5f);
	for(int i=0; i<_digit_count; i++){
		float offset(right - width * 0.5f - width * static_cast<float>(i));
		_image[i]->SetOffsetX(offset);
	}
}


DamagePopup::~DamagePopup(){
	for(int i=0; i<DIGIT_MAX; i++){
		if(_image[i] != nullptr){
			_image[i]->Destroy();
			_image[i] = nullptr;
		}
	}
}

void DamagePopup::Update(void){
	if(_owner != nullptr){
		D3DXVECTOR3 bottom(_owner->GetPosition());
		D3DXVECTOR3 position(bottom);
		position.y += static_cast<float>(_time_count) * 1.0f;
		for(int i=0; i<_digit_count; i++){
			_image[i]->SetPosition(position);
		}
	}

	if(_time_count < TIME_LIMIT){
		_time_count++;
	}
}
