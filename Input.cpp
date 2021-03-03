#include "Input.h"
#include <math.h>
#include "EffekseerForDXLib.h"

Input::Input()
{
}


Input::~Input()
{
}

// 入力情報の更新
void Input::UpdateKey()
{
	// 更新する前に１フレーム前のキー情報を残しておく
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

	// 最新のキー情報に更新
	GetHitKeyStateAll(keyState);

}

//押されているか
bool Input::GetKey(int _keyCode)
{
	return (keyState[_keyCode] == 1);
}

//押された瞬間
bool Input::GetKeyDown(int _keyCode)
{
	return (keyState[_keyCode] == 1 && preKeyState[_keyCode] == 0);
}
//離された瞬間
bool Input::GetKeyUp(int _keyCode)
{
	return (keyState[_keyCode] == 0 && preKeyState[_keyCode] == 1);
}

//押されているか
bool Input::GetJoypadKey(int _button)
{
	return (_button & 1);
}

//押された瞬間
bool Input::GetJoypadKeyUp(int _button)
{
	return (padState.Buttons[_button] & 1 && prePadState.Buttons[_button] & 0);

}
//離された瞬間
bool Input::GetJoypadKeyDown(int _button)
{
	return (padState.Buttons[_button] & 0 && prePadState.Buttons[_button] & 1);
}

