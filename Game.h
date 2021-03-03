#ifndef _GAME_H_
#define _GAME_H_
#include "EffekseerForDXLib.h"
#include "SceneBase.h"


class Time;

class Game
{

	Time* time;
public:
	~Game();
	//�Q�[�����s
	void Run();
	//�I��
	void ShutDown();
	//�ŏ��̃V�[�����Z�b�g
	void setFirstScene(SceneBase* pScene) { m_nowScene = pScene; }
	//�X�N���[�������Z�b�g
	void setScreen(int width, int height, bool Fullscreen);

	int FrameStartTime;

	//�C���X�^���X
	static Game& GameInstance()
	{
		static Game GameSys;
		return GameSys;
	}


private:
	//--�֐�--//
	//�V���O���g��
	Game();
	//������
	void Init();
	//�X�V
	void Update();
	//�`��
	void Draw();

	//--�ϐ���--//
	// �E�B���h�E���E����
	int       m_screenWidth, m_screenHeight;
	//�t���X�N���[�����ǂ����t���O
	bool      m_FullScreen;
	bool      m_IsGameQuit;

	SceneBase* m_nowScene;

};
#define GAMEINSTANCE Game::GameInstance()
#endif

