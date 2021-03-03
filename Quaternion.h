#pragma once
#include <math.h>
#include "DxLib.h"
//クォータニオン構造体
typedef struct
{
	double t;   //real
	double x;   //x
	double y;   //y
	double z;   //z
} QUATERNION;

//クォータニオンの計算
QUATERNION operator*(QUATERNION q1, QUATERNION q2);

//回転クォータニオン
QUATERNION CreateRotationQuaternion(double radian, VECTOR Axis);

//位置クォータニオン
QUATERNION CreateXYZToQuaternion(double PosX, double PosY, double PosZ);

//クォータニオンから回転行列へ
MATRIX QuaternionToMatrix(QUATERNION q); 


