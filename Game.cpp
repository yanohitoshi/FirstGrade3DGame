#include "Game.h"
#include "Input.h"
#include "Time.h"
#include "EffekseerForDXLib.h"

Game::Game()
	:m_screenWidth(1500)
	, m_screenHeight(800)
	, m_FullScreen(false)
{
}


Game::~Game()
{
}

void Game::setScreen(int width, int height, bool FullScreen)
{
	m_screenWidth = width;
	m_screenHeight = height;
	m_FullScreen = FullScreen;
}


// �V�[���̎��s�i�V�[���ύX�����邩�Ȃ����𔻒f�j
void Game::Update()
{
	//�V�[�������s
	//���̃V�[���Ǝ��̃V�[�����ׂ邽�߂̏���
	SceneBase* tmpScene;
	tmpScene = m_nowScene->Update();

	// Effekseer�ɂ��Đ����̃G�t�F�N�g���X�V����B
	UpdateEffekseer3D();

	//�V�[���̕ύX�͂�������
	if (tmpScene != m_nowScene)
	{
		//�O�̃V�[���̉��
		delete m_nowScene;

		//�V�K�V�[�������̃V�[���ɍ����ւ�
		m_nowScene = tmpScene;
		m_nowScene->Init();
	}
}

void Game::Init()
{
	if (!m_FullScreen)
	{
		ChangeWindowMode(TRUE);
	}
	SetGraphMode(m_screenWidth, m_screenHeight, 32, 60);
	DxLib_Init();   // DX���C�u��������������
	// Effekseer������������B
	// �����ɂ͉�ʂɕ\������ő�p�[�e�B�N������ݒ肷��B
	if (Effekseer_Init(8000) == -1)
	{
		DxLib_End();
	}

	SetMouseDispFlag(true);
	SetDrawScreen(DX_SCREEN_BACK); //�`���𗠉�ʂɐݒ�


}

void Game::Draw()
{
	ClearDrawScreen();

	if (!m_nowScene)
	{
		return;
	}
	m_nowScene->Draw();
	// Effekseer�ɂ��Đ����̃G�t�F�N�g��`�悷��B
	DrawEffekseer3D();

	ScreenFlip();
}

void Game::ShutDown()
{
	delete m_nowScene;

	// Effekseer���I������B
	Effkseer_End();
	//DXLib���I��
	DxLib::DxLib_End();
}


void Game::Run()
{
	//DXLib�̏�����
	Init();

	//�v���O�������[�v�����[�v��Ԃ�
	bool ProgramLooping = true;
	//���݂̃V�[���̏�����
	m_nowScene->Init();

	//���̎��Ԃ�FrameStartTime�ɓ����
	FrameStartTime = GetNowCount();

	TIME_INSTANCE.Init();

	while (ProgramLooping)
	{

		//�U�OFPS�ɂȂ�܂ő҂�
		while(GetNowCount() - FrameStartTime < 1000 / 60){}

		//�t���[���J�n���̎��Ԃ��Ƃ�
		FrameStartTime = GetNowCount();

		if (ProcessMessage() != 0) 
		{
			break;
		}
		if (CheckHitKey(KEY_INPUT_ESCAPE) == 1 || INPUT_INSTANCE.padState.Buttons[XINPUT_BUTTON_BACK] == 1 && INPUT_INSTANCE.prePadState.Buttons[XINPUT_BUTTON_BACK] == 0)
		{
			break;
		}
		TIME_INSTANCE.Update2();
		INPUT_INSTANCE.UpdateKey();
		Update();
		Draw();
	}
	ShutDown();
}
