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
Renderer *Debug::_renderer = NULL;
char Debug::_buffer[BUFFER_MAX] = {};
LPD3DXFONT Debug::_font = NULL;					// �t�H���g�ւ̃|�C���^

int Debug::_mesh_id = -1;			//���_�o�b�t�@�̃|�C���^
Debug::HIT_VIEW Debug::_hit_view[HIT_VIEW_MAX] = {};

//*****************************************************************************
//�y�������z
//  �o�b�t�@�N���A
//  �Ԃ�l: �������ɐ����������ǂ���
//  ����: �Ȃ�
//*****************************************************************************
HRESULT Debug::SetUp(void){
	LPDIRECT3DDEVICE9 device = _renderer->GetDevice();
	VERTEX_3D *work_vtx = NULL;
	
	memset(_buffer, 0, BUFFER_MAX);

	// ���\���p�t�H���g��ݒ�
	if(FAILED(D3DXCreateFont(device, 18, 0, 0, 0, FALSE, SHIFTJIS_CHARSET,
		OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, "Terminal", &_font))){
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
	memset(_buffer, 0, BUFFER_MAX);

	if(_font != NULL){
		_font->Release();
		_font = NULL;
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

	strcat(_buffer, work);
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

	device = _renderer->GetDevice();

	device->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);

	Renderer::MESH_SET *mesh = _renderer->GetMesh(_mesh_id);

	//hit view
	for(i=0; i<HIT_VIEW_MAX; i++){
		//���Ȃ���͔�΂�
		if(!_hit_view[i].flag){continue;}

		//world������
		D3DXMatrixIdentity(&world);					//���[���h�s����Ƃ肠����E�ɂ���

		//scaling
		D3DXMatrixScaling(&scale_mtx, _hit_view[i].radius, _hit_view[i].radius, 1.0f);
		D3DXMatrixMultiply(&world, &world, &scale_mtx);

		//translation
		D3DXMatrixTranslation(&translate_mtx, _hit_view[i].position.x, _hit_view[i].position.y, _hit_view[i].position.z);
		D3DXMatrixMultiply(&world, &world, &translate_mtx);

		_renderer->SetWorld(world);

		D3DXMATERIAL *mat = (D3DXMATERIAL*)mesh->mat_buff->GetBufferPointer();
		for (unsigned int j = 0; j<mesh->mat_num; j++) {
			D3DMATERIAL9 work_mat = mat[j].MatD3D;
			D3DXVECTOR4 diffuse(work_mat.Diffuse.r,
				work_mat.Diffuse.g,
				work_mat.Diffuse.b,
				work_mat.Diffuse.a);

			_renderer->SetTextureToShader(mesh->texture[j]);
			_renderer->SetMaterialDiffuse(diffuse);

			_renderer->SetCurrentShader();

			mesh->mesh->DrawSubset(j);
		}
		_hit_view[i].flag = false;
	}

	device->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);

	

#endif

	if(_font != NULL){

		// �e�L�X�g�`��
		_font->DrawText(NULL, _buffer, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));

	}
	memset(_buffer, 0, BUFFER_MAX);
#endif
}


void Debug::LoadHitView(void){
	_mesh_id = _renderer->LoadMesh("data/MODEL/sphere.x");
}
void Debug::ReleaseHitView(void){
}

void Debug::EntryHitView(D3DXVECTOR3 pos, float radius){
	int i = 0;				//loop index
#ifdef _DEBUG_HIT_DRAW_

	for(i=0; i<HIT_VIEW_MAX; i++){
		if(!_hit_view[i].flag){
			_hit_view[i].position = pos;
			_hit_view[i].radius = radius;
			_hit_view[i].flag = true;
			break;
		}
	}
#endif
}
