#include "Ui.h"
#include "Time.h"


Ui::Ui()
{
}


Ui::~Ui()
{
}

void Ui::Init()
{
	posx = 0;
	posy = 990;
	flashPosX1 = 0;
	flashPosY1 = 0;
	flashPosX2 = 1980;
	flashPosY2 = 1080;
	countPosx = 0;
	countPosy = 0;

	image = LoadGraph("data/texture/tutorial.png");
	countImage1 = LoadGraph("data/texture/1.png");
	countImage2 = LoadGraph("data/texture/2.png");
	countImage3 = LoadGraph("data/texture/3.png");
	FlashingImage = LoadGraph("data/texture/Flashing.png");
	startImage = LoadGraph("data/texture/START.png");
	count = 0;
	flashCount = 0;
	extend = 1;
	extendCount = 0;
}
void Ui::Update()
{
	++count;
}
void Ui::Draw()
{
	DrawGraph(posx, posy, image, true);
}
void Ui::countDraw()
{
	if (count >= 0 && count <= 60)
	{
		DrawGraph(countPosx, countPosy, countImage3, true);
	}
	if (count >= 61 && count <= 120)
	{
		DrawGraph(countPosx, countPosy, countImage2, true);
	}
	if (count >= 121 && count <= 180)
	{
		DrawGraph(countPosx, countPosy, countImage1, true);
	}
	if (count >= 181 && count <= 240)
	{
		DrawGraph(countPosx, countPosy, startImage, true);
	}
}
void Ui::playDraw()
{
	if (TIME_INSTANCE.countDown <= 5)
	{
		if (flashCount >= 30 && flashCount <= 60)
		{
			DrawExtendGraph(flashPosX1, flashPosY1, flashPosX2 * extend, flashPosY2 * extend, FlashingImage, true);
			if (flashCount == 60)
			{
				flashCount = 0;
				//extend = 1;
			}
		}
		++flashCount;
	}
}


