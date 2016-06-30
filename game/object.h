//*****************************************************************************
//  sceneモジュール
//  サンプルシーン
//  author: 中島将浩
//  update: 2014/04/15
//*****************************************************************************
#ifndef _OBJECT_H_
#define _OBJECT_H_

#include "main.h"

#include <d3dx9.h>

//*****************************************************************************
//  constant
//*****************************************************************************

//*****************************************************************************
//  class
//*****************************************************************************
class Renderer;					//描画機能を利用するための前方宣言

class Object{
public:
	enum DRAW_LAYER{
		DRAW_LAYER_FIELD = 0,
		DRAW_LAYER_SHADOW,
		DRAW_LAYER_SKIN_MESH,
		DRAW_LAYER_MESH,
		DRAW_LAYER_INSTANCING_MESH,
		DRAW_LAYER_ALPHA,
		DRAW_LAYER_BILLBOARD,
		DRAW_LAYER_EFFEKSEER,
		DRAW_LAYER_2D,
		DRAW_LAYER_FADE,
		DRAW_LAYER_SCREEN,				//画面分割後の描画用
		DRAW_LAYER_EFFEKSEER_2D,
		DRAW_LAYER_MAX
	};
	//*****************************************************************************
	//【コンストラクタ】
	//  第1引数: れんだらー
	//*****************************************************************************
	Object(Renderer *master_renderer, int layer_no = DRAW_LAYER_MESH) : NATURAL_SPEED_DOWN(0.975f){
		_renderer = master_renderer;
		_next = NULL;
		_layer = layer_no;
		_death = false;
		_position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		_pre_position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		_velocity = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		_rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		_pre_rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		_size = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
		_radius = 0.0f;
		_visible = true;
		PushBackToList(layer_no);
	}

	//*****************************************************************************
	//【デス様】
	//  あとかたづけ
	//  引数: なし
	//*****************************************************************************
	virtual ~Object(){_renderer = NULL; RemoveFromList(_layer);}

	//*****************************************************************************
	//【初期化】
	//  返り値: 初期化に成功したかどうか
	//  引数: なし
	//*****************************************************************************
	virtual HRESULT SetUp(void);

	//*****************************************************************************
	//【終了(pure virtual)】
	//  返り値: なし
	//  引数: なし
	//*****************************************************************************
	virtual void Release(void) = 0;

	//*****************************************************************************
	//【更新(pure virtual)】
	//  返り値: なし
	//  引数: なし
	//*****************************************************************************
	virtual void Update(void);

	//*****************************************************************************
	//【描画(pure virtual)】
	//  返り値: なし
	//  引数: なし
	//*****************************************************************************
	virtual void Draw(void) = 0;

	//*****************************************************************************
	//【しね！】
	//  返り値: なし
	//  引数: なし
	//*****************************************************************************
	virtual void Destroy(){_death = true;}

	//*****************************************************************************
	//【しね！ハイエナどもめ！】
	//  返り値: なし
	//  引数: なし
	//*****************************************************************************
	static void DestroyAll(void);

	//*****************************************************************************
	//【全更新】
	//  返り値: なし
	//  引数: なし
	//*****************************************************************************
	static void UpdateAll(void);

	//*****************************************************************************
	//【描画】
	//  返り値: なし
	//  引数: なし
	//*****************************************************************************
	static void DrawAll(void);
	static void DrawLayer(DRAW_LAYER layer);

	//*****************************************************************************
	//【全削除】
	//  死亡フラグ回収
	//  返り値: なし
	//  引数: なし
	//*****************************************************************************
	static void Flush(void);

	//*****************************************************************************
	//【こいつ、います？】
	//  対象のオブジェクトが存在するかどうか
	//  返り値: なし
	//  引数: なし
	//*****************************************************************************
	static bool Extist(Object *object);

	//*****************************************************************************
	//【当たり判定(球と球)】
	//  二つのオブジェクトの当たり判定を調べます as ball and ball
	//  返り値: なし
	//  引数: なし
	//*****************************************************************************
	static bool HitCheckBallBall(Object* ball_a, Object* ball_b);

	//*****************************************************************************
	//【当たり判定(点と箱)】
	//  二つのオブジェクトの当たり判定を調べます as point and box
	//  返り値: なし
	//  引数: なし
	//*****************************************************************************
	static bool HitCheckPointBox(Object* point, Object* box);

	//*****************************************************************************
	//【当たり判定(点と円柱)】
	//  二つのオブジェクトの当たり判定を調べます as point and pole
	//  返り値: なし
	//  引数: なし
	//*****************************************************************************
	static bool HitCheckPointPole(Object* point, Object* pole);

	virtual void GetWorldMatrix(D3DXMATRIX* out);

	//accessor
	D3DXVECTOR3 GetPosition(void){return _position;}
	D3DXVECTOR3 GetPrePosition(void){return _pre_position;}
	D3DXVECTOR3 GetRotation(void){return _rotation;}
	D3DXVECTOR3 GetPreRotation(void){return _pre_rotation;}
	D3DXVECTOR3 GetVelocity(void){return _velocity;}
	D3DXVECTOR3 GetSize(void){return _size;}
	void SetVelocity(D3DXVECTOR3 src){_velocity = src;}
	void SetPosition(D3DXVECTOR3 value){_position = value;}
	float GetHitRadius(void){return _radius;}
	void SetHitRadius(float value){_radius = value;}
	void AddRotation(D3DXVECTOR3 value){_rotation += value;}
	void SetVisible(bool value){ _visible = value; }
	bool GetVisible(void){ return _visible; }
	void SetSize(D3DXVECTOR3 value){ _size = value; }
	void SetSize(float value){ _size.x = _size.y = _size.z = value; }
	void SetRotation(D3DXVECTOR3 value){_rotation = value;}
	bool Dead(void){return _death;}

protected:
	Renderer *_renderer;
	//当たり判定用の変数群
	D3DXVECTOR3 _position;
	D3DXVECTOR3 _pre_position;
	D3DXVECTOR3 _velocity;
	D3DXVECTOR3 _rotation;
	D3DXVECTOR3 _pre_rotation;
	D3DXVECTOR3 _size;
	float _radius;
	bool _visible;							//可視フラグ

	//子クラスから利用できる、速度の自然減衰
	void NaturalSpeedDown(void){_velocity *= NATURAL_SPEED_DOWN;}

	

private:
	Object *_next;
	int _layer;
	bool _death;								//死亡フラグ
	const float NATURAL_SPEED_DOWN;

	static Object *_top[DRAW_LAYER_MAX];
	void PushBackToList(int layer_no);
	void RemoveFromList(int layer_no);

};

//accessor

#endif//_SCENE_H_