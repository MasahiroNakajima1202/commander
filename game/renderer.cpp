//*****************************************************************************
//  rebderer���W���[��
//  author: �������_
//  update: 2014/04/15
//*****************************************************************************

#include "renderer.h"
//#include "fade.h"
//#include "game_input.h"

#include "debug.h"
#include "render_texture.h"
#include "vertex_shader.h"
#include "pixel_shader.h"
#include "vs2d.h"
#include "ps2d.h"
#include "render_texture.h"
#include "vs_skin_mesh.h"
#include "vs_instancing.h"
//*****************************************************************************
//  constant
//*****************************************************************************


//*****************************************************************************
//  library link
//*****************************************************************************

//*****************************************************************************
//�y�������z
//  DirectX9�̏���������
//  �Ԃ�l: �������ɐ����������ǂ���
//  ��1����: HINSTANCE
//  ��2����: �E�B���h�E�n���h��
//  ��3����: �E�B���h�E���[�h�̃t���O FALSE�Ńt���X�N���[��
//*****************************************************************************
HRESULT Renderer::SetUp(HINSTANCE hInstance, HWND hWnd, BOOL bWindow){
	D3DPRESENT_PARAMETERS d3dpp;
    D3DDISPLAYMODE d3ddm;
	HRESULT hr = S_OK;
	int i = 0;					//loop index

	// Direct3D�I�u�W�F�N�g�̐���
	_D3D = Direct3DCreate9(D3D_SDK_VERSION);

	if(_D3D == nullptr)
	{
		return E_FAIL;
	}

	// ���݂̃f�B�X�v���C���[�h���擾
    if(FAILED(_D3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
	{
		return E_FAIL;
	}

	// �f�o�C�X�̃v���[���e�[�V�����p�����[�^�̐ݒ�
	ZeroMemory(&d3dpp, sizeof(d3dpp));							// ���[�N���[���N���A
	d3dpp.BackBufferCount			= 1;						// �o�b�N�o�b�t�@�̐�
	d3dpp.BackBufferWidth			= SCREEN_WIDTH;				// �Q�[����ʃT�C�Y(��)
	d3dpp.BackBufferHeight			= SCREEN_HEIGHT;			// �Q�[����ʃT�C�Y(����)
	d3dpp.BackBufferFormat			= D3DFMT_UNKNOWN;			// �o�b�N�o�b�t�@�̃t�H�[�}�b�g�͌��ݐݒ肳��Ă�����̂��g��
	d3dpp.SwapEffect				= D3DSWAPEFFECT_DISCARD;	// �f���M���ɓ������ăt���b�v����
	d3dpp.Windowed					= bWindow;					// �E�B���h�E���[�h
	d3dpp.EnableAutoDepthStencil	= TRUE;						// �f�v�X�o�b�t�@�i�y�o�b�t�@�j�ƃX�e���V���o�b�t�@���쐬
	d3dpp.AutoDepthStencilFormat	= D3DFMT_D24S8;				// �f�v�X�o�b�t�@�Ƃ���16bit���g��

	if(bWindow)
	{// �E�B���h�E���[�h
		d3dpp.BackBufferFormat           = D3DFMT_UNKNOWN;					// �o�b�N�o�b�t�@
		d3dpp.FullScreen_RefreshRateInHz = 0;								// ���t���b�V�����[�g
		d3dpp.PresentationInterval       = D3DPRESENT_INTERVAL_IMMEDIATE;	// �C���^�[�o��
	}
	else
	{// �t���X�N���[�����[�h
		d3dpp.BackBufferFormat           = D3DFMT_R5G6B5;					// �o�b�N�o�b�t�@
		d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;			// ���t���b�V�����[�g
		d3dpp.PresentationInterval       = D3DPRESENT_INTERVAL_DEFAULT;		// �C���^�[�o��
	}

	// �f�o�C�X�I�u�W�F�N�g�̐���
	// [�f�o�C�X�쐬����]<�`��>��<���_����>���n�[�h�E�F�A�ōs�Ȃ�
	if(FAILED(_D3D->CreateDevice(D3DADAPTER_DEFAULT,						// �f�B�X�v���C�A�_�v�^
									D3DDEVTYPE_HAL,							// �f�B�X�v���C�^�C�v
									hWnd,									// �t�H�[�J�X����E�C���h�E�ւ̃n���h��
									D3DCREATE_HARDWARE_VERTEXPROCESSING,		// �f�o�C�X�쐬����̑g�ݍ��킹(�ق�Ƃ̓n�[�h�ł�肽�����ǃX�L�����b�V���̂��߂�)
									&d3dpp,									// �f�o�C�X�̃v���[���e�[�V�����p�����[�^
									&_device)))						// �f�o�C�X�C���^�[�t�F�[�X�ւ̃|�C���^
	{
		// ��L�̐ݒ肪���s������
		// [�f�o�C�X�쐬����]<�`��>���n�[�h�E�F�A�ōs���A<���_����>��CPU�ōs�Ȃ�
		if(FAILED(_D3D->CreateDevice(D3DADAPTER_DEFAULT, 
										D3DDEVTYPE_HAL, 
										hWnd, 
										D3DCREATE_SOFTWARE_VERTEXPROCESSING, 
										&d3dpp,
										&_device)))
		{
			// ��L�̐ݒ肪���s������
			// [�f�o�C�X�쐬����]<�`��>��<���_����>��CPU�ōs�Ȃ�
			if(FAILED(_D3D->CreateDevice(D3DADAPTER_DEFAULT, 
											D3DDEVTYPE_REF,
											hWnd, 
											D3DCREATE_SOFTWARE_VERTEXPROCESSING, 
											&d3dpp,
											&_device)))
			{
				// ���������s
				return E_FAIL;
			}
		}
	}

	

	ResetSamplerState();

	//�t�H�O�̐ݒ�
	float fog_start = 200.0f;
	float fog_end = 40000.0f;
	//D3DDevice->SetRenderState(D3DRS_FOGENABLE, TRUE);						//�t�H�O��ON��
	_device->SetRenderState(D3DRS_FOGCOLOR, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));	//�t�H�O�̐F
	_device->SetRenderState(D3DRS_FOGVERTEXMODE, D3DFOG_LINEAR);			//���_�t�H�O
	_device->SetRenderState(D3DRS_FOGTABLEMODE, D3DFOG_NONE);				//�s�N�Z���t�H�O
	_device->SetRenderState(D3DRS_FOGSTART, *(DWORD*)&fog_start);			//�t�H�O�J�n�ʒu
	_device->SetRenderState(D3DRS_FOGEND, *(DWORD*)&fog_end);				//�t�H�O�I���ʒu

	//D3DXCOLOR color(1.0f, 0.75f, 0.5f, 1.0f);
	D3DXCOLOR color(1.0f, 1.0f, 1.0f, 1.0f);

	for(i=0; i<TEXTURE_MAX; i++){
		_texture[i] = nullptr;
		memset(_texture_name[i], '\0', 64);
	}

	D3DXMatrixIdentity(&_view);
	D3DXMatrixIdentity(&_world);
	D3DXMatrixIdentity(&_projection);

	_light_position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);;
	_point_light_ratio = 0.0f;

	//�e�N�X�`���Ȃ��̂Ƃ��̔��F�e�N�X�`��
	D3DXCreateTextureFromFile(_device, "data/TEXTURE/white.png", &_white_texture);


	_rendering_vs[Object::DRAW_LAYER_FIELD]				= new VertexShader(this, "data/SHADER/half_lambert.hlsl", "VSHalfLambert");
	_rendering_ps[Object::DRAW_LAYER_FIELD]				= new PixelShader (this, "data/SHADER/half_lambert.hlsl", "PSLightTexture");
	_rendering_vs[Object::DRAW_LAYER_SHADOW]			= new VertexShader(this, "data/SHADER/half_lambert.hlsl", "VSHalfLambert");
	_rendering_ps[Object::DRAW_LAYER_SHADOW]			= new PixelShader (this, "data/SHADER/half_lambert.hlsl", "PSLightTexture");
	_rendering_vs[Object::DRAW_LAYER_SKIN_MESH]			= new VSSkinMesh  (this);
	_rendering_ps[Object::DRAW_LAYER_SKIN_MESH]			= new PixelShader (this, "data/SHADER/half_lambert.hlsl", "PSLightTexture");
	_rendering_vs[Object::DRAW_LAYER_MESH]				= new VertexShader(this, "data/SHADER/half_lambert.hlsl", "VSHalfLambert");
	_rendering_ps[Object::DRAW_LAYER_MESH]				= new PixelShader (this, "data/SHADER/half_lambert.hlsl", "PSLightTexture");
	_rendering_vs[Object::DRAW_LAYER_INSTANCING_MESH]	= new VSInstancing(this);
	_rendering_ps[Object::DRAW_LAYER_INSTANCING_MESH]	= new PixelShader (this, "data/SHADER/half_lambert.hlsl", "PSLightTexture");
	_rendering_vs[Object::DRAW_LAYER_ALPHA]				= new VertexShader(this, "data/SHADER/half_lambert.hlsl", "VSHalfLambert");
	_rendering_ps[Object::DRAW_LAYER_ALPHA]				= new PixelShader (this, "data/SHADER/half_lambert.hlsl", "PSLightTexture");
	_rendering_vs[Object::DRAW_LAYER_BILLBOARD]			= new VertexShader(this, "data/SHADER/billboard.hlsl", "VSBillboard");
	_rendering_ps[Object::DRAW_LAYER_BILLBOARD]			= new PixelShader (this, "data/SHADER/billboard.hlsl", "PSTexture");
	_rendering_vs[Object::DRAW_LAYER_2D]				= new VS2D(this);
	_rendering_ps[Object::DRAW_LAYER_2D]				= new PS2D(this);
	_rendering_vs[Object::DRAW_LAYER_FADE]				= new VS2D(this);
	_rendering_ps[Object::DRAW_LAYER_FADE]				= new PS2D(this);
	_rendering_vs[Object::DRAW_LAYER_SCREEN]			= new VS2D(this);
	_rendering_ps[Object::DRAW_LAYER_SCREEN]			= new PS2D(this);
	_rendering_vs[Object::DRAW_LAYER_EFFEKSEER]			= new VS2D(this);//effekseer�搶�̑O�ɂ̓V�F�[�_�[�ȂǺ�и�ޓ��R
	_rendering_ps[Object::DRAW_LAYER_EFFEKSEER]			= new PS2D(this);//����͂����̃_�~�[�ł�
	_rendering_vs[Object::DRAW_LAYER_EFFEKSEER_2D]		= new VS2D(this);
	_rendering_ps[Object::DRAW_LAYER_EFFEKSEER_2D]		= new PS2D(this);


	//effekseer�֘A
	//_effekseer_renderer = nullptr;
	//_effekseer_manager = nullptr;
	//_effekseer_renderer = EffekseerRendererDX9::Renderer::Create(_device, EFFEKSEER_SPRITE_MAX);
	//_effekseer_manager = Effekseer::Manager::Create(EFFEKSEER_SPRITE_MAX);

	// �`����@�̎w��A�Ǝ��Ɋg�����Ȃ������`���ł��B
	//_effekseer_manager->SetSpriteRenderer(_effekseer_renderer->CreateSpriteRenderer());
	//_effekseer_manager->SetRibbonRenderer(_effekseer_renderer->CreateRibbonRenderer());
	//_effekseer_manager->SetRingRenderer(_effekseer_renderer->CreateRingRenderer());
	// �e�N�X�`���摜�̓Ǎ����@�̎w��(�p�b�P�[�W������ǂݍ��ޏꍇ�g������K�v������܂��B)
	//_effekseer_manager->SetTextureLoader(_effekseer_renderer->CreateTextureLoader() );
	// ���W�n�̎w��(RH�ŉE��n�ALH�ō���n)
	//_effekseer_manager->SetCoordinateSystem(Effekseer::CoordinateSystem::LH);

	//Effekseer::Matrix44 effekseer_proj;
	//Effekseer::Matrix44 effekseer_view;
	//for(int i = 0; i<16; i++){
	//	int row(i/4), line(i%4);
	//	effekseer_proj.Values[row][line] = _projection.m[row][line];
	//}
	//effekseer_view.Indentity();

	// ���e�s��̍X�V
	//_effekseer_renderer->SetProjectionMatrix(effekseer_proj);
	// �J�����s��̍X�V
	//_effekseer_renderer->SetCameraMatrix(effekseer_view);

	
	return S_OK;
}

