#include "Input.h"
#include <math.h>
#include "EffekseerForDXLib.h"

Input::Input()
{
}


Input::~Input()
{
}

// ���͏��̍X�V
void Input::UpdateKey()
{
	// �X�V����O�ɂP�t���[���O�̃L�[�����c���Ă���
 	memcpy(preKeyState, keyState, sizeof(keyState));

	prePadState = padState;

	GetJoypadXInputState(DX_INPUT_KEY_PAD1,&padState);

	int stickX = 0;
	int stickY = 0;
	GetJoypadAnalogInput(&stickX, &stickY, DX_INPUT_PAD1);
	//printfDx("%d %d\n", stickX, stickY);

	if (fabs(stickX) > 200) padState.ThumbLX = stickX;
	else padState.ThumbLX = 0;

	if (fabs(stickY) > 200) padState.ThumbLY = stickY;
	else padState.ThumbLY = 0;

	
	//printfDx("%f %f\n", padState.ThumbLX, padState.ThumbLY);
	//for (int i = 0; i < 16; i++)
	//{
	//	printfDx("%2d:%d", i, padState.Buttons[i]);
	//}

	// �ŐV�̃L�[���ɍX�V
	GetHitKeyStateAll(keyState);

}

//������Ă��邩
bool Input::GetKey(int _keyCode)
{
	return (keyState[_keyCode] == 1);
}

//�����ꂽ�u��
bool Input::GetKeyDown(int _keyCode)
{
	return (keyState[_keyCode] == 1 && preKeyState[_keyCode] == 0);
}
//�����ꂽ�u��
bool Input::GetKeyUp(int _keyCode)
{
	return (keyState[_keyCode] == 0 && preKeyState[_keyCode] == 1);
}

//������Ă��邩
bool Input::GetJoypadKey(int _button)
{
	return (_button & 1);
}

//�����ꂽ�u��
bool Input::GetJoypadKeyUp(int _button)
{
	return (padState.Buttons[_button] & 1 && prePadState.Buttons[_button] & 0);

}
//�����ꂽ�u��
bool Input::GetJoypadKeyDown(int _button)
{
	return (padState.Buttons[_button] & 0 && prePadState.Buttons[_button] & 1);
}

