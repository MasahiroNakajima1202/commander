//*****************************************************************************
//  “GAI
//  author: ’†“‡«_
//  update: 2016/08/16
//*****************************************************************************
#include "actor_ai.h"

#include "ai_state.h"
#include "ai_path.h"
//*****************************************************************************
//  constant
//*****************************************************************************

//*****************************************************************************
//  class
//*****************************************************************************

ActorAI::ActorAI(BattleObjectAccessor* accessor, Renderer* renderer, BattleActor* owner) :
_accessor(accessor),
_renderer(renderer),
_owner(owner),
_current_state(nullptr){
	for (int i = 0; i < PATH_MAX; i++){
		_path_array[i] = nullptr;
	}

	for (int i = 0; i < STATE_MAX; i++) {
		_state_array[i] = nullptr;
	}
}

ActorAI::~ActorAI() {

}

void ActorAI::Update(void) {
	if (_current_state != nullptr){
		_current_state->Update();
	}

#pragma region state switching
	if (_current_state != nullptr) {
		AIState* next(_current_state->CheckPath());
		if (next != nullptr) {
			_current_state = next;
		}
	}
#pragma endregion
}

void ActorAI::SetCurrentState(AIState* value) {
	if (value == nullptr) {
		_current_state = value;
		return;
	}

	//©•ª‚Ì‚¿•¨‚Æ‚µ‚Ä“o˜^‚³‚ê‚Ä‚¢‚é‚à‚Ì‚¾‚¯‚ğİ’è
	bool exist(false);
	for (int i = 0; i < STATE_MAX; i++) {
		if (_state_array[i] == nullptr) { continue; }

		exist |= _state_array[i] == value;
	}

	if (exist) {
		_current_state = value;
	}
}

ActorAI* ActorAI::AddState(AIState* state) {
	if (state == nullptr) { return this; }

	for (int i = 0; i < STATE_MAX; i++)	{
		if (_state_array[i] == state) {
			return this;
		}
	}

	int index(-1);
	for (int i = 0; i < STATE_MAX; i++){
		if (_state_array[i] == nullptr) {
			index = i;
			break;
		}
	}

	if (0 <= index || index < STATE_MAX) {
		_state_array[index] = state;
	}

	return this;
}

ActorAI* ActorAI::AddPath(AIPath* path) {
	if (path == nullptr) { return this; }

	for (int i = 0; i < PATH_MAX; i++) {
		if (_path_array[i] == path) {
			return this;
		}
	}

	int index(-1);
	for (int i = 0; i < PATH_MAX; i++) {
		if (_path_array[i] == nullptr) {
			index = i;
			break;
		}
	}

	if (0 <= index || index < PATH_MAX) {
		_path_array[index] = path;
	}

	return this;
}

