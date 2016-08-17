//*****************************************************************************
//  rebderer���W���[��
//  DX�̏�������`��Ȃǂ𐿂�����
//  author: �������_
//  update: 2014/04/15
//*****************************************************************************
#ifndef _RENDERER_H_
#define _RENDERER_H_

#include "main.h"
#include "object.h"
#include "camera.h"


#include <d3dx9.h>
#define DIRECTINPUT_VERSION (0x0800)			//�x���Ԃ�
#include "dinput.h"

//effekseer�֘A
//#include <Effekseer.h>
//#include <EffekseerRendererDX9.h>

//#define FVF_VERTEX_2D (D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)	//2D�e�N�X�`���ݒ�
//#define	FVF_VERTEX_3D	(D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1)
//�X�L�����b�V���p�̒��_�t�H�[�}�b�g (���_ / 3 weight / mtx index / normal / diffuse / tex coord)
//#define FVF_VERTEX_BLEND_3D (D3DFVF_XYZB4 | D3DFVF_LASTBETA_UBYTE4 | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1)

//*****************************************************************************
// struct
//*****************************************************************************
typedef struct
{
	D3DXVECTOR3 vtx;		// ���_���W
	float rhw;				// �e�N�X�`���̃p�[�X�y�N�e�B�u�R���N�g�p
	D3DCOLOR diffuse;		// ���ˌ�
	D3DXVECTOR2 tex;		// �e�N�X�`�����W
} VERTEX_2D;

typedef struct
{
	D3DXVECTOR3 vtx;		// ���_���W
	D3DXVECTOR3 nor;		// �@���x�N�g��
	D3DCOLOR diffuse;		// ���ˌ�
	D3DXVECTOR2 tex;		// �e�N�X�`�����W
} VERTEX_3D;

typedef struct
{
	D3DXVECTOR3 vtx;		// ���_���W
	D3DXVECTOR3 nor;		// �@���x�N�g��
	D3DXVECTOR2 tex;		// �e�N�X�`�����W
} VERTEX_MESH;

struct VERTEX_BLEND_3D
{
    D3DXVECTOR3 vtx;		// ���_���W
    float weight[3];		// �d��
    DWORD mtx_index;		// ���_�C���f�b�N�X(���ʃo�C�g�����)
    D3DXVECTOR3 nor;		// �@���x�N�g��
	D3DCOLOR diffuse;		// ���ˌ�
	D3DXVECTOR2 tex;		// �e�N�X�`�����W
};

//*****************************************************************************
// ���C�u�����̃����N
//*****************************************************************************
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "dxguid.lib")


#if defined(DEBUG) || defined(_DEBUG)
#pragma comment(lib, "d3dx9d.lib")
#else
#pragma comment(lib, "d3dx9.lib")
#endif//_DEBUG

#pragma comment(lib, "dinput8.lib")

//effekseer�֘A
#pragma comment(lib, "Effekseer.lib")
#pragma comment(lib, "EffekseerRendererDX9.lib")

//*****************************************************************************
//  class
//*****************************************************************************
class GameInput;
class Light;
class Object;
class RenderTexture;
class VertexShader;
class PixelShader;
class Renderer{
public:
	//*****************************************************************************
	//�y�R���X�g���N�^�z
	//  �Ȃɂ����Ȃ��B
	//  ����: �Ȃ�
	//*****************************************************************************
	Renderer() :
		_cur_vs(nullptr),
		_cur_ps(nullptr),
		_light_direction(0.0f, 0.0f, 0.0f),
		_light_diffuse(0.0f, 0.0f, 0.0f, 0.0f),
		_light_position(0.0f, 0.0f, 0.0f),
		_point_light_ratio(0.0f){
		int i = 0;
		_D3D = nullptr;
		_device = nullptr;
		for(i=0; i<TEXTURE_MAX; i++){
			_texture[i] = nullptr;
			memset(_texture_name[i], '\0', 64);
		}
		memset(_mesh, 0, sizeof(MESH_SET) * MESH_MAX);
		for(i=0; i<MESH_MAX; i++){
			memset(_mesh[i].texture, -1, sizeof(int) * MAT_MAX);
		}

		for(i=0; i<Object::DRAW_LAYER_MAX; i++){
			_rendering_vs[i] = nullptr;
			_rendering_ps[i] = nullptr;
		}
	}

	//*****************************************************************************
	//�y�f�X�l�z
	//  ���Ƃ����Â�
	//  ����: �Ȃ�
	//*****************************************************************************
	virtual ~Renderer(){Release();}

	//*****************************************************************************
	//�y�������z
	//  DirectX9�̏���������
	//  �Ԃ�l: �������ɐ����������ǂ���
	//  ��1����: HINSTANCE
	//  ��2����: �E�B���h�E�n���h��
	//  ��3����: �E�B���h�E���[�h�̃t���O FALSE�Ńt���X�N���[��
	//*****************************************************************************
	HRESULT SetUp(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);

	//*****************************************************************************
	//�y�I���z
	//  DirectX9�̏I������
	//  �Ԃ�l: �Ȃ�
	//  ����: �Ȃ�
	//*****************************************************************************
	void Release(void);

	//*****************************************************************************
	//�y�X�V�z
	//  DirectX9�̍X�V����
	//  �Ԃ�l: �Ȃ�
	//  ����: �Ȃ�
	//*****************************************************************************
	void Update(void);

