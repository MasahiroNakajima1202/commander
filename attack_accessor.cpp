//*****************************************************************************
//  UŒ‚”»’èŠÇ—ƒNƒ‰ƒX
//  author: ’†“‡«_
//  update: 2015/10/25
//*****************************************************************************
#include "attack_accessor.h"
#include "attack.h"
//*****************************************************************************
//  constant
//*****************************************************************************

//*****************************************************************************
//  class
//*****************************************************************************
AttackAccessor::AttackAccessor() :
_count(0){
	for(int i = 0; i<BUFFER_MAX; i++){
		_buffer[i] = nullptr;
	}
}

AttackAccessor::~AttackAccessor(){
	Clear();
}

void AttackAccessor::Update(void){
	for(int i = 0; i<BUFFER_MAX; i++){
		if(_buffer[i] == nullptr){break;}

		if(_buffer[i]->Finished()){
			delete _buffer[i];
			break;
		}

		_buffer[i]->Update();
	}
}


int AttackAccessor::Entry(Attack* attack){
	if(attack == nullptr){return -1;}
	
	int index(SearchSpace());
	if(index >= BUFFER_MAX){return -1;}

	_buffer[index] = attack;
	return index;
}
void AttackAccessor::Leave(int index){
	if(index < 0 || BUFFER_MAX <= index){return;}

	_buffer[index] = nullptr;
}
void AttackAccessor::Leave(Attack* attack){
	int index(GetIndex(attack));

	Leave(index);
}
int AttackAccessor::GetIndex(Attack* attack){
	if(attack == nullptr){return -1;}
	
	int index(-1);

	for(int i = 0; i<BUFFER_MAX; i++){
		if(_buffer[i] == attack){
			index = i;
		}
	}

	return index;
}


void AttackAccessor::Clear(void){
	for(int i = 0; i<BUFFER_MAX; i++){
		if(_buffer[i] != nullptr){
			delete _buffer[i];
			_buffer[i] = nullptr;
		}
	}
}
int AttackAccessor::GetCount(void){
	int count(0);
	for(int i = 0; i<BUFFER_MAX; i++){
		if(_buffer[i] != nullptr){
			count++;
		}
	}

	return count;
}
Attack* AttackAccessor::Get(int index){
	if(index < 0 || BUFFER_MAX <= index){return nullptr;}
	int count(-1);
	Attack* attack(nullptr);
	for(int i = 0; i<BUFFER_MAX; i++){
		if(_buffer[i] != nullptr){
			count++;
		}

		if(count == index){
			attack = _buffer[i];
			break;
		}
	}

	return attack;
}

int AttackAccessor::SearchSpace(void){
	int index(-1);
	for(int i = 0; i<BUFFER_MAX; i++){
		if(_buffer[i] == nullptr){
			index = i;
			break;
		}
	}

	return index;
}

