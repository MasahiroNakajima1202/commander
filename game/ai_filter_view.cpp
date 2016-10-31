//*****************************************************************************
//  “GAIƒtƒBƒ‹ƒ^ƒNƒ‰ƒX Ž‹ŠE“à
//  author: ’†“‡«_
//  update: 2016/10/03
//*****************************************************************************
#include "ai_filter_view.h"

#include "battle_actor.h"
//*****************************************************************************
//  constant
//*****************************************************************************

AIFilterView::AIFilterView(BattleObjectAccessor* accessor, BattleActor* owner, float angle) :
AIFilter(accessor, owner),
_angle(angle){
}

AIFilterView::~AIFilterView() {
}

//walk to ‚ÌŠÔ‚ÉŒü‚«‚ª•Ï‚í‚é‚æ‚¤‚É

void AIFilterView::Judge(AIState::POINT* point) {
	if (_owner == nullptr) { return; }

	D3DXVECTOR3 from(_owner->GetPosition());
	D3DXVECTOR3 to(point->position);
	D3DXVECTOR3 v(to - from);

	if (D3DXVec3Dot(&v, &v) == 0.0f) {
		point->enable = true;
		return;
	}

	D3DXVec3Normalize(&v, &v);
	float rotation(_owner->GetRotation().y);
	D3DXVECTOR3 front(sinf(rotation), 0.0f, cosf(rotation));

	float r(D3DXVec3Dot(&v, &front));
	
	point->enable = (r > cosf(_angle));
}
