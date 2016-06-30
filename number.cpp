//*****************************************************************************
//  number���W���[��
//  �T���v���V�[��
//  author: �������_
//  update: 2014/06/18
//*****************************************************************************

#include "number.h"
#include "renderer.h"

//*****************************************************************************
//  static variables
//*****************************************************************************


//*****************************************************************************
//�y�R���X�g���N�^�z
//  ���_�o�b�t�@NULL�l�߂Ȃ�
//  ����: �Ȃ�
//*****************************************************************************
Number::Number(Renderer *master_renderer){
	_renderer = master_renderer;
	_texture_index = -1;
	_vtx = NULL;
	_x = 0.0f;
	_y = 0.0f;
	_align = ALIGN_LEFT;
	_value = 0;
}

//*****************************************************************************
//�y�f�X�l�z
//  ���Ƃ����Â�
//  ����: �Ȃ�
//*****************************************************************************
Number::~Number(){
	Release();
}

//*****************************************************************************
//�y�������z
//  �Ԃ�l: �������ɐ����������ǂ���
//  ����: �Ȃ�
//*****************************************************************************
HRESULT Number::SetUp(float x, float y, float width, float height, ALIGN align){
	LPDIRECT3DDEVICE9 device = NULL;			//�f�o�C�X�擾�p
	VERTEX_2D *work_vtx = NULL;					//���_���擪�A�h���X�i�[�p
	float x_align = 0.0f;

	x_align = -width + (float)align * width * 0.5f;

	//�f�o�C�X�̎擾
	device = _renderer->GetDevice();

	//���_�m��
	if(FAILED(device->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
										  D3DUSAGE_WRITEONLY,
										  0,
										  D3DPOOL_MANAGED,
										  &_vtx,
										  NULL))){
		_vtx = NULL;
		return E_FAIL;
	}

	_vtx->Lock(0, 0, (void**)&work_vtx, 0);					//���҂���̃A�N�Z�X�⃁�����Ĕz�u�����b�N����

	//���_���̏������� ��������
	work_vtx[0].vtx = D3DXVECTOR3(x + x_align			, y - height/2.0f, 0.0f);
	work_vtx[1].vtx = D3DXVECTOR3(x + x_align + width	, y - height/2.0f, 0.0f);
	work_vtx[2].vtx = D3DXVECTOR3(x + x_align			, y + height/2.0f, 0.0f);
	work_vtx[3].vtx = D3DXVECTOR3(x + x_align + width	, y + height/2.0f, 0.0f);
	work_vtx[0].rhw = 1.0f;
	work_vtx[1].rhw = 1.0f;
	work_vtx[2].rhw = 1.0f;
	work_vtx[3].rhw = 1.0f;
	work_vtx[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	work_vtx[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	work_vtx[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	work_vtx[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	work_vtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	work_vtx[1].tex = D3DXVECTOR2(0.1f, 0.0f);
	work_vtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	work_vtx[3].tex = D3DXVECTOR2(0.1f, 1.0f);

	_vtx->Unlock();

	_texture_index = _renderer->LoadTexture("data/TEXTURE/number.png");

	this->_x = x;
	this->_y = y;
	this->_align = align;
	this->_width = width;
	this->_height = height;

	return S_OK;
}

//*****************************************************************************
//�y�I���z
//  �Ԃ�l: �Ȃ�
//  ����: �Ȃ�
//*****************************************************************************
void Number::Release(void){
	_x = 0.0f;
	_y = 0.0f;

	if(_vtx != NULL){
		_vtx->Release();
		_vtx = NULL;
	}
}

//*****************************************************************************
//�y�X�V�z
//  �Ԃ�l: �Ȃ�
//  ����: �Ȃ�
//*****************************************************************************
void Number::Update(void){
}

//*****************************************************************************
//�y�`��z
//  �Ԃ�l: �Ȃ�
//  ����: �Ȃ�
//*****************************************************************************
void Number::Draw(void){
	//renderer null check
	if(_renderer == NULL){return;}

	//LPDIRECT3DDEVICE9 device = _renderer->GetDevice();

	//device->SetFVF(FVF_VERTEX_2D);								//���_�`��`���̎w��

	//device->SetStreamSource(0, vtx, 0, sizeof(VERTEX_2D));		//���_�o�b�t�@���f�[�^�X�g���[���Ƀo�C���h

	//device->SetTexture(0, renderer->GetTexture(texture_index));								//�e�N�X�`���̃Z�b�g
	//	
	//device->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);			//�`��
}
void Number::Draw(float x, float y){
	SetPosition(x, y);
	Draw();
}

//accessor
void Number::SetPosition(float x, float y){
	VERTEX_2D *work_vtx = NULL;					//���_���擪�A�h���X�i�[�p
	float x_align = 0.0f;

	if(this->_x == x && this->_y == y){return;}

	this->_x = x;
	this->_y = y;

	x_align = -_width + (float)_align * _width * 0.5f;

	_vtx->Lock(0, 0, (void**)&work_vtx, 0);					//���҂���̃A�N�Z�X�⃁�����Ĕz�u�����b�N����

	//���_���̏������� ��������
	work_vtx[0].vtx = D3DXVECTOR3(x + x_align			, y - _height/2.0f, 0.0f);
	work_vtx[1].vtx = D3DXVECTOR3(x + x_align + _width	, y - _height/2.0f, 0.0f);
	work_vtx[2].vtx = D3DXVECTOR3(x + x_align			, y + _height/2.0f, 0.0f);
	work_vtx[3].vtx = D3DXVECTOR3(x + x_align + _width	, y + _height/2.0f, 0.0f);

	_vtx->Unlock();
}
void Number::SetValue(int value){
	if(this->_value == value){return;}

	VERTEX_2D *work_vtx = NULL;						//���_���擪�A�h���X�i�[�p
	float left = 0.0f;

	this->_value = value;

	left = 0.1f * (float)value;

	_vtx->Lock(0, 0, (void**)&work_vtx, 0);			//���҂���̃A�N�Z�X�⃁�����Ĕz�u�����b�N����

	//���_���̏������� ��������
	work_vtx[0].tex = D3DXVECTOR2(left			, 0.0f);
	work_vtx[1].tex = D3DXVECTOR2(left + 0.1f	, 0.0f);
	work_vtx[2].tex = D3DXVECTOR2(left			, 1.0f);
	work_vtx[3].tex = D3DXVECTOR2(left + 0.1f	, 1.0f);

	_vtx->Unlock();
}