	//*****************************************************************************
	//�y�`��z
	//  DirectX9�̕`�揈�� DX�Ɋւ���`��}�X�^�[
	//  DirectX�̕`��@�\��K�v�Ƃ��郂�W���[���̕`�惁�\�b�h�͂��̒��ŌĂяo�����ƂɂȂ�
	//  �Ԃ�l: �Ȃ�
	//  ����: �Ȃ�
	//*****************************************************************************
	void Draw(bool swap = true, D3DCOLOR clear_color = D3DCOLOR_RGBA(16, 64, 144, 255));
	void DrawScreen(D3DCOLOR clear_color = D3DCOLOR_RGBA(16, 64, 144, 255));

	//*****************************************************************************
	//�y�e�N�X�`���̓ǂݍ��݁z
	//  �e�N�X�`���ǂݍ��݈˗� ���łɑ��݂��Ă���ꍇ�͂����Ԃ�
	//  ���s���ɂ�-1��Ԃ�
	//  �Ԃ�l: �e�N�X�`��ID
	//  ����: �t�@�C����
	//*****************************************************************************
	int LoadTexture(const char *filename);

	//*****************************************************************************
	//�y�e�N�X�`���̎擾�z
	//  �e�N�X�`��ID����e�N�X�`����Ԃ�
	//  �Ԃ�l: �e�N�X�`���̃A�h���X
	//  ����: �e�N�X�`��ID
	//*****************************************************************************
	LPDIRECT3DTEXTURE9 GetTexture(int texture_id);

	//*****************************************************************************
	//�y�S�e�N�X�`���̔j���z
	//  �Ԃ�l: �Ȃ�
	//  ����: �Ȃ�
	//*****************************************************************************
	void ReleaseAllTexture(void);

	//���b�V�����i�[�p
	static const int MAT_MAX = 32;
	struct MESH_SET{
		LPD3DXMESH mesh;									//���b�V�����A�h���X
		LPD3DXBUFFER mat_buff;								//�}�e���A�����A�h���X
		DWORD mat_num;										//�}�e���A���̐�
		char filename[64];
		int texture[MAT_MAX];
	};
	//*****************************************************************************
	//�y���b�V���̓ǂݍ��݁z
	//  ���b�V���ǂݍ��݈˗� ���łɑ��݂��Ă���ꍇ�͂����Ԃ�
	//  ���s���ɂ�-1��Ԃ�
	//  �Ԃ�l: ���b�V��ID
	//  ����: �t�@�C����
	//*****************************************************************************
	int LoadMesh(const char *filename);

	//*****************************************************************************
	//�y���b�V���̎擾�z
	//  ���b�V��ID����e�N�X�`����Ԃ�
	//  �Ԃ�l: ���b�V���Z�b�g�̃A�h���X
	//  ����: ���b�V��ID
	//*****************************************************************************
	MESH_SET *GetMesh(int mesh_id);

	//*****************************************************************************
	//�y�S���b�V���̔j���z
	//  �Ԃ�l: �Ȃ�
	//  ����: �Ȃ�
	//*****************************************************************************
	void ReleaseAllMesh(void);

	void DestroyLight(int index);							//���C�g��ׂ�
	void DestroyAllLight(void);								//���C�g������Ԓׂ�

	void SetCurrentVertexShader(VertexShader* vs);
	void SetCurrentPixelShader(PixelShader* ps);
	void SetTextureToShader(int texture_id);
	void SetRenderTextureToShader(RenderTexture* texture);

	void SetCurrentShader(void);

	//�V�F�[�_�[�v���p�e�B
	void SetMaterialDiffuse(D3DXVECTOR4 value);
	void SetWorld(D3DXMATRIX& value);
	void SetWorldArray(D3DXMATRIX* value, int length);
	void SetView(D3DXMATRIX& value);
	void SetProjection(D3DXMATRIX& value);
	void SetLightDirection(D3DXVECTOR3 direction);
	void SetLightDiffuse(D3DXVECTOR4 diffuse);
	void SetLightPosition(D3DXVECTOR3 position);
	void SetPointLightRatio(float ratio);

	D3DXMATRIX& GetView(void){return _view;}

	static const int BONE_TABLE_MAX = 52;

	//accessor
	LPDIRECT3DDEVICE9 GetDevice(void){return _device;}
	//Effekseer::Manager* GetEffekseerManager(void){return _effekseer_manager;}
	//EffekseerRenderer::Renderer* GetEffekseerRenderer(void){return _effekseer_renderer;}
private:
	int SearchFreeLightIndex(void);

	LPDIRECT3D9			_D3D;			// Direct3D�I�u�W�F�N�g
	LPDIRECT3DDEVICE9	_device;		// Device�I�u�W�F�N�g(�`��ɕK�v)


	static const int TEXTURE_MAX = 64;
	LPDIRECT3DTEXTURE9 _texture[TEXTURE_MAX];
	char _texture_name[TEXTURE_MAX][64];

	LPDIRECT3DTEXTURE9 _white_texture;			//NULL���̃e�N�X�`��
	
	static const int MESH_MAX = 64;
	MESH_SET _mesh[MESH_MAX];

	D3DXMATRIX _projection;
	D3DXMATRIX _view;
	D3DXMATRIX _world;
	D3DXVECTOR3 _light_direction;
	D3DXVECTOR4 _light_diffuse;
	D3DXVECTOR3 _light_position;
	float _point_light_ratio;

	//�����_�[�^�[�Q�b�g�ύX�p�e�N�X�`��

	VertexShader* _cur_vs;
	PixelShader* _cur_ps;

	VertexShader* _rendering_vs[Object::DRAW_LAYER_MAX];
	PixelShader* _rendering_ps[Object::DRAW_LAYER_MAX];

	static const int EFFEKSEER_SPRITE_MAX = 256;
	//EffekseerRenderer::Renderer* _effekseer_renderer;
	//Effekseer::Manager* _effekseer_manager;

	void ResetSamplerState(void);
};

#endif//_RENDERER_H_