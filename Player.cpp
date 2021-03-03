#include <math.h>
#include "Player.h"
#include "Stage.h"
#include "TitleStage.h"
#include "Shot.h"
#include "Wall.h"
#include "System.h"
#include "Input.h"
#include "Camera.h"
#include "EffekseerForDXLib.h"



Player::Player()
{
}


Player::~Player()
{
	// モデルのアンロード.
	MV1DeleteModel(model);
	// エフェクトリソースを削除する。(Effekseer終了時に破棄されるので削除しなくてもいい)
	DeleteEffekseerEffect(effectResourceHandle);
}


//初期化
void Player::Init()
{
	// ３Ｄモデルの読み込み
	model = MV1LoadModel("data/model/snowman/snowman.pmx");
	model2 = MV1LoadModel("data/model/star.x");
	model3 = MV1LoadModel("data/model/batu.x");
	//エフェクトの読み込み
	effectResourceHandle = LoadEffekseerEffect("data/effect/AndrewFM01/smoke.efk");
	//-----初期化-----//
	//ポジション
	pos = VGet(0.0f, 25.0f, 0.0f);
	//速度
	vel = VGet(0.0f, 0.0f, 0.0f);
	//スピード
	speed = 5.0f;
	//サイズ
	size = VGet(13.0f, 15.0f, 13.0f);
	//回転値
	rote = 0.0f;
	rote2 = 0.0f;
	//向き
	dir = VGet(0.0f, 0.0f, -1.0f);
	//傾き
	tilt = 0.0f;
	tmpRote = 0.0f;
	//カウント関連の初期化
	frameCount = 0;
	tiltCount = 0;
	hitCount = 0;
	damageCount = 0;

	//エフェクト関連
	playingEffectHandle = -1;
	effectPos = VGet(0.0f, 0.0f, 0.0f);

	shotSeHandle = LoadSoundMem("data/SE/knife-throw1.mp3");

}
//更新
void Player::Update(Stage &stage,Shot* shot[], Wall* wall[])
{

	VECTOR padVec = VGet(INPUT_INSTANCE.padState.ThumbLX, INPUT_INSTANCE.padState.ThumbLY, 0);
	if (!(padVec.x == 0 && padVec.y == 0))
	{
		padVec = VNorm(padVec);	// 正規化したパッド入力ベクトル.XもYもゼロだとエラーになるので正規化しない
	}

	//移動処理

	if (fabs(INPUT_INSTANCE.padState.ThumbLX) > 200 || fabs(INPUT_INSTANCE.padState.ThumbLY) > 200)
	{
		dir = VGet(INPUT_INSTANCE.padState.ThumbLX, 0.0, -INPUT_INSTANCE.padState.ThumbLY);
		if (frameCount % 10 == 0)
		{
			// エフェクトを再生する。
			playingEffectHandle = PlayEffekseer3DEffect(effectResourceHandle);

			if (playingEffectHandle >= 0)
			{
				//エフェクト発生ポジション
				effectPos.x = pos.x;
				effectPos.y = pos.y;
				effectPos.z = pos.z;

				// 再生中のエフェクトを移動する。
				SetPosPlayingEffekseer3DEffect(playingEffectHandle, effectPos.x, effectPos.y, effectPos.z);
			}

		}


	}

	dir = VNorm(dir);
	vel = VScale(dir, speed);
	float radianRot = atan2f(dir.z, -dir.x); //  dirからラジアンの回転角度をとる 
	rote = radianRot * 180.0f / DX_PI_F + 90.0f; // rote = 0-360 degree

	if (INPUT_INSTANCE.padState.ThumbLX == 0.0f && INPUT_INSTANCE.padState.ThumbLY == 0.0f)
	{
		speed = 0.0f;
		rote = tmpRote;
	}
	else
	{
		speed = 3.0f;
	}
	tmpRote = rote;
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


	//壁の押し戻し
	if (pos.x + (size.x / 2.0f) >= wall[2]->GetPos().x)//右
	{
		vel.x = 0;
		pos.x = wall[2]->GetPos().x - (size.x / 2.0f) - 5.0f;
	}
	if (pos.x - (size.x / 2.0f) <= wall[3]->GetPos().x)//左
	{
		vel.x = 0;
		pos.x = wall[3]->GetPos().x + (size.x / 2.0f) + 5.0f;

	}
	if (pos.z + (size.z / 2.0f) >= wall[0]->GetPos().z)//奥
	{
		vel.z = 0;
		pos.z = wall[0]->GetPos().z - (size.z / 2.0f) - 5.0f;
	}
	if (pos.z - (size.z / 2.0f) <= wall[1]->GetPos().z)//手前
	{
		vel.z = 0;
		pos.z = wall[1]->GetPos().z + (size.z / 2.0f) + 5.0f;
	}

	//プレイヤーの傾き
	if (frameCount % 10 == 0)
	{
		if (tiltCount == 2)
		{
			tilt = 30.0;
		}
		else if (tiltCount == 4)
		{
			tilt = 330.0;
		}
		else
		{
			tilt = 0.0;
		}

		if (tiltCount > 5)
		{
			tiltCount = 0;
		}

		tiltCount++;
	}

	// sを押した場合は処理を分岐
	if (INPUT_INSTANCE.GetKeyDown(KEY_INPUT_SPACE) || INPUT_INSTANCE.padState.Buttons[XINPUT_BUTTON_B] == 1 && INPUT_INSTANCE.prePadState.Buttons[XINPUT_BUTTON_B] == 0)
	{

		if (shot[0]->attackflag == false)
		{
			PlaySoundMem(shotSeHandle, DX_PLAYTYPE_BACK);
			// 弾１が画面に存在していない場合は弾１を出す
			// 弾１の位置をセット
			shot[0]->pos = VGet(pos.x, pos.y + 15.0f, pos.z);
			shot[0]->SetDir(dir);
			// 弾１は現時点を持って存在するので、存在状態を保持する変数に１を代入する
			shot[0]->attackflag = true;
			shot[0]->moveFlag = true;

		}
		else if (shot[1]->attackflag == 0)
		{
			PlaySoundMem(shotSeHandle, DX_PLAYTYPE_BACK);
			// 弾２が画面に存在していない場合は弾２を出す
			// 弾2の位置をセット
			shot[1]->pos = VGet(pos.x, pos.y + 15.0f, pos.z);
			shot[1]->SetDir(dir);
			// 弾２は現時点を持って存在するので、存在状態を保持する変数に１を代入する
			shot[1]->attackflag = true;
			shot[1]->moveFlag = true;

		}
		else if (shot[2]->attackflag == 0)
		{
			PlaySoundMem(shotSeHandle, DX_PLAYTYPE_BACK);
			// 弾3が画面に存在していない場合は弾２を出す
			// 弾3の位置をセット
			shot[2]->pos = VGet(pos.x, pos.y + 15.0f, pos.z);
			shot[2]->SetDir(dir);
			// 弾3は現時点を持って存在するので、存在状態を保持する変数に１を代入する
			shot[2]->attackflag = true;
			shot[2]->moveFlag = true;
		}
		else if (shot[3]->attackflag == 0)
		{
			PlaySoundMem(shotSeHandle, DX_PLAYTYPE_BACK);
			// 弾3が画面に存在していない場合は弾２を出す
			// 弾3の位置をセット
			shot[3]->pos = VGet(pos.x, pos.y + 15.0f, pos.z);
			shot[3]->SetDir(dir);
			// 弾3は現時点を持って存在するので、存在状態を保持する変数に１を代入する
			shot[3]->attackflag = true;
			shot[3]->moveFlag = true;
		}
		else if (shot[4]->attackflag == 0)
		{
			PlaySoundMem(shotSeHandle, DX_PLAYTYPE_BACK);
			// 弾3が画面に存在していない場合は弾２を出す
			// 弾3の位置をセット
			shot[4]->pos = VGet(pos.x, pos.y + 15.0f, pos.z);
			shot[4]->SetDir(dir);
			// 弾3は現時点を持って存在するので、存在状態を保持する変数に１を代入する
			shot[4]->attackflag = true;
			shot[4]->moveFlag = true;
		}
		else if (shot[5]->attackflag == 0)
		{
			PlaySoundMem(shotSeHandle, DX_PLAYTYPE_BACK);
			// 弾3が画面に存在していない場合は弾２を出す
			// 弾3の位置をセット
			shot[5]->pos = VGet(pos.x, pos.y + 15.0f, pos.z);
			shot[5]->SetDir(dir);
			// 弾3は現時点を持って存在するので、存在状態を保持する変数に１を代入する
			shot[5]->attackflag = true;
			shot[5]->moveFlag = true;
		}
	}

	//位置情報の更新
	pos.x += vel.x;
	pos.y += vel.y;
	pos.z += vel.z;


	//プレイヤーの位置の設定
	MV1SetPosition(model, pos);
	// 時間を経過させる。
	time++;
	frameCount++;
}

