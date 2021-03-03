#include "Stage.h"
#include "EffekseerForDXLib.h"



Stage::Stage()
{
}


Stage::~Stage()
{
	// モデルのアンロード.
	MV1DeleteModel(model);
}

//初期化
void Stage::Init()
{
	// ３Ｄモデルの読み込み
	model = MV1LoadModel("data/model/stage5.x");
	pos = VGet(0.0f, 0.0f, 0.0f);
	size = VGet(1700.0f, 60.0f, 1700.0f);

}
//更新
void Stage::Updata()
{
	//ステージの位置の設定
	MV1SetPosition(model, pos);
}
//描画
void Stage::Draw()
{
	//ステージの描画
	MV1DrawModel(model);
}
