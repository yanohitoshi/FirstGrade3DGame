#include "TitleStage.h"
#include "EffekseerForDXLib.h"


TitleStage::TitleStage()
{
}


TitleStage::~TitleStage()
{
	// モデルのアンロード.
	MV1DeleteModel(model);
}

//初期化
void TitleStage::Init()
{
	//-----３D関連-----//
	//3Dモデルのロード
	model = MV1LoadModel("data/model/titleStage/titleStage.pmd");
	pos = VGet(0.0f, 200.0f, 50.0f);
	size = VGet(800.0f, 10.0f, 800.0f);
}
//更新
void TitleStage::Updata()
{
	//ステージの位置の設定
	MV1SetPosition(model, pos);

}
//描画
void TitleStage::Draw()
{
	// ３Ｄモデルのスケールを引き伸ばし
	MV1SetScale(model, VGet(4.0f, 4.0f, 4.0f));
	//ステージの描画
	MV1DrawModel(model);
}
