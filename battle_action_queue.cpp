//*****************************************************************************
//  s“®—\–ñ
//  author: ’†“‡«_
//  update: 2015/10/25
//*****************************************************************************
#include "battle_action_queue.h"
#include "battle_action.h"
//*****************************************************************************
//  constant
//*****************************************************************************


BattleActionQueue::BattleActionQueue():
_read_cursor(0),
_write_cursor(0){
	for(int i=0; i<BUFFER_MAX; i++){
		_buffer[i] = nullptr;
	}
}

BattleActionQueue::~BattleActionQueue(){
	Clear();
}

void BattleActionQueue::Enqueue(BattleAction* value){
	if(value == nullptr){return;}

	//if buffer is full
	if((_write_cursor + 1) % BUFFER_MAX == _read_cursor){return;}

	_buffer[_write_cursor] = value;
	_write_cursor++;
	_write_cursor%=BUFFER_MAX;

}
BattleAction* BattleActionQueue::Dequeue(void){
	if(_read_cursor == _write_cursor){return nullptr;}

	BattleAction* ret(_buffer[_read_cursor]);
	_buffer[_read_cursor] = nullptr;
	_read_cursor++;
	_read_cursor%=BUFFER_MAX;

	return ret;
}

bool BattleActionQueue::IsEmpty(void){
	return _read_cursor == _write_cursor;
}

void BattleActionQueue::Clear(void){
	while(!IsEmpty()){
		delete Dequeue();
	}
}


