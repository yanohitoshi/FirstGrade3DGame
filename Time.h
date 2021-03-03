#ifndef _TIME_H_
#define _TIME_H_

#include "EffekseerForDXLib.h"

class Time
{
public:

	~Time();

	void Init();

	void Update1();
	void Update2();
	void Draw();
	void DrawResult();
	int countDown;
	int defeatCount;

	//
	static Time& timeInstance()
	{
		static Time timeInst;
		return timeInst;
	}

private:

	//ƒVƒ“ƒOƒ‹ƒgƒ“
	Time();
	int startTime;
	int tempTime;
	int font;
	int image;
	int resultImage;
	int posX;
	int posY;
};
#define TIME_INSTANCE Time::timeInstance()
#endif

