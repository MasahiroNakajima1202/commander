//*****************************************************************************
//  ����
//  �������_
//  UPDATE:2013/07/23
//*****************************************************************************
#include "joypad.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define JOYPAD_REPEAT_EARLY_REF (20)				//���s�[�g�̍ŏ��̋󔒎���
#define JOYPAD_REPEAT_LENGTH (5)					//���s�[�g�̊Ԋu

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************

//*****************************************************************************
// static variables
//*****************************************************************************
LPDIRECTINPUTDEVICE8 Joypad::_joypad_device = NULL;			//DirectInput�̃L�[�{�[�h�p�f�o�C�X


//*****************************************************************************
// ���C�u���������N
//*****************************************************************************


//=============================================================================
// �L�[�{�[�h�̏�����
//=============================================================================
HRESULT Joypad::SetUp(HINSTANCE hInstance, HWND hWnd)
{
	HRESULT hr = S_OK;
	int i;//loop index

	if(_input_obj == NULL){return E_FAIL;}

	//�o�b�t�@������
	for(i=0;i<256;i++){
		_key_state[i] = 0;
		_trig_state[i] = 0;
		_release_state[i] = 0;
		_repeat_state[i] = 0;
		_press_count[i] = 0;
	}

	_h_input = 0;
	_v_input = 0;

	// �f�o�C�X�I�u�W�F�N�g���쐬
	hr = _input_obj->EnumDevices(DI8DEVCLASS_GAMECTRL, EnumJoysticksCallback, NULL, DIEDFL_ATTACHEDONLY);
	if(FAILED(hr)){
		MessageBox(hWnd, "DirectJoypad�f�o�C�X�I�u�W�F�N�g�̍쐬�Ɏ��s���܂����B", "error", MB_OK);
		return hr;
	}

	if(_joypad_device == NULL){return E_FAIL;}

	// �f�[�^�t�H�[�}�b�g��ݒ�
	hr = _joypad_device->SetDataFormat(&c_dfDIJoystick);
	if(FAILED(hr)){
		MessageBox(hWnd, "�f�[�^�t�H�[�}�b�g�̐ݒ�Ɏ��s���܂����B", "error", MB_OK);
		return hr;
	}

	// �������[�h��ݒ�i�t�H�A�O���E���h����r�����[�h�j
	hr = _joypad_device->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE));
	if(FAILED(hr)){
		MessageBox(hWnd, "�������[�h�̐ݒ�Ɏ��s���܂����B", "error", MB_OK);
		return hr;
	}

	_joypad_device->EnumObjects(EnumAxesCallback, (void*)hWnd, DIDFT_AXIS);

	// �L�[�{�[�h�ւ̃A�N�Z�X�����l��(���͐���J�n)
	_joypad_device->Acquire();

	return S_OK;
}

//=============================================================================
// �L�[�{�[�h�̏I������
//=============================================================================
void Joypad::Release(void)
{
	int i = 0;//loop index

	// �f�o�C�X�I�u�W�F�N�g�̊J��
	if(_joypad_device != NULL){
		_joypad_device->Unacquire();			//�A�N�Z�X���̔j��
		_joypad_device->Release();
		_joypad_device = NULL;
	}

	for(i=0; i<256; i++){
		_key_state[i] = 0;					//�L�[���
		_trig_state[i] = 0;					//�g���K�[���
		_release_state[i] = 0;				//�����[�X���
		_repeat_state[i] = 0;				//���s�[�g���
		_press_count[i] = 0;					//�����J�E���^
	}
}

//=============================================================================
// �L�[�{�[�h�̍X�V����
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
			//trig�v�Z
			_trig_state[i] = (_key_state[i] ^ joy_state.rgbButtons[i]) & joy_state.rgbButtons[i];

			//release�v�Z
			_release_state[i] = (_key_state[i] ^ joy_state.rgbButtons[i]) & _key_state[i];

			//repeat�v�Z
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

			//���l����ւ�
			_key_state[i] = joy_state.rgbButtons[i];
		}
	}
	else{//�L�[�{�[�h�̏�Ԏ擾�Ɏ��s���Ă����ꍇ
		//�A�N�Z�X��������蒼��
		_joypad_device->Acquire();
	}
}

//=============================================================================
// �L�[�{�[�h�̃v���X��Ԃ��擾
//=============================================================================
bool Joypad::GetPress(int key)
{
	return (_key_state[key] != 0);
}

//=============================================================================
// �L�[�{�[�h�̃g���K�[��Ԃ��擾
//=============================================================================
bool Joypad::GetTrigger(int key)
{
	return (_trig_state[key] != 0);
}

//=============================================================================
// �L�[�{�[�h�̃��s�[�g��Ԃ��擾
//=============================================================================
bool Joypad::GetRepeat(int key)
{
	return (_repeat_state[key] != 0);
}

//=============================================================================
// �L�[�{�[�h�̃����|�X��Ԃ��擾
//=============================================================================
bool Joypad::GetRelease(int key)
{
	return (_release_state[key] != 0);
}

//=============================================================================
// �R���X�g���N�^
//=============================================================================
Joypad::Joypad(HINSTANCE hInstance, HWND hWnd) : Input(hInstance, hWnd){
	int i = 0;//loop index

	for(i=0; i<256; i++){
		_key_state[i] = 0;					//�L�[���
		_trig_state[i] = 0;					//�g���K�[���
		_release_state[i] = 0;				//�����[�X���
		_repeat_state[i] = 0;				//���s�[�g���
		_press_count[i] = 0;					//�����J�E���^
	}
}

//=============================================================================
// �f�X�l
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