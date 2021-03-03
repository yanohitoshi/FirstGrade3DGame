#ifndef _ITEM_H_
#define _ITEM_H_
#include "EffekseerForDXLib.h"

class Stage;
class Player;

enum flagNum
{
	POWER_UP
	, POWER_DOWN
	,SPEED_UP
	,SPEED_DOWN
};

class Item
{
public:
	Item();
	~Item();
	//初期化
	void Init();
	//更新
	void Update(Stage &stage, Player &player);
	//描画
	void Draw();
	//押し戻し
	void Back(Stage &stage);
	//アイテム効果のフラグスイッチ
	void flagSwith();

	//持っているフラグ
	int flagState = 0;

	//------フラグ関連------//
	//重力フラグ
	bool gravityFlag = true;
	//接地判定フラグ
	bool isGround = false;
	//生存フラグ
	bool aliveFlag = true;
	//リスポーンフラグ
	bool respawnFlag = true;

	// モデルハンドルの取得.
	int GetModelHandle() { return model; }

	// ポジションのgetter/setter.
	const VECTOR& GetPos() const { return pos; }
	const VECTOR& GetSize() const { return size; }
	void SetPos(const VECTOR set) { pos = set; }
	const float GetRote() const { return rote; }


private:
	int	   model;	// モデルハンドル.
	VECTOR pos;			// ポジション.
	float rote;

	//実際に作用する速度
	VECTOR vel;
	//サイズ
	VECTOR size;
	//向き
	VECTOR dir;
	//速度
	float speed;

	//
	VECTOR tilt;

	//カウント関連
	//リスポーンカウント
	int respawnCount;
	int frameCount;
	int tiltCount;
	//エフェクト読み込み時のハンドル
	int effectResourceHandle;
	//再生中のエフェクトのハンドル
	int playingEffectHandle = -1;
	//エフェクトの再生時間を取るための時間
	int time;
	//エフェクトのポジション
	VECTOR effectPos;



};
#endif

