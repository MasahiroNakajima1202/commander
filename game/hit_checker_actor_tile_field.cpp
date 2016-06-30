//*****************************************************************************
//  攻撃判定とキャラクター間の当たり判定クラス
//  author: 中島将浩
//  update: 2015/10/31
//*****************************************************************************
#include "hit_checker_actor_tile_field.h"

#include "battle_object_accessor.h"
#include "battle_actor.h"
#include "tile_field.h"

void HitCheckerActorTileField::Update(void){
	if(_accessor == nullptr){return;}

	int player_count(_accessor->GetPlayerCount());
	for(int i=0; i<player_count; i++){
		BattleActor* player(_accessor->GetPlayer(i));
		HitCheckActor(player);
	}

	int enemy_count(_accessor->GetEnemyCount());
	for(int i=0; i<enemy_count; i++){
		BattleActor* enemy(_accessor->GetEnemy(i));
		HitCheckActor(enemy);
	}
}

void HitCheckerActorTileField::HitCheckActor(BattleActor* actor){
	if(actor == nullptr){return;}
	TileField* field(static_cast<TileField*>(_accessor->GetModelField()));
	if(field == nullptr){return;}

	D3DXVECTOR3 position(actor->GetPosition());
	D3DXVECTOR3 pre_position(actor->GetPrePosition());
	float tile_size(TileField::GetTileSize());
	float width(static_cast<float>(field->GetWidth()) * tile_size), depth(static_cast<float>(field->GetDepth()) * tile_size);

	//範囲内チェック 端ぴったりはあんまり望ましくないので、0.5内側に入れる
	position.x = max(position.x, -width * 0.5f + 0.5f);
	position.x = min(position.x,  width * 0.5f - 0.5f);
	position.z = max(position.z, -depth * 0.5f + 0.5f);
	position.z = min(position.z,  depth * 0.5f - 0.5f);
	
	float dest_height(field->GetHeight(position.x, position.z));
	if(dest_height < position.y){
		//そもそも地面に当たってない
		return;
	}
	
	D3DXVECTOR3 work_position(0.0f, 0.0f, 0.0f);
	if(StopActor(pre_position, position, work_position)){
		position = work_position;
	}

	float work_height(field->GetHeight(position.x, position.z));
	position.y = max(position.y, work_height);//ここで減速or加速を

	actor->SetPosition(position);
}

bool HitCheckerActorTileField::StopActor(D3DXVECTOR3 pre_position, D3DXVECTOR3 cur_position, D3DXVECTOR3 &out_position){
	TileField* field(static_cast<TileField*>(_accessor->GetModelField()));
	if(field == nullptr){return false;}
	float cur_height(field->GetHeight(cur_position.x,cur_position.z));
	float pre_height(max(field->GetHeight(pre_position.x,pre_position.z), pre_position.y));
	float tile_height(TileField::GetTileHeight());

	bool stop(cur_height - pre_height > tile_height * 2.0f);
	if(stop){
		int pre_x_index(-1), pre_z_index(-1);
		int cur_x_index(-1), cur_z_index(-1);
		float tile_size(TileField::GetTileSize());
		float width(static_cast<float>(field->GetWidth()) * tile_size), depth(static_cast<float>(field->GetDepth()) * tile_size);
	
		field->PositionToIndex(pre_position.x, pre_position.z, pre_x_index, pre_z_index);
		field->PositionToIndex(cur_position.x, cur_position.z, cur_x_index, cur_z_index);

		float center_x(-width * 0.5f + static_cast<float>(pre_x_index) * tile_size + tile_size * 0.5f);
		float center_z(-depth * 0.5f + static_cast<float>(pre_z_index) * tile_size + tile_size * 0.5f);

		D3DXVECTOR3 position(cur_position);
		if(cur_x_index != pre_x_index){
			position.x = max(position.x, center_x - tile_size * 0.5f + 0.1f);
			position.x = min(position.x, center_x + tile_size * 0.5f - 0.1f);
		}
		if(cur_z_index != pre_z_index){
			position.z = max(position.z, center_z - tile_size * 0.5f + 0.1f);
			position.z = min(position.z, center_z + tile_size * 0.5f - 0.1f);
		}
		out_position = position;
	}

	return stop;
}