//*****************************************************************************
//�y�I���z
//  DirectX9�̏I������
//  �Ԃ�l: �Ȃ�
//  ����: �Ȃ�
//*****************************************************************************
void Renderer::Release(void){
	//effekseer�֘A
	//if(_effekseer_manager != nullptr){
	//	_effekseer_manager->StopAllEffects();
	//	_effekseer_manager->Destroy();
	//	_effekseer_manager = nullptr;
	//}

	//if(_effekseer_renderer != nullptr){
	//	_effekseer_renderer->Destory();
	//	_effekseer_renderer = nullptr;
	//}
	
	//�e�N�X�`�����
	ReleaseAllTexture();
	ReleaseAllMesh();

	if(_D3D != nullptr){
		_D3D->Release();
		_D3D = nullptr;
	}
	if(_device != nullptr){
		_device->Release();
		_device = nullptr;
	}

	if(_white_texture != nullptr){
		_white_texture->Release();
		_white_texture = nullptr;
	}

	for (int i=0; i<Object::DRAW_LAYER_MAX; i++){
		if (_rendering_vs[i] != nullptr){
			delete _rendering_vs[i];
			_rendering_vs[i] = nullptr;
		}
		if (_rendering_ps[i] != nullptr){
			delete _rendering_ps[i];
			_rendering_ps[i] = nullptr;
		}
	}
}

