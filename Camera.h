#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "EffekseerForDXLib.h"

class Player;

class Camera
{
public:
	Camera();
	~Camera();

	//èâä˙âª
	void Init();
	//çXêV
	void Update(const Player& player);
	void UpdateTitle(const Player& player);
	void SetPos(const VECTOR set) { pos = set; }

private:
	VECTOR pos;
	VECTOR cameraToPlayer;
	VECTOR dir;
	VECTOR vel;
	bool clearFlag = false;
	float speed;
};

#endif // _CAMERA_H_