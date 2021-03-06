#include "Input.h"
#include "OverScene.h"
#include "TitleScene.h"
#include "SceneBase.h"
#include "Time.h"
#include "EffekseerForDXLib.h"


OverScene::OverScene()
{
}


OverScene::~OverScene()
{
}

//初期化
void OverScene::Init()
{
	posx = 0;
	posy = 0;
	overImage = LoadGraph("data/texture/overImage.png");

	//BGM
	bgmHandle = LoadSoundMem("data/bgm/title.mp3");

}

//更新
SceneBase* OverScene::Update()
{

	if (INPUT_INSTANCE.padState.Buttons[XINPUT_BUTTON_A] & 1)
	{
		return new TitleScene;
	}
	return this;

}

//描画
void OverScene::Draw()
{
	ClearDrawScreen();
	DrawGraph(posx, posy, overImage, true);
	TIME_INSTANCE.DrawResult();

}
