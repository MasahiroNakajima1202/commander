//*****************************************************************************
//  入力
//  中島将浩
//  UPDATE:2013/07/23
//*****************************************************************************
#ifndef _JOYPAD_H_
#define _JOYPAD_H_

#include "input.h"


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
class Joypad : Input{
public:
	//コンストデスト
	Joypad(HINSTANCE hInstance, HWND hWnd);
	virtual ~Joypad();

	HRESULT SetUp(HINSTANCE hInstance, HWND hWnd);
	void Release(void);
	void Update(void);

	bool GetPress(int key);
	bool GetTrigger(int key);
	bool GetRepeat(int key);
	bool GetRelease(int key);

	int GetStickH(void);
	int GetStickV(void);

	virtual int GetType(void){return TYPE_JOYPAD;}


protected:
	static LPDIRECTINPUTDEVICE8 _joypad_device;			//DirectInputのキーボード用デバイス

	static const int H_MIN = 100;
	static const int V_MIN = 100;

	int _h_input;										//横方向入力
	int _v_input;										//縦方向入力

	//ようわからんコールバック
	static BOOL CALLBACK Joypad::EnumJoysticksCallback( const DIDEVICEINSTANCE *pdidInstance , VOID *pContext );
	static BOOL CALLBACK Joypad::EnumAxesCallback( const DIDEVICEOBJECTINSTANCE *pdidoi , VOID *pContext );
	
};


#endif