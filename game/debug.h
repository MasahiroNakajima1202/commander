//*****************************************************************************
//  debug���W���[��
//  author: �������_
//  update: 2014/05/13
//*****************************************************************************
#ifndef _DEBUG_H_
#define _DEBUG_H_

#include "main.h"
#include <d3dx9.h>

#include "renderer.h"

//*****************************************************************************
//  constant
//*****************************************************************************
//#define _DEBUG_HIT_DRAW_

//*****************************************************************************
//  class
//*****************************************************************************
class Renderer;

class Debug{
public:
	//*****************************************************************************
	//�y�R���X�g���N�^�z
	//  ����: �Ȃ�
	//*****************************************************************************
	Debug(){}


	//*****************************************************************************
	//�y�f�X�l�z
	//  ���Ƃ����Â�
	//  ����: �Ȃ�
	//*****************************************************************************
	virtual ~Debug(){Release();}

	//*****************************************************************************
	//�y�������z
	//  �o�b�t�@�N���A�A�t�H���g�̎擾
	//  �Ԃ�l: �������ɐ����������ǂ���
	//  ����: �Ȃ�
	//*****************************************************************************
	static HRESULT SetUp(void);

	//*****************************************************************************
	//�y�I���z
	//  �Ԃ�l: �Ȃ�
	//  ����: �Ȃ�
	//*****************************************************************************
	static void Release(void);

	//*****************************************************************************
	//�y�o�́z
	//  �Ԃ�l: �Ȃ�
	//  ��1����: ������
	//  ��2����: �ϒ�����
	//*****************************************************************************
	static void Print(char* format, ...);

	//*****************************************************************************
	//�y�`��z
	//  �Ԃ�l: �Ȃ�
	//  ����: �Ȃ�
	//*****************************************************************************
	static void Draw(void);

	//accessor
	static void SetRenderer(Renderer *renderer){Debug::renderer = renderer;}

	static void SetCameraView(D3DXMATRIX *value){camera_view = *value;}
	static void EntryHitView(D3DXVECTOR3 pos, float radius);


private:
	static void LoadHitView(void);
	static void ReleaseHitView(void);

	static const int BUFFER_MAX = 1024;

	static Renderer *renderer;
	static char buffer[BUFFER_MAX];
	static LPD3DXFONT font;					// �t�H���g�ւ̃|�C���^

	static LPDIRECT3DVERTEXBUFFER9 vtx;			//���_�o�b�t�@�̃|�C���^
	static int texture_index;

	struct HIT_VIEW{
		D3DXVECTOR3 position;
		float radius;
		bool flag;
	};

	static const int HIT_VIEW_MAX = 128;
	static HIT_VIEW hit_view[HIT_VIEW_MAX];
	static D3DXMATRIX camera_view;


};

//accessor

#endif//_DEBUG_H_