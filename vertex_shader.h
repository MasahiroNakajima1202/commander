//*****************************************************************************
//  ���_�V�F�[�_���N���X
//  �ێ�����萔���W�X�^��wvp�ϊ��n�A���C�g�n�A�}�e���A���n�̂�
//  author: �������_
//  update: 2015/06/08
//*****************************************************************************
#ifndef _VERTEX_SHADER_H_
#define _VERTEX_SHADER_H_

#include "main.h"
#include <d3dx9.h>

//*****************************************************************************
//  constant
//*****************************************************************************

//*****************************************************************************
//  class
//*****************************************************************************
class Renderer;
class VertexShader{
protected:
	VertexShader(){}
public:

	//*****************************************************************************
	//�y�R���X�g���N�^�z
	//  ���_�o�b�t�@NULL�l�߂Ȃ�
	//  ����: �Ȃ�
	//*****************************************************************************
	VertexShader(Renderer *master_renderer, const char *filename, const char *name);

	//*****************************************************************************
	//�y�f�X�l�z
	//  ���Ƃ����Â�
	//  ����: �Ȃ�
	//*****************************************************************************
	virtual ~VertexShader();

	virtual void Set(void);

	//accessor
	virtual void SetWorld(D3DXMATRIX* value){_world = *value;}
	virtual void SetWorldArray(D3DXMATRIX* value, int length){}
	virtual void SetView(D3DXMATRIX* value){_view = *value;}
	virtual void SetProjection(D3DXMATRIX* value){_projection = *value;}
	virtual void SetLightDirection(D3DXVECTOR3 value){_light_direction = value;}
	virtual void SetLightDiffuse(D3DXVECTOR4 value){_light_diffuse = value;}
	virtual void SetMaterialDiffuse(D3DXVECTOR4 value){_material_diffuse = value;}
protected:
	Renderer *_renderer;
	IDirect3DVertexShader9 *_shader;
	ID3DXConstantTable *_constant;

	D3DXMATRIX _world;
	D3DXMATRIX _view;
	D3DXMATRIX _projection;
	
	D3DXVECTOR3 _light_direction;
	D3DXVECTOR4 _light_diffuse;

	D3DXVECTOR4 _material_diffuse;
};

//accessor

#endif//_VERTEX_SHADER_H_