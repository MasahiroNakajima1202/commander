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
class BattleObjectAccessor;
class BattleActor;
class ModelField;
class AIGenerator;
class AIFilter;
class AIScorer;
class BattleEnemyFactory {
	BattleEnemyFactory() {}
public:
	BattleEnemyFactory(Renderer* renderer, BattleObjectAccessor* accessor, ModelField* field) :
	_renderer(renderer),
	_accessor(accessor),
	_field(field){}
	virtual ~BattleEnemyFactory() {}

	void Build(BattleActor** dest, int limit_length);

private:
	Renderer* _renderer;
	BattleObjectAccessor* _accessor;
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

	void BuildEnemy(char* filename, BattleActor** dest, int limit_length);
	void BuildAI(char* filename, BattleActor* dest);


	struct AIData {
		int mode;
		char type[32];
		char name[32];
		float stride;
		float angle;
		float dist;
		float range;

		AIData() :
			mode(0),
			stride(0.0f),
			angle(0.0f),
			dist(0.0f),
			range(0.0f){
			strcpy(type, "");
			strcpy(name, "");
		}
	};
	AIGenerator* CreateGenerator(AIData& data, BattleActor* owner);
	AIFilter* CreateFilter(AIData& data, BattleActor* owner);
	AIScorer* CreateScorer(AIData& data, BattleActor* owner);

	void  ExtractWord(char* buffer, int begin, int buffer_length, char* word_buffer, int& word_length, int& end);
};


#endif//_GAME_H_