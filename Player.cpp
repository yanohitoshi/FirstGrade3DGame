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
	// ���f���̃A�����[�h.
	MV1DeleteModel(model);
	// �G�t�F�N�g���\�[�X���폜����B(Effekseer�I�����ɔj�������̂ō폜���Ȃ��Ă�����)
	DeleteEffekseerEffect(effectResourceHandle);
}


//������
void Player::Init()
{
	// �R�c���f���̓ǂݍ���
	model = MV1LoadModel("data/model/snowman/snowman.pmx");
	model2 = MV1LoadModel("data/model/star.x");
	model3 = MV1LoadModel("data/model/batu.x");
	//�G�t�F�N�g�̓ǂݍ���
	effectResourceHandle = LoadEffekseerEffect("data/effect/AndrewFM01/smoke.efk");
	//-----������-----//
	//�|�W�V����
	pos = VGet(0.0f, 25.0f, 0.0f);
	//���x
	vel = VGet(0.0f, 0.0f, 0.0f);
	//�X�s�[�h
	speed = 5.0f;
	//�T�C�Y
	size = VGet(13.0f, 15.0f, 13.0f);
	//��]�l
	rote = 0.0f;
	rote2 = 0.0f;
	//����
	dir = VGet(0.0f, 0.0f, -1.0f);
	//�X��
	tilt = 0.0f;
	tmpRote = 0.0f;
	//�J�E���g�֘A�̏�����
	frameCount = 0;
	tiltCount = 0;
	hitCount = 0;
	damageCount = 0;

	//�G�t�F�N�g�֘A
	playingEffectHandle = -1;
	effectPos = VGet(0.0f, 0.0f, 0.0f);

	shotSeHandle = LoadSoundMem("data/SE/knife-throw1.mp3");

}
//�X�V
void Player::Update(Stage &stage,Shot* shot[], Wall* wall[])
{

	VECTOR padVec = VGet(INPUT_INSTANCE.padState.ThumbLX, INPUT_INSTANCE.padState.ThumbLY, 0);
	if (!(padVec.x == 0 && padVec.y == 0))
	{
		padVec = VNorm(padVec);	// ���K�������p�b�h���̓x�N�g��.X��Y���[�����ƃG���[�ɂȂ�̂Ő��K�����Ȃ�
	}

	//�ړ�����

	if (fabs(INPUT_INSTANCE.padState.ThumbLX) > 200 || fabs(INPUT_INSTANCE.padState.ThumbLY) > 200)
	{
		dir = VGet(INPUT_INSTANCE.padState.ThumbLX, 0.0, -INPUT_INSTANCE.padState.ThumbLY);
		if (frameCount % 10 == 0)
		{
			// �G�t�F�N�g���Đ�����B
			playingEffectHandle = PlayEffekseer3DEffect(effectResourceHandle);

			if (playingEffectHandle >= 0)
			{
				//�G�t�F�N�g�����|�W�V����
				effectPos.x = pos.x;
				effectPos.y = pos.y;
				effectPos.z = pos.z;

				// �Đ����̃G�t�F�N�g���ړ�����B
				SetPosPlayingEffekseer3DEffect(playingEffectHandle, effectPos.x, effectPos.y, effectPos.z);
			}

		}


	}

	dir = VNorm(dir);
	vel = VScale(dir, speed);
	float radianRot = atan2f(dir.z, -dir.x); //  dir���烉�W�A���̉�]�p�x���Ƃ� 
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


	//�ǂ̉����߂�
	if (pos.x + (size.x / 2.0f) >= wall[2]->GetPos().x)//�E
	{
		vel.x = 0;
		pos.x = wall[2]->GetPos().x - (size.x / 2.0f) - 5.0f;
	}
	if (pos.x - (size.x / 2.0f) <= wall[3]->GetPos().x)//��
	{
		vel.x = 0;
		pos.x = wall[3]->GetPos().x + (size.x / 2.0f) + 5.0f;

	}
	if (pos.z + (size.z / 2.0f) >= wall[0]->GetPos().z)//��
	{
		vel.z = 0;
		pos.z = wall[0]->GetPos().z - (size.z / 2.0f) - 5.0f;
	}
	if (pos.z - (size.z / 2.0f) <= wall[1]->GetPos().z)//��O
	{
		vel.z = 0;
		pos.z = wall[1]->GetPos().z + (size.z / 2.0f) + 5.0f;
	}

	//�v���C���[�̌X��
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

	// s���������ꍇ�͏����𕪊�
	if (INPUT_INSTANCE.GetKeyDown(KEY_INPUT_SPACE) || INPUT_INSTANCE.padState.Buttons[XINPUT_BUTTON_B] == 1 && INPUT_INSTANCE.prePadState.Buttons[XINPUT_BUTTON_B] == 0)
	{

		if (shot[0]->attackflag == false)
		{
			PlaySoundMem(shotSeHandle, DX_PLAYTYPE_BACK);
			// �e�P����ʂɑ��݂��Ă��Ȃ��ꍇ�͒e�P���o��
			// �e�P�̈ʒu���Z�b�g
			shot[0]->pos = VGet(pos.x, pos.y + 15.0f, pos.z);
			shot[0]->SetDir(dir);
			// �e�P�͌����_�������đ��݂���̂ŁA���ݏ�Ԃ�ێ�����ϐ��ɂP��������
			shot[0]->attackflag = true;
			shot[0]->moveFlag = true;

		}
		else if (shot[1]->attackflag == 0)
		{
			PlaySoundMem(shotSeHandle, DX_PLAYTYPE_BACK);
			// �e�Q����ʂɑ��݂��Ă��Ȃ��ꍇ�͒e�Q���o��
			// �e2�̈ʒu���Z�b�g
			shot[1]->pos = VGet(pos.x, pos.y + 15.0f, pos.z);
			shot[1]->SetDir(dir);
			// �e�Q�͌����_�������đ��݂���̂ŁA���ݏ�Ԃ�ێ�����ϐ��ɂP��������
			shot[1]->attackflag = true;
			shot[1]->moveFlag = true;

		}
		else if (shot[2]->attackflag == 0)
		{
			PlaySoundMem(shotSeHandle, DX_PLAYTYPE_BACK);
			// �e3����ʂɑ��݂��Ă��Ȃ��ꍇ�͒e�Q���o��
			// �e3�̈ʒu���Z�b�g
			shot[2]->pos = VGet(pos.x, pos.y + 15.0f, pos.z);
			shot[2]->SetDir(dir);
			// �e3�͌����_�������đ��݂���̂ŁA���ݏ�Ԃ�ێ�����ϐ��ɂP��������
			shot[2]->attackflag = true;
			shot[2]->moveFlag = true;
		}
		else if (shot[3]->attackflag == 0)
		{
			PlaySoundMem(shotSeHandle, DX_PLAYTYPE_BACK);
			// �e3����ʂɑ��݂��Ă��Ȃ��ꍇ�͒e�Q���o��
			// �e3�̈ʒu���Z�b�g
			shot[3]->pos = VGet(pos.x, pos.y + 15.0f, pos.z);
			shot[3]->SetDir(dir);
			// �e3�͌����_�������đ��݂���̂ŁA���ݏ�Ԃ�ێ�����ϐ��ɂP��������
			shot[3]->attackflag = true;
			shot[3]->moveFlag = true;
		}
		else if (shot[4]->attackflag == 0)
		{
			PlaySoundMem(shotSeHandle, DX_PLAYTYPE_BACK);
			// �e3����ʂɑ��݂��Ă��Ȃ��ꍇ�͒e�Q���o��
			// �e3�̈ʒu���Z�b�g
			shot[4]->pos = VGet(pos.x, pos.y + 15.0f, pos.z);
			shot[4]->SetDir(dir);
			// �e3�͌����_�������đ��݂���̂ŁA���ݏ�Ԃ�ێ�����ϐ��ɂP��������
			shot[4]->attackflag = true;
			shot[4]->moveFlag = true;
		}
		else if (shot[5]->attackflag == 0)
		{
			PlaySoundMem(shotSeHandle, DX_PLAYTYPE_BACK);
			// �e3����ʂɑ��݂��Ă��Ȃ��ꍇ�͒e�Q���o��
			// �e3�̈ʒu���Z�b�g
			shot[5]->pos = VGet(pos.x, pos.y + 15.0f, pos.z);
			shot[5]->SetDir(dir);
			// �e3�͌����_�������đ��݂���̂ŁA���ݏ�Ԃ�ێ�����ϐ��ɂP��������
			shot[5]->attackflag = true;
			shot[5]->moveFlag = true;
		}
	}

	//�ʒu���̍X�V
	pos.x += vel.x;
	pos.y += vel.y;
	pos.z += vel.z;


	//�v���C���[�̈ʒu�̐ݒ�
	MV1SetPosition(model, pos);
	// ���Ԃ��o�߂�����B
	time++;
	frameCount++;
}

