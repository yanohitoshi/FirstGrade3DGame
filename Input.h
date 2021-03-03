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
	//現在のキー入力情報
	XINPUT_STATE padState;
	//１フレーム前のキー入力情報
	XINPUT_STATE prePadState;

	static Input& InputInstance()
	{
		static Input InputInst;
		return InputInst;
	}


private:
	//シングルトン
	Input();
	//現在のキー入力情報
	char keyState[256];
	//１フレーム前のキー入力情報
	char preKeyState[256];


};
#define INPUT_INSTANCE Input::InputInstance() 

#endif

