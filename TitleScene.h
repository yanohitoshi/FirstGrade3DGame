#ifndef _TITLESCENE_H_
#define _TITLESCENE_H_
#include "EffekseerForDXLib.h"
#include "SceneBase.h"
#include "GameScene.h"
class Camera;
class Player;
class TitleStage;
class Shot;
class TitleBg;
class Ui;
class Enemy;


class TitleScene : public SceneBase
{
	Camera* camera;
	Player* player;
	TitleStage* titleStage;
	Shot* shot[shotNum];
	TitleBg* titleBg;
	Ui* ui;
	Enemy* enemy;
public:
	//コンストラクタ
	TitleScene();
	//デストラクタ
	~TitleScene();
	//初期化
	void Init();
	//更新
	SceneBase* Update();
	//描画
	void Draw();

private:
	//画像ハンドル
	int titleImage;
	int ruleImage;

	//2Dポジション
	int posX;
	int posY;
	//ゲーム開始用フラグ
	int startCount;
	bool startCountFlag = false;

	//チュートリアル画像表示フラグ
	bool imgChangeFlag = false;

	//サウンド関連
	int bgmHandle;
	bool soundFlag = true;
	int startSEHandle;
	bool startSoundFlag = true;
	int startBottanSEHandle;

	bool startUpFlag = false;

};
#endif

