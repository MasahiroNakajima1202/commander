//=============================================================================
//  fade�@�\�̃��W���[��
//  author: �������_
//  update: 2014/03/16
//=============================================================================

#include "fade.h"

//*****************************************************************************
//  constant def
//*****************************************************************************
#define FADE_LENGTH (8)								//�t�F�[�h�̑����l

//*****************************************************************************
//  static variables
//*****************************************************************************
LPDIRECT3DTEXTURE9 Fade::_texture = NULL;			//�t�F�[�h�̃e�N�X�`��
LPDIRECT3DVERTEXBUFFER9 Fade::_vtx = NULL;
Fade::FADE Fade::_state = FADE_NON;
int Fade::_value = 0;
Renderer *Fade::_renderer = NULL;
LPDIRECT3DVERTEXDECLARATION9 Fade::_decl;

//=============================================================================
// �t�F�[�h�̏�����
//=============================================================================
bool Fade::SetUp(Renderer *master_renderer){
	LPDIRECT3DDEVICE9 device = NULL;		//�f�o�C�X�擾�p
	VERTEX_2D *work_vtx = NULL;					//���_���擪�A�h���X�i�[�p

	_renderer = master_renderer;

	//�t�F�[�h�̏�ԏ�����
	_state = FADE_NON;
	_value = 255;

	//�f�o�C�X�̎擾
	device = _renderer->GetDevice();

	//���_�v�f�̒�`
	D3DVERTEXELEMENT9 v_ele[] = {
		{ 0, 0, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0 },
		{ 0, 16, D3DDECLTYPE_D3DCOLOR, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_COLOR, 0 },
		{ 0, 20, D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 0 },
		D3DDECL_END()
	};

	//declaration������
	if (FAILED(device->CreateVertexDeclaration(v_ele, &_decl))){
		return false;
	}

	//���_�o�b�t�@�̊m��
	if(FAILED(device->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
										  D3DUSAGE_WRITEONLY,
										  0,
										  D3DPOOL_MANAGED,
										  &_vtx,
										  NULL))){
		return false;
	}

	//���_���̎擾
	_vtx->Lock(0, 0, (void**)&work_vtx, 0);					//���҂���̃A�N�Z�X�⃁�����Ĕz�u�����b�N����

	//���_���̏�����
	work_vtx[0].vtx = D3DXVECTOR3(0, 0, 0.0f);
	work_vtx[1].vtx = D3DXVECTOR3(SCREEN_WIDTH, 0, 0.0f);
	work_vtx[2].vtx = D3DXVECTOR3(0, SCREEN_HEIGHT, 0.0f);
	work_vtx[3].vtx = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);
	work_vtx[0].rhw = 1.0f;
	work_vtx[1].rhw = 1.0f;
	work_vtx[2].rhw = 1.0f;
	work_vtx[3].rhw = 1.0f;
	work_vtx[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	work_vtx[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	work_vtx[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	work_vtx[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	work_vtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	work_vtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	work_vtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	work_vtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	_vtx->Unlock();

	return S_OK;
}

//=============================================================================
// �t�F�[�h�̍X�V
//=============================================================================
void Fade::Update(void){

	if(_state == FADE_OUT){
		_value += FADE_LENGTH;
		if(_value >= 255){
			_value = 255;
			_state = FADE_NON;
		}
	}

	if(_state == FADE_IN){
		_value -= FADE_LENGTH;
		if(_value <= 0){
			_value = 0;
			_state = FADE_NON;
		}
	}

}

//=============================================================================
// �t�F�[�h�̕`��
//=============================================================================
void Fade::Draw(void){
	VERTEX_2D *work_vtx = NULL;					//���_���擪�A�h���X�i�[�p
	LPDIRECT3DDEVICE9 device = NULL;

	if(_renderer == NULL || _vtx == NULL){return;}

	//���_���̎擾
	_vtx->Lock(0, 0, (void**)&work_vtx, 0);					//���҂���̃A�N�Z�X�⃁�����Ĕz�u�����b�N����

	//���_���̏�����
	work_vtx[0].diffuse = D3DCOLOR_RGBA(0, 0, 0, _value);
	work_vtx[1].diffuse = D3DCOLOR_RGBA(0, 0, 0, _value);
	work_vtx[2].diffuse = D3DCOLOR_RGBA(0, 0, 0, _value);
	work_vtx[3].diffuse = D3DCOLOR_RGBA(0, 0, 0, _value);

	_vtx->Unlock();


	//�f�o�C�X�̎擾
	device = _renderer->GetDevice();

	//�t�H�O�̏�Ԏ擾
	DWORD def_fog = 0;
	device->GetRenderState(D3DRS_FOGENABLE, &def_fog);

	//�t�H�O������
	device->SetRenderState(D3DRS_FOGENABLE, FALSE);

	device->SetVertexDeclaration(_decl);

	device->SetStreamSource(0, _vtx, 0, sizeof(VERTEX_2D));

	device->SetTexture(0, _texture);

	device->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

	device->SetRenderState(D3DRS_FOGENABLE, def_fog);
}

//=============================================================================
// �t�F�[�h�̏I������
//=============================================================================
void Fade::Release(void){
	if(_texture != NULL){
		_texture->Release();
		_texture = NULL;
	}
	if(_vtx != NULL){
		_vtx->Release();
		_vtx = NULL;
	}
	if(_decl != NULL){
		_decl->Release();
		_decl = NULL;
	}
}


//=============================================================================
// �t�F�[�h�C���J�n
//=============================================================================
void Fade::FadeIn(void){
	_state = FADE_IN;
}

//=============================================================================
// �t�F�[�h�A�E�g�J�n
//=============================================================================
void Fade::FadeOut(void){
	_state = FADE_OUT;
}

bool Fade::IsBlackOut(void){
	return (_value >= 255);
}