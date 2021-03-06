//*****************************************************************************
//  sceneモジュール
//  サンプルシーン
//  author: 中島将浩
//  update: 2014/04/15
//*****************************************************************************
#ifndef _SCENE_2D_H_
#define _SCENE_2D_H_

#include "main.h"
#include "object.h"

//*****************************************************************************
//  constant
//*****************************************************************************

//*****************************************************************************
//  class
//*****************************************************************************
class Object2D : public Object{
	public:
	//*****************************************************************************
	//【コンストラクタ】
	//  頂点バッファNULL詰めなど
	//  引数: なし
	//*****************************************************************************
	Object2D(Renderer *master_renderer, int layer_no = Object::DRAW_LAYER_2D);

	//*****************************************************************************
	//【デストラクタ】
	//  あとかたづけ
	//  引数: なし
	//*****************************************************************************
	virtual ~Object2D(){Release();}

	//*****************************************************************************
	//【初期化】
	//  返り値: 初期化に成功したかどうか
	//  引数: なし
	//*****************************************************************************
	HRESULT SetUp(float x, float y, float width, float height, char *filename);

	//*****************************************************************************
	//【終了】
	//  返り値: なし
	//  引数: なし
	//*****************************************************************************
	virtual void Release(void);

	//*****************************************************************************
	//【更新】
	//  返り値: なし
	//  引数: なし
	//*****************************************************************************
	virtual void Update(void);

	//*****************************************************************************
	//【描画】
	//  返り値: なし
	//  引数: なし
	//*****************************************************************************
	virtual void Draw(void);


	void SetV(float v0, float v1, float v2, float v3);		//スピードメーターで欲しくなったVのみの設定

	void SetAlpha(int value);
	void PopUp(D3DXVECTOR2 from, D3DXVECTOR2 to, int frame_length);
	
	//accessor
	void SetRotation(float angle){_rotation.z = angle;}
	void SetOffset(float value){_offset = value;}
	void SetScale(D3DXVECTOR2 value){_scale = value;}
protected:
	LPDIRECT3DVERTEXBUFFER9 _vtx;			//頂点バッファのポインタ
	int _texture;							//テクスチャへのポインタ
	
	D3DXVECTOR2 _scale;

	//ポップアップ機能
	D3DXVECTOR2 _pop_from;
	D3DXVECTOR2 _pop_to;
	bool _pop_up;
	int _pop_count;
	int _pop_length;

	float _offset;

	LPDIRECT3DVERTEXDECLARATION9 _decl;

};

//accessor

#endif//_SCENE_H_