#include "Enemy.h"
#include "Stage.h"
#include "Shot.h"
#include "Player.h"
#include "Wall.h"
#include "Camera.h"
#include "TitleStage.h"
#include "System.h"
#include "GameScene.h"
#include "Time.h"
#include "EffekseerForDXLib.h"


Enemy::Enemy()
{
}


Enemy::~Enemy()
{
	// ���f���̃A�����[�h.
	MV1DeleteModel(model);
	// �G�t�F�N�g���\�[�X���폜����B(Effekseer�I�����ɔj�������̂ō폜���Ȃ��Ă�����)
	DeleteEffekseerEffect(effectResourceHandle);
}

//������
void Enemy::Init(int modelhandle1, int modelhandle2, int modelhandle3,int modelhandle4)
{
	//// �񓯊��ǂݍ��ݐݒ�ɕύX
	//SetUseASyncLoadFlag(TRUE);

	model1 = MV1DuplicateModel(modelhandle1);
	model2 = MV1DuplicateModel(modelhandle2);
	model3 = MV1DuplicateModel(modelhandle3);
	shadowModel = MV1DuplicateModel(modelhandle4);
	//// �����ǂݍ��ݐݒ�ɕύX
	//SetUseASyncLoadFlag(FALSE);

	//�G�t�F�N�g�̓ǂݍ���
	effectResourceHandle = LoadEffekseerEffect("data/effect/NitoriBox/Aya_Attack.efk");

	pos = VGet(100.0f, 100.0f, 100.0f);
	vel = VGet(0.0f, 0.0f, 0.0f);
	size = VGet(12.0f, 6.0f, 12.0f);
	dir = VGet(0.0f, 0.0f, 0.0f);
	enemyToPlayer = VGet(0.0f, 0.0f, 0.0f);
	speed = 2.0f;
	tilt = 0.0f;
	shadowPos = VGet(pos.x, 10.0f, pos.z);

	//�J�E���g�֘A
	time = 0;
	respawnCount = 0;
	frameCount = 0;
	tiltCount = 0;
	startCount = 0;
	//�G�l�~�[�̎�ޏ�����
	enemyType = GetRandom(0,2);
	if (enemyType == HOMING)
	{
		model = model1;
	}
	else if (enemyType == REFLECTION)
	{
		model = model2;
	}
	else if (enemyType == SLOW)
	{
		model = model3;
	}

	//�G�t�F�N�g�֘A
	playingEffectHandle = -1;
	time = 0;
	effectPos = VGet(0.0f, 0.0f, 0.0f);

	hitSE = LoadSoundMem("data/SE/punch-stop1.mp3");
	titleButHitSE = LoadSoundMem("data/SE/incorrect1.mp3");
	titleHitSE = LoadSoundMem("data/SE/correct2.mp3");
}


