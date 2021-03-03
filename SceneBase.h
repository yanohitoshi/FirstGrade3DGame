#ifndef _SCENEBASE_H_
#define _SCENEBASE_H_
#include "EffekseerForDXLib.h"

class SceneBase
{
public:
	SceneBase() {};
	virtual      ~SceneBase() {};

	virtual       SceneBase*  Update() = 0;
	virtual void  Init() = 0;
	virtual void  Draw() = 0;
};
#endif