//*****************************************************************************
//�y�X�V�z
//  DirectX9�̍X�V����
//  �Ԃ�l: �Ȃ�
//  ����: �Ȃ�
//*****************************************************************************
void Renderer::Update(void){

	//effekseer��view��ʒm
	//Effekseer::Matrix44 effekseer_proj;
	//Effekseer::Matrix44 effekseer_view;
	//for(int i = 0; i<16; i++){
	//	int row(i/4), line(i%4);
	//	effekseer_view.Values[row][line] = _view.m[row][line];
	//	effekseer_proj.Values[row][line] = _projection.m[row][line];
	//}

	// ���e�s��̍X�V
	//_effekseer_renderer->SetProjectionMatrix(effekseer_proj);
	// �J�����s��̍X�V
	//_effekseer_renderer->SetCameraMatrix(effekseer_view);

	//_effekseer_manager->Update(1.0f);
}

//*****************************************************************************
//�y�`��z
//  DirectX9�̕`�揈�� DX�Ɋւ���`��}�X�^�[
//  DirectX�̕`��@�\��K�v�Ƃ��郂�W���[���̕`�惁�\�b�h�͂��̒��ŌĂяo�����ƂɂȂ�
//  �Ԃ�l: �������ɐ����������ǂ���
//  ����: �Ȃ�
//*****************************************************************************
void Renderer::Draw(bool swap, D3DCOLOR clear_color){

	_device->Clear(0, nullptr,
						(D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL),
						clear_color,
						1.0f, 0);
	if(SUCCEEDED(_device->BeginScene())){

		VertexShader* def_vs(_cur_vs);
		PixelShader* def_ps(_cur_ps);

		for (int i = 0; i<Object::DRAW_LAYER_SCREEN; i++){
			SetCurrentVertexShader(_rendering_vs[i]);
			SetCurrentPixelShader(_rendering_ps[i]);

			Object::DrawLayer(static_cast<Object::DRAW_LAYER>(i));
		}

		//_effekseer_renderer->BeginRendering();
		//Object::DrawLayer(Object::DRAW_LAYER::DRAW_LAYER_EFFEKSEER);
		//_effekseer_manager->Draw();
		//_effekseer_renderer->EndRendering();
		ResetSamplerState();

		SetCurrentVertexShader(_rendering_vs[Object::DRAW_LAYER_MESH]);
		SetCurrentPixelShader(_rendering_ps[Object::DRAW_LAYER_MESH]);
		Debug::Draw();

		_cur_vs = def_vs;
		_cur_ps = def_ps;
		
		_device->EndScene();
	}

	//�o�b�t�@�̃X���b�v
	if(swap){
		_device->Present(nullptr, nullptr, 0, nullptr);
	}
}
void Renderer::DrawScreen(D3DCOLOR clear_color){
	_device->Clear(0, nullptr,
		(D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL),
		clear_color,
		1.0f, 0);
	if (SUCCEEDED(_device->BeginScene())){

		VertexShader* def_vs(_cur_vs);
		PixelShader* def_ps(_cur_ps);

		SetCurrentVertexShader(_rendering_vs[Object::DRAW_LAYER_SCREEN]);
		SetCurrentPixelShader(_rendering_ps[Object::DRAW_LAYER_SCREEN]);

		_device->SetRenderState(D3DRS_ZENABLE, FALSE);						//Z�o�b�t�@�̐ݒ�

		Object::DrawLayer(static_cast<Object::DRAW_LAYER>(Object::DRAW_LAYER_SCREEN));
		
		_device->SetRenderState(D3DRS_ZENABLE, TRUE);						//Z�o�b�t�@�̐ݒ�

		//_effekseer_renderer->BeginRendering();
		//Object::DrawLayer(Object::DRAW_LAYER::DRAW_LAYER_EFFEKSEER_2D);
		//_effekseer_renderer->EndRendering();
		ResetSamplerState();

		_cur_vs = def_vs;
		_cur_ps = def_ps;

		_device->EndScene();
	}

	//�o�b�t�@�̃X���b�v
	_device->Present(nullptr, nullptr, 0, nullptr);
}


