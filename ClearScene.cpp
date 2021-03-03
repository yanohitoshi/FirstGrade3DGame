#include "Input.h"
#include "ClearScene.h"
#include "TitleScene.h"
#include "SceneBase.h"
#include "Time.h"
#include "EffekseerForDXLib.h"

ClearScene::ClearScene()
{
}


ClearScene::~ClearScene()
{
}

//������
void ClearScene::Init()
{
	posx = 0;
	posy = 0;
	clearImage = LoadGraph("data/texture/clearImage.png");

	//BGM
	bgmHandle = LoadSoundMem("data/bgm/title.mp3");

}
//�X�V
SceneBase* ClearScene::Update()
{
	if (INPUT_INSTANCE.padState.Buttons[XINPUT_BUTTON_A] & 1)
	{
		return new TitleScene;
	}
	return this;

}
//�`��
void ClearScene::Draw()
{
	DrawGraph(posx, posy, clearImage, true);
	TIME_INSTANCE.DrawResult();
}


