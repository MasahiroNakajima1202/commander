//*****************************************************************************
//  �X�L�����b�V���p���_�V�F�[�_
//  author: �������_
//  update: 2015/12/03
//*****************************************************************************
#ifndef _VS_SKIN_MESH_H_
#define _VS_SKIN_MESH_H_

#include "vertex_shader.h"
#include "renderer.h"

//*****************************************************************************
//  constant
//*****************************************************************************

//*****************************************************************************
//  class
//*****************************************************************************
class Renderer;
class VSSkinMesh : public VertexShader{
private:
	VSSkinMesh(){}
public:

	//*****************************************************************************
	//�y�R���X�g���N�^�z
	//  ���_�o�b�t�@NULL�l�߂Ȃ�
	//  ����: �Ȃ�
	//*****************************************************************************
	VSSkinMesh(Renderer *master_renderer);

	//*****************************************************************************
	//�y�f�X�l�z
	//  ���Ƃ����Â�
	//  ����: �Ȃ�
	//*****************************************************************************
	virtual ~VSSkinMesh();

	virtual void Set(void);

	//accessor
	virtual void SetWorldArray(D3DXMATRIX* value, int length);

protected:
	D3DXMATRIX _world_array[Renderer::BONE_TABLE_MAX];
};

//accessor

#endif//_VERTEX_SHADER_H_