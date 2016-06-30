//*****************************************************************************
//  ���Ɨp
//  �������_
//  UPDATE : 2014/04/15
//*****************************************************************************
//*****************************************************************************
//  include
//*****************************************************************************
#include "main.h"
#include "manager.h"
#include "mouse_cursor.h"
#include "debug.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define CLASS_NAME		"AppClass"			// �E�C���h�E�̃N���X��
#define WINDOW_NAME		"���C�e�B���O"		// �E�C���h�E�̃L���v�V������

//*****************************************************************************
// �\���̒�`
//*****************************************************************************


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
HRESULT SetUp(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);
void Release(void);
void Update(void);
void Draw(void);

//*****************************************************************************
// �O���[�o���ϐ�:
//*****************************************************************************
HWND _main_window;
#ifdef _DEBUG
int						g_nCountFPS = 0;			// FPS�J�E���^
#endif

#ifdef _DEBUG
#ifndef DBG_NEW
#define DBG_NEW new(_NORMAL_BLOCK, __FILE__, __LINE__)
#endif
#endif

//=============================================================================
// ���C���֐�
//=============================================================================
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);	// �����Ă��ǂ����ǁA�x�����o��i���g�p�錾�j
	UNREFERENCED_PARAMETER(lpCmdLine);		// �����Ă��ǂ����ǁA�x�����o��i���g�p�錾�j

	//OutputDebugString("test");

	int ret = MessageBox(NULL, "�E�B���h�E���[�h�ŋN�����܂����H", "�N���I�v�V����", MB_YESNO);
	BOOL window = FALSE;
	if(ret == IDYES){
		window = TRUE;
	}

	DWORD dwExecLastTime;
	DWORD dwFPSLastTime;
	DWORD dwCurrentTime;
	DWORD dwFrameCount;

	WNDCLASSEX	wcex = {
		sizeof(WNDCLASSEX),
		CS_CLASSDC,
		WndProc,
		0,
		0,
		hInstance,
		NULL,
		LoadCursor(NULL, IDC_ARROW),
		(HBRUSH)(COLOR_WINDOW + 1),
		NULL,
		CLASS_NAME,
		NULL
	};
	MSG msg;
	
	// �E�B���h�E�N���X�̓o�^
	RegisterClassEx(&wcex);

	// �E�B���h�E�̍쐬
	_main_window = CreateWindowEx(0,
						CLASS_NAME,
						WINDOW_NAME,
						WS_OVERLAPPEDWINDOW,
						CW_USEDEFAULT,
						CW_USEDEFAULT,
						(SCREEN_WIDTH + GetSystemMetrics(SM_CXDLGFRAME) * 2),
						(SCREEN_HEIGHT + GetSystemMetrics(SM_CXDLGFRAME) * 2 + GetSystemMetrics(SM_CYCAPTION)),
						NULL,
						NULL,
						hInstance,
						NULL);

	

	// ����������(�E�B���h�E���쐬���Ă���s��)
	if(FAILED(SetUp(hInstance, _main_window, window))){
		return -1;
	}



	// �t���[���J�E���g������
	timeBeginPeriod(1);					// ����\��ݒ�
	dwExecLastTime = 
	dwFPSLastTime = timeGetTime();		// �V�X�e���������~���b�P�ʂŎ擾
	dwCurrentTime =
	dwFrameCount = 0;


	// �E�C���h�E�̕\��(�����������̌�ɍs��)
	ShowWindow(_main_window, nCmdShow);
	UpdateWindow(_main_window);
	
	// ���b�Z�[�W���[�v
	while(1)
	{
        if(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) != 0)	// ���b�Z�[�W���擾���Ȃ������ꍇ"0"��Ԃ�
		{// Windows�̏���
			if(msg.message == WM_QUIT)
			{// PostQuitMessage()���Ă΂ꂽ�烋�[�v�I��
				break;
			}
			else
			{
				// ���b�Z�[�W�̖|��Ƒ��o
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
        }
		else
		{
			dwCurrentTime = timeGetTime();		// �V�X�e���������擾

			if((dwCurrentTime - dwFPSLastTime) >= 500)	// 0.5�b���ƂɎ��s
			{
#ifdef _DEBUG
				g_nCountFPS = (dwFrameCount * 1000) / (dwCurrentTime - dwFPSLastTime);		// FPS�𑪒�
#endif
			    
				dwFPSLastTime = dwCurrentTime;		// FPS�𑪒肵��������ۑ�
				dwFrameCount = 0;					// �J�E���g���N���A
			}

			if((dwCurrentTime - dwExecLastTime) >= (1000 / 60))		// 1/60�b���ƂɎ��s
			{
				dwExecLastTime = dwCurrentTime;		// ��������������ۑ�

#ifdef _DEBUG
				Debug::Print("FPS: %d\n", g_nCountFPS);
#endif
				// �X�V����
				Update();

				// �`�揈��
				Draw();

				dwFrameCount++;			// �J�E���g�����Z
			}
		}
	}
	
	// �E�B���h�E�N���X�̓o�^������
	UnregisterClass(CLASS_NAME, wcex.hInstance);

	// �I������
	Release();

	timeEndPeriod(1);				// ����\��߂�

	_CrtDumpMemoryLeaks();

	return (int)msg.wParam;
}

//=============================================================================
// �v���V�[�W��
//=============================================================================
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch(uMsg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_KEYDOWN:
		switch(wParam)
		{
		case VK_ESCAPE:
			DestroyWindow(hWnd);
			break;
		}
		break;
	case WM_LBUTTONDOWN://���N���b�N
		MouseCursor::LeftDown();
		break;
	case WM_LBUTTONUP:
		MouseCursor::LeftUp();
		break;
	case WM_RBUTTONDOWN://�E�N���b�N
		MouseCursor::RightDown();
		break;
	case WM_RBUTTONUP:
		MouseCursor::RightUp();
		break;
	default:
		break;
	}


	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

//=============================================================================
// ����������
//=============================================================================
HRESULT SetUp(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
	Manager::SetUp(hInstance, hWnd, bWindow);

	//�V�F�[�_�[�ǂݍ���
	//vs_lambert = new VertexShader(renderer, "data/SHADER/half_lambert.hlsl", "VSHalfLambert");
	//ps_lambert = new PixelShader(renderer, "data/SHADER/half_lambert.hlsl", "PSLightTexture");

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void Release(void){
	//�܂ˁ[����̏I��
	Manager::Release();
}

//=============================================================================
// �X�V����
//=============================================================================
void Update(void){
	//�܂ˁ[����̍X�V
	Manager::Update();
}

//=============================================================================
// �`�揈��
//=============================================================================
void Draw(void){
	
	Manager::Draw();

}

//accessor
HWND GetMainWindowHandle(void){
	return _main_window;
}