//*****************************************************************************
//�y�e�N�X�`���̓ǂݍ��݁z
//  �e�N�X�`���ǂݍ��݈˗� ���łɑ��݂��Ă���ꍇ�͂����Ԃ�
//  ���s���ɂ�-1��Ԃ�
//  �Ԃ�l: �e�N�X�`��ID
//  ����: �t�@�C����
//*****************************************************************************
int Renderer::LoadTexture(const char *filename){
	int i = 0;						//loop index

	//null check
	if(filename == nullptr){return -1;}

	//�������O�̓z�����Ȃ����ǂ����`�F�b�N
	for(i=0; i<TEXTURE_MAX; i++){
		if(strcmp(filename, _texture_name[i]) == 0){
			if(_texture[i] == nullptr){
				i = -1;
			}
			return i;
		}
	}

	//���Ȃ��̂ŁA�󂫂�T��
	for(i=0; i<TEXTURE_MAX; i++){
		if(_texture_name[i][0] == '\0'){
			break;
		}
	}

	strcpy(_texture_name[i], filename);
	D3DXCreateTextureFromFile(_device, filename, &_texture[i]);

	if(_texture[i] == nullptr){
		strcpy(_texture_name[i], "");
		i = -1;
	}

	return i;
}

//*****************************************************************************
//�y�e�N�X�`���̎擾�z
//  �e�N�X�`��ID����e�N�X�`����Ԃ�
//  �Ԃ�l: �e�N�X�`���̃A�h���X
//  ����: �e�N�X�`��ID
//*****************************************************************************
LPDIRECT3DTEXTURE9 Renderer::GetTexture(int texture_id){
	//section check
	if(texture_id < 0 || TEXTURE_MAX <= texture_id){return nullptr;}

	return _texture[texture_id];
}

