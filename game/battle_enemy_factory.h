//****************************************************************
//  ìGÇÃèâä˙ê∂ê¨ÉNÉâÉX
//  author: íÜìáè´ç_
//  update: 2016/9/27
//****************************************************************

#ifndef _BATTLE_ENEMY_FACTORY_H_
#define _BATTLE_ENEMY_FACTORY_H_

//*****************************************************************************
//  include
//*****************************************************************************
#include "main.h"
#include "scene.h"


#include <d3dx9.h>

//*****************************************************************************
//  class definition
//*****************************************************************************

class Renderer;
class BattleActor;
class ModelField;
class BattleEnemyFactory {
	BattleEnemyFactory() {}
public:
	BattleEnemyFactory(Renderer* renderer, ModelField* field):
	_renderer(renderer),
	_field(field){}
	virtual ~BattleEnemyFactory() {}

	void Build(BattleActor** dest, int limit_length);

private:
	Renderer* _renderer;
	ModelField* _field;

	static const int STR_LENGTH = 64;
	struct ENEMY_DATA {
		char name[STR_LENGTH];
		D3DXVECTOR3 position;
		char filename[STR_LENGTH];

		void Initialize(void) {
			strcpy(name, "");
			strcpy(filename, "");
			position.x = position.y = position.z = 0.0f;
		}
	};
	void LoadByAttribute(ENEMY_DATA& dest, char* attr, int attr_length, char* value, int value_length);
	BattleActor* CreateEnemy(ENEMY_DATA& data);
	void CreateAndAtachAI(unsigned char* str_data, int& cursor);


	void BuildEnemy(char* filename, BattleActor** dest, int limit_length);
	void BuildAI(char* filename, BattleActor** dest, int limit_length);
};


#endif//_GAME_H_