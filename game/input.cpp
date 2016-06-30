//*****************************************************************************
//  入力
//  中島将浩
//  UPDATE:2013/07/23
//*****************************************************************************
#include "input.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define INPUT_REPEAT_EARLY_REF (20)				//リピートの最初の空白時間
#define INPUT_REPEAT_LENGTH (5)					//リピートの間隔

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************

//*****************************************************************************
// static variables
//*****************************************************************************
LPDIRECTINPUT8 Input::_input_obj = NULL;			//DirectInputオブジェクトへのポインタ
int Input::_obj_ref = 0;							//参照カウンタ


//*****************************************************************************
// ライブラリリンク
//*****************************************************************************


//=============================================================================
// キーボードの初期化
//=============================================================================
HRESULT Input::SetUp(HINSTANCE hInstance, HWND hWnd)
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

	// デバイスオブジェクトを作成
	hr = _input_obj->CreateDevice(GUID_SysKeyboard, &_key_device, NULL);
	if(FAILED(hr)){
		MessageBox(hWnd, "DirectInputデバイスオブジェクトの作成に失敗しました。", "error", MB_OK);
		return hr;
	}

	// データフォーマットを設定
	hr = _key_device->SetDataFormat(&c_dfDIKeyboard);
	if(FAILED(hr)){
		MessageBox(hWnd, "データフォーマットの設定に失敗しました。", "error", MB_OK);
		return hr;
	}

	// 協調モードを設定（フォアグラウンド＆非排他モード）
	hr = _key_device->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE));
	if(FAILED(hr)){
		MessageBox(hWnd, "協調モードの設定に失敗しました。", "error", MB_OK);
		return hr;
	}

	// キーボードへのアクセス権を獲得(入力制御開始)
	_key_device->Acquire();

	return S_OK;
}

//=============================================================================
// キーボードの終了処理
//=============================================================================
void Input::Release(void)
{
	int i = 0;//loop index
	

	// デバイスオブジェクトの開放
	if(_key_device != NULL){
		_key_device->Unacquire();			//アクセス権の破棄
		_key_device->Release();
		_key_device = NULL;
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
void Input::Update(void)
{
	BYTE aKeyState[256];
	int i;//loop index

	if(SUCCEEDED(_key_device->GetDeviceState(sizeof(aKeyState), &aKeyState[0]))){
		for(i=0;i<256;i++){
			//trig計算
			_trig_state[i] = (_key_state[i] ^ aKeyState[i]) & aKeyState[i];

			//release計算
			_release_state[i] = (_key_state[i] ^ aKeyState[i]) & _key_state[i];

			//repeat計算
			if(aKeyState[i]){
				_press_count[i]++;
			}
			else{
				_press_count[i] = 0;
			}

			if(((_press_count[i] >= INPUT_REPEAT_EARLY_REF) && (_press_count[i] % INPUT_REPEAT_LENGTH == 0)) || _trig_state[i]){
				_repeat_state[i] = 1;
			}
			else{
				_repeat_state[i] = 0;
			}

			//数値入れ替え
			_key_state[i] = aKeyState[i];
		}
	}
	else{//キーボードの状態取得に失敗していた場合
		//アクセス権限を取り直す
		_key_device->Acquire();
	}
}

//=============================================================================
// キーボードのプレス状態を取得
//=============================================================================
bool Input::GetPress(int key)
{
	return (_key_state[key] != 0);
}

//=============================================================================
// キーボードのトリガー状態を取得
//=============================================================================
bool Input::GetTrigger(int key)
{
	return (_trig_state[key] != 0);
}

//=============================================================================
// キーボードのリピート状態を取得
//=============================================================================
bool Input::GetRepeat(int key)
{
	return (_repeat_state[key] != 0);
}

//=============================================================================
// キーボードのリリ－ス状態を取得
//=============================================================================
bool Input::GetRelease(int key)
{
	return (_release_state[key] != 0);
}

//=============================================================================
// コンストラクタ
//=============================================================================
Input::Input(HINSTANCE hInstance, HWND hWnd){
	int i = 0;//loop index
	HRESULT hr;

	// DirectInputオブジェクトの作成
	if(_input_obj == NULL){
		hr = DirectInput8Create(hInstance, DIRECTINPUT_VERSION,
								IID_IDirectInput8, (void**)&_input_obj, NULL);
		if(FAILED(hr)){
			MessageBox(hWnd, "DirectInputオブジェクトの作成に失敗しました。", "error", MB_OK);
		}
	}

	_key_device = NULL;

	_obj_ref++;

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
Input::~Input(void){
	_obj_ref--;
	if(_obj_ref == 0){
		// DirectInputオブジェクトの開放
		if(_input_obj != NULL){
			_input_obj->Release();
			_input_obj = NULL;
		}
	}
	Release();
}