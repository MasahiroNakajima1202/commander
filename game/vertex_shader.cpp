//*****************************************************************************
//  ���_�V�F�[�_���N���X �P���ȃ����o�[�g���T�|�[�g���܂�
//  author: �������_
//  update: 2015/06/08
//*****************************************************************************

#include "vertex_shader.h"
#include "renderer.h"

//*****************************************************************************
//  constant
//*****************************************************************************


//*****************************************************************************
//�y�R���X�g���N�^�z
//  ���_�o�b�t�@NULL�l�߂Ȃ�
//  ����: �Ȃ�
//*****************************************************************************
VertexShader::VertexShader(Renderer *master_renderer, const char *filename, const char *name) :
_renderer(master_renderer),
_shader(NULL),
_constant(NULL){
	LPDIRECT3DDEVICE9 device = _renderer->GetDevice();

	//�V�F�[�_�̓ǂݍ���
	LPD3DXBUFFER code = NULL;
	LPD3DXBUFFER error = NULL;

	HRESULT hr = D3DXCompileShaderFromFile(filename, NULL, NULL, name, "vs_2_0", 0, &code, &error, &_constant);

	if(FAILED(hr)){
		MessageBox(NULL, (LPSTR)error->GetBufferPointer(), "error", MB_OK);
	}

	device->CreateVertexShader((DWORD*)code->GetBufferPointer(), &_shader);

	if(error != NULL){
		error->Release();
		error = NULL;
	}
	if(code != NULL){
		code->Release();
		code = NULL;
	}

	//�e�萔���W�X�^�p�ϐ��̏�����
	D3DXMatrixIdentity(&_world);
	D3DXMatrixIdentity(&_view);
	D3DXMatrixIdentity(&_projection);
	
	_light_direction = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	_light_diffuse = D3DXVECTOR4(0.0f, 0.0f, 0.0f, 0.0f);

	_material_diffuse = D3DXVECTOR4(0.0f, 0.0f, 0.0f, 0.0f);
}

//*****************************************************************************
//�y�f�X�l�z
//  ���Ƃ����Â�
//  ����: �Ȃ�
//*****************************************************************************
VertexShader::~VertexShader(){
	if(_shader != NULL){
		_shader->Release();
		_shader = NULL;
	}
	if(_constant != NULL){
		_constant->Release();
		_constant = NULL;
	}
}

void VertexShader::Set(void){
	LPDIRECT3DDEVICE9 device = _renderer->GetDevice();

	device->SetVertexShader(_shader);

	D3DXMATRIX wvp(_world * _view * _projection);

	_constant->SetMatrix(device, "_wvp", &wvp);

	_constant->SetMatrix(device, "_world", &_world);

	_constant->SetFloatArray(device, "_light_direction", (float*)&_light_direction, 4);
	_constant->SetFloatArray(device, "_light_diffuse", (float*)&_light_diffuse, 4);

	_constant->SetFloatArray(device, "_mat_diffuse", (float*)&_material_diffuse, 4);
}

