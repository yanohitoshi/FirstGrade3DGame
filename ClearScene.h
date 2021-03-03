#ifndef _CLEARSCENE_H_
#define _CLEARSCENE_H_
#include "EffekseerForDXLib.h"
#include "SceneBase.h"

class ClearScene : public SceneBase
{
public:
	ClearScene();
	~ClearScene();
	//初期化
	void Init();
	//更新
	SceneBase* Update();
	//描画
	void Draw();


private:
	//画像ハンドル
	int clearImage;
	//ポジション
	int posx;
	int posy;

	//サウンド関連
	int bgmHandle;
	bool soundFlag = true;

};
#endif

