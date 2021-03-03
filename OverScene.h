#ifndef _OVERSCENE_H_
#define _OVERSCENE_H_
#include "EffekseerForDXLib.h"
#include "SceneBase.h"

class OverScene : public SceneBase
{
public:
	OverScene();
	~OverScene();
	//������
	void Init();
	//�X�V
	SceneBase* Update();
	//�`��
	void Draw();


private:
	//�摜�n���h��
	int overImage;
	//�|�W�V����
	int posx;
	int posy;

	//�T�E���h�֘A
	int bgmHandle;
	bool soundFlag = true;

};
#endif

