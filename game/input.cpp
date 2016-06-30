//*****************************************************************************
//  ����
//  �������_
//  UPDATE:2013/07/23
//*****************************************************************************
#include "input.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define INPUT_REPEAT_EARLY_REF (20)				//���s�[�g�̍ŏ��̋󔒎���
#define INPUT_REPEAT_LENGTH (5)					//���s�[�g�̊Ԋu

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************

//*****************************************************************************
// static variables
//*****************************************************************************
LPDIRECTINPUT8 Input::_input_obj = NULL;			//DirectInput�I�u�W�F�N�g�ւ̃|�C���^
int Input::_obj_ref = 0;							//�Q�ƃJ�E���^


//*****************************************************************************
// ���C�u���������N
//*****************************************************************************


//=============================================================================
// �L�[�{�[�h�̏�����
//=============================================================================
HRESULT Input::SetUp(HINSTANCE hInstance, HWND hWnd)
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

	// �f�o�C�X�I�u�W�F�N�g���쐬
	hr = _input_obj->CreateDevice(GUID_SysKeyboard, &_key_device, NULL);
	if(FAILED(hr)){
		MessageBox(hWnd, "DirectInput�f�o�C�X�I�u�W�F�N�g�̍쐬�Ɏ��s���܂����B", "error", MB_OK);
		return hr;
	}

	// �f�[�^�t�H�[�}�b�g��ݒ�
	hr = _key_device->SetDataFormat(&c_dfDIKeyboard);
	if(FAILED(hr)){
		MessageBox(hWnd, "�f�[�^�t�H�[�}�b�g�̐ݒ�Ɏ��s���܂����B", "error", MB_OK);
		return hr;
	}

	// �������[�h��ݒ�i�t�H�A�O���E���h����r�����[�h�j
	hr = _key_device->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE));
	if(FAILED(hr)){
		MessageBox(hWnd, "�������[�h�̐ݒ�Ɏ��s���܂����B", "error", MB_OK);
		return hr;
	}

	// �L�[�{�[�h�ւ̃A�N�Z�X�����l��(���͐���J�n)
	_key_device->Acquire();

	return S_OK;
}

//=============================================================================
// �L�[�{�[�h�̏I������
//=============================================================================
void Input::Release(void)
{
	int i = 0;//loop index
	

	// �f�o�C�X�I�u�W�F�N�g�̊J��
	if(_key_device != NULL){
		_key_device->Unacquire();			//�A�N�Z�X���̔j��
		_key_device->Release();
		_key_device = NULL;
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
void Input::Update(void)
{
	BYTE aKeyState[256];
	int i;//loop index

	if(SUCCEEDED(_key_device->GetDeviceState(sizeof(aKeyState), &aKeyState[0]))){
		for(i=0;i<256;i++){
			//trig�v�Z
			_trig_state[i] = (_key_state[i] ^ aKeyState[i]) & aKeyState[i];

			//release�v�Z
			_release_state[i] = (_key_state[i] ^ aKeyState[i]) & _key_state[i];

			//repeat�v�Z
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

			//���l����ւ�
			_key_state[i] = aKeyState[i];
		}
	}
	else{//�L�[�{�[�h�̏�Ԏ擾�Ɏ��s���Ă����ꍇ
		//�A�N�Z�X��������蒼��
		_key_device->Acquire();
	}
}

//=============================================================================
// �L�[�{�[�h�̃v���X��Ԃ��擾
//=============================================================================
bool Input::GetPress(int key)
{
	return (_key_state[key] != 0);
}

//=============================================================================
// �L�[�{�[�h�̃g���K�[��Ԃ��擾
//=============================================================================
bool Input::GetTrigger(int key)
{
	return (_trig_state[key] != 0);
}

//=============================================================================
// �L�[�{�[�h�̃��s�[�g��Ԃ��擾
//=============================================================================
bool Input::GetRepeat(int key)
{
	return (_repeat_state[key] != 0);
}

//=============================================================================
// �L�[�{�[�h�̃����|�X��Ԃ��擾
//=============================================================================
bool Input::GetRelease(int key)
{
	return (_release_state[key] != 0);
}

//=============================================================================
// �R���X�g���N�^
//=============================================================================
Input::Input(HINSTANCE hInstance, HWND hWnd){
	int i = 0;//loop index
	HRESULT hr;

	// DirectInput�I�u�W�F�N�g�̍쐬
	if(_input_obj == NULL){
		hr = DirectInput8Create(hInstance, DIRECTINPUT_VERSION,
								IID_IDirectInput8, (void**)&_input_obj, NULL);
		if(FAILED(hr)){
			MessageBox(hWnd, "DirectInput�I�u�W�F�N�g�̍쐬�Ɏ��s���܂����B", "error", MB_OK);
		}
	}

	_key_device = NULL;

	_obj_ref++;

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
Input::~Input(void){
	_obj_ref--;
	if(_obj_ref == 0){
		// DirectInput�I�u�W�F�N�g�̊J��
		if(_input_obj != NULL){
			_input_obj->Release();
			_input_obj = NULL;
		}
	}
	Release();
}