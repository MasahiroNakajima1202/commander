//*****************************************************************************
//  “GAIó‘ÔˆÚsƒNƒ‰ƒX
//  author: ’†“‡«_
//  update: 2016/07/05
//*****************************************************************************
#include "ai_path.h"


AIPath::AIPath(BattleObjectAccessor* accessor, Renderer* renderer, AIState* from, AIState* to):
_accessor(accessor),
_renderer(renderer),
_from(from),
_to(to){
}

AIPath::~AIPath(){
}

void AIPath::Update(void){
}