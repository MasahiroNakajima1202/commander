//*****************************************************************************
//  scene_xモジュール
//  author: 中島将浩
//  update: 2014/04/23
//*****************************************************************************
#ifndef _SCENE_X_H_
#define _SCENE_X_H_

#include "main.h"
#include "object.h"

//*****************************************************************************
//  constant
//*****************************************************************************

//*****************************************************************************
//  class
//*****************************************************************************
class ObjectX : public Object{
public:

	//*****************************************************************************
	//【コンストラクタ】
	//  頂点バッファNULL詰めなど
	//  引数: なし
	//*****************************************************************************
	ObjectX(Renderer *master_renderer, int layer_no = Object::DRAW_LAYER_MESH);

	//*****************************************************************************
	//【デス様】
	//  あとかたづけ
	//  引数: なし
	//*****************************************************************************
	virtual ~ObjectX(){Release();}

	//*****************************************************************************
	//【初期化】
	//  返り値: 初期化に成功したかどうか
	//  引数: なし
	//*****************************************************************************
	HRESULT SetUp(char *filename = NULL);

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
	virtual void Update(void);

	//*****************************************************************************
	//【描画】
	//  返り値: なし
	//  引数: なし
	//*****************************************************************************
	virtual void Draw(void);

	//accessor
	int GetMeshId(void){return _mesh_id;}
	void SetWireFrameFlag(bool value){_wire_frame = value;}
protected:
	int _mesh_id;
	bool _transparent;
	bool _wire_frame;
};

//accessor

#endif//_SCENE_X_H_