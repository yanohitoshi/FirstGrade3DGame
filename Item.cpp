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
	// ���f���̃A�����[�h.
	MV1DeleteModel(model);
	// �G�t�F�N�g���\�[�X���폜����B(Effekseer�I�����ɔj�������̂ō폜���Ȃ��Ă�����)
	DeleteEffekseerEffect(effectResourceHandle);
}

//������
void Item::Init()
{
	// �R�c���f���̓ǂݍ���
	model = MV1LoadModel("data/model/itemBox/itembox.pmx");
	//�G�t�F�N�g�̓ǂݍ���
	effectResourceHandle = LoadEffekseerEffect("data/effect/tktk1/Wind1.efk");

	pos = VGet(0.0f, 0.0f, 0.0f);
	vel = VGet(0.0f, 0.0f, 0.0f);
	size = VGet(15.0f, 15.0f, 15.0f);
	dir = VGet(0.0f, 0.0f, 0.0f);
	speed = 1.0f;

	tilt = VGet(0.0f, 0.0f, 0.0f);

	//�J�E���g�֘A
	time = 0;
	respawnCount = 0;
	frameCount = 0;
	tiltCount = 0;

	//�G�t�F�N�g�֘A
	playingEffectHandle = -1;
	time = 0;
	effectPos = VGet(0.0f, 0.0f, 0.0f);

}
//�X�V
void Item::Update(Stage &stage, Player &player)
{

	//�d��
	if (gravityFlag == true)
	{
		vel.y -= GRAVITY_ACCEL;
	}

	//�X�e�[�W�Ƃ̓����蔻��
	if (IsHit(pos.x, pos.y, pos.z, stage.GetPos().x, stage.GetPos().y, stage.GetPos().z, size.x, size.y, size.z, stage.GetSize().x, stage.GetSize().y, stage.GetSize().z) == true)
	{
		gravityFlag = false;
		vel.y = 0.0f;
	}
	//�v���C���[�Ƃ̓����蔻��
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

	//�A�C�e���̃��X�|�[��
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

	//�ʒu���̍X�V
	//
	pos.x += vel.x;
	pos.y += vel.y;
	pos.z += vel.z;

	//�A�C�e���̈ʒu�̐ݒ�
	MV1SetPosition(model, pos);

	//�A�C�e���̉�]
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
//�`��
void Item::Draw()
{
	// �y�o�b�t�@��L���ɂ���
	SetUseZBuffer3D(TRUE);

	// �y�o�b�t�@�ւ̏������݂�L���ɂ���
	SetWriteZBuffer3D(TRUE);

	 // �R�c���f���̃X�P�[����x�������ɂQ�{�ɂ���
	MV1SetScale(model, VGet(2.5f, 2.5f, 2.5f));

	// �R�c���f����Y���̉�]�l���O�x�ɃZ�b�g����
	MV1SetRotationXYZ(model, VGet(0.0f, tilt.y * DX_PI_F / 180.0f, 0.0f));

	if (aliveFlag == true)
	{
		//�G�l�~�[�̕`��
		MV1DrawModel(model);
	}

}
//�����߂�
void Item::Back(Stage &stage)
{
	PushBackStage(pos.x, pos.y, pos.z, stage.GetPos().x, stage.GetPos().y, stage.GetPos().z, size.x, size.y, size.z, stage.GetSize().x, stage.GetSize().y, stage.GetSize().z, vel.x, vel.y, vel.z);
	//�ڒn���Ă��邩�̃`�F�b�N
	//�t���O�̃��Z�b�g
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