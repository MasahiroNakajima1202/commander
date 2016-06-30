//*****************************************************************************
//  ����
//  �������_
//  UPDATE:2013/07/23
//*****************************************************************************
#ifndef _INPUT_H_
#define _INPUT_H_

#include "main.h"
#define DIRECTINPUT_VERSION (0x0800)			//�x���Ԃ�
#include "dinput.h"

#pragma comment(lib, "dinput8.lib")


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
class Input{
public:
	//�R���X�g�f�X�g
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
	static LPDIRECTINPUT8 _input_obj;			//DirectInput�I�u�W�F�N�g�ւ̃|�C���^
	static int _obj_ref;						//�Q�ƃJ�E���^
	LPDIRECTINPUTDEVICE8 _key_device;			//DirectInput�̃L�[�{�[�h�p�f�o�C�X
	BYTE _key_state[256];						//�L�[���
	BYTE _trig_state[256];						//�g���K�[���
	BYTE _release_state[256];					//�����[�X���
	BYTE _repeat_state[256];					//���s�[�g���
	unsigned int _press_count[256];				//�����J�E���^
};


#endif