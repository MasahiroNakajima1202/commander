//****************************************************************
//  gameÉNÉâÉX
//  author: íÜìáè´ç_
//  update: 2014/3/16
//****************************************************************

#ifndef _BATTLE_H_
#define _BATTLE_H_

//*****************************************************************************
//  include
//*****************************************************************************
#include "main.h"
#include "scene.h"


#include <d3dx9.h>

//*****************************************************************************
//  class definition
//*****************************************************************************
class Object;
class Renderer;
class Camera;
class SkinMesh;

class BattleObjectAccessor;
class Judge;
class BattleCommander;
class CameraDirector;
class Battle : public Scene{
public:
	Battle(Renderer *master_renderer, Input *input) :
	Scene(master_renderer, input),
	_battle_object_accessor(nullptr),
	_judge(nullptr),
	_commander(nullptr){
	}
	~Battle(void){
		Release();
	}

	void SetUp(void);
	void Update(void);
	void Draw(void);
	void Release(void);

private:
	BattleObjectAccessor* _battle_object_accessor;
	Judge* _judge;
	BattleCommander* _commander;
};


#endif//_GAME_H_