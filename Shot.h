#ifndef _SHOT_H_
#define _SHOT_H_
#include "EffekseerForDXLib.h"

class Player;
class Wall;

class Shot
{
public:

	Shot();
	~Shot();

	//初期化
	void Init();
	//更新
	void Update(Player &player, Wall* wall[]);
	//タイトル用更新
	void UpdateTitle(Player &player);
	//描画
	void Draw();

	//実際に作用する速度
	VECTOR vel;

	//------フラグ関連------//
	//フラグ
	bool attackflag;
	bool moveFlag;
	//攻撃待機フラグ
	bool reAttackFlag;
	bool firstShotFlag;
	//カウント関連
	int attackCount;


	//エフェクトの読み込み用ハンドル
	int effectResourceHandle;

	// モデルハンドルの取得.
	int GetModelHandle() { return model; }

	// ポジションのgetter/setter.
	const VECTOR& GetPos() const { return pos; }
	void SetPos(const VECTOR set) { pos = set; }
	const VECTOR& GetSize() const { return size; }
	void SetDir(const VECTOR set) { dir = set; }
	const VECTOR& GetDir() const { return tmpDir; }

	//ポジション
	VECTOR pos;

	const int shotNum = 3;

private:

	//モデルハンドル
	int	 model;
	//サイズ
	VECTOR size;
	//向き
	VECTOR dir;
	//直角を出すためのVECTOR
	VECTOR upDir;
	//回転
	VECTOR rote;
	//スピード
	float speed;

	//フレームカウント
	int frameCount;

	//エフェクトの再生時のハンドル
	int playingEffectHandle = -1;
	//エフェクトを再生するための時間
	int time;
	//エフェクトのポジション
	VECTOR effectPos;
	//
	VECTOR tmpDir;

	//クォータニオン関連
	//軸
	VECTOR axis;
	MATRIX mat;
	double radian;
};
#endif
