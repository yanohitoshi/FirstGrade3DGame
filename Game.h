#ifndef _GAME_H_
#define _GAME_H_
#include "EffekseerForDXLib.h"
#include "SceneBase.h"


class Time;

class Game
{

	Time* time;
public:
	~Game();
	//ゲーム実行
	void Run();
	//終了
	void ShutDown();
	//最初のシーンをセット
	void setFirstScene(SceneBase* pScene) { m_nowScene = pScene; }
	//スクリーン情報をセット
	void setScreen(int width, int height, bool Fullscreen);

	int FrameStartTime;

	//インスタンス
	static Game& GameInstance()
	{
		static Game GameSys;
		return GameSys;
	}


private:
	//--関数--//
	//シングルトン
	Game();
	//初期化
	void Init();
	//更新
	void Update();
	//描画
	void Draw();

	//--変数等--//
	// ウィンドウ幅・高さ
	int       m_screenWidth, m_screenHeight;
	//フルスクリーンかどうかフラグ
	bool      m_FullScreen;
	bool      m_IsGameQuit;

	SceneBase* m_nowScene;

};
#define GAMEINSTANCE Game::GameInstance()
#endif

