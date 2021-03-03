#include "Shot.h"
#include "Player.h"
#include "Input.h"
#include "Wall.h"
#include <math.h>
#include "Quaternion.h"
#include "EffekseerForDXLib.h"
#include "DxLib.h"




Shot::Shot()
{
}


Shot::~Shot()
{
	// モデルのアンロード.
	MV1DeleteModel(model);
}


//初期化
void Shot::Init()
{
	// ３Ｄモデルの読み込み
	model = MV1LoadModel("data/model/shot.x");
	//エフェクトの読み込み
	effectResourceHandle = LoadEffekseerEffect("data/effect/preShot.efk");

	pos = VGet(0.0f, 5.0f, 0.0f);
	vel = VGet(0.0f, 0.0f, 0.0f);
	speed = 8.0f;
	size = VGet(20.0f, 20.0f, 20.0f);
	dir = VGet(0.0f, 0.0f, -1.0f);
	rote = VGet(0.0f, 0.0f, 0.0f);
	upDir = VGet(0.0f, 1.0f, 0.0f);
	//軸
	axis = VGet(0.0f, 0.0f, 0.0f);
	radian = 1;
	//カウント関連
	attackCount = 0;
	frameCount = 0;

	//フラグ
	attackflag = false;
	moveFlag = true;
	//攻撃待機フラグ
	reAttackFlag = false;
	firstShotFlag = true;

	// 再生中のエフェクトのハンドルを初期化する。
	playingEffectHandle = -1;
	//エフェクトポジションの初期化
	effectPos = VGet(0.0f, 0.0f, 0.0f);
}

//更新
void Shot::Update(Player &player,Wall* wall[])
{
	radian += 0.2f;

	if (attackflag == true)
	{
		if (moveFlag == true)
		{

			dir = player.dir;
			dir = VNorm(dir);
			vel = VScale(dir, speed);

			moveFlag = false;
		}
		axis = VCross(upDir, dir);

		QUATERNION quaternion;
		quaternion = CreateRotationQuaternion(radian, axis);

		mat = QuaternionToMatrix(quaternion);
		MATRIX matTrans;
		matTrans = MGetTranslate(pos);
		mat = MMult(mat, matTrans);       //移動×回転×スケール
	}

	//壁に当たったら消す
	if (pos.x >= wall[2]->GetPos().x)//右
	{
		attackflag = false;
	}
	if (pos.x <= wall[3]->GetPos().x)//左
	{
		attackflag = false;
	}
	if (pos.z >= wall[0]->GetPos().z)//奥
	{
		attackflag = false;
	}
	if (pos.z <= wall[1]->GetPos().z)//手前
	{
		attackflag = false;
	}

	pos.x += vel.x;
	pos.z += vel.z;

	++radian;
	// 時間を経過させる。
	++frameCount;
	++time;

}
//描画
void Shot::Draw()
{
	// Ｚバッファを有効にする
	SetUseZBuffer3D(TRUE);

	// Ｚバッファへの書き込みを有効にする
	SetWriteZBuffer3D(TRUE);

	if (attackflag == true)
	{
		//ショットの位置の設定と行列セット
		MV1SetMatrix(model, mat);
		//ショットの描画
		MV1DrawModel(model);
	}

}

//更新
void Shot::UpdateTitle(Player &player)
{
	radian += 0.2f;

	if (attackflag == true)
	{
		if (moveFlag == true)
		{
				dir = player.dir;
				dir = VNorm(dir);
				vel = VScale(dir, speed);
			
			moveFlag = false;
		}

		axis = VCross(upDir, dir);

		QUATERNION quaternion;
		quaternion = CreateRotationQuaternion(radian, axis);

		mat = QuaternionToMatrix(quaternion);
		MATRIX matTrans;
		matTrans = MGetTranslate(pos);
		mat = MMult(mat, matTrans);       //移動×回転×スケール

	}

	//壁に当たったら消す
	if (pos.x >= 500.0f)//右
	{
		attackflag = false;
	}
	if (pos.x <= -500.0f)//左
	{
		attackflag = false;
	}
	if (pos.z >= 500.0f)//奥
	{
		attackflag = false;
	}
	if (pos.z <= -500.0f)//手前
	{
		attackflag = false;
	}

	pos.x += vel.x;
	pos.z += vel.z;

	// 時間を経過させる。
	time++;

}


