//*****************************************************************************
//  I—¹”»’èƒNƒ‰ƒX
//  author: ’†“‡«_
//  update: 2015/11/30
//*****************************************************************************
#include "battle_end_demo_none.h"

BattleEndDemoNone::BattleEndDemoNone(BattleObjectAccessor* accessor, Renderer* renderer):
BattleEndDemo(accessor, renderer){
}

BattleEndDemoNone::~BattleEndDemoNone(){
}

void BattleEndDemoNone::Update(void){
}

bool BattleEndDemoNone::Finished(void){
	return true;
}

