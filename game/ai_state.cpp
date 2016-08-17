//*****************************************************************************
//  “GAI
//  author: ’†“‡«_
//  update: 2016/04/11
//*****************************************************************************
#include "ai_state.h"
#include "ai_path.h"
#include "battle_actor.h"
//*****************************************************************************
//  constant
//*****************************************************************************


AIState::AIState(BattleObjectAccessor* accessor, Renderer* renderer, BattleActor* owner):
_accessor(accessor),
_renderer(renderer),
_owner(owner){
	for (int i = 0; i < PATH_MAX; i++){
		_path_array[i] = nullptr;
	}
}

AIState::~AIState(){
}

AIState* AIState::CheckPath(void){
	AIState* ret(nullptr);

	for(int i = 0; i < PATH_MAX; i++){
		AIPath* path(_path_array[i]);
		if(path == nullptr){continue;}

		bool change(path->CheckToPassThrough());
		if(change){
			ret = path->GetNext();
			break;
		}
	}

	return ret;
}
