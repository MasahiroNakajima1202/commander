//*****************************************************************************
//  scene���W���[��
//  �T���v���V�[��
//  author: �������_
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
class Renderer;					//�`��@�\�𗘗p���邽�߂̑O���錾

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
		DRAW_LAYER_SCREEN,				//��ʕ�����̕`��p
		DRAW_LAYER_EFFEKSEER_2D,
		DRAW_LAYER_MAX
	};
	//*****************************************************************************
	//�y�R���X�g���N�^�z
	//  ��1����: ��񂾂�[
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
	//�y�f�X�l�z
	//  ���Ƃ����Â�
	//  ����: �Ȃ�
	//*****************************************************************************
	virtual ~Object(){_renderer = NULL; RemoveFromList(_layer);}

	//*****************************************************************************
	//�y�������z
	//  �Ԃ�l: �������ɐ����������ǂ���
	//  ����: �Ȃ�
	//*****************************************************************************
	virtual HRESULT SetUp(void);

	//*****************************************************************************
	//�y�I��(pure virtual)�z
	//  �Ԃ�l: �Ȃ�
	//  ����: �Ȃ�
	//*****************************************************************************
	virtual void Release(void) = 0;

	//*****************************************************************************
	//�y�X�V(pure virtual)�z
	//  �Ԃ�l: �Ȃ�
	//  ����: �Ȃ�
	//*****************************************************************************
	virtual void Update(void);

	//*****************************************************************************
	//�y�`��(pure virtual)�z
	//  �Ԃ�l: �Ȃ�
	//  ����: �Ȃ�
	//*****************************************************************************
	virtual void Draw(void) = 0;

	//*****************************************************************************
	//�y���ˁI�z
	//  �Ԃ�l: �Ȃ�
	//  ����: �Ȃ�
	//*****************************************************************************
	virtual void Destroy(){_death = true;}

	//*****************************************************************************
	//�y���ˁI�n�C�G�i�ǂ��߁I�z
	//  �Ԃ�l: �Ȃ�
	//  ����: �Ȃ�
	//*****************************************************************************
	static void DestroyAll(void);

	//*****************************************************************************
	//�y�S�X�V�z
	//  �Ԃ�l: �Ȃ�
	//  ����: �Ȃ�
	//*****************************************************************************
	static void UpdateAll(void);

	//*****************************************************************************
	//�y�`��z
	//  �Ԃ�l: �Ȃ�
	//  ����: �Ȃ�
	//*****************************************************************************
	static void DrawAll(void);
	static void DrawLayer(DRAW_LAYER layer);

	//*****************************************************************************
	//�y�S�폜�z
	//  ���S�t���O���
	//  �Ԃ�l: �Ȃ�
	//  ����: �Ȃ�
	//*****************************************************************************
	static void Flush(void);

	//*****************************************************************************
	//�y�����A���܂��H�z
	//  �Ώۂ̃I�u�W�F�N�g�����݂��邩�ǂ���
	//  �Ԃ�l: �Ȃ�
	//  ����: �Ȃ�
	//*****************************************************************************
	static bool Extist(Object *object);

	//*****************************************************************************
	//�y�����蔻��(���Ƌ�)�z
	//  ��̃I�u�W�F�N�g�̓����蔻��𒲂ׂ܂� as ball and ball
	//  �Ԃ�l: �Ȃ�
	//  ����: �Ȃ�
	//*****************************************************************************
	static bool HitCheckBallBall(Object* ball_a, Object* ball_b);

	//*****************************************************************************
	//�y�����蔻��(�_�Ɣ�)�z
	//  ��̃I�u�W�F�N�g�̓����蔻��𒲂ׂ܂� as point and box
	//  �Ԃ�l: �Ȃ�
	//  ����: �Ȃ�
	//*****************************************************************************
	static bool HitCheckPointBox(Object* point, Object* box);

	//*****************************************************************************
	//�y�����蔻��(�_�Ɖ~��)�z
	//  ��̃I�u�W�F�N�g�̓����蔻��𒲂ׂ܂� as point and pole
	//  �Ԃ�l: �Ȃ�
	//  ����: �Ȃ�
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
	//�����蔻��p�̕ϐ��Q
	D3DXVECTOR3 _position;
	D3DXVECTOR3 _pre_position;
	D3DXVECTOR3 _velocity;
	D3DXVECTOR3 _rotation;
	D3DXVECTOR3 _pre_rotation;
	D3DXVECTOR3 _size;
	float _radius;
	bool _visible;							//���t���O

	//�q�N���X���痘�p�ł���A���x�̎��R����
	void NaturalSpeedDown(void){_velocity *= NATURAL_SPEED_DOWN;}

	

private:
	Object *_next;
	int _layer;
	bool _death;								//���S�t���O
	const float NATURAL_SPEED_DOWN;

	static Object *_top[DRAW_LAYER_MAX];
	void PushBackToList(int layer_no);
	void RemoveFromList(int layer_no);

};

//accessor

#endif//_SCENE_H_