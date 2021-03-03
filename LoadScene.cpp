#include "LoadScene.h"
#include "OverScene.h"
#include "TitleScene.h"
#include "GameScene.h"
#include "SceneBase.h"
#include "Input.h"


LoadScene::LoadScene()
{
}


LoadScene::~LoadScene()
{
}

void LoadScene::Init()
{
	posx = 0;
	posy = 0;
	loadImage = LoadGraph("data/texture/Loading.png");

}
//�X�V
SceneBase* LoadScene::Update()
{
	return new GameScene;
}
//�`��
void LoadScene::Draw()
{
	DrawGraph(posx, posy, loadImage, true);
}