//�X�V
void Enemy::Update(Stage &stage, Player &player, Shot* shot[],Wall* wall[], Camera* camera)
{

	if (startUpFlag == true)
	{
		if (gravityFlag == false)
		{
			if (enemyType == HOMING)
			{
				if (type1Flag == true)
				{
					//�G�l�~�[����v���C���[�ւ̃x�N�g�����Ƃ�
					enemyToPlayer = VSub(player.GetPos(), pos);

					//�x�N�g���̐��K��
					dir = VNorm(enemyToPlayer);
					type1Flag = false;
				}
				//�����߂�
				if (pos.x + (size.x / 2.0f) >= wall[2]->GetPos().x)//�E
				{
					pos.x = wall[2]->GetPos().x - (size.x / 2.0f) - 5.0f;
					type1Flag = true;
				}
				if (pos.x - (size.x / 2.0f) <= wall[3]->GetPos().x)//��
				{
					pos.x = wall[3]->GetPos().x + (size.x / 2.0f) + 5.0f;
					type1Flag = true;
				}
				if (pos.z + (size.z / 2.0f) >= wall[0]->GetPos().z)//��
				{
					pos.z = wall[0]->GetPos().z - (size.z / 2.0f) - 5.0f;
					type1Flag = true;
				}
				if (pos.z - (size.z / 2.0f) <= wall[1]->GetPos().z)//��O
				{
					pos.z = wall[1]->GetPos().z + (size.z / 2.0f) + 5.0f;
					type1Flag = true;
				}

				speed = 3.0f;

				vel = VScale(dir, speed);

			}
			else if (enemyType == REFLECTION)
			{
				if (dirSetFlag == true)
				{
					//�����������_���łƂ�
					dir = VGet(GetRandom(-1.0f, 1.0f), 0.0f, GetRandom(-1.0f, 1.0f));
					//��������z���ǂ��炩��0.0�����������蒼��
					if (dir.x == 0.0f || dir.z == 0.0f)
					{
						dir = VGet(GetRandom(-1.0f, 1.0f), 0.0f, GetRandom(-1.0f, 1.0f));
					}
					dirSetFlag = false;
				}
				if (pos.x + (size.x / 2.0f) >= wall[2]->GetPos().x)//�E
				{
					dir.x = -1.0f;
					pos.x = wall[2]->GetPos().x - (size.x / 2.0f) - 5.0f;
				}
				if (pos.x - (size.x / 2.0f) <= wall[3]->GetPos().x)//��
				{
					dir. x= 1.0f;
					pos.x = wall[3]->GetPos().x + (size.x / 2.0f) + 5.0f;
				}
				if (pos.z + (size.z / 2.0f) >= wall[0]->GetPos().z)//��
				{
					dir.z = -1.0f;
					pos.z = wall[0]->GetPos().z - (size.z / 2.0f) - 5.0f;
				}
				if (pos.z - (size.z / 2.0f) <= wall[1]->GetPos().z)//��O
				{
					dir.z = 1.0f;
					pos.z = wall[1]->GetPos().z + (size.z / 2.0f) + 5.0f;
				}

				speed = 2.5f;

				vel = VScale(dir, speed);

			}
			else if (enemyType == SLOW)
			{
				if (dirSetFlag == true)
				{
					//�����������_���łƂ�
					dir = VGet(GetRandom(-1.0f, 1.0f), 0.0f, GetRandom(-1.0f, 1.0f));
					//��������z���ǂ��炩��0.0�����������蒼��
					if (dir.x == 0.0f || dir.z == 0.0f)
					{
						dir = VGet(GetRandom(-1.0f, 1.0f), 0.0f, GetRandom(-1.0f, 1.0f));
					}
					dirSetFlag = false;
				}
				if (pos.x + (size.x / 2.0f) >= wall[2]->GetPos().x)//�E
				{
					dir.x = -1.0f;
					pos.x = wall[2]->GetPos().x - (size.x / 2.0f) - 5.0f;
				}
				if (pos.x - (size.x / 2.0f) <= wall[3]->GetPos().x)//��
				{
					dir.x = 1.0f;
					pos.x = wall[3]->GetPos().x + (size.x / 2.0f) + 5.0f;
				}
				if (pos.z + (size.z / 2.0f) >= wall[0]->GetPos().z)//��
				{
					dir.z = -1.0f;
					pos.z = wall[0]->GetPos().z - (size.z / 2.0f) - 5.0f;
				}
				if (pos.z - (size.z / 2.0f) <= wall[1]->GetPos().z)//��O
				{
					dir.z = 1.0f;
					pos.z = wall[1]->GetPos().z + (size.z / 2.0f) + 5.0f;
				}

				speed = 1.5f;
				vel = VScale(dir, speed);
			}
		}

		if (dir.x < 0.0f)
		{
			rote = 270.0f;
		}
		else if (dir.x > 0.0f)
		{
			rote = 90.0f;
		}

		if (dir.z > 0.0f)
		{
			rote = 180.0f;

		}
		else if (dir.z < 0.0f)
		{
			rote = 0.0f;
		}


		//�d��
		if (gravityFlag == true)
		{
			vel.y = -1;
			vel.x = 0;
			vel.z = 0;

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
				player.aliveFlag = false;
				WaitTimer(1000);
			}
		}
		//�V���b�g�Ƃ̓����蔻��
		for (int i = 0; i < shotNum; i++)
		{
			if (shot[i]->attackflag == true && aliveFlag == true)
			{
				if (IsHit(pos.x, pos.y, pos.z, shot[i]->pos.x, shot[i]->pos.y, shot[i]->pos.z, size.x, size.y + 5.0f, size.z, shot[i]->GetSize().x, shot[i]->GetSize().y, shot[i]->GetSize().z) == true)
				{
					PlaySoundMem(hitSE, DX_PLAYTYPE_BACK);
					TIME_INSTANCE.defeatCount++;
					aliveFlag = false;
					// ����I�ɃG�t�F�N�g���Đ�����
					if (aliveFlag == false)
					{
						// �G�t�F�N�g���Đ�����B
						playingEffectHandle = PlayEffekseer3DEffect(effectResourceHandle);

						// �G�t�F�N�g�̈ʒu�����Z�b�g����B
						effectPos.x = 0.0f;
					}

					if (playingEffectHandle >= 0)
					{
						effectPos.x = pos.x;
						effectPos.y = pos.y;
						effectPos.z = pos.z;

						// �Đ����̃G�t�F�N�g���ړ�����B
						SetPosPlayingEffekseer3DEffect(playingEffectHandle, effectPos.x, effectPos.y, effectPos.z);
					}

					shot[i]->attackflag = false;
				}
			}
		}

		if (aliveFlag == false)
		{
			if (respawnFlag == true)
			{
				pos = (VGet(GetRandom(wall[3]->GetPos().x + 10.0f, wall[2]->GetPos().x - 10.0f), 300.0f, GetRandom(wall[1]->GetPos().z + 10.0f, wall[0]->GetPos().z - 10.0f)));
				aliveFlag = true;
				gravityFlag = true;
				enemyType = GetRandom(0, 2);
				if (enemyType == HOMING)
				{
					model = model1;
				}
				else if (enemyType == REFLECTION)
				{
					model = model2;
				}
				else if (enemyType == SLOW)
				{
					model = model3;
				}
				dirSetFlag = true;
				type1Flag = true;
			}
			else
			{
				if (respawnCount == 540)
				{
					respawnFlag = true;
					respawnCount = 0;
				}
				respawnCount++;
			}
		}

		//�X��
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


		//�ʒu���̍X�V
		if (aliveFlag == true)
		{
			pos.x += vel.x;
			pos.y += vel.y;
			pos.z += vel.z;
			/*shadowPos.x = pos.x;
			shadowPos.z = pos.z;*/
		}

	}

	//�G�l�~�[�̈ʒu�̐ݒ�
	MV1SetPosition(model, pos);
	MV1SetPosition(shadowModel,VGet(pos.x,25.0f,pos.z + 10.0f));

	// ���Ԃ��o�߂�����B
	++time;
	++frameCount;

}
//�`��
void Enemy::Draw()
{
	// �y�o�b�t�@��L���ɂ���
	SetUseZBuffer3D(TRUE);

	// �y�o�b�t�@�ւ̏������݂�L���ɂ���
	SetWriteZBuffer3D(TRUE);

	 // �R�c���f���̃X�P�[���������L�΂�
	MV1SetScale(model, VGet(3.0f, 3.0f, 3.0f));

	// �R�c���f���̉�]
	MV1SetRotationXYZ(model, VGet(0.0f, rote * DX_PI_F / 180.0f, tilt * DX_PI_F / 180.0f));

	if (aliveFlag == true && startUpFlag == true)
	{
		//�G�l�~�[�̕`��
		MV1DrawModel(model);
		//�G�l�~�[�̕`��
		MV1DrawModel(shadowModel);
	}

}

