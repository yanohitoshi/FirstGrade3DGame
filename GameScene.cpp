#include "GameScene.h"
#include "SceneBase.h"
#include "OverScene.h"
#include "ClearScene.h"
#include "Player.h"
#include "Enemy.h"
#include "Camera.h"
#include "System.h"
#include "Input.h"
#include "Stage.h"
#include "Wall.h"
#include "Shot.h"
#include "Bg.h"
#include "Time.h"
#include "Ui.h"
#include "EffekseerForDXLib.h"


GameScene::GameScene()
{
}


GameScene::~GameScene()
{
	delete (camera);
	delete (player);
	delete (stage);
	delete (bg);
	for (int i = 0; i < enemyNum; i++)
	{
		delete (enemy[i]);
	}
	for (int i = 0; i < wallNum; i++)
	{
		delete (wall[i]);
	}
	for (int i = 0; i < shotNum; i++)
	{
		delete (shot[i]);
	}
}

//初期化
void GameScene::Init()
{
	gameState = START;
	startCount = 0;
	endCount = 0;
	clearCount = 0;
	//UI
	ui = new Ui();

	// カメラを生成
	camera = new Camera();

	// プレイヤーを生成
	player = new Player();
	//プレイヤー
	player->Init();

	//ステージの生成
	stage = new Stage();

	//背景の生成
	bg = new Bg();

	//エネミーの生成
	for (int i = 0; i < enemyNum; i++)
	{
		enemy[i] = new Enemy();
	}

	//壁の生成
	for (int i = 0; i < wallNum; i++)
	{
		wall[i] = new Wall();
	}

	//ショットの生成
	for (int i = 0; i < shotNum; i++)
	{
		shot[i] = new Shot();
	}

	//---初期化関連----//
	//UI
	ui->Init();

	//カメラ
	camera->Init();

	//エネミー
	// ３Ｄモデルの読み込み
	int model1 = MV1LoadModel("data/model/newEnemy/newenemy.pmx");
	int model2 = MV1LoadModel("data/model/newEnemy2/newenemy.pmx");
	int model3 = MV1LoadModel("data/model/newEnemy3/newenemy.pmx");
	int model4 = MV1LoadModel("data/model/shadow.x");
	for (int i = 0; i < enemyNum; i++)
	{
		enemy[i]->Init(model1, model2, model3,model4);
	}
	for (int i = 0; i < 10; i++)
	{
		enemy[i]->startUpFlag = true;
	}
	//ステージ
	stage->Init();


	//ショット
	for (int i = 0; i < shotNum; i++)
	{
		shot[i]->Init();
	}

	//背景
	bg->Init();

	//壁
	for (int i = 0; i < wallNum; i++)
	{
		wall[i]->Init();
	}

	//壁のポジションセット
	//奥
	wall[0]->SetPos(VGet(0.0f, 40.0f, 780.0f));
	wall[0]->wallState = UP;
	//手前
	wall[1]->SetPos(VGet(0.0f, 40.0f, -780.0f));
	wall[1]->wallState = DOWN;
	//右
	wall[2]->SetPos(VGet(790.0f, 40.0f, 0.0f));
	wall[2]->wallState = RIGHT;
	//左
	wall[3]->SetPos(VGet(-790.0f, 40.0f, 0.0f));
	wall[3]->wallState = LEFT;

	//モデルハンドルのセット
	wall[0]->SetModelHandole(wall[0]->GetModelHandle1());
	wall[1]->SetModelHandole(wall[1]->GetModelHandle1());
	wall[2]->SetModelHandole(wall[2]->GetModelHandle2());
	wall[3]->SetModelHandole(wall[3]->GetModelHandle2());

	//サイズのセット
	wall[0]->SetSize(wall[0]->GetSize1());
	wall[1]->SetSize(wall[1]->GetSize1());
	wall[2]->SetSize(wall[2]->GetSize2());
	wall[3]->SetSize(wall[3]->GetSize2());


	startFlag = true;

	TIME_INSTANCE.defeatCount = 0;

	//BGM
	bgmHandle = LoadSoundMem("data/bgm/battal.mp3");
	clearSeHandle = LoadSoundMem("data/SE/clearSE.mp3");
	overSeHandle = LoadSoundMem("data/SE/zannense.mp3");

}
//更新
SceneBase* GameScene::Update()
{
	//ゲームスタート時
	if (gameState == START)
	{
		if (startFlag == true)
		{
			//プレイヤー
			player->Update(*stage, shot, wall);
			//エネミーのポジションをセット
			//0番から４番まで
			for (int i = 0; i <= 4; i++)
			{
				enemy[i]->SetPos(VGet(GetRandom(100, 750), 100.0f, GetRandom(100, 700)));
			}
			//５番から9番まで
			for (int i = 5; i <= 9; i++)
			{
				enemy[i]->SetPos(VGet(GetRandom(-750, -100), 100.0f, GetRandom(100, 700)));
			}
			//10番から14番まで
			for (int i = 10; i <= 14; i++)
			{
				enemy[i]->SetPos(VGet(GetRandom(100, 750), 100.0f, GetRandom(-100, -700)));
			}
			//15番から19番まで
			for (int i = 15; i <= 19; i++)
			{
				enemy[i]->SetPos(VGet(GetRandom(-100, -750), 100.0f, GetRandom(-100, -700)));
			}
			startFlag = false;
		}
		//背景
		bg->Updata();

		//カメラ
		camera->Update(*player);
		ui->Update();
		++startCount;
		if (startCount == 240)
		{
			TIME_INSTANCE.Update1();
			gameState = PLAY;
		}
	}

	if (gameState == PLAY)
	{

		if (soundFlag == true)
		{
			int b = 255 * 80 / 100;

			ChangeVolumeSoundMem(b, bgmHandle);
			PlaySoundMem(bgmHandle, DX_PLAYTYPE_LOOP);

			soundFlag = false;
		}

		//-----制御関連-----//
		//プレイヤー
		player->Update(*stage,shot,wall);

		//ショット
		for (int i = 0; i < shotNum; i++)
		{
			shot[i]->Update(*player,wall);
		}
		//エネミー
		for (int i = 0; i < enemyNum; i++)
		{
			enemy[i]->Update(*stage, *player, shot,wall,camera);
		}
		//ステージ
		stage->Updata();
		//壁
		for (int i = 0; i < wallNum; i++)
		{
			wall[i]->Update();
		}

		//背景
		bg->Updata();
		//カメラ
		camera->Update(*player);

		//押し戻し
		player->Back(*stage);

		if (player->aliveFlag == false)
		{
			StopSoundMem(bgmHandle);
			soundFlag = true;
			gameState = END;
		}

		if (TIME_INSTANCE.countDown == 0)
		{
			StopSoundMem(bgmHandle);
			soundFlag = true;
			gameState = CLEAR;
		}

		if (TIME_INSTANCE.countDown == 45)
		{
			for (int i = 0; i < 15; i++)
			{
				if (enemy[i]->startUpFlag == false)
				{
					enemy[i]->SetPos(VGet(GetRandom(-500, 500), 300.0f, GetRandom(-500, 500)));
					enemy[i]->startUpFlag = true;
				}
			}
		}
		if (TIME_INSTANCE.countDown == 15)
		{
			for (int i = 0; i < 20; i++)
			{
				if (enemy[i]->startUpFlag == false)
				{
					enemy[i]->SetPos(VGet(GetRandom(-200, 200), 300.0f, GetRandom(-200, 200)));
					enemy[i]->startUpFlag = true;
				}
			}
		}

	}

	if (gameState == CLEAR)
	{
		//カメラ
		camera->Update(*player);
		for (int i = 0; i < enemyNum; i++)
		{
			enemy[i]->UpdateClear(*stage, *player, shot, wall, camera);
		}
		player->UpdateClear(*stage);
		if (soundFlag == true)
		{
			int b = 255 * 80 / 100;

			ChangeVolumeSoundMem(b, bgmHandle);
			PlaySoundMem(clearSeHandle, DX_PLAYTYPE_BACK);

			soundFlag = false;
		}
		++clearCount;
		if (clearCount == 180)
		{
			return new ClearScene;
		}
	}

	if (gameState == END)
	{
		if (soundFlag == true)
		{
			int b = 255 * 80 / 100;

			ChangeVolumeSoundMem(b, bgmHandle);
			PlaySoundMem(overSeHandle, DX_PLAYTYPE_BACK);

			soundFlag = false;
		}

		//カメラ
		camera->Update(*player);
		player->UpdateEnd();
		++endCount;
		if (endCount == 180)
		{
			return new OverScene;
		}
	}
	return this;

}
//描画
void GameScene::Draw()
{
	//----描画関連----//
	ClearDrawScreen();
	if (gameState == START)
	{
		//壁
		for (int i = 0; i < wallNum; i++)
		{
			wall[i]->Draw();
		}
		//背景
		bg->Draw();

		//ステージ
		stage->Draw();

		//プレイヤー
		player->Draw();

		//UI
		ui->countDraw();

	}
	if (gameState == PLAY)
	{
		//壁
		for (int i = 0; i < wallNum; i++)
		{
			wall[i]->Draw();
		}

		//背景
		bg->Draw();

		//ステージ
		stage->Draw();

		//エネミー
		for (int i = 0; i < enemyNum; i++)
		{
			enemy[i]->Draw();
		}

		//ショット
		for (int i = 0; i < shotNum; i++)
		{
			shot[i]->Draw();
		}

		//プレイヤー
		player->Draw();

		TIME_INSTANCE.Draw();

		//UI
		ui->Draw();
		ui->playDraw();

	}

	if (gameState == CLEAR)
	{

		//壁
		for (int i = 0; i < wallNum; i++)
		{
			wall[i]->Draw();
		}

		//背景
		bg->Draw();

		//ステージ
		stage->Draw();

		for (int i = 0; i < enemyNum; i++)
		{
			enemy[i]->Draw();
		}

		//プレイヤー
		player->Draw();

		//UI
		ui->Draw();
	}

	if (gameState == END)
	{
		//壁
		for (int i = 0; i < wallNum; i++)
		{
			wall[i]->Draw();
		}
		//背景
		bg->Draw();

		//ステージ
		stage->Draw();

		//プレイヤー
		player->DrawEnd();

		//UI
		ui->Draw();
	}
}
