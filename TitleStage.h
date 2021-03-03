#ifndef _TITLESTAGE_H_
#define _TITLESTAGE_H_
#include "EffekseerForDXLib.h"

class TitleStage
{
public:
	TitleStage();
	~TitleStage();
	//初期化
	void Init();
	//更新
	void Updata();
	//描画
	void Draw();

	// モデルハンドルの取得.
	int GetModelHandle() { return model; }

	//ゲッターとセッター
	const VECTOR& GetPos() const { return pos; }
	void SetPos(const VECTOR set) { pos = set; }
	const VECTOR& GetSize() const { return size; }
private:
	//3Dポジション
	VECTOR pos;
	//サイズ
	VECTOR size;
	//モデル
	int model;

};
#endif

