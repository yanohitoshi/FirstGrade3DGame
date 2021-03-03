#include <math.h>
#include <time.h>
#include "System.h"
#include "EffekseerForDXLib.h"


bool IsHit(float posX1, float posY1, float posZ1, float posX2, float posY2, float posZ2, float sizeX1, float sizeY1, float sizeZ1, float sizeX2, float sizeY2, float sizeZ2)
{
	//a�̉E����b�̍������傫��
	//a�̍�����b�̍�����菬����
	//a�̏㑤��b�̉�����菬����
	//a�̉�����b�̏㑤���傫��

	if (posX1 + (sizeX1 / 2.0f) > posX2 - (sizeX2 / 2.0f) &&
		posX1 - (sizeX1 / 2.0f) < posX2 + (sizeX2 / 2.0f) &&
		posY1 + (sizeY1 / 2.0f) > posY2 - (sizeY2 / 2.0f) &&
		posY1 - (sizeY1 / 2.0f) < posY2 + (sizeY2 / 2.0f) &&
		posZ1 + (sizeZ1 / 2.0f) > posZ2 - (sizeZ2 / 2.0f) &&
		posZ1 - (sizeZ1 / 2.0f) < posZ2 + (sizeZ2 / 2.0f))
	{
		return true;

	}
	return false;
}


bool IsHitGround(float posX1, float posY1, float posZ1, float posX2, float posY2, float posZ2, float sizeX1, float sizeY1, float sizeZ1, float sizeX2, float sizeY2, float sizeZ2)
{

	//a�̉E����b�̍������傫��
	//a�̍�����b�̍�����菬����
	//a�̏㑤��b�̉�����菬����
	//a�̉�����b�̏㑤���傫��

	if (posX1 + (sizeX1 / 2.0f) - 2.0f > posX2 - (sizeX2 / 2.0f) &&
		posX1 - (sizeX1 / 2.0f) + 2.0f < posX2 + (sizeX2 / 2.0f) &&
		posY1 + (sizeY1 / 2.0f) + 2.0f > posY2 - (sizeY2 / 2.0f) &&
		posY1 - (sizeY1 / 2.0f) - 2.0f < posY2 + (sizeY2 / 2.0f) &&
		posZ1 + (sizeZ1 / 2.0f) + 2.0f > posZ2 - (sizeZ2 / 2.0f) &&
		posZ1 - (sizeZ1 / 2.0f) - 2.0f < posZ2 + (sizeZ2 / 2.0f))
	{
		return true;

	}
	return false;
}

VECTOR PushBackStage(float posX1, float posY1, float posZ1, float posX2, float posY2, float posZ2, float sizeX1, float sizeY1, float sizeZ1, float sizeX2, float sizeY2, float sizeZ2, float velX, float velY, float velZ )
{

	//�Փ˂����̂ł߂荞�݂�߂�
	//���ꂼ��̍��������߂�
	float dx1 = posX2 + (sizeX2 / 2.0f) - posX1 - (sizeX1 / 2.0f);
	float dx2 = posX1 - (sizeX1 / 2.0f) - posX2 + (sizeX2 / 2.0f);
	float dy1 = posY2 + (sizeY2 / 2.0f) - posY1 - (sizeY1 / 2.0f);
	float dy2 = posY1 - (sizeY1 / 2.0f) - posY2 + (sizeY2 / 2.0f);
	float dz1 = posZ2 + (sizeZ2 / 2.0f) - posZ1 - (sizeZ1 / 2.0f);
	float dz2 = posZ1 - (sizeZ1 / 2.0f) - posZ2 + (sizeZ2 / 2.0f);

	//��Βl���Ƃ�
	float dx = (fabs(dx1) < fabs(dx2)) ? dx1 : dx2;
	float dy = (fabs(dy1) < fabs(dy2)) ? dy1 : dy2;
	float dz = (fabs(dz1) < fabs(dz2)) ? dz1 : dz2;

	//x��y.z�����������Ƃ�����߂�
	if (fabs(dx) < fabs(dy) && fabs(dx) < fabs(dz))
	{
		posX1 += dx;
		velX = 0;
		return (VGet(posX1,posY1,posZ1));
	}
	//y��x.z�����������Ƃ�����߂�
	else if (fabs(dx) > fabs(dy) && fabs(dz) > fabs(dy))
	{
		posY1 += dy;
		velY = 0;
		return (VGet(posX1, posY1, posZ1));
	}
	//z��x.y�����������Ƃ�����߂�
	else
	{
		posZ1 += dz;
		velZ = 0;
		return (VGet(posX1, posY1, posZ1));
	}
}

