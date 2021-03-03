#ifndef _PLAYER_H_
#define _PLAYER_H_
#include "EffekseerForDXLib.h"

class Stage;
class Shot;
class Wall;
class Camera;
class TitleStage;

class Player
{
public:

	Player();
	~Player();

	//初期化
	void Init();
	//更新
	void Update(Stage& stage,Shot* shot[],Wall* wall[]);
	//タイトル用
	void UpdateTitle(TitleStage &stage, Shot* shot[]);
	//エンド用
	void UpdateEnd();
	//クリア用
	void UpdateClear(Stage &stage);

	//描画
	void Draw();
	void DrawEnd();
	void DrawTitle();
	//押し戻し
	void Back(Stage& stage);
	void BackTitle(TitleStage& stage);

	//------フラグ関連------//
	//ジャンプフラグ
	bool jumpFlag = true;
	//重力フラグ
	bool gravityFlag = true;
	//接地判定フラグ
	bool isGround = false;
	//生存フラグ
	bool aliveFlag = true;
	//壁判定フラグ
	bool hitWallFlag = false;
	//タイトル用ダメージフラグ
	bool tileDamageFlag = false;
	int damageCount;

	//向き
	VECTOR dir;
	//カウント関連
	int frameCount;
	int tiltCount;
	int hitCount;
	// モデルハンドルの取得.
	int GetModelHandle() { return model; }
	int GetplayingEffectHandle() { return playingEffectHandle; }

	//ゲッターとセッター
	void SetPos(const VECTOR set) { pos = set; }
	const float GetRote() const { return rote; }
	const VECTOR& GetPos() const { return pos; }
	const VECTOR& GetSize() const { return size; }

private:
	// モデルハンドル
	int model;
	int model2;
	int model3;
	// ポジション.
	VECTOR pos;
	//モデルの回転値
	float rote;
	float rote2;
	//傾き度
	float tilt;
	//実際に作用する速度
	VECTOR vel;
	//スピード
	float speed;
	//サイズ
	VECTOR size;
	//重力
	float gravity;
	//エフェクト読み込み時のハンドル
	int effectResourceHandle;
	//再生中のエフェクトのハンドル
	int playingEffectHandle = -1;
	//エフェクトの再生時間を取るための時間
	int time;
	//エフェクトのポジション
	VECTOR effectPos;

	float tmpRote;

	//SE関連
	int shotSeHandle;

};
#endif
