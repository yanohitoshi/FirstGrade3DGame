#include "Game.h"
#include "Input.h"
#include "Time.h"
#include "EffekseerForDXLib.h"

Game::Game()
	:m_screenWidth(1500)
	, m_screenHeight(800)
	, m_FullScreen(false)
{
}


Game::~Game()
{
}

void Game::setScreen(int width, int height, bool FullScreen)
{
	m_screenWidth = width;
	m_screenHeight = height;
	m_FullScreen = FullScreen;
}


// シーンの実行（シーン変更があるかないかを判断）
void Game::Update()
{
	//シーンを実行
	//今のシーンと次のシーンを比べるための準備
	SceneBase* tmpScene;
	tmpScene = m_nowScene->Update();

	// Effekseerにより再生中のエフェクトを更新する。
	UpdateEffekseer3D();

	//シーンの変更はあったか
	if (tmpScene != m_nowScene)
	{
		//前のシーンの解放
		delete m_nowScene;

		//新規シーンを今のシーンに差し替え
		m_nowScene = tmpScene;
		m_nowScene->Init();
	}
}

void Game::Init()
{
	if (!m_FullScreen)
	{
		ChangeWindowMode(TRUE);
	}
	SetGraphMode(m_screenWidth, m_screenHeight, 32, 60);
	DxLib_Init();   // DXライブラリ初期化処理
	// Effekseerを初期化する。
	// 引数には画面に表示する最大パーティクル数を設定する。
	if (Effekseer_Init(8000) == -1)
	{
		DxLib_End();
	}

	SetMouseDispFlag(true);
	SetDrawScreen(DX_SCREEN_BACK); //描画先を裏画面に設定


}

void Game::Draw()
{
	ClearDrawScreen();

	if (!m_nowScene)
	{
		return;
	}
	m_nowScene->Draw();
	// Effekseerにより再生中のエフェクトを描画する。
	DrawEffekseer3D();

	ScreenFlip();
}

void Game::ShutDown()
{
	delete m_nowScene;

	// Effekseerを終了する。
	Effkseer_End();
	//DXLibを終了
	DxLib::DxLib_End();
}


void Game::Run()
{
	//DXLibの初期化
	Init();

	//プログラムループをループ状態に
	bool ProgramLooping = true;
	//現在のシーンの初期化
	m_nowScene->Init();

	//今の時間をFrameStartTimeに入れる
	FrameStartTime = GetNowCount();

	TIME_INSTANCE.Init();

	while (ProgramLooping)
	{

		//６０FPSになるまで待つ
		while(GetNowCount() - FrameStartTime < 1000 / 60){}

		//フレーム開始時の時間をとる
		FrameStartTime = GetNowCount();

		if (ProcessMessage() != 0) 
		{
			break;
		}
		if (CheckHitKey(KEY_INPUT_ESCAPE) == 1 || INPUT_INSTANCE.padState.Buttons[XINPUT_BUTTON_BACK] == 1 && INPUT_INSTANCE.prePadState.Buttons[XINPUT_BUTTON_BACK] == 0)
		{
			break;
		}
		TIME_INSTANCE.Update2();
		INPUT_INSTANCE.UpdateKey();
		Update();
		Draw();
	}
	ShutDown();
}
