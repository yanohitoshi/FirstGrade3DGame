#pragma once
#include <math.h>
#include "DxLib.h"
//�N�H�[�^�j�I���\����
typedef struct
{
	double t;   //real
	double x;   //x
	double y;   //y
	double z;   //z
} QUATERNION;

//�N�H�[�^�j�I���̌v�Z
QUATERNION operator*(QUATERNION q1, QUATERNION q2);

//��]�N�H�[�^�j�I��
QUATERNION CreateRotationQuaternion(double radian, VECTOR Axis);

//�ʒu�N�H�[�^�j�I��
QUATERNION CreateXYZToQuaternion(double PosX, double PosY, double PosZ);

//�N�H�[�^�j�I�������]�s���
MATRIX QuaternionToMatrix(QUATERNION q); 


