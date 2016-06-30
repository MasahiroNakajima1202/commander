//*****************************************************************************
//  入力
//  中島将浩
//  UPDATE:2013/07/23
//*****************************************************************************
#include "joypad.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define JOYPAD_REPEAT_EARLY_REF (20)				//リピートの最初の空白時間
#define JOYPAD_REPEAT_LENGTH (5)					//リピートの間隔

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************

//*****************************************************************************
// static variables
//*****************************************************************************
LPDIRECTINPUTDEVICE8 Joypad::_joypad_device = NULL;			//DirectInputのキーボード用デバイス


//*****************************************************************************
// ライブラリリンク
//*****************************************************************************


//=============================================================================
// キーボードの初期化
//=============================================================================
HRESULT Joypad::SetUp(HINSTANCE hInstance, HWND hWnd)
{
	HRESULT hr = S_OK;
	int i;//loop index

	if(_input_obj == NULL){return E_FAIL;}

	//バッファ初期化
	for(i=0;i<256;i++){
		_key_state[i] = 0;
		_trig_state[i] = 0;
		_release_state[i] = 0;
		_repeat_state[i] = 0;
		_press_count[i] = 0;
	}

	_h_input = 0;
	_v_input = 0;

	// デバイスオブジェクトを作成
	hr = _input_obj->EnumDevices(DI8DEVCLASS_GAMECTRL, EnumJoysticksCallback, NULL, DIEDFL_ATTACHEDONLY);
	if(FAILED(hr)){
		MessageBox(hWnd, "DirectJoypadデバイスオブジェクトの作成に失敗しました。", "error", MB_OK);
		return hr;
	}

	if(_joypad_device == NULL){return E_FAIL;}

	// データフォーマットを設定
	hr = _joypad_device->SetDataFormat(&c_dfDIJoystick);
	if(FAILED(hr)){
		MessageBox(hWnd, "データフォーマットの設定に失敗しました。", "error", MB_OK);
		return hr;
	}

	// 協調モードを設定（フォアグラウンド＆非排他モード）
	hr = _joypad_device->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE));
	if(FAILED(hr)){
		MessageBox(hWnd, "協調モードの設定に失敗しました。", "error", MB_OK);
		return hr;
	}

	_joypad_device->EnumObjects(EnumAxesCallback, (void*)hWnd, DIDFT_AXIS);

	// キーボードへのアクセス権を獲得(入力制御開始)
	_joypad_device->Acquire();

	return S_OK;
}

//=============================================================================
// キーボードの終了処理
//=============================================================================
void Joypad::Release(void)
{
	int i = 0;//loop index

	// デバイスオブジェクトの開放
	if(_joypad_device != NULL){
		_joypad_device->Unacquire();			//アクセス権の破棄
		_joypad_device->Release();
		_joypad_device = NULL;
	}

	for(i=0; i<256; i++){
		_key_state[i] = 0;					//キー情報
		_trig_state[i] = 0;					//トリガー情報
		_release_state[i] = 0;				//リリース情報
		_repeat_state[i] = 0;				//リピート情報
		_press_count[i] = 0;					//押下カウンタ
	}
}

//=============================================================================
// キーボードの更新処理
//=============================================================================
void Joypad::Update(void)
{
	DIJOYSTATE joy_state;
	int i;//loop index

	if(_joypad_device == NULL){
		return;
	}

	if(SUCCEEDED(_joypad_device->GetDeviceState(sizeof(DIJOYSTATE), &joy_state))){
		_h_input = joy_state.lX;
		_v_input = joy_state.lY;
		for(i=0;i<32;i++){
			//trig計算
			_trig_state[i] = (_key_state[i] ^ joy_state.rgbButtons[i]) & joy_state.rgbButtons[i];

			//release計算
			_release_state[i] = (_key_state[i] ^ joy_state.rgbButtons[i]) & _key_state[i];

			//repeat計算
			if(joy_state.rgbButtons[i]){
				_press_count[i]++;
			}
			else{
				_press_count[i] = 0;
			}

			if(((_press_count[i] >= JOYPAD_REPEAT_EARLY_REF) && (_press_count[i] % JOYPAD_REPEAT_LENGTH == 0)) || _trig_state[i]){
				_repeat_state[i] = 1;
			}
			else{
				_repeat_state[i] = 0;
			}

			//数値入れ替え
			_key_state[i] = joy_state.rgbButtons[i];
		}
	}
	else{//キーボードの状態取得に失敗していた場合
		//アクセス権限を取り直す
		_joypad_device->Acquire();
	}
}

//=============================================================================
// キーボードのプレス状態を取得
//=============================================================================
bool Joypad::GetPress(int key)
{
	return (_key_state[key] != 0);
}

//=============================================================================
// キーボードのトリガー状態を取得
//=============================================================================
bool Joypad::GetTrigger(int key)
{
	return (_trig_state[key] != 0);
}

//=============================================================================
// キーボードのリピート状態を取得
//=============================================================================
bool Joypad::GetRepeat(int key)
{
	return (_repeat_state[key] != 0);
}

//=============================================================================
// キーボードのリリ－ス状態を取得
//=============================================================================
bool Joypad::GetRelease(int key)
{
	return (_release_state[key] != 0);
}

//=============================================================================
// コンストラクタ
//=============================================================================
Joypad::Joypad(HINSTANCE hInstance, HWND hWnd) : Input(hInstance, hWnd){
	int i = 0;//loop index

	for(i=0; i<256; i++){
		_key_state[i] = 0;					//キー情報
		_trig_state[i] = 0;					//トリガー情報
		_release_state[i] = 0;				//リリース情報
		_repeat_state[i] = 0;				//リピート情報
		_press_count[i] = 0;					//押下カウンタ
	}
}

//=============================================================================
// デス様
//=============================================================================
Joypad::~Joypad(void){
	Release();
}

int Joypad::GetStickH(void){
	int ret = _h_input;
	if(-H_MIN < ret && ret < H_MIN){
		ret = 0;
	}
	return ret;
}
int Joypad::GetStickV(void){
	int ret = _v_input;
	if(-V_MIN < ret && ret < V_MIN){
		ret = 0;
	}
	return ret;
}

BOOL CALLBACK Joypad::EnumJoysticksCallback( const DIDEVICEINSTANCE *pdidInstance , VOID *pContext )
{
	HRESULT hr;
	
	hr = _input_obj->CreateDevice( pdidInstance->guidInstance , &_joypad_device , NULL );
	
	if ( FAILED( hr ) ) return DIENUM_CONTINUE;
	
	return DIENUM_STOP;
}


BOOL CALLBACK Joypad::EnumAxesCallback( const DIDEVICEOBJECTINSTANCE *pdidoi , VOID *pContext )
{
	HRESULT     hr;
	DIPROPRANGE diprg;
	
	diprg.diph.dwSize       = sizeof( DIPROPRANGE );
	diprg.diph.dwHeaderSize = sizeof( DIPROPHEADER );
	diprg.diph.dwHow        = DIPH_BYID;
	diprg.diph.dwObj        = pdidoi->dwType;
	diprg.lMin              = 0 - 1000;
	diprg.lMax              = 0 + 1000;
	hr = _joypad_device->SetProperty( DIPROP_RANGE , &diprg.diph );
	
	if ( FAILED( hr ) ) return DIENUM_STOP;
	
	return DIENUM_CONTINUE;
}