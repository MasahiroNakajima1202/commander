//*****************************************************************************
//  戦闘時のギミック 梯子
//  author: 中島将浩
//  update: 2016/03/13
//*****************************************************************************
#include "gimmick_ladder.h"
#include "renderer.h"
#include "object_x.h"
#include "hit_cube.h"
#include "tile_field.h"
#include "battle_actor.h"
//*****************************************************************************
//  constant
//*****************************************************************************

GimmickLadder::GimmickLadder(Renderer *renderer, D3DXVECTOR3 position, D3DXVECTOR3 rotation, int height_num):
Gimmick(renderer, position, rotation),
_height_num(min(height_num, HEIGHT_MAX)){
	for(int i = 0; i<HEIGHT_MAX; i++){
		_ladder_image[i] = nullptr;
	}

	for(int i = 0; i<_height_num; i++){
		_ladder_image[i] = new ObjectX(renderer);
		_ladder_image[i]->SetUp("data/MODEL/ladder.x");
	}

	float tile_height(TileField::GetTileHeight());
	float tile_size(TileField::GetTileSize());
	D3DXVECTOR3 ladder_position(_position);
	ladder_position.y += static_cast<float>(_height_num) * tile_height * 0.5f;
	_hit = new HitCube(_renderer, ladder_position, D3DXVECTOR3(tile_size, tile_height * static_cast<float>(_height_num), 5.0f));
}

GimmickLadder::~GimmickLadder(){
	for(int i = 0; i<HEIGHT_MAX; i++){
		if(_ladder_image[i] != nullptr){
			_ladder_image[i]->Destroy();
			_ladder_image[i] = nullptr;
		}
	}
}

void GimmickLadder::Update(void){
	Gimmick::Update();

	float tile_height(TileField::GetTileHeight());
	D3DXVECTOR3 position(_position);
	for(int i = 0; i<_height_num; i++){
		if(_ladder_image[i] == nullptr){break;}

		_ladder_image[i]->SetPosition(position);
		position.y += tile_height;
	}

	if(_hit != nullptr){
		float tile_size(TileField::GetTileSize());
		D3DXVECTOR3 ladder_position(_position);
		ladder_position.y += static_cast<float>(_height_num) * tile_height * 0.5f;
		_hit->SetPosition(ladder_position);
		_hit->SetRotation(_rotation);
	}

	for(int i = 0; i<_height_num; i++){
		if(_ladder_image[i] == nullptr){continue;}

		_ladder_image[i]->SetRotation(_rotation);
	}

}

void GimmickLadder::ReactToActor(BattleActor* actor){
	float height(actor->GetPrePosition().y);
	height += 0.1f;
	float tile_height(TileField::GetTileHeight());
	height = min(height, _position.y + static_cast<float>(_height_num) * tile_height);
	D3DXVECTOR3 position(actor->GetPosition());
	position.y = height;

	actor->SetPosition(position);
}