//*****************************************************************************
//�y�S�e�N�X�`���̔j���z
//  �Ԃ�l: �Ȃ�
//  ����: �Ȃ�
//*****************************************************************************
void Renderer::ReleaseAllTexture(void){
	int i = 0;					//loop index

	for(i=0; i<TEXTURE_MAX; i++){
		if(_texture[i] != nullptr){
			_texture[i]->Release();
			_texture[i] = nullptr;
		}

		memset(_texture_name[i], '\0', 64);
	}
}

//*****************************************************************************
//�y���b�V���̓ǂݍ��݁z
//  ���b�V���ǂݍ��݈˗� ���łɑ��݂��Ă���ꍇ�͂����Ԃ�
//  ���s���ɂ�-1��Ԃ�
//  �Ԃ�l: ���b�V��ID
//  ����: �t�@�C����
//*****************************************************************************
int Renderer::LoadMesh(const char *filename){
	int i = 0, j = 0;						//loop index
	HRESULT hr = S_OK;

	LPD3DXBUFFER adjacency_buff = nullptr;								//�אڏ��


	//null check
	if(filename == nullptr){return -1;}

	//�������O�̓z�����Ȃ����ǂ����`�F�b�N
	for(i=0; i<MESH_MAX; i++){
		if(strcmp(filename, _mesh[i].filename) == 0){
			if(_mesh[i].mesh == nullptr){
				i = -1;
			}
			return i;
		}
	}

	//���Ȃ��̂ŁA�󂫂�T��
	for(i=0; i<MESH_MAX; i++){
		if(_mesh[i].filename[0] == '\0'){
			break;
		}
	}

	strcpy(_mesh[i].filename, filename);
	if(FAILED(D3DXLoadMeshFromX(filename,
								D3DXMESH_SYSTEMMEM,
								_device,
								&adjacency_buff,
								&_mesh[i].mat_buff,
								nullptr,
								&_mesh[i].mat_num,
								&_mesh[i].mesh))){
		return -1;
	}
	D3DXMATERIAL *mat = nullptr;
	mat = (D3DXMATERIAL*)_mesh[i].mat_buff->GetBufferPointer();
	int mut_num = _mesh[i].mat_num;
	for(j=0; j<mut_num; j++){
		//�}�e���A���ɑΉ�����e�N�X�`���̓ǂݍ���
		_mesh[i].texture[j] = LoadTexture(mat[j].pTextureFilename);
	}

	if(_mesh[i].mesh == nullptr){
		strcpy(_mesh[i].filename, "");
		i = -1;
	}

	//optimaize
	hr = _mesh[i].mesh->OptimizeInplace(
		D3DXMESHOPT_COMPACT | D3DXMESHOPT_ATTRSORT | D3DXMESHOPT_VERTEXCACHE,
		(DWORD*)adjacency_buff->GetBufferPointer(),
		nullptr,
		nullptr,
		nullptr);

	if(adjacency_buff != nullptr){
		adjacency_buff->Release();
	}

	if(FAILED(hr)){
		return -1;
	}

	//���_�v�f�̒�`
	D3DVERTEXELEMENT9 v_ele[] = {
		{0,  0, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0},
		{0, 12, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_NORMAL, 0},
		{0, 24, D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 0},
		D3DDECL_END()
	};

	//�R���o�[�g
	LPD3DXMESH old_mesh = _mesh[i].mesh;
	hr = old_mesh->CloneMesh(D3DXMESH_MANAGED, v_ele, _device, &_mesh[i].mesh);

	//�R���o�[�g�O�̂��ׂ�
	old_mesh->Release();

	if(FAILED(hr)){
		return -1;
	}

	//������������Ȃ̂������IFVF�ł��Q�Ƃ��ēǂ�ł݂Ă�����
	//D3DXComputeNormals(mesh[i].mesh, nullptr);


	return i;
}

