//*****************************************************************************
//  �GAI�t�B���^�N���X ���E��
//  author: �������_
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

void AIFilterView::Judge(AIState::POINT* point) {
	if (_owner == nullptr) { return; }

	D3DXVECTOR3 from(_owner->GetPosition());
	D3DXVECTOR3 to(point->position);
	D3DXVECTOR3 v(to - from);
	D3DXVec3Normalize(&v, &v);
	float rotation(_owner->GetRotation().y);
	D3DXVECTOR3 front(sinf(rotation), 0.0f, cosf(rotation));

	float r(D3DXVec3Dot(&v, &front));
	point->enable = (r > cosf(_angle));
	//AIScore�̒��ۉ��Ǝ�������c�c�̑O�ɓ���m�F���炢��邩 ���łɃf�o�b�O�X�t�B�A�ɐF��������悤��
}