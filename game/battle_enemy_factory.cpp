//****************************************************************
//  “G‚Ì‰Šú¶¬ƒNƒ‰ƒX
//  author: ’†“‡«_
//  update: 2016/9/27
//****************************************************************

#include "battle_enemy_factory.h"

#include "battle_actor.h"
#include "model_field.h"

#include "actor_ai.h"
#include "ai_state.h"
#include "ai_generator_lattice.h"
#include "ai_filter_view.h"
#include "ai_scorer_distance_player.h"

#include <stdio.h>

void BattleEnemyFactory::Build(BattleActor** dest, int limit_length) {
	BuildEnemy("data/Level/enemy.txt", dest, limit_length);
	BuildAI("data/Level/ai.txt", dest[0]);
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
		//•¶š—ñ‚ğ:‚Ì‘OŒã‚Å•ª‰ğ
		int attr_length(0);
		char attr[STR_LENGTH];
		int value_length(0);
		char value[STR_LENGTH];
		sscanf(buffer + cursor, "%s : %s", attr, value);
		attr_length = strlen(attr);
		value_length = strlen(value);

		//MAKE‚È‚ç¶¬
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

		//1‘®«“Ç‚İ‚İ
		LoadByAttribute(enemy_data, attr, attr_length, value, value_length);

		cursor += attr_length + 3 + value_length;
	}

	delete[] buffer;
	buffer = nullptr;
}

void BattleEnemyFactory::BuildAI(char* filename, BattleActor* owner) {
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

	ActorAI* ai(new ActorAI(_accessor, _renderer, owner));
	AIState* ai_state(new AIState(_accessor, _renderer, owner));

	int cursor(0);
	int index(0);
	ENEMY_DATA enemy_data;
	enemy_data.Initialize();
	int mode(0);
	AIData data;
	while (cursor < buffer_length) {
		char word[64] = "";
		int word_length(0);
		int next_cursor(cursor);

		ExtractWord(buffer, cursor, buffer_length, word, word_length, next_cursor);
		cursor = next_cursor;
		if (word[0] == '\0') {break;}

		//GENERATOR / FILTER / SCORE‚È‚ç¶¬
		if (strcmp(word, "GENERATOR") == 0) {
			data.mode = 0;
		}
		if (strcmp(word, "FILTER") == 0) {
			data.mode = 1;
		}
		if (strcmp(word, "SCORE") == 0) {
			data.mode = 2;
		}

		if (strcmp(word, "TYPE") == 0) {
			ExtractWord(buffer, cursor, buffer_length, word, word_length, next_cursor);
			cursor = next_cursor;

			strcpy(data.type, word);
		}
		if (strcmp(word, "NAME") == 0) {
			ExtractWord(buffer, cursor, buffer_length, word, word_length, next_cursor);
			cursor = next_cursor;

			strcpy(data.name, word);
		}
		if (strcmp(word, "STRIDE") == 0) {
			ExtractWord(buffer, cursor, buffer_length, word, word_length, next_cursor);
			cursor = next_cursor;

			sscanf(word, "%f", &data.stride);
		}
		if (strcmp(word, "ANGLE") == 0) {
			ExtractWord(buffer, cursor, buffer_length, word, word_length, next_cursor);
			cursor = next_cursor;

			sscanf(word, "%f", &data.angle);
		}
		if (strcmp(word, "DIST") == 0) {
			ExtractWord(buffer, cursor, buffer_length, word, word_length, next_cursor);
			cursor = next_cursor;

			sscanf(word, "%f", &data.dist);
		}
		if (strcmp(word, "RANGE") == 0) {
			ExtractWord(buffer, cursor, buffer_length, word, word_length, next_cursor);
			cursor = next_cursor;

			sscanf(word, "%f", &data.range);
		}
		if (strcmp(word, "MAKE") == 0) {
			if (data.mode == 0) {
				AIGenerator* gen(CreateGenerator(data, owner));
				ai_state->SetGenerator(gen);
			}
			else if (data.mode == 1) {
				AIFilter* filter(CreateFilter(data, owner));
				ai_state->AddFilter(filter);
			}
			else if (data.mode == 2) {
				AIScorer* scorer(CreateScorer(data, owner));
				ai_state->AddScorer(scorer);
			}
		}
	}

	delete[] buffer;
	buffer = nullptr;

	ai->AddState(ai_state);
	ai->SetCurrentState(ai_state);
	owner->SetAI(ai);
}


void BattleEnemyFactory::ExtractWord(char* src_buffer, int begin, int buffer_length, char* word_buffer, int& word_length, int& end) {
	if (src_buffer == nullptr) { return; }
	if (word_buffer == nullptr) { return; }

	int cursor(begin);

	//previouce spaces
	while (src_buffer[cursor] == ' ' || src_buffer[cursor] == '\n' || src_buffer[cursor] == '\r') {
		cursor++;
	}

	//word
	int index(0);
	while (!(src_buffer[cursor] == ' ' || src_buffer[cursor] == '\n' || src_buffer[cursor] == '\r')) {
		if (cursor >= buffer_length) {
			break;
		}
		word_buffer[index] = src_buffer[cursor];
		cursor++;
		index++;
	}

	word_buffer[index] = '\0';
	word_length = index;

	end = cursor;
}

AIGenerator* BattleEnemyFactory::CreateGenerator(AIData& data, BattleActor* owner) {
	if (strcmp(data.type, "LATTICE") == 0) {
		AIGeneratorLattice* gen(new AIGeneratorLattice(_accessor, owner, 9, 1, 9, data.stride, data.stride, data.stride));
		return gen;
	}

	return nullptr;
}
AIFilter* BattleEnemyFactory::CreateFilter(AIData& data, BattleActor* owner) {
	if (strcmp(data.type, "VIEW") == 0) {
		float angle(data.angle / 180.0f * D3DX_PI);
		AIFilterView* filter(new AIFilterView(_accessor, owner, angle));

		return filter;
	}

	return nullptr;
}
AIScorer* BattleEnemyFactory::CreateScorer(AIData& data, BattleActor* owner) {
	if (strcmp(data.type, "DIST_PLAYER") == 0) {
		AIScorerDistancePlayer* scorer(new AIScorerDistancePlayer(_accessor));
		scorer->SetDistance(data.dist);
		scorer->SetRange(data.range);
		return scorer;
	}

	return nullptr;
}
