//*****************************************************************************
//  3D�|���S��
//  �T���v���V�[��
//  author: �������_
//  update: 2015/11/25
//*****************************************************************************

#include "renderer.h"
#include "sprite3d.h"


//*****************************************************************************
//  constant
//*****************************************************************************
//*****************************************************************************
//�y�R���X�g���N�^�z
//  ���_�o�b�t�@nullptr�l�߂Ȃ�
//  ����: �Ȃ�
//*****************************************************************************
Sprite3D::Sprite3D(Renderer *master_renderer, int layer_no) : Object(master_renderer, layer_no){
	_vtx = nullptr;
	_texture = -1;
}

//*****************************************************************************
//�y�������z
//  ����: �Ȃ�
//*****************************************************************************
HRESULT Sprite3D::SetUp(D3DXVECTOR3 position, D3DXVECTOR3 rotation, float width, float height, char *filename){
	LPDIRECT3DDEVICE9 device = _renderer->GetDevice();

	//���_�m��
	if (FAILED(device->CreateVertexBuffer(sizeof(VERTEX_3D) * 4,
		D3DUSAGE_WRITEONLY,
		0,
		D3DPOOL_MANAGED,
		&_vtx,
		nullptr))){
		_vtx = nullptr;
		return E_FAIL;
	}

	VERTEX_3D *work_vtx(nullptr);

	//���_���̏�����
	_vtx->Lock(0, 0, (void**)&work_vtx, 0);					//���҂���̃A�N�Z�X�⃁�����Ĕz�u�����b�N����

	//���_���̏�������
	work_vtx[0].vtx = D3DXVECTOR3(-0.5f, -0.5f, 0.0f);
	work_vtx[1].vtx = D3DXVECTOR3(0.5f, -0.5f, 0.0f);
	work_vtx[2].vtx = D3DXVECTOR3(-0.5f, 0.5f, 0.0f);
	work_vtx[3].vtx = D3DXVECTOR3(0.5f, 0.5f, 0.0f);
	work_vtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
	work_vtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
	work_vtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
	work_vtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
	work_vtx[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	work_vtx[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	work_vtx[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	work_vtx[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	work_vtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	work_vtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	work_vtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	work_vtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	_vtx->Unlock();

	_texture = _renderer->LoadTexture(filename);

	_position = position;
	_rotation = rotation;
	_size.x = width;
	_size.y = height;

	//���_�v�f�̒�`
	D3DVERTEXELEMENT9 v_ele[] = {
		{ 0, 0, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0 },
		{ 0, 12, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_NORMAL, 0 },
		{ 0, 24, D3DDECLTYPE_D3DCOLOR, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_COLOR, 0 },
		{ 0, 28, D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 0 },
		D3DDECL_END()
	};

	//declaration������
	if (FAILED(device->CreateVertexDeclaration(v_ele, &_decl))){
		return E_FAIL;
	}

	return S_OK;
}

//*****************************************************************************
//�y�I���z
//  �Ԃ�l: �Ȃ�
//  ����: �Ȃ�
//*****************************************************************************
void Sprite3D::Release(void){
	if (_vtx != nullptr){
		_vtx->Release();
		_vtx = nullptr;
	}

	if (_decl != nullptr){
		_decl->Release();
		_decl = nullptr;
	}
}

//*****************************************************************************
//�y�X�V�z
//  �Ԃ�l: �Ȃ�
//  ����: �Ȃ�
//*****************************************************************************
void Sprite3D::Update(void){
}

//*****************************************************************************
//�y�`��z
//  �Ԃ�l: �Ȃ�
//  ����: �Ȃ�
//*****************************************************************************
void Sprite3D::Draw(void){
	//renderer nullptr check
	if (_renderer == nullptr){ return; }
	if (!_visible){ return; }

	LPDIRECT3DDEVICE9 device = _renderer->GetDevice();
	D3DXMATRIX world_mtx, scaling_mtx, rotation_mtx, translate_mtx;

	device->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);				//�w�ʃJ�����O�̐ݒ�

	D3DXMatrixIdentity(&world_mtx);					//���[���h�s����Ƃ肠����E�ɂ���

	D3DXMatrixScaling(&scaling_mtx, _size.x, _size.y, 0.0f);								//scaling
	D3DXMatrixMultiply(&world_mtx, &world_mtx, &scaling_mtx);

	D3DXMatrixRotationYawPitchRoll(&rotation_mtx, _rotation.y, _rotation.x, _rotation.z);	//rotation
	D3DXMatrixMultiply(&world_mtx, &world_mtx, &rotation_mtx);

	D3DXMatrixTranslation(&translate_mtx, _position.x, _position.y, _position.z);				//translation
	D3DXMatrixMultiply(&world_mtx, &world_mtx, &translate_mtx);

	_renderer->SetWorld(world_mtx);

	D3DXVECTOR4 diffuse(1.0f, 0.0f, 0.0f, 0.5f);
	_renderer->SetMaterialDiffuse(diffuse);

	device->SetVertexDeclaration(_decl);

	device->SetStreamSource(0, _vtx, 0, sizeof(VERTEX_3D));		//���_�o�b�t�@���f�[�^�X�g���[���Ƀo�C���h

	_renderer->SetTextureToShader(_texture);

	_renderer->SetCurrentShader();

	device->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);			//�`��

	device->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);				//�w�ʃJ�����O�̐ݒ�

}
