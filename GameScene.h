#ifndef _GAMESCENE_H_
#define _GAMESCENE_H_
#include "EffekseerForDXLib.h"
#include "SceneBase.h"

class Camera;
class Player;
class Enemy;
class Stage;
class Shot;
class Bg;
class Wall;
class Ui;

const int enemyNum = 20;
const int wallNum = 4;
const int shotNum = 6;

enum GameState
{
	START = 0
	,PLAY = 1
	,CLEAR = 2
	,END = 3
};


class GameScene : public SceneBase
{
	Player* player;
	Camera* camera;
	Enemy* enemy[enemyNum];
	Stage* stage;
	Shot* shot[shotNum];
	Bg* bg;
	Wall* wall[wallNum];
	Ui* ui;
public:
	GameScene();
	~GameScene();
	//������
	void Init();
	//�X�V
	SceneBase* Update();
	//�`��
	void Draw();

	//�Q�[���V�[���̃Q�[���X�e�[�^�X
	int gameState;
	//�X�^�[�g�֘A
	//�X�e�[�^�X���X�^�[�g�̎��p
	bool startFlag;
	int startCount;
	//�N���A�̎��p
	int clearCount;
	//�Q�[��end�t���O
	bool endFlag = false;
	int endCount;

	//�T�E���h�֘A
	int bgmHandle;
	bool soundFlag = true;
	int clearSeHandle;
	int overSeHandle;
};
#endif