void Player::Draw()
{
	// �y�o�b�t�@��L���ɂ���
	SetUseZBuffer3D(TRUE);

	// �y�o�b�t�@�ւ̏������݂�L���ɂ���
	SetWriteZBuffer3D(TRUE);


	// �R�c���f���̌X��
	MV1SetRotationXYZ(model, VGet(0.0f, rote* DX_PI_F / 180.0f, tilt * DX_PI_F / 180.0f));

	//�v���C���[�̕`��
	MV1DrawModel(model);
}
//�����߂�
void Player::Back(Stage& stage)
{
	pos = PushBackStage(pos.x, pos.y, pos.z, stage.GetPos().x, stage.GetPos().y, stage.GetPos().z, size.x, size.y, size.z, stage.GetSize().x, stage.GetSize().y, stage.GetSize().z, vel.x, vel.y, vel.z);
	//�ڒn���Ă��邩�̃`�F�b�N
	//�t���O�̃��Z�b�g
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
//�����߂�
void Player::BackTitle(TitleStage& stage)
{
	pos = PushBackStage(pos.x, pos.y, pos.z, stage.GetPos().x, stage.GetPos().y, stage.GetPos().z, size.x, size.y, size.z, stage.GetSize().x, stage.GetSize().y, stage.GetSize().z, vel.x, vel.y, vel.z);
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


//�X�V
void Player::UpdateTitle(TitleStage &stage, Shot* shot[])
{
	
	VECTOR padVec = VGet(INPUT_INSTANCE.padState.ThumbLX, INPUT_INSTANCE.padState.ThumbLY, 0);
	if (!(padVec.x == 0 && padVec.y == 0))
	{
		padVec = VNorm(padVec);	// ���K�������p�b�h���̓x�N�g��.X��Y���[�����ƃG���[�ɂȂ�̂Ő��K�����Ȃ�
	}

	//�ړ�����

	if (fabs(INPUT_INSTANCE.padState.ThumbLX) > 200 || fabs(INPUT_INSTANCE.padState.ThumbLY) > 200)
	{
		dir = VGet(INPUT_INSTANCE.padState.ThumbLX, 0.0, -INPUT_INSTANCE.padState.ThumbLY);
		if (frameCount % 10 == 0)
		{
			// �G�t�F�N�g���Đ�����B
			playingEffectHandle = PlayEffekseer3DEffect(effectResourceHandle);

			if (playingEffectHandle >= 0)
			{
				//�G�t�F�N�g�����|�W�V����
				effectPos.x = pos.x;
				effectPos.y = pos.y;
				effectPos.z = pos.z;

				// �Đ����̃G�t�F�N�g���ړ�����B
				SetPosPlayingEffekseer3DEffect(playingEffectHandle, effectPos.x, effectPos.y, effectPos.z);
			}

		}
		

	}
	
	dir = VNorm(dir);
	vel = VScale(dir, speed);
	float radianRot = atan2f(dir.z, -dir.x); //  dir���烉�W�A���̉�]�p�x���Ƃ� 
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

	//�ǂ̉����߂�
	if (pos.x + (size.x / 2.0f) >= 250.0f)//�E
	{
		vel.x = 0;
		pos.x = 250.0f - (size.x / 2.0f) - 5.0f;
	}
	if (pos.x - (size.x / 2.0f) <= -250.0f)//��
	{
		vel.x = 0;
		pos.x = -250.0f + (size.x / 2.0f) + 5.0f;

	}
	if (pos.z + (size.z / 2.0f) >= 0.0f)//��
	{
		vel.z = 0;
		pos.z = 0.0f - (size.z / 2.0f) - 5.0f;
	}
	if (pos.z - (size.z / 2.0f) <= -350.0f)//��O
	{
		vel.z = 0;
		pos.z = -350.0f + (size.z / 2.0f) + 5.0f;
	}


	// s���������ꍇ�͏����𕪊�
	if (INPUT_INSTANCE.GetKeyDown(KEY_INPUT_SPACE) || INPUT_INSTANCE.padState.Buttons[XINPUT_BUTTON_B] == 1 && INPUT_INSTANCE.prePadState.Buttons[XINPUT_BUTTON_B] == 0)
	{

		if (shot[0]->attackflag == false)
		{
			PlaySoundMem(shotSeHandle, DX_PLAYTYPE_BACK);

			// �e�P����ʂɑ��݂��Ă��Ȃ��ꍇ�͒e�P���o��
			// �e�P�̈ʒu���Z�b�g
			shot[0]->pos = VGet(pos.x, pos.y + 15.0f, pos.z);
			shot[0]->SetDir(dir);
			// �e�P�͌����_�������đ��݂���̂ŁA���ݏ�Ԃ�ێ�����ϐ��ɂP��������
			shot[0]->attackflag = true;
			shot[0]->moveFlag = true;

		}
		else if (shot[1]->attackflag == 0)
		{
			PlaySoundMem(shotSeHandle, DX_PLAYTYPE_BACK);

			// �e�Q����ʂɑ��݂��Ă��Ȃ��ꍇ�͒e�Q���o��
			// �e2�̈ʒu���Z�b�g
			shot[1]->pos = VGet(pos.x, pos.y + 15.0f, pos.z);
			shot[1]->SetDir(dir);
			// �e�Q�͌����_�������đ��݂���̂ŁA���ݏ�Ԃ�ێ�����ϐ��ɂP��������
			shot[1]->attackflag = true;
			shot[1]->moveFlag = true;

		}
		else if (shot[2]->attackflag == 0)
		{
			PlaySoundMem(shotSeHandle, DX_PLAYTYPE_BACK);

			// �e3����ʂɑ��݂��Ă��Ȃ��ꍇ�͒e�Q���o��
			// �e3�̈ʒu���Z�b�g
			shot[2]->pos = VGet(pos.x, pos.y + 15.0f, pos.z);
			shot[2]->SetDir(dir);
			// �e3�͌����_�������đ��݂���̂ŁA���ݏ�Ԃ�ێ�����ϐ��ɂP��������
			shot[2]->attackflag = true;
			shot[2]->moveFlag = true;
		}
		else if (shot[3]->attackflag == 0)
		{
			PlaySoundMem(shotSeHandle, DX_PLAYTYPE_BACK);

			// �e3����ʂɑ��݂��Ă��Ȃ��ꍇ�͒e�Q���o��
			// �e3�̈ʒu���Z�b�g
			shot[3]->pos = VGet(pos.x, pos.y + 15.0f, pos.z);
			shot[3]->SetDir(dir);
			// �e3�͌����_�������đ��݂���̂ŁA���ݏ�Ԃ�ێ�����ϐ��ɂP��������
			shot[3]->attackflag = true;
			shot[3]->moveFlag = true;
		}
		else if (shot[4]->attackflag == 0)
		{
			PlaySoundMem(shotSeHandle, DX_PLAYTYPE_BACK);

			// �e3����ʂɑ��݂��Ă��Ȃ��ꍇ�͒e�Q���o��
			// �e3�̈ʒu���Z�b�g
			shot[4]->pos = VGet(pos.x, pos.y + 15.0f, pos.z);
			shot[4]->SetDir(dir);
			// �e3�͌����_�������đ��݂���̂ŁA���ݏ�Ԃ�ێ�����ϐ��ɂP��������
			shot[4]->attackflag = true;
			shot[4]->moveFlag = true;
		}
		else if (shot[5]->attackflag == 0)
		{
			PlaySoundMem(shotSeHandle, DX_PLAYTYPE_BACK);

			// �e3����ʂɑ��݂��Ă��Ȃ��ꍇ�͒e�Q���o��
			// �e3�̈ʒu���Z�b�g
			shot[5]->pos = VGet(pos.x, pos.y + 15.0f, pos.z);
			shot[5]->SetDir(dir);
			// �e3�͌����_�������đ��݂���̂ŁA���ݏ�Ԃ�ێ�����ϐ��ɂP��������
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

	//�ʒu���̍X�V
	pos.x += vel.x;
	pos.y += vel.y;
	pos.z += vel.z;


	//�v���C���[�̈ʒu�̐ݒ�
	MV1SetPosition(model, pos);
	MV1SetPosition(model3, VGet(pos.x - 10.0f,pos.y + 30.0f,pos.z));
	++frameCount;
}

void Player::UpdateEnd()
{
	tilt = 0.0f;
	rote += 10.0f;
	rote2 -= 12.0f;
	//�v���C���[�̈ʒu�̐ݒ�
	MV1SetPosition(model2, VGet(pos.x,pos.y + 15.0f,pos.z));

}

void Player::UpdateClear(Stage &stage)
{
	//�d��
	vel.y -= GRAVITY_ACCEL;
	

	if (jumpFlag == true)
	{
		vel.y = 5.0f;
	}

	//�X�e�[�W�Ƃ̓����蔻��
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
	//�v���C���[�̈ʒu�̐ݒ�
	MV1SetPosition(model, pos);

}

void Player::DrawTitle()
{
	// �y�o�b�t�@��L���ɂ���
	SetUseZBuffer3D(TRUE);

	// �y�o�b�t�@�ւ̏������݂�L���ɂ���
	SetWriteZBuffer3D(TRUE);


	// �R�c���f���̌X��
	MV1SetRotationXYZ(model, VGet(0.0f, rote* DX_PI_F / 180.0f, tilt * DX_PI_F / 180.0f));

	//�v���C���[�̕`��
	MV1DrawModel(model);
	if (tileDamageFlag == true)
	{
		MV1DrawModel(model3);
	}
}


void Player::DrawEnd()
{
	// �y�o�b�t�@��L���ɂ���
	SetUseZBuffer3D(TRUE);

	// �y�o�b�t�@�ւ̏������݂�L���ɂ���
	SetWriteZBuffer3D(TRUE);


	// �R�c���f���̌X��
	MV1SetRotationXYZ(model, VGet(0.0f, rote* DX_PI_F / 180.0f, tilt * DX_PI_F / 180.0f));
	MV1SetRotationXYZ(model2, VGet(0.0f, rote2* DX_PI_F / 180.0f, 0.0f));

	//�v���C���[�̕`��
	MV1DrawModel(model);
	MV1DrawModel(model2);
}


