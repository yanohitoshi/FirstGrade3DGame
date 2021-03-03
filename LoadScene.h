#ifndef _LOADSCENE_H_
#define _LOADSCENE_H_
#include "EffekseerForDXLib.h"
#include "SceneBase.h"

class LoadScene : public SceneBase
{
public:
	LoadScene();
	~LoadScene();
	//初期化
	void Init();
	//更新
	SceneBase* Update();
	//描画
	void Draw();


private:
	//画像ハンドル
	int loadImage;
	//ポジション
	int posx;
	int posy;

};
#endif
