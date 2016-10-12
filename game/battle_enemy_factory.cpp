//****************************************************************
//  敵の初期生成クラス
//  author: 中島将浩
//  update: 2016/9/27
//****************************************************************

#include "battle_enemy_factory.h"

#include "battle_actor.h"
#include "model_field.h"

#include "actor_ai.h"
#include "ai_state.h"
#include "ai_generator_lattice.h"
#include "ai_filter_view.h"

#include <stdio.h>

void BattleEnemyFactory::Build(BattleActor** dest, int limit_length) {
	BuildEnemy("data/Level/enemy.txt", dest, limit_length);
	//BuildAI("data/Level/ai.txt", dest, limit_length);
	
	ActorAI* ai = new ActorAI(_accessor, _renderer, dest[0]);
	AIState* ai_state = new AIState(_accessor, _renderer, dest[0]);
	AIGeneratorLattice* generator = new AIGeneratorLattice(_accessor, dest[0], 10, 1, 10, 20.0f, 0.0f, 20.0f);
	AIFilterView* filter = new AIFilterView(_accessor, dest[0], D3DX_PI * 0.25f);
	ai_state->AddFilter(filter);
	ai_state->SetGenerator(generator);
	ai->AddState(ai_state);
	dest[0]->SetAI(ai);
	ai->SetCurrentState(ai_state);
}


void BattleEnemyFactory::LoadByAttribute(ENEMY_DATA& dest, char* attr, int attr_length, char* value, int value_length) {
	if (strncmp(attr, "NAME", 4) == 0) {
		strcpy(dest.name, value);
	}
	else if (strncmp(attr, "POSITION", 8) == 0) {
		float x(0.0f), y(0.0f), z(0.0f);
		sscanf(value, "%f,%f,%f", &x, &y, &z);
		dest.position.x = x;
		dest.position.y = y;
		dest.position.z = z;
	}
	else if (strncmp(attr, "FILE", 4) == 0) {
		strcpy(dest.filename, value);
	}
}

BattleActor* BattleEnemyFactory::CreateEnemy(ENEMY_DATA& data){
	BattleActor::PARAMETER param;
	param.hp = 100;
	param.attack = 1;
	param.defence = 1;
	param.max_hp = 100;
	BattleActor* enemy(new BattleActor(_renderer, param, data.filename));

	D3DXVECTOR3 position(data.position);
	position.y = _field->GetHeight(position.x, position.z);
	enemy->SetPosition(position);

	return enemy;
}

void BattleEnemyFactory::BuildEnemy(char* filename, BattleActor** dest, int limit_length) {
	FILE* fp(nullptr);
	fp = fopen(filename, "rb");
	if (fp == nullptr) { return; }

	char* buffer(nullptr);
	int buffer_length(0);

	fseek(fp, 0, SEEK_END);
	buffer_length = ftell(fp);
	buffer = new char[buffer_length];
	fseek(fp, 0, SEEK_SET);
	fread(buffer, 1, buffer_length, fp);
	fclose(fp);

	int cursor(0);
	int index(0);
	ENEMY_DATA enemy_data;
	enemy_data.Initialize();
	while (cursor < buffer_length) {
		if (buffer[cursor] == '\n' || buffer[cursor] == '\r') {
			cursor++;
			continue;
		}
		//文字列を:の前後で分解
		int attr_length(0);
		char attr[STR_LENGTH];
		int value_length(0);
		char value[STR_LENGTH];
		sscanf(buffer + cursor, "%s : %s", attr, value);
		attr_length = strlen(attr);
		value_length = strlen(value);

		//MAKEなら生成
		if (strncmp(attr, "MAKE", 4) == 0) {
			//Create
			if (0 <= index && index < limit_length) {
				dest[index] = CreateEnemy(enemy_data);
				index++;
			}

			enemy_data.Initialize();

			cursor += 6;
			continue;
		}

		//1属性読み込み
		LoadByAttribute(enemy_data, attr, attr_length, value, value_length);

		cursor += attr_length + 3 + value_length;
	}

	delete[] buffer;
	buffer = nullptr;
}

void BattleEnemyFactory::BuildAI(char* filename, BattleActor** dest, int limit_length) {
	FILE* fp(nullptr);
	fp = fopen(filename, "rb");
	if (fp == nullptr) { return; }

	char* buffer(nullptr);
	int buffer_length(0);

	fseek(fp, 0, SEEK_END);
	buffer_length = ftell(fp);
	buffer = new char[buffer_length];
	fseek(fp, 0, SEEK_SET);
	fread(buffer, 1, buffer_length, fp);
	fclose(fp);

	int cursor(0);
	int index(0);
	ENEMY_DATA enemy_data;
	enemy_data.Initialize();
	while (cursor < buffer_length) {
		if (buffer[cursor] == '\n' || buffer[cursor] == '\r') {
			cursor++;
			continue;
		}
		//文字列を:の前後で分解
		int attr_length(0);
		char attr[STR_LENGTH];
		int value_length(0);
		char value[STR_LENGTH];
		sscanf(buffer + cursor, "%s : %s", attr, value);
		attr_length = strlen(attr);
		value_length = strlen(value);

		//GENERATOR / FILTER / SCOREなら生成
		

		cursor += attr_length + 3 + value_length;
	}

	delete[] buffer;
	buffer = nullptr;
}

void BattleEnemyFactory::CreateAndAtachAI(unsigned char* str_data, int& cursor) {
	//kokokara
}
