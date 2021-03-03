#ifndef _OVERSCENE_H_
#define _OVERSCENE_H_
#include "EffekseerForDXLib.h"
#include "SceneBase.h"

class OverScene : public SceneBase
{
public:
	OverScene();
	~OverScene();
	//初期化
	void Init();
	//更新
	SceneBase* Update();
	//描画
	void Draw();


private:
	//画像ハンドル
	int overImage;
	//ポジション
	int posx;
	int posy;

	//サウンド関連
	int bgmHandle;
	bool soundFlag = true;

};
#endif

