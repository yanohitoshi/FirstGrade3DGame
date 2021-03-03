#include "Bg.h"
#include "EffekseerForDXLib.h"



Bg::Bg()
{
}

Bg::~Bg()
{
	// モデルのアンロード.
	MV1DeleteModel(model);
	MV1DeleteModel(model2);

}

void Bg::Init()
{

	//３Ｄモデルの読み込み
	model = MV1LoadModel("data/model/skynao/skynao01/skynao.pmx");
	model2 = MV1LoadModel("data/model/bgGrund.x");

	pos = VGet(0.0f, -1000.0f, 0.0f);
	pos2 = VGet(0.0f, -1000.0f, 0.0f);

}

void Bg::Updata()
{
	//ステージの位置の設定
	MV1SetPosition(model, pos);
	//ステージの位置の設定
	MV1SetPosition(model2, pos2);
}

void Bg::Draw()
{
	// ３Ｄモデルの拡大
	MV1SetScale(model, VGet(25.0f, 25.0f, 25.0f));
	//ステージの描画
	MV1DrawModel(model);
	// ３Ｄモデルの拡大
	MV1SetScale(model2, VGet(25.0f, 25.0f, 25.0f));
	//ステージの描画
	MV1DrawModel(model2);
}
