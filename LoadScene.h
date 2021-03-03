#ifndef _LOADSCENE_H_
#define _LOADSCENE_H_
#include "EffekseerForDXLib.h"
#include "SceneBase.h"

class LoadScene : public SceneBase
{
public:
	LoadScene();
	~LoadScene();
	//������
	void Init();
	//�X�V
	SceneBase* Update();
	//�`��
	void Draw();


private:
	//�摜�n���h��
	int loadImage;
	//�|�W�V����
	int posx;
	int posy;

};
#endif
