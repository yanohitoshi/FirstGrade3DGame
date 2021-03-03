#include "Quaternion.h"
#include "DxLib.h"

//�N�H�[�^�j�I���̌v�Z
QUATERNION operator*(QUATERNION q1, QUATERNION q2)
{
	QUATERNION ans;
	double d1, d2, d3, d4;

	//t�p�����[�^�̌v�Z 
	d1 = q1.t * q2.t;
	d2 = -q1.x * q2.x;
	d3 = -q1.y * q2.y;
	d4 = -q1.z * q2.z;
	ans.t = d1 + d2 + d3 + d4;

	//x�p�����[�^�̌v�Z 
	d1 = q1.t * q2.x;
	d2 = q2.t * q1.x;
	d3 = q1.y * q2.z;
	d4 = -q1.z * q2.y;
	ans.x = d1 + d2 + d3 + d4;

	//y�p�����[�^�̌v�Z
	d1 = q1.t * q2.y;
	d2 = q2.t * q1.y;
	d3 = q1.z * q2.x;
	d4 = -q1.x * q2.z;
	ans.y = d1 + d2 + d3 + d4;

	//z�p�����[�^�̌v�Z
	d1 = q1.t * q2.z;
	d2 = q2.t * q1.z;
	d3 = q1.x * q2.y;
	d4 = -q1.y * q2.x;
	ans.z = d1 + d2 + d3 + d4;

	return ans;
}

//��]�N�H�[�^�j�I��
QUATERNION CreateRotationQuaternion(double radian, VECTOR Axis)
{
	QUATERNION ans;
	double norm;
	double ccc, sss;

	ans.t = ans.x = ans.y = ans.z = 0.0;

	norm = Axis.x * Axis.x + Axis.y * Axis.y + Axis.z * Axis.z;
	if (norm <= 0.0) return ans;

	norm = 1.0 / sqrt(norm);
	Axis.x *= norm;
	Axis.y *= norm;
	Axis.z *= norm;

	ccc = cos(0.5 * radian);
	sss = sin(0.5 * radian);

	ans.t = ccc;
	ans.x = sss * Axis.x;
	ans.y = sss * Axis.y;
	ans.z = sss * Axis.z;

	return ans;
}

//�ʒu�N�H�[�^�j�I��
QUATERNION CreateXYZToQuaternion(double PosX, double PosY, double PosZ)
{
	QUATERNION ans;

	ans.t = 0.0;
	ans.x = PosX;
	ans.y = PosY;
	ans.z = PosZ;

	return ans;
}

//�N�H�[�^�j�I�������]�s���
MATRIX QuaternionToMatrix(QUATERNION q)
{
	MATRIX mat = MGetIdent();
	//X��
	mat.m[0][0] = 1.0f - 2.0f * q.y * q.y - 2.0f * q.z * q.z;
	mat.m[0][1] = 2.0f * q.x * q.y + 2.0f * q.t * q.z;
	mat.m[0][2] = 2.0f * q.x * q.z - 2.0f * q.t * q.y;

	//Y��
	mat.m[1][0] = 2.0f * q.x * q.y - 2.0f * q.t * q.z;
	mat.m[1][1] = 1.0f - 2.0f * q.x * q.x - 2.0f * q.z * q.z;
	mat.m[1][2] = 2.0f * q.y * q.z + 2.0f * q.t * q.x;

	//Z��
	mat.m[2][0] = 2.0f * q.x * q.z + 2.0f * q.t * q.y;
	mat.m[2][1] = 2.0f * q.y * q.z - 2.0f * q.t * q.x;
	mat.m[2][2] = 1.0f - 2.0f * q.x * q.x - 2.0f * q.y * q.y;

	return mat;
}

