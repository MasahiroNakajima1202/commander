//*****************************************************************************
//  敵AI状態移行クラス プレイヤーが一定以上近くにいる
//  author: 中島将浩
//  update: 2016/07/28
//*****************************************************************************
#include "ai_path_near_player.h"
#include "battle_actor.h"
#include "battle_object_accessor.h"
	
AIPathNearPlayer::AIPathNearPlayer(BattleObjectAccessor* accessor, Renderer* renderer, AIState* from, AIState* to, BattleActor* owner, int threshold, float range):
AIPath(accessor, renderer, from, to),
_owner(owner),
_threthold(threshold),
_range(range){
}

AIPathNearPlayer::~AIPathNearPlayer(){
}

void AIPathNearPlayer::Update(void){
}

bool AIPathNearPlayer::CheckToPassThrough(void){
	if(_owner == nullptr){return false;}
	if(_accessor == nullptr){return false;}

	int player_count(_accessor->GetPlayerCount());
	int close_count(0);
	for(int i = 0; i < player_count; i++){
		BattleActor* player(_accessor->GetPlayer(i));
		if(player == nullptr){continue;}
		
		D3DXVECTOR3 to_player(player->GetPosition() - _owner->GetPosition());
		to_player.y = 0.0f;

		float sq_length(D3DXVec3LengthSq(&to_player));
		if(sq_length < _range * _range){
			close_count++;
		}
	}

	return close_count >= _threthold;
}
