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

//������
void Camera::Init()
{
	pos = VGet(0.0f, 0.0f, 0.0f);
	cameraToPlayer = VGet(0.0f, 0.0f, 0.0f);
	dir = VGet(0.0f, 0.0f, 0.0f);
	vel = VGet(0.0f, 0.0f, 0.0f);
	speed = 3.0f;
}
//�X�V
void Camera::Update(const Player& player)	// �X�V.
{
	if (TIME_INSTANCE.countDown == 0)
	{
		clearFlag = true;
	}

	if (player.aliveFlag == false || clearFlag == true)
	{
		//�G�l�~�[����v���C���[�ւ̃x�N�g�����Ƃ�
		cameraToPlayer = VSub(player.GetPos(), pos);

		//�x�N�g���̐��K��
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
	// DX���C�u�����̃J������Effekseer�̃J�����𓯊�����B
	Effekseer_Sync3DSetting();
}

//�X�V
void Camera::UpdateTitle(const Player& player)	// �X�V.
{
	pos.x = player.GetPos().x;
	pos.y = player.GetPos().y + 150.0f;
	pos.z = player.GetPos().z - 300.0f;


	SetCameraPositionAndTargetAndUpVec(pos, player.GetPos(), VGet(0.0f, 1.0f, 0.0f));
	// DX���C�u�����̃J������Effekseer�̃J�����𓯊�����B
	Effekseer_Sync3DSetting();
}