//�����߂�
void Enemy::Back(Stage &stage)
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

//�X�V
void Enemy::UpdateTitle(TitleStage &stage, Player &player, Shot* shot[],Camera* camera)
{

	if (dir.x < 0.0f)
	{
		rote = 270.0f;
	}
	else if (dir.x > 0.0f)
	{
		rote = 90.0f;
	}

	if (dir.z > 0.0f)
	{
		rote = 180.0f;

	}
	else if (dir.z < 0.0f)
	{
		rote = 0.0f;
	}


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
			PlaySoundMem(titleButHitSE, DX_PLAYTYPE_BACK);
			player.tileDamageFlag = true;
			aliveFlag = false;
		}
	}
	//�V���b�g�Ƃ̓����蔻��
	for (int i = 0; i < shotNum; i++)
	{
		if (shot[i]->attackflag == true && aliveFlag == true)
		{
			if (IsHit(pos.x, pos.y, pos.z, shot[i]->pos.x, shot[i]->pos.y, shot[i]->pos.z, size.x, size.y + 5.0f, size.z, shot[i]->GetSize().x, shot[i]->GetSize().y, shot[i]->GetSize().z) == true)
			{
				PlaySoundMem(titleHitSE, DX_PLAYTYPE_BACK);
				aliveFlag = false;
				++startCount;
				// ����I�ɃG�t�F�N�g���Đ�����
				if (aliveFlag == false)
				{
					// �G�t�F�N�g���Đ�����B
					playingEffectHandle = PlayEffekseer3DEffect(effectResourceHandle);

					// �G�t�F�N�g�̈ʒu�����Z�b�g����B
					effectPos.x = 0.0f;
				}

				if (playingEffectHandle >= 0)
				{
					effectPos.x = pos.x;
					effectPos.y = pos.y;
					effectPos.z = pos.z;

					// �Đ����̃G�t�F�N�g���ړ�����B
					SetPosPlayingEffekseer3DEffect(playingEffectHandle, effectPos.x, effectPos.y, effectPos.z);
				}

				shot[i]->attackflag = false;
			}
		}
	}

	if (aliveFlag == false)
	{
		enemyType = GetRandom(0, 2);
		if (enemyType == HOMING)
		{
			model = model1;
		}
		else if (enemyType == REFLECTION)
		{
			model = model2;
		}
		else if (enemyType == SLOW)
		{
			model = model3;
		}
		dirSetFlag = true;
		type1Flag = true;
		aliveFlag = true;
		gravityFlag = true;
		pos = (VGet(GetRandom(-200.0f, 200.0f), 400.0f, GetRandom(-300, -100)));
	}

	//�ʒu���̍X�V
	if (aliveFlag == true)
	{
		pos.x += vel.x;
		pos.y += vel.y;
		pos.z += vel.z;
	}

	//�G�l�~�[�̈ʒu�̐ݒ�
	MV1SetPosition(model, pos);

	// ���Ԃ��o�߂�����B
	++time;
	++frameCount;

}

void Enemy::UpdateClear(Stage &stage, Player &player, Shot* shot[], Wall* wall[], Camera* camera)
{
	if (endEffectFlag == true)
	{
		aliveFlag = false;
	
		// �G�t�F�N�g���Đ�����B
		playingEffectHandle = PlayEffekseer3DEffect(effectResourceHandle);

		// �G�t�F�N�g�̈ʒu�����Z�b�g����B
		effectPos.x = 0.0f;


		if (playingEffectHandle >= 0)
		{
			effectPos.x = pos.x;
			effectPos.y = pos.y;
			effectPos.z = pos.z;

			// �Đ����̃G�t�F�N�g���ړ�����B
			SetPosPlayingEffekseer3DEffect(playingEffectHandle, effectPos.x, effectPos.y, effectPos.z);
		}	

		endEffectFlag = false;
	}
}
