//*****************************************************************************
//  2D�p�s�N�Z���V�F�[�_
//  author: �������_
//  update: 2015/10/28
//*****************************************************************************
#ifndef _PS_2D_H_
#define _PS_2D_H_

#include "pixel_shader.h"

//*****************************************************************************
//  constant
//*****************************************************************************

//*****************************************************************************
//  class
//*****************************************************************************
class Renderer;
class PS2D : public PixelShader{
protected:
	PS2D(){}
public:

	//*****************************************************************************
	//�y�R���X�g���N�^�z
	//  ���_�o�b�t�@NULL�l�߂Ȃ�
	//  ����: �Ȃ�
	//*****************************************************************************
	PS2D(Renderer *master_renderer);

	//*****************************************************************************
	//�y�f�X�l�z
	//  ���Ƃ����Â�
	//  ����: �Ȃ�
	//*****************************************************************************
	virtual ~PS2D();

	//accessor
protected:
};

//accessor

#endif//_PIXEL_SHADER_H_