#ifndef _CLEARSCENE_H_
#define _CLEARSCENE_H_
#include "EffekseerForDXLib.h"
#include "SceneBase.h"

class ClearScene : public SceneBase
{
public:
	ClearScene();
	~ClearScene();
	//������
	void Init();
	//�X�V
	SceneBase* Update();
	//�`��
	void Draw();


private:
	//�摜�n���h��
	int clearImage;
	//�|�W�V����
	int posx;
	int posy;

	//�T�E���h�֘A
	int bgmHandle;
	bool soundFlag = true;

};
#endif

