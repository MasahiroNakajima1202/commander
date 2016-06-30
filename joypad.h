//*****************************************************************************
//  ����
//  �������_
//  UPDATE:2013/07/23
//*****************************************************************************
#ifndef _JOYPAD_H_
#define _JOYPAD_H_

#include "input.h"


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
class Joypad : Input{
public:
	//�R���X�g�f�X�g
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
	static LPDIRECTINPUTDEVICE8 _joypad_device;			//DirectInput�̃L�[�{�[�h�p�f�o�C�X

	static const int H_MIN = 100;
	static const int V_MIN = 100;

	int _h_input;										//����������
	int _v_input;										//�c��������

	//�悤�킩���R�[���o�b�N
	static BOOL CALLBACK Joypad::EnumJoysticksCallback( const DIDEVICEINSTANCE *pdidInstance , VOID *pContext );
	static BOOL CALLBACK Joypad::EnumAxesCallback( const DIDEVICEOBJECTINSTANCE *pdidoi , VOID *pContext );
	
};


#endif