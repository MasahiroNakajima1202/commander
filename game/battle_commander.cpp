//*****************************************************************************
//  作戦行動指示クラス
//  author: 中島将浩
//  update: 2015/10/31
//*****************************************************************************
#include "battle_commander.h"
#include "battle_object_accessor.h"
#include "mouse_cursor.h"
#include "cursor3d.h"
#include "battle_actor.h"
#include "hit.h"
#include "hit_sphere.h"
#include "battle_action_walk.h"
#include "battle_operation_attack.h"

#include "battle_commander_state.h"
#include "battle_commander_state_free.h"
#include "battle_commander_state_direction.h"

BattleCommander::BattleCommander(BattleObjectAccessor* accessor, Renderer* renderer):
_accessor(accessor),
_renderer(renderer),
_cur_state(nullptr){
	for(int i = 0; i<STATE::MAX; i++){
		_state[i] = nullptr;
	}

	_state[STATE::FREE] = new BattleCommanderStateFree(this, accessor, renderer);
	_state[STATE::DIRECTION] = new BattleCommanderStateDirection(this, accessor, renderer);

	ChangeState(FREE);
}

BattleCommander::~BattleCommander(){
	for(int i = 0; i<STATE::MAX; i++){
		if(_state[i] != nullptr){
			delete _state[i];
			_state[i] = nullptr;
		}
	}
}

void BattleCommander::Update(void){

	if(_cur_state != nullptr){
		_cur_state->Update();
	}

	MouseCursor* mouse_cursor(_accessor->GetMouseCursor());
	if(mouse_cursor != nullptr && _cur_state != nullptr){
		if(mouse_cursor->GetLeftTrigger()){
			_cur_state->MouseLeftDown();
		}

		if(mouse_cursor->GetLeftRelease()){
			_cur_state->MouseLeftUp();
		}

		if(mouse_cursor->GetRightTrigger()){
			_cur_state->MouseRightDown();
		}

		if(mouse_cursor->GetRightRelease()){
			_cur_state->MouseRightUp();
		}
	}
}

void BattleCommander::ChangeState(STATE state){
	if(_cur_state == _state[state]){return;}

	if(_cur_state != nullptr){
		_cur_state->StateOut();
	}
	_cur_state = _state[state];
	_cur_state->StateIn();
}



