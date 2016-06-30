//*****************************************************************************
//  2D�p���_�V�F�[�_
//  author: �������_
//  update: 2015/06/08
//*****************************************************************************
#include "vs2d.h"
#include "renderer.h"
//*****************************************************************************
//�y�R���X�g���N�^�z
//  ���_�o�b�t�@NULL�l�߂Ȃ�
//  ����: �Ȃ�
//*****************************************************************************
VS2D::VS2D(Renderer *master_renderer):
VertexShader(master_renderer, "data/SHADER/shader2d.hlsl", "VS2D"){
	D3DXMatrixOrthoLH(&_projection,
		static_cast<float>(SCREEN_WIDTH),		//����
		static_cast<float>(SCREEN_HEIGHT),		//�悱
		0.0f,									//near�l
		1.0f);									//far�l

	D3DXMATRIX offset;
	D3DXMatrixIdentity(&offset);
	offset._22 = -1.0f;
	offset._41 -= static_cast<float>(SCREEN_WIDTH / 2);
	offset._42 += static_cast<float>(SCREEN_HEIGHT / 2);

	D3DXMatrixMultiply(&_projection, &offset, &_projection);
}

//*****************************************************************************
//�y�f�X�l�z
//  ���Ƃ����Â�
//  ����: �Ȃ�
//*****************************************************************************
VS2D::~VS2D(){}

void VS2D::Set(void){
	LPDIRECT3DDEVICE9 device = _renderer->GetDevice();

	device->SetVertexShader(_shader);

	D3DXMATRIX wvp(_world * _projection);

	//wvp��ݒ�
	_constant->SetMatrix(device, "_wvp", &wvp);

	//world��ݒ�
	_constant->SetMatrix(device, "_world", &_world);

}
