//*****************************************************************************
//  スキンメッシュクラス
//  中島将浩
//  UPDATE:2014/03/27
//*****************************************************************************
#ifndef _MY_SKIN_MESH_H_
#define _MY_SKIN_MESH_H_

#include "main.h"
#include "renderer.h"
#include "object.h"


//#define _CONVERTER_

//*****************************************************************************
// class def
//*****************************************************************************
class SkinMesh : public Object{
public:

	//*****************************************************************************
	//【コンストラクタ】
	//  頂点確保もしない
	//  引数: なし
	//*****************************************************************************
	SkinMesh(Renderer *master_renderer, int layer_no = DRAW_LAYER_SKIN_MESH);

	//*****************************************************************************
	//【デストラクタ】
	//  頂点情報の解放を行う。
	//*****************************************************************************
	virtual ~SkinMesh();

	//*****************************************************************************
	//【読み込み】
	//  返り値  : 読み込みの成否
	//  第1引数 : テクスチャのファイルパス
	//*****************************************************************************
#ifdef _CONVERTER_
	bool Load(char *filename);
#endif

	//*****************************************************************************
	//【解放】
	//  頂点データやボーン行列をすべて破棄
	//  返り値  : なし
	//  引数    : なし
	//*****************************************************************************
	virtual void Release(void);

	//*****************************************************************************
	//【更新】
	//  アニメーションと、各ボーン行列の更新
	//  返り値  : なし
	//  第1引数 : なし
	//*****************************************************************************
	virtual void Update(void);

	//*****************************************************************************
	//【描画】
	//  引数の位置を中心として、矩形を描画
	//  返り値  : なし
	//  第1引数 : 描画中心位置のx座標
	//  第2引数 : 描画中心位置のy座標
	//  第3引数 : 描画中心位置のz座標
	//*****************************************************************************
	//virtual void Draw(float x, float y, float z);
	virtual void Draw(void);

	//*****************************************************************************
	//【アニメーションの追加】
	//  新しいアニメーションを追加する
	//  返り値  : なし
	//  第1引数 : 開始フレーム
	//  第2引数 : 終了フレーム
	//  第3引数 : 再生速度
	//*****************************************************************************
	void MakeNewAnimation(float begin, float end, float speed = 1.0f);
	void MakeNewAnimation(float begin, float end, bool loop, char *name, float speed = 1.0f);

	void ExportModelFile(char *filename = "model.ndk");
	void LoadModelFile(char *filename);

	//*****************************************************************************
	//【アニメーション操作】
	//  コメント省略
	//*****************************************************************************
	void SetCurrentAnimation(int anim_id, bool blend = true){
		if(0 <= anim_id && anim_id < _animation_count){
			_previous_animation = _current_animation;
			_current_animation = anim_id;
			_animation_switching = 0;
			_animation_blending = true;
		}
	}
	void PlayCurrentAnimation(void){_play_flag = true;}
	void StopAnimation(void){_play_flag = false;}
	void PlayAnimation(int anim_id, bool blend = true){
		SetCurrentAnimation(anim_id, blend);
		ResetCurrentAnimation();
		PlayCurrentAnimation();
	}
	void ResetAnimation(int anim_id){
		if(0 <= anim_id && anim_id < _animation_count){
			_animation[anim_id].time = 0.0f;
		}
	}
	void ResetCurrentAnimation(void){
		ResetAnimation(_current_animation);
	}
	void ResetAllAnimation(void){
		for(int i = 0; i<_animation_count; i++){
			ResetAnimation(i);
		}
	}
	void GetAnimationName(int index, char *str);
	void SetAnimationName(int index, char *str);
	void PauseAnimation(void){_pause = true;}
	void RestartAnimation(void){_pause = false;}

	void SetReverse(bool value){_reverse = value;}
	void SetTransparent(bool value){_transparent = value;}

	D3DXMATRIX* GetBoneWorldByName(char *name);
	D3DXMATRIX* GetBoneOffsetByName(char *name);

protected:

private:
	struct MESH{
		LPDIRECT3DVERTEXBUFFER9 vertex;
		LPDIRECT3DINDEXBUFFER9 index;
		int vertex_count;
		int index_count;
		D3DMATERIAL9 material;
		char texture_filename[128];			//テクスチャ名
		int texture;						//テクスチャ

		char uvset_name[128];
	};

	struct KEY_FRAME{
		float time;
		D3DXVECTOR3 translation;
		D3DXQUATERNION rotation;
		D3DXVECTOR3 scaling;
	};

	struct BONE{
		int id;
		D3DXMATRIX bone_mtx;				//ボーン行列(こいつはローカル)
		D3DXMATRIX offset_mtx;				//ボーンオフセット行列(こいつはグローバル)
		D3DXMATRIX transform_mtx;			//姿勢(ボーンオフセットと同格、グローバル)
		D3DXMATRIX world_mtx;				//ワールド(最終的なやつなんで、グローバル)

		BONE *child;						//子
		BONE *sibling;						//兄弟

		char name[128];						//ボーンの名前

		int key_count;
		KEY_FRAME *key;

		BONE(){
			child=NULL;
			sibling=NULL;
			memset(name, 0, 128);
			id=-1;
		}
	};

	struct ANIMATION{
		float begin;				//開始時間
		float end;					//終了時間
		float speed;				//再生速度 1.0fがデフォルト
		float time;					//現在の位置
		bool loop;					//loop falg
		char name[64];				//animation name

		ANIMATION(){
			begin = 0.0f;
			end = 0.0f;
			speed = 1.0f;
			time = 0.0f;
			loop = false;
			memset(name, 0, sizeof(char) * 64);
		}
	};

	int _mesh_count;
	MESH *_mesh;
	int _mesh_cursor;

	int _bone_count;
	BONE *_bone;
	BONE *_root;
	float _cur_time;					//動確用
	int _bone_cursor;				//ボーン読み込み先を指すため

	//animation
	int _animation_count;				//animation配列の数
	ANIMATION *_animation;				//animation配列先頭

	int _current_animation;				//現在のアニメーション
	int _previous_animation;
	bool _animation_blending;
	float _animation_blend_weight;
	int _animation_switching;			//アニメーション移行時間
	static const int ANIMATION_SWITCHING_TIME = 8;
	bool _play_flag;
	bool _pause;
	bool _transparent;

	bool _reverse;

	BONE* SearchBoneByName(char *name);

	//回転キーフレーム
	//骨を更新
	void UpdateBoneMatrix(BONE *subject, D3DXMATRIX *parent);

	//行列からrotationを抜き出す
	void ExtractTranslationFromMatrix(D3DXMATRIX *dst, D3DXMATRIX *src);
	void ExtractRotationFromMatrix(D3DXMATRIX *dst, D3DXMATRIX *src);
	void ExtractScalingFromMatrix(D3DXMATRIX *dst, D3DXMATRIX *src);

	//キーフレーム間の補間
	D3DXVECTOR3 InterpolateTranslation(BONE *subject, float time);
	D3DXQUATERNION InterpolateRotation(BONE *subject, float time);
	D3DXVECTOR3 InterpolateScaling(BONE *subject, float time);

	D3DXVECTOR3 InterpolateBlendTranslation(BONE *subject, float prev_time, float next_time, float t);
	D3DXQUATERNION InterpolateBlendRotation(BONE *subject, float prev_time, float next_time, float t);
	D3DXVECTOR3 InterpolateBlendScaling(BONE *subject, float prev_time, float next_time, float t);

	LPDIRECT3DVERTEXDECLARATION9 _decl;

};


#endif//_MY_SKIN_MESH_H_