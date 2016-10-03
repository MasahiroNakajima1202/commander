//*****************************************************************************
//  “GAI“_—ñ¶¬‚­‚ç‚·ƒNƒ‰ƒX
//  author: ’†“‡«_
//  update: 2016/09/06
//*****************************************************************************
#include "ai_generator.h"
#include "ai_state.h"
#include "battle_actor.h"

#include "debug.h"

AIGenerator::AIGenerator(BattleObjectAccessor* accessor, BattleActor* owner) :
	_accessor(accessor),
	_owner(owner){
}

AIGenerator::~AIGenerator() {
	
}
