//*****************************************************************************
//  îªíËÉNÉâÉX
//  author: íÜìáè´ç_
//  update: 2015/10/30
//*****************************************************************************
#ifndef _JUDGE_H_
#define _JUDGE_H_

#include "main.h"
#include <d3dx9.h>

//*****************************************************************************
//  constant
//*****************************************************************************

//*****************************************************************************
//  class
//*****************************************************************************
class Renderer;
class BattleObjectAccessor;
class JudgeBattleEnd;
class SceneFactory;
class Judge{
private:
	Judge(){}
public:

	Judge(BattleObjectAccessor* accessor, Renderer* renderer);

	virtual ~Judge();

	void Update(void);

	//accessor
protected:
	BattleObjectAccessor* _accessor;
	Renderer* _renderer;
	JudgeBattleEnd* _end_judge;
	bool _scene_fade_out;
	SceneFactory* _next;
};



#endif//_NUMBER_H_