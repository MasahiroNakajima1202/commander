//*****************************************************************************
//  debug���W���[��
//  author: �������_
//  update: 2014/05/13
//*****************************************************************************

#include "debug.h"
#include "renderer.h"
#include "stdio.h"

//*****************************************************************************
//  sttic variables
//*****************************************************************************
Renderer *Debug::renderer = NULL;
char Debug::buffer[BUFFER_MAX] = {};
LPD3DXFONT Debug::font = NULL;					// �t�H���g�ւ̃|�C���^

LPDIRECT3DVERTEXBUFFER9 Debug::vtx = NULL;			//���_�o�b�t�@�̃|�C���^
int Debug::texture_index = -1;
Debug::HIT_VIEW Debug::hit_view[HIT_VIEW_MAX] = {};
D3DXMATRIX Debug::camera_view;

//*****************************************************************************
//�y�������z
//  �o�b�t�@�N���A
//  �Ԃ�l: �������ɐ����������ǂ���
//  ����: �Ȃ�
//*****************************************************************************
HRESULT Debug::SetUp(void){
	LPDIRECT3DDEVICE9 device = renderer->GetDevice();
	VERTEX_3D *work_vtx = NULL;
	
	memset(buffer, 0, BUFFER_MAX);

	// ���\���p�t�H���g��ݒ�
	if(FAILED(D3DXCreateFont(device, 18, 0, 0, 0, FALSE, SHIFTJIS_CHARSET,
		OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, "Terminal", &font))){
			return E_FAIL;
	}

	LoadHitView();




	return S_OK;
}

//*****************************************************************************
//�y�I���z
//  �Ԃ�l: �Ȃ�
//  ����: �Ȃ�
//*****************************************************************************
void Debug::Release(void){
	memset(buffer, 0, BUFFER_MAX);

	if(font != NULL){
		font->Release();
		font = NULL;
	}

	ReleaseHitView();
}

//*****************************************************************************
//�y�o�́z
//  �Ԃ�l: �Ȃ�
//  ��1����: ������
//  ��2����: �ϒ�����
//*****************************************************************************
void Debug::Print(char* format, ...){
#ifdef _DEBUG
	va_list list;
	char work[256] = {};

	va_start(list, format);

	vsprintf(work, format, list);

	strcat(buffer, work);
	va_end(list);
#endif
}

//*****************************************************************************
//�y�`��z
//  �Ԃ�l: �Ȃ�
//  ����: �Ȃ�
//*****************************************************************************
void Debug::Draw(void){
#ifdef _DEBUG
	RECT rect = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
	int i = 0;				//loop index
	D3DXMATRIX translate_mtx, scale_mtx;
	LPDIRECT3DDEVICE9 device = NULL;		//�f�o�C�X�擾�p
	D3DXMATRIX view_mtx;					//view inverse���d����ł�������
	D3DXMATRIX world;						//�i�[�p���[���h�s��

#ifdef _DEBUG_HIT_DRAW_

	device = renderer->GetDevice();

	//�r���{�[�h�̓��C�g��؂�I�I�I�I�I
	device->SetRenderState(D3DRS_LIGHTING, FALSE);

	//�����_�[�X�e�[�g�Ń��e�X�g��ON��
	device->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	device->SetRenderState(D3DRS_ALPHAREF, 32);
	device->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	//�J������view���E��
	view_mtx = camera_view;
	D3DXMatrixInverse(&view_mtx, NULL, &view_mtx);

	device->SetFVF(FVF_VERTEX_3D);										//���_�`��`���̎w��
	device->SetStreamSource(0, vtx, 0, sizeof(VERTEX_3D));				//���_�o�b�t�@���f�[�^�X�g���[���Ƀo�C���h
	device->SetTexture(0, renderer->GetTexture(texture_index));			//���ꂩ��`�悷��e�N�X�`���̃Z�b�g


	//hit view
	for(i=0; i<HIT_VIEW_MAX; i++){
		//���Ȃ���͔�΂�
		if(!hit_view[i].flag){continue;}

		//world������
		D3DXMatrixIdentity(&world);					//���[���h�s����Ƃ肠����E�ɂ���

		//scaling
		D3DXMatrixScaling(&scale_mtx, hit_view[i].radius, hit_view[i].radius, 1.0f);
		D3DXMatrixMultiply(&world, &world, &scale_mtx);

		D3DXMatrixMultiply(&world, &world, &view_mtx);

		world._41 = 0.0f;
		world._42 = 0.0f;
		world._43 = 0.0f;

		//translation
		D3DXMatrixTranslation(&translate_mtx, hit_view[i].position.x, hit_view[i].position.y, hit_view[i].position.z);
		D3DXMatrixMultiply(&world, &world, &translate_mtx);

		device->SetTransform(D3DTS_WORLD, &world);

		device->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);					//�`��

		hit_view[i].flag = false;
	}


	//���A���C�g�܂����Ȃ���
	device->SetRenderState(D3DRS_LIGHTING, TRUE);

	//�����_�[�X�e�[�g����
	device->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);

#endif

	if(font != NULL){

		// �e�L�X�g�`��
		font->DrawText(NULL, buffer, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));

	}
	memset(buffer, 0, BUFFER_MAX);
#endif
}


void Debug::LoadHitView(void){
	LPDIRECT3DDEVICE9 device = NULL;		//�f�o�C�X�擾�p
	VERTEX_3D *work_vtx = NULL;
	int i = 0;								//loop index

	device = renderer->GetDevice();

	//���_���̐ݒ�
	if(FAILED(device->CreateVertexBuffer(sizeof(VERTEX_3D) * 4,
										 D3DUSAGE_WRITEONLY,
										 0,
										 D3DPOOL_MANAGED,
										 &vtx,
										 NULL))){
		return;
	}

	vtx->Lock(0, 0, (void**)&work_vtx, 0);

	for(i=0; i<4; i++){
		work_vtx[i].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		work_vtx[i].nor = D3DXVECTOR3(0.0f, 0.0f, 1.0f);			//�ǂ����Ӗ��Ȃ����c�c
	}
	work_vtx[0].vtx = D3DXVECTOR3(-1.0f/2.0f,  1.0f/2.0f, 0.0f);
	work_vtx[1].vtx = D3DXVECTOR3( 1.0f/2.0f,  1.0f/2.0f, 0.0f);
	work_vtx[2].vtx = D3DXVECTOR3(-1.0f/2.0f, -1.0f/2.0f, 0.0f);
	work_vtx[3].vtx = D3DXVECTOR3( 1.0f/2.0f, -1.0f/2.0f, 0.0f);
	work_vtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	work_vtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	work_vtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	work_vtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	vtx->Unlock();

	//�e�N�X�`���o�^
	texture_index = renderer->LoadTexture("data/TEXTURE/flare03.png");
}
void Debug::ReleaseHitView(void){
	if(vtx != NULL){
		vtx->Release();
		vtx = NULL;
	}
}

void Debug::EntryHitView(D3DXVECTOR3 pos, float radius){
	int i = 0;				//loop index
#ifdef _DEBUG_HIT_DRAW_

	for(i=0; i<HIT_VIEW_MAX; i++){
		if(!hit_view[i].flag){
			hit_view[i].position = pos;
			hit_view[i].radius = radius;
			hit_view[i].flag = true;
			break;
		}
	}
#endif
}
