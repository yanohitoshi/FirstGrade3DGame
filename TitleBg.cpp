#include "TitleBg.h"
#include "EffekseerForDXLib.h"



TitleBg::TitleBg()
{
}


TitleBg::~TitleBg()
{
}

void TitleBg::Init()
{
	// ３Ｄモデルの読み込み
	model = MV1LoadModel("data/model/skynao/skynao01/skynao.pmx");
	pos = VGet(0.0f, -1000.0f,0.0f);
}

void TitleBg::Updata()
{
	//ステージの位置の設定
	MV1SetPosition(model, pos);
}

void TitleBg::Draw()
{
	// ３Ｄモデルの拡大
	MV1SetScale(model, VGet(20.0f, 25.0f, 20.0f));
	//ステージの描画
	MV1DrawModel(model);
}
