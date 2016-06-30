//****************************************************************
//  scene_factoryモジュール
//  シーンのジェネレータ
//  author: 中島将浩
//  update: 2013/7/02
//****************************************************************
#ifndef _SCENE_FACTORY_H_
#define _SCENE_FACTORY_H_
//****************************************************************
//  include
//****************************************************************
#include "scene.h"							//シーンを知るため
#include "battle.h"

#include "renderer.h"
class Input;

//****************************************************************
//  class definition
//****************************************************************
//class SceneChanger;						//管理人の存在だけは知っておく
class SceneFactory{
public:
	virtual Scene* Make(Renderer *master_renderer, Input *input) = 0;			//継承が前提の純粋継承関数

private:
};

//戦闘シーンクラスファクトリー
class BattleFactory : public SceneFactory{
public:
	Scene* Make(Renderer *master_renderer, Input *input){return new Battle(master_renderer, input);}

private:
};

//タイトルクラスファクトリー
//class TitleFactory : public SceneFactory{
//public:
//	Scene* Make(Renderer *master_renderer, Input *input){return new Title(master_renderer, input);}
//
//private:
//};
//
////リザルトクラスファクトリー
//class ResultFactory : public SceneFactory{
//public:
//	Scene* Make(Renderer *master_renderer, Input *input){return new Result(master_renderer, input);}
//
//private:
//};

#endif//_SCENE_FACTORY_H_