//*****************************************************************************
//  scene_billboard���W���[��
//  author: �������_
//  update: 2014/05/07
//*****************************************************************************


#include "object_billboard.h"
#include "renderer.h"

//*****************************************************************************
//  constant
//*****************************************************************************

//*****************************************************************************
//�y�R���X�g���N�^�z
//  ���_�o�b�t�@NULL�߂߂Ȃ�
//  ����: �Ȃ�
//*****************************************************************************
ObjectBillboard::ObjectBillboard(Renderer *master_renderer, int layer_no):
Object(master_renderer, layer_no),
_vtx(nullptr),
_texture_id(-1),
_decl(nullptr),
_scale(1.0f, 1.0f),
_offset(0.0f, 0.0f, 0.0f){
}


//*****************************************************************************
//�y�����ݒ�z
//  �Ԃ�l: �ݒ�ɐ����������ǂ���
//  ��1����: ���S�ʒu
//  ��2����: ����
//  ��3����: �c��
//  ��4����: �e�N�X�`���p�X
//*****************************************************************************
HRESULT ObjectBillboard::SetUp(D3DXVECTOR3 pos, float width, float height, char *texture_filename){
	LPDIRECT3DDEVICE9 device = nullptr;		//�f�o�C�X�擾�p
	VERTEX_3D *work_vtx = nullptr;
	int i = 0;								//loop index

	device = _renderer->GetDevice();

	//���_���̐ݒ�
	if(FAILED(device->CreateVertexBuffer(sizeof(VERTEX_3D) * 4,
										 D3DUSAGE_WRITEONLY,
										 0,
										 D3DPOOL_MANAGED,
										 &_vtx,
										 nullptr))){
		return E_FAIL;
	}

	_vtx->Lock(0, 0, (void**)&work_vtx, 0);

	for(i=0; i<4; i++){
		work_vtx[i].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		work_vtx[i].nor = D3DXVECTOR3(0.0f, 0.0f, 1.0f);			//�ǂ����Ӗ��Ȃ����c�c
	}
	work_vtx[0].vtx = D3DXVECTOR3(-0.5f,  0.5f, 0.0f);
	work_vtx[1].vtx = D3DXVECTOR3( 0.5f,  0.5f, 0.0f);
	work_vtx[2].vtx = D3DXVECTOR3(-0.5f, -0.5f, 0.0f);
	work_vtx[3].vtx = D3DXVECTOR3( 0.5f, -0.5f, 0.0f);
	work_vtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	work_vtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	work_vtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	work_vtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	_vtx->Unlock();

	_position = pos;
	_size.x = width;
	_size.y = height;
	_size.z = 0.0f;

	//�e�N�X�`���o�^
	_texture_id = _renderer->LoadTexture(texture_filename);

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
void ObjectBillboard::Release(void){
	if(_vtx != nullptr){
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
void ObjectBillboard::Update(void){
	Object::Update();
}

//*****************************************************************************
//�y�`��z
//  �Ԃ�l: �Ȃ�
//  ����: �Ȃ�
//*****************************************************************************
void ObjectBillboard::Draw(void){
	D3DXMATRIX translate_mtx, scaling_mtx;
	LPDIRECT3DDEVICE9 device = nullptr;		//�f�o�C�X�擾�p
	D3DXMATRIX view_mtx;					//view inverse���d����ł�������
	D3DXMATRIX world;						//�i�[�p���[���h�s��
	int i = 0;								//loop index

	device = _renderer->GetDevice();

	D3DXMatrixIdentity(&world);					//���[���h�s����Ƃ肠����E�ɂ���

	//scaling
	D3DXMatrixScaling(&scaling_mtx, _size.x * _scale.x, _size.y * _scale.y, 0.0f);
	D3DXMatrixMultiply(&world, &world, &scaling_mtx);

	//offset
	D3DXMatrixTranslation(&translate_mtx, _offset.x, _offset.y, _offset.z);
	D3DXMatrixMultiply(&world, &world, &translate_mtx);

	//�J������view�̊p�x�������E��
	view_mtx = _renderer->GetView();
	D3DXMatrixInverse(&view_mtx, nullptr, &view_mtx);
	view_mtx._41 = 0.0f;
	view_mtx._42 = 0.0f;
	view_mtx._43 = 0.0f;
	D3DXMatrixMultiply(&world, &world, &view_mtx);

	//world._41 = 0.0f;
	//world._42 = 0.0f;
	//world._43 = 0.0f;

	//translation
	D3DXMatrixTranslation(&translate_mtx, _position.x, _position.y, _position.z);
	D3DXMatrixMultiply(&world, &world, &translate_mtx);

	_renderer->SetWorld(world);

	D3DXVECTOR4 diffuse(1.0f, 0.0f, 0.0f, 0.5f);
	_renderer->SetMaterialDiffuse(diffuse);

	device->SetVertexDeclaration(_decl);

	_renderer->SetTextureToShader(_texture_id);

	device->SetStreamSource(0, _vtx, 0, sizeof(VERTEX_3D));					//���_�o�b�t�@���f�[�^�X�g���[���Ƀo�C���h

	_renderer->SetCurrentShader();

	device->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);						//�`��
}

//*****************************************************************************
//�y���_�o�b�t�@��UV�l�ݒ�z
//  �Ԃ�l: �Ȃ�
//  ����: �Ȃ�
//*****************************************************************************
void ObjectBillboard::SetUV(float left, float top, float right, float bottom){
	VERTEX_3D *work_vtx = nullptr;

	_vtx->Lock(0, 0, (void**)&work_vtx, 0);

	work_vtx[0].tex = D3DXVECTOR2(left, top);
	work_vtx[1].tex = D3DXVECTOR2(right, top);
	work_vtx[2].tex = D3DXVECTOR2(left, bottom);
	work_vtx[3].tex = D3DXVECTOR2(right, bottom);

	_vtx->Unlock();
}

//accessor
