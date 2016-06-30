//*****************************************************************************
//  ”»’èƒNƒ‰ƒX
//  author: ’†“‡«_
//  update: 2015/10/30
//*****************************************************************************
#include "judge.h"
#include "battle_object_accessor.h"
#include "attack.h"
#include "attack_sphere.h"
#include "mouse_cursor.h"
#include "cursor3d.h"

#include "hit_checker_attack_actor.h"
#include "hit_checker_actor_field.h"
#include "hit_checker_actor_tile_field.h"
#include "hit_checker_actor_gimmick.h"
#include "judge_battle_end.h"

#include "manager.h"
#include "scene_factory.h"
#include "fade.h"

#include "battle_end_demo.h"
#include "battle_end_demo_none.h"
#include "battle_end_demo_win.h"
#include "battle_end_demo_lose.h"

//test
#include "battle_skill.h"
#include "battle_skill_attack.h"
#include "battle_actor.h"

Judge::Judge(BattleObjectAccessor* accessor, Renderer* renderer):
_accessor(accessor),
_renderer(renderer),
_end_judge(nullptr),
_scene_fade_out(false),
_next(nullptr){
	_end_judge = new JudgeBattleEnd(accessor);
}

Judge::~Judge(){
	if(_end_judge != nullptr){
		delete _end_judge;
		_end_judge = nullptr;
	}

	if(_next != nullptr){
		delete _next;
		_next = nullptr;
	}
}

void Judge::Update(void){
	//hit check attack and actor
	HitCheckerAttackActor attack_actor(_accessor, _renderer);
	attack_actor.Update();

	//hit check attack and actor
	//HitCheckerActorField(_accessor).Update();
	HitCheckerActorTileField actor_field(_accessor);
	actor_field.Update();

	HitCheckerkActorGimmick actor_gimmick(_accessor);
	actor_gimmick.Update();

	//test: create attack
	MouseCursor* mouse_cursor(_accessor->GetMouseCursor());
	Cursor3D* cursor3d(_accessor->GetCursor3D());
	//if(mouse_cursor->GetLeftTrigger()){
	//	D3DXVECTOR3 position(cursor3d->GetPosition());
	//	AttackSphere* attack(new AttackSphere(position, 20.0f, 60));
	//}

	if(_end_judge != nullptr){
		_end_judge->Update();
	}


	if(_end_judge->End() && _accessor->GetEndDemo() == nullptr){
		if(_end_judge->Lose()){
			_next = new BattleFactory();
			_accessor->SetEndDemo(new BattleEndDemoLose(_accessor, _renderer));
		}
		else if(_end_judge->Win()){
			_next = new BattleFactory();
			_accessor->SetEndDemo(new BattleEndDemoWin(_accessor, _renderer));
		}
		else{
			_next = new BattleFactory();
			_accessor->SetEndDemo(new BattleEndDemoNone(_accessor, _renderer));
		}
	}

	BattleEndDemo* end_demo(_accessor->GetEndDemo());
	bool demo_finished(end_demo != nullptr && end_demo->Finished());
	if(_end_judge->End() && demo_finished && !_scene_fade_out){
		Manager::SetSceneFactory(_next);
		Fade::FadeOut();
		_scene_fade_out = true;
		_next = nullptr;
	}
}