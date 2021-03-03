#include "Item.h"
#include "Stage.h"
#include "Player.h"
#include "System.h"
#include "EffekseerForDXLib.h"



Item::Item()
{
}


Item::~Item()
{
	// モデルのアンロード.
	MV1DeleteModel(model);
	// エフェクトリソースを削除する。(Effekseer終了時に破棄されるので削除しなくてもいい)
	DeleteEffekseerEffect(effectResourceHandle);
}

//初期化
void Item::Init()
{
	// ３Ｄモデルの読み込み
	model = MV1LoadModel("data/model/itemBox/itembox.pmx");
	//エフェクトの読み込み
	effectResourceHandle = LoadEffekseerEffect("data/effect/tktk1/Wind1.efk");

	pos = VGet(0.0f, 0.0f, 0.0f);
	vel = VGet(0.0f, 0.0f, 0.0f);
	size = VGet(15.0f, 15.0f, 15.0f);
	dir = VGet(0.0f, 0.0f, 0.0f);
	speed = 1.0f;

	tilt = VGet(0.0f, 0.0f, 0.0f);

	//カウント関連
	time = 0;
	respawnCount = 0;
	frameCount = 0;
	tiltCount = 0;

	//エフェクト関連
	playingEffectHandle = -1;
	time = 0;
	effectPos = VGet(0.0f, 0.0f, 0.0f);

}
//更新
void Item::Update(Stage &stage, Player &player)
{

	//重力
	if (gravityFlag == true)
	{
		vel.y -= GRAVITY_ACCEL;
	}

	//ステージとの当たり判定
	if (IsHit(pos.x, pos.y, pos.z, stage.GetPos().x, stage.GetPos().y, stage.GetPos().z, size.x, size.y, size.z, stage.GetSize().x, stage.GetSize().y, stage.GetSize().z) == true)
	{
		gravityFlag = false;
		vel.y = 0.0f;
	}
	//プレイヤーとの当たり判定
	if (aliveFlag == true)
	{
		if (IsHit(pos.x, pos.y, pos.z, player.GetPos().x, player.GetPos().y, player.GetPos().z, size.x, size.y, size.z, player.GetSize().x, player.GetSize().y, player.GetSize().z) == true)
		{
			aliveFlag = false;
			respawnFlag = false;
			flagSwith();
			if (flagState == POWER_UP)
			{
				player.powerUpFlag = true;
			}
			else if (flagState == POWER_DOWN)
			{
				player.powreDownFlag = true;
			}
			else if (flagState == SPEED_UP)
			{
				player.speedUpFlag = true;
			}
			else if (flagState == SPEED_UP)
			{
				player.speedDownFlag = true;
			}
		}
	}

	//アイテムのリスポーン
	if (aliveFlag == false)
	{
		if (respawnFlag == true)
		{
			pos = (VGet(GetRandom(800, -800), 100.0f, GetRandom(750, -750)));
			aliveFlag = true;
			gravityFlag = true;
			playingEffectHandle = -1;
			player.powerUpFlag = false;
			player.powreDownFlag = false;
			player.speedUpFlag = false;
			player.speedDownFlag = false;

		}
		else
		{
			if (respawnCount == 360)
			{
				respawnFlag = true;
				respawnCount = 0;
			}
			respawnCount++;
		}
	}

	//位置情報の更新
	//
	pos.x += vel.x;
	pos.y += vel.y;
	pos.z += vel.z;

	//アイテムの位置の設定
	MV1SetPosition(model, pos);

	//アイテムの回転
	if (frameCount % 10 == 0)
	{
		tilt.x++;
		tilt.y++;
		tilt.z++;

		if (tilt.x >= 365.0f)
		{
			tilt.x = 0.0f;
		}
		if (tilt.y >= 365.0f)
		{
			tilt.y = 0.0f;
		}
		if (tilt.z >= 365.0f)
		{
			tilt.z = 0.0f;
		}
	}


}
//描画
void Item::Draw()
{
	// Ｚバッファを有効にする
	SetUseZBuffer3D(TRUE);

	// Ｚバッファへの書き込みを有効にする
	SetWriteZBuffer3D(TRUE);

	 // ３Ｄモデルのスケールをx軸方向に２倍にする
	MV1SetScale(model, VGet(2.5f, 2.5f, 2.5f));

	// ３ＤモデルのY軸の回転値を０度にセットする
	MV1SetRotationXYZ(model, VGet(0.0f, tilt.y * DX_PI_F / 180.0f, 0.0f));

	if (aliveFlag == true)
	{
		//エネミーの描画
		MV1DrawModel(model);
	}

}
//押し戻し
void Item::Back(Stage &stage)
{
	PushBackStage(pos.x, pos.y, pos.z, stage.GetPos().x, stage.GetPos().y, stage.GetPos().z, size.x, size.y, size.z, stage.GetSize().x, stage.GetSize().y, stage.GetSize().z, vel.x, vel.y, vel.z);
	//接地しているかのチェック
	//フラグのリセット
	isGround = false;
	if (IsHitGround(pos.x, pos.y, pos.z, stage.GetPos().x, stage.GetPos().y, stage.GetPos().z, size.x, size.y, size.z, stage.GetSize().x, stage.GetSize().y, stage.GetSize().z) == true)
	{
		isGround = true;
		gravityFlag = false;
	}
	else
	{
		gravityFlag = true;
	}

}

void Item::flagSwith()
{
	flagState = GetRandom(0, 3);
}