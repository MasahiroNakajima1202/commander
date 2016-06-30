//*****************************************************************************
//  �s�N�Z���V�F�[�_���N���X
//  �ێ�����萔���W�X�^�͂Ȃ��A�e�N�X�`�����݂̂�ێ�����
//  author: �������_
//  update: 2015/06/08
//*****************************************************************************
#ifndef _PIXEL_SHADER_H_
#define _PIXEL_SHADER_H_

#include "main.h"
#include <d3dx9.h>

//*****************************************************************************
//  constant
//*****************************************************************************

//*****************************************************************************
//  class
//*****************************************************************************
class Renderer;
class PixelShader{
protected:
	PixelShader(){}
public:

	//*****************************************************************************
	//�y�R���X�g���N�^�z
	//  ���_�o�b�t�@NULL�l�߂Ȃ�
	//  ����: �Ȃ�
	//*****************************************************************************
	PixelShader(Renderer *master_renderer, const char *filename, const char *name);

	//*****************************************************************************
	//�y�f�X�l�z
	//  ���Ƃ����Â�
	//  ����: �Ȃ�
	//*****************************************************************************
	virtual ~PixelShader();

	virtual void Set(void);

	//accessor
	void SetTexture(LPDIRECT3DTEXTURE9 value){_texture = value;}

	virtual void SetLightDirection(D3DXVECTOR3 value);
	virtual void SetLightDiffuse(D3DXVECTOR4 value);
	virtual void SetLightPosition(D3DXVECTOR3 value);
	virtual void SetPointLightRatio(float value);
protected:
	Renderer *_renderer;
	IDirect3DPixelShader9 *_shader;
	ID3DXConstantTable *_constant;

	//�萔���W�X�^�p�f�[�^
	LPDIRECT3DTEXTURE9 _texture;

	D3DXVECTOR3 _light_direction;
	D3DXVECTOR4 _light_diffuse;
	D3DXVECTOR3 _light_position;
	float _point_light_ratio;

};

//accessor

#endif//_PIXEL_SHADER_H_