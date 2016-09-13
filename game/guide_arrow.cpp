//*****************************************************************************
//  s‚«æ‚ðŽ¦‚·–îˆó
//  author: ’†“‡«_
//  update: 2015/12/30
//*****************************************************************************
#include "guide_arrow.h"
#include "renderer.h"
#include "sprite3d.h"

GuideArrow::GuideArrow(Renderer *renderer):
_renderer(renderer),
_arrow(nullptr),
_line(nullptr),
_begin(0.0f, 0.0f, 0.0f),
_end(0.0f, 0.0f, 0.0f),
_visible(false){
	_arrow = new Sprite3D(renderer);
	_arrow->SetUp(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 10.0f, 10.0f, "");
	_line = new Sprite3D(renderer);
	_line->SetUp(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 10.0f, 10.0f, "");
}

GuideArrow::~GuideArrow(){
	if(_arrow != nullptr){
		_arrow->Destroy();
		_arrow = nullptr;
	}

	if(_line != nullptr){
		_line->Destroy();
		_line = nullptr;
	}
}

void GuideArrow::Update(void){
	CommitImage();
}

void GuideArrow::SetBeginPosition(D3DXVECTOR3 position){
	_begin = position;

	CommitImage();
}

void GuideArrow::SetEndPosition(D3DXVECTOR3 position){
	_end = position;

	CommitImage();
}

//accessor
void GuideArrow::SetVisible(bool visible){
	_visible = visible;

	if(_arrow != nullptr){
		_arrow->SetVisible(visible);
	}

	if(_line != nullptr){
		_line->SetVisible(visible);
	}
}

void GuideArrow::CommitImage(void){
	D3DXVECTOR3 direction(_end - _begin);
	float length(D3DXVec3Length(&direction));
	if(length > 0.0f){
		direction /= length;
	}
	else{
		direction = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
	}

	const float ARROW_MAX_LENGTH(10.0f);
	const float ARROW_WIDTH(20.0f);
	const float LINE_WIDTH(10.0f);

	float arrow_length(min(ARROW_MAX_LENGTH, length));
	float line_length(max(0.0f, length - arrow_length));

	D3DXVECTOR3 line_center(_begin + direction * (line_length * 0.5f));
	D3DXVECTOR3 arrow_center(_begin + direction * (line_length + arrow_length * 0.5f));

	D3DXVECTOR3 rotation(D3DX_PI * 0.5f, 0.0f, -atan2f(direction.x, direction.z));

	line_center.y += 1.0f;
	arrow_center.y += 1.0f;

	if(_arrow != nullptr){
		_arrow->SetPosition(arrow_center);
		_arrow->SetSize(D3DXVECTOR3(ARROW_WIDTH, arrow_length, 0.0f));
		_arrow->SetRotation(rotation);
	}

	if(_line != nullptr){
		_line->SetPosition(line_center);
		_line->SetSize(D3DXVECTOR3(LINE_WIDTH, line_length, 0.0f));
		_line->SetRotation(rotation);
	}
}