//*****************************************************************************
//�y���b�V���̎擾�z
//  ���b�V��ID����e�N�X�`����Ԃ�
//  �Ԃ�l: ���b�V���Z�b�g�̃A�h���X
//  ����: ���b�V��ID
//*****************************************************************************
Renderer::MESH_SET* Renderer::GetMesh(int mesh_id){
	//section check
	if(mesh_id < 0 || MESH_MAX <= mesh_id){return nullptr;}

	return &_mesh[mesh_id];
}

//*****************************************************************************
//�y�S���b�V���̔j���z
//  �Ԃ�l: �Ȃ�
//  ����: �Ȃ�
//*****************************************************************************
void Renderer::ReleaseAllMesh(void){
	int i = 0;					//loop index

	for(i=0; i<MESH_MAX; i++){
		if(_mesh[i].mesh != nullptr){
			_mesh[i].mesh->Release();
			_mesh[i].mesh = nullptr;
		}

		if(_mesh[i].mat_buff != nullptr){
			_mesh[i].mat_buff->Release();
			_mesh[i].mat_buff = nullptr;
		}

		memset(_mesh[i].filename, '\0', 64);
		memset(_mesh[i].texture, -1, MAT_MAX);
		_mesh[i].mat_num = 0;
	}
}




void Renderer::SetCurrentVertexShader(VertexShader* vs){
	_cur_vs = vs;
}
void Renderer::SetCurrentPixelShader(PixelShader* ps){
	_cur_ps = ps;
}


void Renderer::SetTextureToShader(int texture_id){
	if(_cur_ps == nullptr){return;}
	LPDIRECT3DTEXTURE9 work(nullptr);
	if(texture_id < 0 || TEXTURE_MAX <= texture_id){
		work = nullptr;
	}
	else{
		work = _texture[texture_id];
	}

	if(work == nullptr){
		work = _white_texture;
	}

	_cur_ps->SetTexture(work);
}

