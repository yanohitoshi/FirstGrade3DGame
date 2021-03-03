#include "Input.h"
#include "TitleScene.h"
#include "SceneBase.h"
#include "GameScene.h"
#include "LoadScene.h"
#include "Time.h"
#include "Camera.h"
#include "Player.h"
#include "TitleStage.h"
#include "TitleBg.h"
#include "Shot.h"
#include "Ui.h"
#include "Enemy.h"
#include "System.h"
#include "EffekseerForDXLib.h"


TitleScene::TitleScene()
{
}


TitleScene::~TitleScene()
{
	delete(camera);
	delete(player);
	delete(titleBg);
	delete(titleStage);
	delete(ui);
	delete(enemy);
	for (int i = 0; i < shotNum; i++)
	{
		delete(shot[i]);
	}
	DeleteSoundMem(bgmHandle);
}

//������
void TitleScene::Init()
{
	// �J�����𐶐�
	camera = new Camera();
	player = new Player();
	for (int i = 0; i < shotNum; i++)
	{
		shot[i] = new Shot();
	}
	titleBg = new TitleBg();
	titleStage = new TitleStage();
	ui = new Ui();
	enemy = new Enemy();
	ui->Init();
	camera->Init();
	player->Init();
	for (int i = 0; i < shotNum; i++)
	{
		shot[i]->Init();
	}
	titleBg->Init();
	titleStage->Init();
	int model1 = MV1LoadModel("data/model/newEnemy/newenemy.pmx");
	int model2 = MV1LoadModel("data/model/newEnemy2/newenemy.pmx");
	int model3 = MV1LoadModel("data/model/newEnemy3/newenemy.pmx");
	int model4 = MV1LoadModel("data/model/shadow.x");
	enemy->Init(model1, model2, model3,model4);

	enemy->SetPos(VGet(GetRandom(-350, 350), 300.0f, GetRandom(-100, -350)));
	enemy->startUpFlag = true;
	enemy->aliveFlag = false;
	//-----�QD�֘A-----//
	posX = 0;
	posY = 0;
	titleImage = LoadGraph("data/texture/title.png");
	ruleImage = LoadGraph("data/texture/rule.png");

	//BGM
	bgmHandle = LoadSoundMem("data/bgm/title.mp3");
	startSEHandle = LoadSoundMem("data/SE/se_maoudamashii_jingle04.mp3");
	//�Q�[���J�n�p�J�E���g
	startCount = 0;
	startBottanSEHandle = LoadSoundMem("data/SE/decision5.mp3");

}

//�X�V
SceneBase* TitleScene::Update()
{
	if (soundFlag == true)
	{
		int b =  255 * 80 /100;
	
		ChangeVolumeSoundMem(b, bgmHandle);
		PlaySoundMem(bgmHandle, DX_PLAYTYPE_LOOP);

		soundFlag = false;
	}

	//�v���C���[
	player->UpdateTitle(*titleStage, shot);

	//�V���b�g
	for (int i = 0; i < shotNum; i++)
	{
		shot[i]->UpdateTitle(*player);
	}
	//�G�l�~�[
	enemy->UpdateTitle(*titleStage, *player, shot,camera);
	//�^�C�g���X�e�[�W
	titleStage->Updata();
	//�^�C�g���w�i
	titleBg->Updata();

	//�����߂�
	player->BackTitle(*titleStage);

	//�J����
	camera->UpdateTitle(*player);
	if (startUpFlag == false)
	{
		enemy->aliveFlag = false;
	}

	if (imgChangeFlag == false)
	{
		enemy->startCount = 0;
		if (INPUT_INSTANCE.padState.Buttons[XINPUT_BUTTON_A] == 1 && INPUT_INSTANCE.prePadState.Buttons[XINPUT_BUTTON_A] == 0)
		{
			PlaySoundMem(startBottanSEHandle, DX_PLAYTYPE_BACK);
			imgChangeFlag = true;
			startUpFlag = true;
			enemy->aliveFlag = true;
			enemy->SetVel(VGet(0.0f, 0.0f, 0.0f));
		}
	}
	else if (imgChangeFlag == true)
	{
		if (INPUT_INSTANCE.padState.Buttons[XINPUT_BUTTON_A] == 1 && INPUT_INSTANCE.prePadState.Buttons[XINPUT_BUTTON_A] == 0 )
		{

			if (startSoundFlag == true)
			{
				int b = 255 * 80 / 100;

				ChangeVolumeSoundMem(b, bgmHandle);
				PlaySoundMem(startSEHandle, DX_PLAYTYPE_BACK);

				startSoundFlag = false;
			}

			StopSoundMem(bgmHandle);
				return new LoadScene;
		}
		if (enemy->startCount >= 5)
		{
			if (startSoundFlag == true)
			{
				int b = 255 * 80 / 100;

				ChangeVolumeSoundMem(b, bgmHandle);
				PlaySoundMem(startSEHandle, DX_PLAYTYPE_BACK);

				startSoundFlag = false;
			}

			++startCount;
			if (startCount > 60)
			{
				StopSoundMem(bgmHandle);
				return new LoadScene;
			}
		}


	}

	return this;
}

//�`��
void TitleScene::Draw()
{
	ClearDrawScreen();
	//----�`��֘A----//
	titleBg->Draw();
	titleStage->Draw();
	//�V���b�g
	for (int i = 0; i < shotNum; i++)
	{
		shot[i]->Draw();
	}

	//�v���C���[
	player->DrawTitle();
	//�G�l�~�[
	enemy->Draw();
	if (imgChangeFlag == true)
	{
		DrawGraph(posX, posY, ruleImage, true);
	}
	else
	{
		DrawGraph(posX, posY, titleImage, true);
	}
	ui->Draw();
}
