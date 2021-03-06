//*****************************************************************************
//  numberモジュール
//  サンプルシーン
//  author: 中島将浩
//  update: 2014/06/18
//*****************************************************************************
#ifndef _NUMBER_H_
#define _NUMBER_H_

#include "main.h"

#include <d3dx9.h>


//*****************************************************************************
//  constant
//*****************************************************************************

//*****************************************************************************
//  class
//*****************************************************************************
class Renderer;
class Number{
public:
	enum ALIGN{
		ALIGN_RIGHT = 0,					//右端合わせ
		ALIGN_CENTER,						//中央合わせ
		ALIGN_LEFT,						//左端合わせ
		ALIGN_MAX
	};

	enum COLOR{
		COLOR_WHITE = 0,
		COLOR_RED,
		COLOR_BLUE,
		COLOR_GRAY,
		COLOR_MAX
	};
	//*****************************************************************************
	//【コンストラクタ】
	//  頂点バッファNULL詰めなど
	//  引数: なし
	//*****************************************************************************
	Number(Renderer *master_renderer);

	//*****************************************************************************
	//【デス様】
	//  あとかたづけ
	//  引数: なし
	//*****************************************************************************
	virtual ~Number();

	//*****************************************************************************
	//【初期化】
	//  返り値: 初期化に成功したかどうか
	//  引数: なし
	//*****************************************************************************
	HRESULT SetUp(float x, float y, float width, float height, ALIGN align = ALIGN_CENTER);

	//*****************************************************************************
	//【終了】
	//  返り値: なし
	//  引数: なし
	//*****************************************************************************
	void Release(void);

	//*****************************************************************************
	//【更新】
	//  返り値: なし
	//  引数: なし
	//*****************************************************************************
	void Update(void);

	//*****************************************************************************
	//【描画】
	//  返り値: なし
	//  引数: なし
	//*****************************************************************************
	void Draw(void);
	void Draw(float x, float y);

	//accessor
	void SetPosition(float x, float y);
	void SetValue(int value);
private:
	Renderer *_renderer;
	LPDIRECT3DVERTEXBUFFER9 _vtx;			//頂点バッファのポインタ
	float _x,_y;
	float _width, _height;
	ALIGN _align;
	int _value;								//0〜9

	int _texture_index;				//テクスチャへのポインタ
};


#endif//_NUMBER_H_