#include "Time.h"
#include "EffekseerForDXLib.h"


Time::Time()
{
}


Time::~Time()
{
}


void Time::Init()
{
	startTime = 0;
	tempTime = 0;
	countDown = 0;
	defeatCount = 0;
	posX = 960;
	posY = 0;
	image = LoadGraph("data/texture/aaa.png");
	resultImage = LoadGraph("data/texture/result.png");
	font = CreateFontToHandle("ÇcÇeÇoó¨óÍëÃW7", 100, 100, DX_FONTTYPE_NORMAL);
}
void Time::Update1()
{
	startTime = GetNowCount();
}

void Time::Update2()
{
	tempTime = GetNowCount();
	countDown = (startTime - tempTime) / 1000 + 60;
}
void Time::Draw()
{
	DrawGraph(posX - 225, posY, image, true);
	DrawFormatStringToHandle(posX - 225, posY, GetColor(225, 0, 0), font, "écÇËÅF%d", countDown);
}

void Time::DrawResult()
{
	DrawGraph(posX - 400, posY + 700, resultImage, true);
	DrawFormatStringToHandle(posX - 400, posY + 700, GetColor(225, 0, 0), font, "ì|ÇµÇΩêî:%dëÃ!!", defeatCount);
}

