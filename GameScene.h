#ifndef _GAMESCENE_H_
#define _GAMESCENE_H_
#include "EffekseerForDXLib.h"
#include "SceneBase.h"

class Camera;
class Player;
class Enemy;
class Stage;
class Shot;
class Bg;
class Wall;
class Ui;

const int enemyNum = 20;
const int wallNum = 4;
const int shotNum = 6;

enum GameState
{
	START = 0
	,PLAY = 1
	,CLEAR = 2
	,END = 3
};


class GameScene : public SceneBase
{
	Player* player;
	Camera* camera;
	Enemy* enemy[enemyNum];
	Stage* stage;
	Shot* shot[shotNum];
	Bg* bg;
	Wall* wall[wallNum];
	Ui* ui;
public:
	GameScene();
	~GameScene();
	//初期化
	void Init();
	//更新
	SceneBase* Update();
	//描画
	void Draw();

	//ゲームシーンのゲームステータス
	int gameState;
	//スタート関連
	//ステータスがスタートの時用
	bool startFlag;
	int startCount;
	//クリアの時用
	int clearCount;
	//ゲームendフラグ
	bool endFlag = false;
	int endCount;

	//サウンド関連
	int bgmHandle;
	bool soundFlag = true;
	int clearSeHandle;
	int overSeHandle;
};
#endif

