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
	//�摜�n���h��
	int image;
	//�|�W�V����
	int posx;
	int posy;
	//�J�E���g�_�E���p
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
	//�_��
	int extendCount;
	int extend;
	int flashCount;
	int flashPosX1;
	int flashPosY1;
	int flashPosX2;
	int flashPosY2;

};
#endif
