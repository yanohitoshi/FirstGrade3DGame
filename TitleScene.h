#ifndef _TITLESCENE_H_
#define _TITLESCENE_H_
#include "EffekseerForDXLib.h"
#include "SceneBase.h"
#include "GameScene.h"
class Camera;
class Player;
class TitleStage;
class Shot;
class TitleBg;
class Ui;
class Enemy;


class TitleScene : public SceneBase
{
	Camera* camera;
	Player* player;
	TitleStage* titleStage;
	Shot* shot[shotNum];
	TitleBg* titleBg;
	Ui* ui;
	Enemy* enemy;
public:
	//�R���X�g���N�^
	TitleScene();
	//�f�X�g���N�^
	~TitleScene();
	//������
	void Init();
	//�X�V
	SceneBase* Update();
	//�`��
	void Draw();

private:
	//�摜�n���h��
	int titleImage;
	int ruleImage;

	//2D�|�W�V����
	int posX;
	int posY;
	//�Q�[���J�n�p�t���O
	int startCount;
	bool startCountFlag = false;

	//�`���[�g���A���摜�\���t���O
	bool imgChangeFlag = false;

	//�T�E���h�֘A
	int bgmHandle;
	bool soundFlag = true;
	int startSEHandle;
	bool startSoundFlag = true;
	int startBottanSEHandle;

	bool startUpFlag = false;

};
#endif

