#ifndef _WALL_H_
#define _WALL_H_
#include "EffekseerForDXLib.h"

enum WallState
{
	RIGHT = 0
	,LEFT = 1
	,UP = 2
	,DOWN = 3
};

class Wall
{
public:
	//コンストラクタ
	Wall();
	//デストラクタ
	~Wall();
	//初期化
	void Init();
	//更新
	void Update();
	//描画
	void Draw();

	const int wallNum = 4;
	bool flag = true;

	// モデルハンドルの取得.
	int GetModelHandle1() { return model1; }
	int GetModelHandle2() { return model2; }
	//ゲッターとセッター
	const VECTOR& GetPos() const { return pos; }
	void SetPos(const VECTOR set) { pos = set; }
	void SetModelHandole(int set) { model = set; }
	const VECTOR& GetSize() const { return size; }
	const VECTOR& GetSize1() const { return size1; }
	const VECTOR& GetSize2() const { return size2; }
	void SetSize(const VECTOR set) { size = set; }

	int wallState;
private:
	//モデルハンドル
	int model;
	int model1;
	int model2;
	//ポジション
	VECTOR pos;
	//速度
	VECTOR vel;
	//サイズ
	VECTOR size;
	VECTOR size1;
	VECTOR size2;
	//カウント
	int wallCount;
	int preWallCount;
	float speed;

};
#endif
