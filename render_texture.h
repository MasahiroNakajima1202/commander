//*****************************************************************************
//  �����_�[�^�[�Q�b�g�p�̃e�N�X�`���N���X
//  author: �������_
//  update: 2015/06/08
//*****************************************************************************
#ifndef _RENDER_TARGET_H_
#define _RENDER_TARGET_H_

#include "main.h"
#include <d3dx9.h>

//*****************************************************************************
//  constant
//*****************************************************************************

//*****************************************************************************
//  class
//*****************************************************************************
class Renderer;
class RenderTexture{
private:
	RenderTexture(){}
public:

	//*****************************************************************************
	//�y�R���X�g���N�^�z
	//  ���_�o�b�t�@NULL�l�߂Ȃ�
	//  ����: �Ȃ�
	//*****************************************************************************
	RenderTexture(Renderer *master_renderer, int width, int height);

	//*****************************************************************************
	//�y�f�X�l�z
	//  ���Ƃ����Â�
	//  ����: �Ȃ�
	//*****************************************************************************
	virtual ~RenderTexture();

	//*****************************************************************************
	//�y�X�V�z
	//  �Ԃ�l: �Ȃ�
	//  ����: �Ȃ�
	//*****************************************************************************
	//virtual void Update(void);

	void Set(void);				//�e�N�X�`���������_�[�^�[�Q�b�g�ɐݒ�
	void Reposit(void);			//���ǂ�

	LPDIRECT3DTEXTURE9 GetTexture(void){return _texture;}

	//accessor
protected:
	Renderer *_renderer;

	LPDIRECT3DTEXTURE9 _texture;
	IDirect3DSurface9 *_surface;
	IDirect3DSurface9 *_zstencil;

	IDirect3DSurface9 *_def_surface;
	IDirect3DSurface9 *_def_zstencil;

	int _width;
	int _height;

	D3DVIEWPORT9 _viewport;
	D3DVIEWPORT9 _def_viewport;
};

//accessor

#endif//_SCENE_X_H_