void Player::Draw()
{
	// Ｚバッファを有効にする
	SetUseZBuffer3D(TRUE);

	// Ｚバッファへの書き込みを有効にする
	SetWriteZBuffer3D(TRUE);


	// ３Ｄモデルの傾き
	MV1SetRotationXYZ(model, VGet(0.0f, rote* DX_PI_F / 180.0f, tilt * DX_PI_F / 180.0f));

	//プレイヤーの描画
	MV1DrawModel(model);
}
//押し戻し
void Player::Back(Stage& stage)
{
	pos = PushBackStage(pos.x, pos.y, pos.z, stage.GetPos().x, stage.GetPos().y, stage.GetPos().z, size.x, size.y, size.z, stage.GetSize().x, stage.GetSize().y, stage.GetSize().z, vel.x, vel.y, vel.z);
	//接地しているかのチェック
	//フラグのリセット
	isGround = false;
	if (IsHitGround(pos.x, pos.y, pos.z, stage.GetPos().x, stage.GetPos().y, stage.GetPos().z, size.x, size.y, size.z, stage.GetSize().x, stage.GetSize().y, stage.GetSize().z) == true)
	{
		isGround = true;
		gravityFlag = false;
		jumpFlag = true;
	}
	else
	{
		gravityFlag = true;
	}
}
//押し戻し
void Player::BackTitle(TitleStage& stage)
{
	pos = PushBackStage(pos.x, pos.y, pos.z, stage.GetPos().x, stage.GetPos().y, stage.GetPos().z, size.x, size.y, size.z, stage.GetSize().x, stage.GetSize().y, stage.GetSize().z, vel.x, vel.y, vel.z);
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


//更新
void Player::UpdateTitle(TitleStage &stage, Shot* shot[])
{
	
	VECTOR padVec = VGet(INPUT_INSTANCE.padState.ThumbLX, INPUT_INSTANCE.padState.ThumbLY, 0);
	if (!(padVec.x == 0 && padVec.y == 0))
	{
		padVec = VNorm(padVec);	// 正規化したパッド入力ベクトル.XもYもゼロだとエラーになるので正規化しない
	}

	//移動処理

	if (fabs(INPUT_INSTANCE.padState.ThumbLX) > 200 || fabs(INPUT_INSTANCE.padState.ThumbLY) > 200)
	{
		dir = VGet(INPUT_INSTANCE.padState.ThumbLX, 0.0, -INPUT_INSTANCE.padState.ThumbLY);
		if (frameCount % 10 == 0)
		{
			// エフェクトを再生する。
			playingEffectHandle = PlayEffekseer3DEffect(effectResourceHandle);

			if (playingEffectHandle >= 0)
			{
				//エフェクト発生ポジション
				effectPos.x = pos.x;
				effectPos.y = pos.y;
				effectPos.z = pos.z;

				// 再生中のエフェクトを移動する。
				SetPosPlayingEffekseer3DEffect(playingEffectHandle, effectPos.x, effectPos.y, effectPos.z);
			}

		}
		

	}
	
	dir = VNorm(dir);
	vel = VScale(dir, speed);
	float radianRot = atan2f(dir.z, -dir.x); //  dirからラジアンの回転角度をとる 
	rote = radianRot * 180.0f / DX_PI_F + 90.0f; // rote = 0-360 degree

	if (INPUT_INSTANCE.padState.ThumbLX == 0.0f && INPUT_INSTANCE.padState.ThumbLY == 0.0f)
	{
		speed = 0.0f;
		rote = tmpRote;
	}
	else
	{
		speed = 3.0f;
	}
	tmpRote = rote;


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

	//壁の押し戻し
	if (pos.x + (size.x / 2.0f) >= 250.0f)//右
	{
		vel.x = 0;
		pos.x = 250.0f - (size.x / 2.0f) - 5.0f;
	}
	if (pos.x - (size.x / 2.0f) <= -250.0f)//左
	{
		vel.x = 0;
		pos.x = -250.0f + (size.x / 2.0f) + 5.0f;

	}
	if (pos.z + (size.z / 2.0f) >= 0.0f)//奥
	{
		vel.z = 0;
		pos.z = 0.0f - (size.z / 2.0f) - 5.0f;
	}
	if (pos.z - (size.z / 2.0f) <= -350.0f)//手前
	{
		vel.z = 0;
		pos.z = -350.0f + (size.z / 2.0f) + 5.0f;
	}


	// sを押した場合は処理を分岐
	if (INPUT_INSTANCE.GetKeyDown(KEY_INPUT_SPACE) || INPUT_INSTANCE.padState.Buttons[XINPUT_BUTTON_B] == 1 && INPUT_INSTANCE.prePadState.Buttons[XINPUT_BUTTON_B] == 0)
	{

		if (shot[0]->attackflag == false)
		{
			PlaySoundMem(shotSeHandle, DX_PLAYTYPE_BACK);

			// 弾１が画面に存在していない場合は弾１を出す
			// 弾１の位置をセット
			shot[0]->pos = VGet(pos.x, pos.y + 15.0f, pos.z);
			shot[0]->SetDir(dir);
			// 弾１は現時点を持って存在するので、存在状態を保持する変数に１を代入する
			shot[0]->attackflag = true;
			shot[0]->moveFlag = true;

		}
		else if (shot[1]->attackflag == 0)
		{
			PlaySoundMem(shotSeHandle, DX_PLAYTYPE_BACK);

			// 弾２が画面に存在していない場合は弾２を出す
			// 弾2の位置をセット
			shot[1]->pos = VGet(pos.x, pos.y + 15.0f, pos.z);
			shot[1]->SetDir(dir);
			// 弾２は現時点を持って存在するので、存在状態を保持する変数に１を代入する
			shot[1]->attackflag = true;
			shot[1]->moveFlag = true;

		}
		else if (shot[2]->attackflag == 0)
		{
			PlaySoundMem(shotSeHandle, DX_PLAYTYPE_BACK);

			// 弾3が画面に存在していない場合は弾２を出す
			// 弾3の位置をセット
			shot[2]->pos = VGet(pos.x, pos.y + 15.0f, pos.z);
			shot[2]->SetDir(dir);
			// 弾3は現時点を持って存在するので、存在状態を保持する変数に１を代入する
			shot[2]->attackflag = true;
			shot[2]->moveFlag = true;
		}
		else if (shot[3]->attackflag == 0)
		{
			PlaySoundMem(shotSeHandle, DX_PLAYTYPE_BACK);

			// 弾3が画面に存在していない場合は弾２を出す
			// 弾3の位置をセット
			shot[3]->pos = VGet(pos.x, pos.y + 15.0f, pos.z);
			shot[3]->SetDir(dir);
			// 弾3は現時点を持って存在するので、存在状態を保持する変数に１を代入する
			shot[3]->attackflag = true;
			shot[3]->moveFlag = true;
		}
		else if (shot[4]->attackflag == 0)
		{
			PlaySoundMem(shotSeHandle, DX_PLAYTYPE_BACK);

			// 弾3が画面に存在していない場合は弾２を出す
			// 弾3の位置をセット
			shot[4]->pos = VGet(pos.x, pos.y + 15.0f, pos.z);
			shot[4]->SetDir(dir);
			// 弾3は現時点を持って存在するので、存在状態を保持する変数に１を代入する
			shot[4]->attackflag = true;
			shot[4]->moveFlag = true;
		}
		else if (shot[5]->attackflag == 0)
		{
			PlaySoundMem(shotSeHandle, DX_PLAYTYPE_BACK);

			// 弾3が画面に存在していない場合は弾２を出す
			// 弾3の位置をセット
			shot[5]->pos = VGet(pos.x, pos.y + 15.0f, pos.z);
			shot[5]->SetDir(dir);
			// 弾3は現時点を持って存在するので、存在状態を保持する変数に１を代入する
			shot[5]->attackflag = true;
			shot[5]->moveFlag = true;
		}
	}
	if (tileDamageFlag == true)
	{
		++damageCount;
		if (damageCount > 60)
		{
			tileDamageFlag = false;
			damageCount = 0;
		}
	}

	//位置情報の更新
	pos.x += vel.x;
	pos.y += vel.y;
	pos.z += vel.z;


	//プレイヤーの位置の設定
	MV1SetPosition(model, pos);
	MV1SetPosition(model3, VGet(pos.x - 10.0f,pos.y + 30.0f,pos.z));
	++frameCount;
}

void Player::UpdateEnd()
{
	tilt = 0.0f;
	rote += 10.0f;
	rote2 -= 12.0f;
	//プレイヤーの位置の設定
	MV1SetPosition(model2, VGet(pos.x,pos.y + 15.0f,pos.z));

}

void Player::UpdateClear(Stage &stage)
{
	//重力
	vel.y -= GRAVITY_ACCEL;
	

	if (jumpFlag == true)
	{
		vel.y = 5.0f;
	}

	//ステージとの当たり判定
	if (IsHit(pos.x, pos.y, pos.z, stage.GetPos().x, stage.GetPos().y, stage.GetPos().z, size.x, size.y, size.z, stage.GetSize().x, stage.GetSize().y, stage.GetSize().z) == true)
	{
		gravityFlag = false;
		jumpFlag = true;
	}
	else
	{
		jumpFlag = false;
	}

	tilt = 0.0f;
	rote = 0.0f;

	pos.y += vel.y;
	//プレイヤーの位置の設定
	MV1SetPosition(model, pos);

}

void Player::DrawTitle()
{
	// Ｚバッファを有効にする
	SetUseZBuffer3D(TRUE);

	// Ｚバッファへの書き込みを有効にする
	SetWriteZBuffer3D(TRUE);


	// ３Ｄモデルの傾き
	MV1SetRotationXYZ(model, VGet(0.0f, rote* DX_PI_F / 180.0f, tilt * DX_PI_F / 180.0f));

	//プレイヤーの描画
	MV1DrawModel(model);
	if (tileDamageFlag == true)
	{
		MV1DrawModel(model3);
	}
}


void Player::DrawEnd()
{
	// Ｚバッファを有効にする
	SetUseZBuffer3D(TRUE);

	// Ｚバッファへの書き込みを有効にする
	SetWriteZBuffer3D(TRUE);


	// ３Ｄモデルの傾き
	MV1SetRotationXYZ(model, VGet(0.0f, rote* DX_PI_F / 180.0f, tilt * DX_PI_F / 180.0f));
	MV1SetRotationXYZ(model2, VGet(0.0f, rote2* DX_PI_F / 180.0f, 0.0f));

	//プレイヤーの描画
	MV1DrawModel(model);
	MV1DrawModel(model2);
}


