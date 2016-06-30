//*****************************************************************************
//  授業用
//  中島将浩
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
// マクロ定義
//*****************************************************************************
#define CLASS_NAME		"AppClass"			// ウインドウのクラス名
#define WINDOW_NAME		"ライティング"		// ウインドウのキャプション名

//*****************************************************************************
// 構造体定義
//*****************************************************************************


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
HRESULT SetUp(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);
void Release(void);
void Update(void);
void Draw(void);

//*****************************************************************************
// グローバル変数:
//*****************************************************************************
HWND _main_window;
#ifdef _DEBUG
int						g_nCountFPS = 0;			// FPSカウンタ
#endif

#ifdef _DEBUG
#ifndef DBG_NEW
#define DBG_NEW new(_NORMAL_BLOCK, __FILE__, __LINE__)
#endif
#endif

//=============================================================================
// メイン関数
//=============================================================================
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);	// 無くても良いけど、警告が出る（未使用宣言）
	UNREFERENCED_PARAMETER(lpCmdLine);		// 無くても良いけど、警告が出る（未使用宣言）

	//OutputDebugString("test");

	int ret = MessageBox(NULL, "ウィンドウモードで起動しますか？", "起動オプション", MB_YESNO);
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
	
	// ウィンドウクラスの登録
	RegisterClassEx(&wcex);

	// ウィンドウの作成
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

	

	// 初期化処理(ウィンドウを作成してから行う)
	if(FAILED(SetUp(hInstance, _main_window, window))){
		return -1;
	}



	// フレームカウント初期化
	timeBeginPeriod(1);					// 分解能を設定
	dwExecLastTime = 
	dwFPSLastTime = timeGetTime();		// システム時刻をミリ秒単位で取得
	dwCurrentTime =
	dwFrameCount = 0;


	// ウインドウの表示(初期化処理の後に行う)
	ShowWindow(_main_window, nCmdShow);
	UpdateWindow(_main_window);
	
	// メッセージループ
	while(1)
	{
        if(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) != 0)	// メッセージを取得しなかった場合"0"を返す
		{// Windowsの処理
			if(msg.message == WM_QUIT)
			{// PostQuitMessage()が呼ばれたらループ終了
				break;
			}
			else
			{
				// メッセージの翻訳と送出
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
        }
		else
		{
			dwCurrentTime = timeGetTime();		// システム時刻を取得

			if((dwCurrentTime - dwFPSLastTime) >= 500)	// 0.5秒ごとに実行
			{
#ifdef _DEBUG
				g_nCountFPS = (dwFrameCount * 1000) / (dwCurrentTime - dwFPSLastTime);		// FPSを測定
#endif
			    
				dwFPSLastTime = dwCurrentTime;		// FPSを測定した時刻を保存
				dwFrameCount = 0;					// カウントをクリア
			}

			if((dwCurrentTime - dwExecLastTime) >= (1000 / 60))		// 1/60秒ごとに実行
			{
				dwExecLastTime = dwCurrentTime;		// 処理した時刻を保存

#ifdef _DEBUG
				Debug::Print("FPS: %d\n", g_nCountFPS);
#endif
				// 更新処理
				Update();

				// 描画処理
				Draw();

				dwFrameCount++;			// カウントを加算
			}
		}
	}
	
	// ウィンドウクラスの登録を解除
	UnregisterClass(CLASS_NAME, wcex.hInstance);

	// 終了処理
	Release();

	timeEndPeriod(1);				// 分解能を戻す

	_CrtDumpMemoryLeaks();

	return (int)msg.wParam;
}

//=============================================================================
// プロシージャ
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
	case WM_LBUTTONDOWN://左クリック
		MouseCursor::LeftDown();
		break;
	case WM_LBUTTONUP:
		MouseCursor::LeftUp();
		break;
	case WM_RBUTTONDOWN://右クリック
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
// 初期化処理
//=============================================================================
HRESULT SetUp(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
	Manager::SetUp(hInstance, hWnd, bWindow);

	//シェーダー読み込み
	//vs_lambert = new VertexShader(renderer, "data/SHADER/half_lambert.hlsl", "VSHalfLambert");
	//ps_lambert = new PixelShader(renderer, "data/SHADER/half_lambert.hlsl", "PSLightTexture");

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void Release(void){
	//まねーじゃの終了
	Manager::Release();
}

//=============================================================================
// 更新処理
//=============================================================================
void Update(void){
	//まねーじゃの更新
	Manager::Update();
}

//=============================================================================
// 描画処理
//=============================================================================
void Draw(void){
	
	Manager::Draw();

}

//accessor
HWND GetMainWindowHandle(void){
	return _main_window;
}