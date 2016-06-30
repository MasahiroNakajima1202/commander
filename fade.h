//=============================================================================
//  fade機能のモジュール
//  author: 中島将浩
//  update: 2013/07/16
//=============================================================================
#ifndef _FADE_H_
#define _FADE_H_

#include "main.h"
#include "renderer.h"

//*****************************************************************************
//  constant
//*****************************************************************************

//*****************************************************************************
//  class def
//*****************************************************************************
class Renderer;
class Fade{
public:
	typedef enum{
		FADE_NON = 0,
		FADE_IN,
		FADE_OUT,
		FADE_MAX
	}FADE;

	Fade(){}
	~Fade(){}

	static bool SetUp(Renderer *master_renderer);
	static void Update(void);
	static void Draw(void);
	static void Release(void);

	static void FadeIn(void);
	static void FadeOut(void);
	static bool IsBlackOut(void);
private:
	static LPDIRECT3DTEXTURE9 _texture;			//フェードのテクスチャ
	static LPDIRECT3DVERTEXBUFFER9 _vtx;		//頂点
	static FADE _state;
	static int _value;
	static Renderer *_renderer;
	static LPDIRECT3DVERTEXDECLARATION9 _decl;
};

#endif//_FADE_H_