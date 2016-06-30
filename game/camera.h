//*****************************************************************************
//  camera���W���[��
//  author: �������_
//  update: 2014/04/23
//*****************************************************************************
#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "main.h"

#include <d3dx9.h>
//*****************************************************************************
//  constant
//*****************************************************************************

//*****************************************************************************
//  class
//*****************************************************************************
class Renderer;
class GameInput;

class Camera{
public:
	//*****************************************************************************
	//�y�R���X�g���N�^�z
	//  ��1����: ��񂾂�[
	//*****************************************************************************
	Camera(Renderer *master_renderer){_renderer = master_renderer;}

	//*****************************************************************************
	//�y�f�X�l�z
	//  ���Ƃ����Â�
	//  ����: �Ȃ�
	//*****************************************************************************
	virtual ~Camera(){_renderer = NULL;}

	//*****************************************************************************
	//�y�������z
	//  �Ԃ�l: �������ɐ����������ǂ���
	//  ����: �Ȃ�
	//*****************************************************************************
	HRESULT SetUp(void);

	//*****************************************************************************
	//�y�I���z
	//  �Ԃ�l: �Ȃ�
	//  ����: �Ȃ�
	//*****************************************************************************
	void Release(void);

	//*****************************************************************************
	//�y�X�V�z
	//  �Ԃ�l: �Ȃ�
	//  ����: �Ȃ�
	//*****************************************************************************
	void Update(GameInput *input = NULL);

	//*****************************************************************************
	//�y�Z�b�g�z
	//  �Ԃ�l: �Ȃ�
	//  ����: �Ȃ�
	//*****************************************************************************
	virtual void Set(void);

	//accessor
	D3DXMATRIX *GetView(void){ return &_view; }
	D3DXMATRIX *GetProjection(void){ return &_proj; }
	D3DXVECTOR3 GetPosition(void){return _eye;}
	D3DXVECTOR3 GetAtPosition(void){return _at;}

	void SetEyePosition(D3DXVECTOR3 value){_eye = _dst_eye = value;}
	void SetAtPosition(D3DXVECTOR3 value){_at = _dst_at = value;}
	void SetDestEyePosition(D3DXVECTOR3 value){_dst_eye = value;}
	void SetDestAtPosition(D3DXVECTOR3 value){_dst_at = value;}
	void SetUpVector(D3DXVECTOR3 value){_up = value;}
	D3DXVECTOR3 GetRight(void){return _right;}
	void SetRight(D3DXVECTOR3 value){_right = value;}
protected:
	Renderer *_renderer;

	D3DXVECTOR3 _eye;										//�J�������_
	D3DXVECTOR3 _at;										//�J���������_
	D3DXVECTOR3 _up;										//�J����������x�N�g��

	D3DXVECTOR3 _dst_eye;									//�J�����n�_�ړI�n
	D3DXVECTOR3 _dst_at;									//�J���������_�ړI�n

	D3DXVECTOR3 _front;
	D3DXVECTOR3 _right;

	float _length;											//�����_�܂ł̒���

	D3DXMATRIX _view;									//�r���[�s��
	D3DXMATRIX _proj;									//�ˉe�s��


};

//accessor

#endif//_CAMERA_H_