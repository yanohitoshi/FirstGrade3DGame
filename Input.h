#ifndef __INPUT_H__
#define __INPUT_H__

#include "EffekseerForDXLib.h"

class Input
{
public:

	~Input();

	void UpdateKey();

	bool GetKey(int _keyCode);
	bool GetKeyUp(int _keyCode);
	bool GetKeyDown(int _keyCode);

	bool GetJoypadKey(int _button);
	bool GetJoypadKeyUp(int _button);
	bool GetJoypadKeyDown(int _button);


	//XINPUT_STATE joypadKey;
	//���݂̃L�[���͏��
	XINPUT_STATE padState;
	//�P�t���[���O�̃L�[���͏��
	XINPUT_STATE prePadState;

	static Input& InputInstance()
	{
		static Input InputInst;
		return InputInst;
	}


private:
	//�V���O���g��
	Input();
	//���݂̃L�[���͏��
	char keyState[256];
	//�P�t���[���O�̃L�[���͏��
	char preKeyState[256];


};
#define INPUT_INSTANCE Input::InputInstance() 

#endif

