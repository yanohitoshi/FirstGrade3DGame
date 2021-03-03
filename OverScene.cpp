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

//������
void OverScene::Init()
{
	posx = 0;
	posy = 0;
	overImage = LoadGraph("data/texture/overImage.png");

	//BGM
	bgmHandle = LoadSoundMem("data/bgm/title.mp3");

}

//�X�V
SceneBase* OverScene::Update()
{

	if (INPUT_INSTANCE.padState.Buttons[XINPUT_BUTTON_A] & 1)
	{
		return new TitleScene;
	}
	return this;

}

//�`��
void OverScene::Draw()
{
	ClearDrawScreen();
	DrawGraph(posx, posy, overImage, true);
	TIME_INSTANCE.DrawResult();

}
