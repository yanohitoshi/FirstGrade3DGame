#ifndef _ENEMY_H_
#define _ENEMY_H_
#include "EffekseerForDXLib.h"

class Stage;
class Shot;
class Player;
class Wall;
class Camera;
class TitleStage;

enum state
{
	HOMING = 0
	,REFLECTION = 1
	,SLOW = 2
};


class Enemy
{
public:
	Enemy();
	~Enemy();


	//初期化
	void Init(int modelhandle1, int modelhandle2, int modelhandle3,int modelhandle4);
	//更新
	void Update(Stage &stage, Player &player, Shot* shot[], Wall* wall[],Camera* camera);
	void UpdateTitle(TitleStage &stage, Player &player, Shot* shot[], Camera* camera);
	void UpdateClear(Stage &stage, Player &player, Shot* shot[], Wall* wall[], Camera* camera);

	//描画
	void Draw();
	//押し戻し
	void Back(Stage &stage);
	//エネミーの種類
	int enemyType = 0;

	//タイトル用ゲームスタートカウント
	int startCount;
	//------フラグ関連------//
	//ジャンプフラグ
	bool jumpFlag = true;
	//重力フラグ
	bool gravityFlag = true;
	//接地判定フラグ
	bool isGround = false;
	//生存フラグ
	bool aliveFlag = true;
	//リスポーンフラグ
	bool respawnFlag = false;
	//エンドフラグ
	bool clearFlag = false;
	//方向セットフラグ
	bool dirSetFlag = true;
	//エネミータイプ１用のフラグ
	bool type1Flag = true;
	//ゲームクリア時のエフェクト発生用フラグ
	bool endEffectFlag = true;
	//ゲーム開始時または時間で起動するためのフラグ
	bool startUpFlag = false;

	// モデルハンドルの取得.
	int GetModelHandle() { return model; }

	//getter
	const VECTOR& GetPos() const { return pos;}
	const VECTOR& GetSize() const { return size;}
	const float GetRote() const { return rote;}
	//setter
	void SetPos(const VECTOR set) { pos = set;}
	void SetVel(const VECTOR set) { vel = set; }


private:

	// モデルハンドル
	int model;
	int model1;
	int model2;
	int model3;
	//影のモデルハンドル
	int shadowModel;
	// ポジション
	VECTOR pos;			
	//影用のポジション
	VECTOR shadowPos;
	//実際に作用する速度
	VECTOR vel;
	//サイズ
	VECTOR size;
	//向き
	VECTOR dir;
	//プレイヤーに向かうベクトル
	VECTOR enemyToPlayer;
	//スピード
	float speed;
	//敵の数
	const int enemyNum = 10;
	//傾き度
	float tilt;
	//回転値
	float rote;

	//-----カウント関連------//
	//リスポーンカウント
	int respawnCount;
	//フレームカウント
	int frameCount;
	//傾き用
	int tiltCount;
	//エネミータイプ１用カウント
	int type1Count;

	//--------エフェクト関連---------//
	//エフェクトのポジション
	VECTOR effectPos;
	//エフェクト読み込み時のハンドル
	int effectResourceHandle;
	//再生中のエフェクトのハンドル
	int playingEffectHandle;
	//エフェクトの再生時間を取るための時間
	int time;

	//効果音関連
	int hitSE;
	int titleButHitSE;
	int titleHitSE;


};
#endif


