//*****************************************************************************
//  “GAI
//  author: ’†“‡«_
//  update: 2016/04/11
//*****************************************************************************
#include "enemy_ai.h"

//*****************************************************************************
//  constant
//*****************************************************************************


EnemyAI::EnemyAI(BattleObjectAccessor* accessor, Renderer* renderer, BattleActor* owner):
_accessor(accessor),
_renderer(renderer),
_owner(owner){
}

EnemyAI::~EnemyAI(){
}