VECTOR PushBackWall(float posX1, float posY1, float posZ1, float posX2, float posY2, float posZ2, float sizeX1, float sizeY1, float sizeZ1, float sizeX2, float sizeY2, float sizeZ2, float velX, float velY, float velZ)
{

		//�Փ˂����̂ł߂荞�݂�߂�
		//���ꂼ��̍��������߂�
	float dx1 = posX2 + (sizeX2 / 2.0f) - posX1 - (sizeX1 / 2.0f);
	float dx2 = posX1 - (sizeX1 / 2.0f) - posX2 + (sizeX2 / 2.0f);
	float dy1 = posY2 + (sizeY2 / 2.0f) - posY1 - (sizeY1 / 2.0f);
	float dy2 = posY1 - (sizeY1 / 2.0f) - posY2 + (sizeY2 / 2.0f);
	float dz1 = posZ2 + (sizeZ2 / 2.0f) - posZ1 - (sizeZ1 / 2.0f);
	float dz2 = posZ1 - (sizeZ1 / 2.0f) - posZ2 + (sizeZ2 / 2.0f);

	//��Βl���Ƃ�
	float dx = (fabs(dx1) < fabs(dx2)) ? dx1 : dx2;
	float dy = (fabs(dy1) < fabs(dy2)) ? dy1 : dy2;
	float dz = (fabs(dz1) < fabs(dz2)) ? dz1 : dz2;

	//x��z�����������Ƃ�����߂�
	if (fabs(dx) < fabs(dy) && fabs(dx) < fabs(dz))
	{
		posX1 += dx;
		velX = 0;
		return (VGet(posX1, posY1, posZ1));
	}
	//z��x�����������Ƃ�����߂�
	else
	{
		posZ1 += dz;
		velZ = 0;
		return (VGet(posX1, posY1, posZ1));
	}
}


int GetRandom(int min, int max)
{
	static int flag;

	if (flag == 0) {
		srand((unsigned int)time(NULL));
		flag = 1;
	}
	return min + (int)(rand()*(max - min + 1.0) / (1.0 + RAND_MAX));
}

//��`�`��i���쒆�̂݁j
void DrawLine(float posX1, float posY1, float posZ1, float sizeX1, float sizeY1, float sizeZ1)
{
	//�ϐ�
	//1����4�͏�̎�O������1
	//5����8�͉��̎�O������5

	VECTOR P1;
	VECTOR P2;
	VECTOR P3;
	VECTOR P4;
	VECTOR P5;
	VECTOR P6;
	VECTOR P7;
	VECTOR P8;

	P1 = VGet(posX1 - (sizeX1 / 2.0f), posY1 + (sizeY1 / 2.0f), posZ1 - (sizeZ1 / 2.0f));
	P2 = VGet(posX1 + (sizeX1 / 2.0f), posY1 + (sizeY1 / 2.0f), posZ1 - (sizeZ1 / 2.0f));
	P3 = VGet(posX1 - (sizeX1 / 2.0f), posY1 + (sizeY1 / 2.0f), posZ1 + (sizeZ1 / 2.0f));
	P4 = VGet(posX1 + (sizeX1 / 2.0f), posY1 + (sizeY1 / 2.0f), posZ1 + (sizeZ1 / 2.0f));
	P5 = VGet(posX1 - (sizeX1 / 2.0f), posY1 - (sizeY1 / 2.0f), posZ1 - (sizeZ1 / 2.0f));
	P6 = VGet(posX1 + (sizeX1 / 2.0f), posY1 - (sizeY1 / 2.0f), posZ1 - (sizeZ1 / 2.0f));
	P7 = VGet(posX1 - (sizeX1 / 2.0f), posY1 - (sizeY1 / 2.0f), posZ1 + (sizeZ1 / 2.0f));
	P8 = VGet(posX1 + (sizeX1 / 2.0f), posY1 - (sizeY1 / 2.0f), posZ1 + (sizeZ1 / 2.0f));


	//--player--//
	// �R�c��ԏ�ɐ�����`�悷��i��O��j
	DrawLine3D(P1, P2, GetColor(255, 255, 255));
	//�i����O���j
	DrawLine3D(P5, P6, GetColor(255, 255, 255));
	//�i����O�E�j
	DrawLine3D(P2, P6, GetColor(255, 255, 255));
	//�i����O���j
	DrawLine3D(P1, P5, GetColor(255, 255, 255));
	//�i������j
	DrawLine3D(P3, P4, GetColor(255, 255, 255));
	//�i�������j
	DrawLine3D(P7, P8, GetColor(255, 255, 255));
	//�i�����E�j
	DrawLine3D(P4, P8, GetColor(255, 255, 255));
	//�i�������j
	DrawLine3D(P3, P7, GetColor(255, 255, 255));
	//�i�����ʏ�j
	DrawLine3D(P1, P3, GetColor(255, 255, 255));
	//�i�����ʉ��j
	DrawLine3D(P5, P7, GetColor(255, 255, 255));
	//�i�E���ʏ�j
	DrawLine3D(P2, P4, GetColor(255, 255, 255));
	//�i�E���ʉ��j
	DrawLine3D(P6, P8, GetColor(255, 255, 255));


}
