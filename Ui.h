#ifndef _UI_H_
#define _UI_H_
#include "EffekseerForDXLib.h"
class Ui
{
public:
	Ui();
	~Ui();

	void Init();
	void Update();
	void Draw();
	void countDraw();
	void playDraw();


private:
	//画像ハンドル
	int image;
	//ポジション
	int posx;
	int posy;
	//カウントダウン用
	int countPosx;
	int countPosy;
	int countImage1;
	int	countImage2;
	int countImage3;
	//int countImage4;
	//int countImage5;
	int startImage;
	int FlashingImage;
	int count;
	//点滅
	int extendCount;
	int extend;
	int flashCount;
	int flashPosX1;
	int flashPosY1;
	int flashPosX2;
	int flashPosY2;

};
#endif
