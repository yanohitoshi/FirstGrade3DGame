#ifndef _SYSTEM_H_
#define _SYSTEM_H_

#include "EffekseerForDXLib.h"


//定数
const float GRAVITY_ACCEL = 0.20f;

//当たり判定（矩形）
bool IsHit(float posX1, float posY1, float posZ1, float posX2, float posY2, float posZ2, float sizeX1, float sizeY1, float sizeZ1, float sizeX2, float sizeY2, float sizeZ2);

//接地当たり判定
bool IsHitGround(float posX1, float posY1, float posZ1, float posX2, float posY2, float posZ2, float sizeX1, float sizeY1, float sizeZ1, float sizeX2, float sizeY2, float sizeZ2);

VECTOR PushBackStage(float posX1, float posY1, float posZ1, float posX2, float posY2, float posZ2, float sizeX1, float sizeY1, float sizeZ1, float sizeX2, float sizeY2, float sizeZ2, float velX, float velY, float velZ);

VECTOR PushBackWall(float posX1, float posY1, float posZ1, float posX2, float posY2, float posZ2, float sizeX1, float sizeY1, float sizeZ1, float sizeX2, float sizeY2, float sizeZ2, float velX, float velY, float velZ);

//矩形描画（制作中のみ)
void DrawLine(float posX1, float posY1, float posZ1, float sizeX1, float sizeY1, float sizeZ1);

//ランダム生成
int GetRandom(int min, int max);


#endif // _SYSTEM_H_
