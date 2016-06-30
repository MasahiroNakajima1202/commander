//*****************************************************************************
//  I—¹”»’èƒNƒ‰ƒX
//  author: ’†“‡«_
//  update: 2015/11/30
//*****************************************************************************
#include "battle_end_demo_win.h"

#include "object2d.h"

BattleEndDemoWin::BattleEndDemoWin(BattleObjectAccessor* accessor, Renderer* renderer):
BattleEndDemo(accessor, renderer),
_logo(nullptr),
_frame_count(0){
	_logo = new Object2D(renderer);
	float x(static_cast<float>(SCREEN_WIDTH) / 2.0f), y(static_cast<float>(SCREEN_HEIGHT) / 2.0f);
	float width(400), height(100);
	_logo->SetUp(x, y, width, height, "data/TEXTURE/goal.png");
	_logo->PopUp(D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2(1.0f, 1.0f), 10);
}

BattleEndDemoWin::~BattleEndDemoWin(){
	if(_logo != nullptr){
		_logo->Destroy();
		_logo = nullptr;
	}
}

void BattleEndDemoWin::Update(void){
	_frame_count++;
}

bool BattleEndDemoWin::Finished(void){
	return _frame_count > 60 * 5;
}

