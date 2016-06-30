//*****************************************************************************
//  入力
//  中島将浩
//  UPDATE:2013/07/23
//*****************************************************************************
#ifndef _INPUT_H_
#define _INPUT_H_

#include "main.h"
#define DIRECTINPUT_VERSION (0x0800)			//警告つぶし
#include "dinput.h"

#pragma comment(lib, "dinput8.lib")


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
class Input{
public:
	//コンストデスト
	Input(HINSTANCE hInstance, HWND hWnd);
	virtual ~Input();

	enum TYPE{
		TYPE_KEYBOARD = 0,
		TYPE_JOYPAD,
		TYPE_MAX
	};

	virtual HRESULT SetUp(HINSTANCE hInstance, HWND hWnd);
	virtual void Release(void);
	virtual void Update(void);

	virtual bool GetPress(int key);
	virtual bool GetTrigger(int key);
	virtual bool GetRepeat(int key);
	virtual bool GetRelease(int key);

	virtual int GetType(void){return TYPE_KEYBOARD;}

protected:
	static LPDIRECTINPUT8 _input_obj;			//DirectInputオブジェクトへのポインタ
	static int _obj_ref;						//参照カウンタ
	LPDIRECTINPUTDEVICE8 _key_device;			//DirectInputのキーボード用デバイス
	BYTE _key_state[256];						//キー情報
	BYTE _trig_state[256];						//トリガー情報
	BYTE _release_state[256];					//リリース情報
	BYTE _repeat_state[256];					//リピート情報
	unsigned int _press_count[256];				//押下カウンタ
};


#endif