void Renderer::SetRenderTextureToShader(RenderTexture* texture){
	if (_cur_ps == nullptr){ return; }
	LPDIRECT3DTEXTURE9 work(texture->GetTexture());

	if (work == nullptr){
		work = _white_texture;
	}

	_cur_ps->SetTexture(work);
}

void Renderer::SetCurrentShader(void){
	if(_cur_vs != nullptr){
		_cur_vs->SetWorld(&_world);
		_cur_vs->SetView(&_view);
		_cur_vs->SetProjection(&_projection);
		_cur_vs->SetLightDirection(_light_direction);
		_cur_vs->SetLightDiffuse(_light_diffuse);
		_cur_vs->Set();
	}

	if(_cur_ps != nullptr){
		_cur_ps->SetLightDirection(_light_direction);
		_cur_ps->SetLightDiffuse(_light_diffuse);
		_cur_ps->SetLightPosition(_light_position);
		_cur_ps->SetPointLightRatio(_point_light_ratio);
		_cur_ps->Set();
	}
}

void Renderer::SetMaterialDiffuse(D3DXVECTOR4 value){
	if(_cur_vs == nullptr){return;}

	_cur_vs->SetMaterialDiffuse(value);
}


void Renderer::SetWorld(D3DXMATRIX& value){
	_world = value;

	if(_cur_vs == nullptr){ return; }
	_cur_vs->SetWorld(&value);
}

void Renderer::SetWorldArray(D3DXMATRIX* value, int length){
	if (_cur_vs == nullptr){ return; }
	_cur_vs->SetWorldArray(value, length);
}


void Renderer::SetView(D3DXMATRIX& value){
	_view = value;

	if(_cur_vs == nullptr){ return; }
	_cur_vs->SetView(&value);
}

void Renderer::SetProjection(D3DXMATRIX& value){
	_projection = value;

	if(_cur_vs == nullptr){ return; }
	_cur_vs->SetProjection(&value);
}

void Renderer::SetLightDiffuse(D3DXVECTOR4 diffuse){
	_light_diffuse = diffuse;

	if (_cur_vs != nullptr){
		_cur_vs->SetLightDiffuse(diffuse);
	}

	if (_cur_ps != nullptr){
		_cur_ps->SetLightDiffuse(diffuse);
	}
}

void Renderer::SetLightDirection(D3DXVECTOR3 direction){
	_light_direction = direction;

	if (_cur_vs != nullptr){
		_cur_vs->SetLightDirection(direction);
	}

	if (_cur_ps != nullptr){
		_cur_ps->SetLightDirection(direction);
	}
}

void Renderer::SetLightPosition(D3DXVECTOR3 position){
	_light_position = position;

	if (_cur_ps == nullptr){ return; }
	_cur_ps->SetLightPosition(position);
}
void Renderer::SetPointLightRatio(float ratio){
	_point_light_ratio = ratio;

	if (_cur_ps == nullptr){ return; }
	_cur_ps->SetPointLightRatio(ratio);
}

void Renderer::ResetSamplerState(void){
	//�����_�[�X�e�[�g�̐ݒ�
	_device->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);				//�w�ʃJ�����O�̐ݒ�
	_device->SetRenderState(D3DRS_ZENABLE, TRUE);						//Z�o�b�t�@�̐ݒ�
	_device->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);			//���u�����h�̐ݒ�
	_device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);		//�`�挳�̃��l�̐ݒ�
	_device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);	//�`���̃��l�̐ݒ�

	for(int i=0; i<4; i++){
		//�T���v���[�X�e�[�g�̐ݒ�
		_device->SetSamplerState(i, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);	//�e�N�X�`���̌J��Ԃ��ݒ�
		_device->SetSamplerState(i, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);
		_device->SetSamplerState(i, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);		//�e�N�X�`���g�k���̕⊮�ݒ�
		_device->SetSamplerState(i, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
		_device->SetSamplerState(i, D3DSAMP_MIPFILTER, D3DTEXF_NONE);

	}

	_device->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);	//���I�y���[�V���� �������킹�̐ݒ�
	_device->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);	//�e�N�X�`������
	_device->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_CURRENT);	//���ݕ`�悳��Ă�����̂���

}
