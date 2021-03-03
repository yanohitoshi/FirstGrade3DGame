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
	// ���f���̃A�����[�h.
	MV1DeleteModel(model);
}


//������
void Shot::Init()
{
	// �R�c���f���̓ǂݍ���
	model = MV1LoadModel("data/model/shot.x");
	//�G�t�F�N�g�̓ǂݍ���
	effectResourceHandle = LoadEffekseerEffect("data/effect/preShot.efk");

	pos = VGet(0.0f, 5.0f, 0.0f);
	vel = VGet(0.0f, 0.0f, 0.0f);
	speed = 8.0f;
	size = VGet(20.0f, 20.0f, 20.0f);
	dir = VGet(0.0f, 0.0f, -1.0f);
	rote = VGet(0.0f, 0.0f, 0.0f);
	upDir = VGet(0.0f, 1.0f, 0.0f);
	//��
	axis = VGet(0.0f, 0.0f, 0.0f);
	radian = 1;
	//�J�E���g�֘A
	attackCount = 0;
	frameCount = 0;

	//�t���O
	attackflag = false;
	moveFlag = true;
	//�U���ҋ@�t���O
	reAttackFlag = false;
	firstShotFlag = true;

	// �Đ����̃G�t�F�N�g�̃n���h��������������B
	playingEffectHandle = -1;
	//�G�t�F�N�g�|�W�V�����̏�����
	effectPos = VGet(0.0f, 0.0f, 0.0f);
}

//�X�V
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
		mat = MMult(mat, matTrans);       //�ړ��~��]�~�X�P�[��
	}

	//�ǂɓ������������
	if (pos.x >= wall[2]->GetPos().x)//�E
	{
		attackflag = false;
	}
	if (pos.x <= wall[3]->GetPos().x)//��
	{
		attackflag = false;
	}
	if (pos.z >= wall[0]->GetPos().z)//��
	{
		attackflag = false;
	}
	if (pos.z <= wall[1]->GetPos().z)//��O
	{
		attackflag = false;
	}

	pos.x += vel.x;
	pos.z += vel.z;

	++radian;
	// ���Ԃ��o�߂�����B
	++frameCount;
	++time;

}
//�`��
void Shot::Draw()
{
	// �y�o�b�t�@��L���ɂ���
	SetUseZBuffer3D(TRUE);

	// �y�o�b�t�@�ւ̏������݂�L���ɂ���
	SetWriteZBuffer3D(TRUE);

	if (attackflag == true)
	{
		//�V���b�g�̈ʒu�̐ݒ�ƍs��Z�b�g
		MV1SetMatrix(model, mat);
		//�V���b�g�̕`��
		MV1DrawModel(model);
	}

}

//�X�V
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
		mat = MMult(mat, matTrans);       //�ړ��~��]�~�X�P�[��

	}

	//�ǂɓ������������
	if (pos.x >= 500.0f)//�E
	{
		attackflag = false;
	}
	if (pos.x <= -500.0f)//��
	{
		attackflag = false;
	}
	if (pos.z >= 500.0f)//��
	{
		attackflag = false;
	}
	if (pos.z <= -500.0f)//��O
	{
		attackflag = false;
	}

	pos.x += vel.x;
	pos.z += vel.z;

	// ���Ԃ��o�߂�����B
	time++;

}


