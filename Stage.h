#ifndef _STAGE_H_
#define _STAGE_H_
#include "EffekseerForDXLib.h"

class Stage
{
public:
	//コンストラクタ
	Stage();
	//デストラクタ
	~Stage();

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
	//モデルハンドル
	int	   model;
	//	ポジション
	VECTOR pos;
	//サイズ
	VECTOR size;

};
#endif
