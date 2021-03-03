#include <math.h>
#include <time.h>
#include "System.h"
#include "EffekseerForDXLib.h"


bool IsHit(float posX1, float posY1, float posZ1, float posX2, float posY2, float posZ2, float sizeX1, float sizeY1, float sizeZ1, float sizeX2, float sizeY2, float sizeZ2)
{
	//aの右側がbの左側より大きい
	//aの左側がbの左側より小さい
	//aの上側がbの下側より小さい
	//aの下側がbの上側より大きい

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

	//aの右側がbの左側より大きい
	//aの左側がbの左側より小さい
	//aの上側がbの下側より小さい
	//aの下側がbの上側より大きい

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

	//衝突したのでめり込みを戻す
	//それぞれの差分を求める
	float dx1 = posX2 + (sizeX2 / 2.0f) - posX1 - (sizeX1 / 2.0f);
	float dx2 = posX1 - (sizeX1 / 2.0f) - posX2 + (sizeX2 / 2.0f);
	float dy1 = posY2 + (sizeY2 / 2.0f) - posY1 - (sizeY1 / 2.0f);
	float dy2 = posY1 - (sizeY1 / 2.0f) - posY2 + (sizeY2 / 2.0f);
	float dz1 = posZ2 + (sizeZ2 / 2.0f) - posZ1 - (sizeZ1 / 2.0f);
	float dz2 = posZ1 - (sizeZ1 / 2.0f) - posZ2 + (sizeZ2 / 2.0f);

	//絶対値をとる
	float dx = (fabs(dx1) < fabs(dx2)) ? dx1 : dx2;
	float dy = (fabs(dy1) < fabs(dy2)) ? dy1 : dy2;
	float dz = (fabs(dz1) < fabs(dz2)) ? dz1 : dz2;

	//xがy.zよりも小さいときｘを戻す
	if (fabs(dx) < fabs(dy) && fabs(dx) < fabs(dz))
	{
		posX1 += dx;
		velX = 0;
		return (VGet(posX1,posY1,posZ1));
	}
	//yがx.zよりも小さいときｘを戻す
	else if (fabs(dx) > fabs(dy) && fabs(dz) > fabs(dy))
	{
		posY1 += dy;
		velY = 0;
		return (VGet(posX1, posY1, posZ1));
	}
	//zがx.yよりも小さいときｘを戻す
	else
	{
		posZ1 += dz;
		velZ = 0;
		return (VGet(posX1, posY1, posZ1));
	}
}

VECTOR PushBackWall(float posX1, float posY1, float posZ1, float posX2, float posY2, float posZ2, float sizeX1, float sizeY1, float sizeZ1, float sizeX2, float sizeY2, float sizeZ2, float velX, float velY, float velZ)
{

		//衝突したのでめり込みを戻す
		//それぞれの差分を求める
	float dx1 = posX2 + (sizeX2 / 2.0f) - posX1 - (sizeX1 / 2.0f);
	float dx2 = posX1 - (sizeX1 / 2.0f) - posX2 + (sizeX2 / 2.0f);
	float dy1 = posY2 + (sizeY2 / 2.0f) - posY1 - (sizeY1 / 2.0f);
	float dy2 = posY1 - (sizeY1 / 2.0f) - posY2 + (sizeY2 / 2.0f);
	float dz1 = posZ2 + (sizeZ2 / 2.0f) - posZ1 - (sizeZ1 / 2.0f);
	float dz2 = posZ1 - (sizeZ1 / 2.0f) - posZ2 + (sizeZ2 / 2.0f);

	//絶対値をとる
	float dx = (fabs(dx1) < fabs(dx2)) ? dx1 : dx2;
	float dy = (fabs(dy1) < fabs(dy2)) ? dy1 : dy2;
	float dz = (fabs(dz1) < fabs(dz2)) ? dz1 : dz2;

	//xがzよりも小さいときｘを戻す
	if (fabs(dx) < fabs(dy) && fabs(dx) < fabs(dz))
	{
		posX1 += dx;
		velX = 0;
		return (VGet(posX1, posY1, posZ1));
	}
	//zがxよりも小さいときｘを戻す
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

//矩形描画（制作中のみ）
void DrawLine(float posX1, float posY1, float posZ1, float sizeX1, float sizeY1, float sizeZ1)
{
	//変数
	//1から4は上の手前左から1
	//5から8は下の手前左から5

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
	// ３Ｄ空間上に線分を描画する（手前上）
	DrawLine3D(P1, P2, GetColor(255, 255, 255));
	//（横手前下）
	DrawLine3D(P5, P6, GetColor(255, 255, 255));
	//（横手前右）
	DrawLine3D(P2, P6, GetColor(255, 255, 255));
	//（横手前左）
	DrawLine3D(P1, P5, GetColor(255, 255, 255));
	//（横奥上）
	DrawLine3D(P3, P4, GetColor(255, 255, 255));
	//（横奥下）
	DrawLine3D(P7, P8, GetColor(255, 255, 255));
	//（横奥右）
	DrawLine3D(P4, P8, GetColor(255, 255, 255));
	//（横奥左）
	DrawLine3D(P3, P7, GetColor(255, 255, 255));
	//（左側面上）
	DrawLine3D(P1, P3, GetColor(255, 255, 255));
	//（左側面下）
	DrawLine3D(P5, P7, GetColor(255, 255, 255));
	//（右側面上）
	DrawLine3D(P2, P4, GetColor(255, 255, 255));
	//（右側面下）
	DrawLine3D(P6, P8, GetColor(255, 255, 255));


}
