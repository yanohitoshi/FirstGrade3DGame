#include "Camera.h"
#include "Player.h"
#include "Time.h"
#include "EffekseerForDXLib.h"



Camera::Camera()
{
}


Camera::~Camera()
{
}

//初期化
void Camera::Init()
{
	pos = VGet(0.0f, 0.0f, 0.0f);
	cameraToPlayer = VGet(0.0f, 0.0f, 0.0f);
	dir = VGet(0.0f, 0.0f, 0.0f);
	vel = VGet(0.0f, 0.0f, 0.0f);
	speed = 3.0f;
}
//更新
void Camera::Update(const Player& player)	// 更新.
{
	if (TIME_INSTANCE.countDown == 0)
	{
		clearFlag = true;
	}

	if (player.aliveFlag == false || clearFlag == true)
	{
		//エネミーからプレイヤーへのベクトルをとる
		cameraToPlayer = VSub(player.GetPos(), pos);

		//ベクトルの正規化
		dir = VNorm(cameraToPlayer);
		vel = VScale(dir, speed);

	}
	else
	{
		pos.x = player.GetPos().x;
		pos.y = player.GetPos().y + 200.0f;
		pos.z = player.GetPos().z - 300.0f;
	}

	if (pos.z >= player.GetPos().z - 120)
	{
		vel.x = 0.0f;
		//vel.y = 0.0f;
		vel.z = 0.0f;
	}
	if (pos.z >= player.GetPos().z - 140)
	{
		vel.y = 0.0f;
	}
	pos.x += vel.x;
	pos.y += vel.y;
	pos.z += vel.z;

	SetCameraPositionAndTargetAndUpVec(pos, player.GetPos(), VGet(0.0f, 1.0f, 0.0f));
	// DXライブラリのカメラとEffekseerのカメラを同期する。
	Effekseer_Sync3DSetting();
}

//更新
void Camera::UpdateTitle(const Player& player)	// 更新.
{
	pos.x = player.GetPos().x;
	pos.y = player.GetPos().y + 150.0f;
	pos.z = player.GetPos().z - 300.0f;


	SetCameraPositionAndTargetAndUpVec(pos, player.GetPos(), VGet(0.0f, 1.0f, 0.0f));
	// DXライブラリのカメラとEffekseerのカメラを同期する。
	Effekseer_Sync3DSetting();
}