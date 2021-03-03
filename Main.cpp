#include "EffekseerForDXLib.h"
#include "Game.h"
#include "GameScene.h"
#include "TitleScene.h"
#include "OverScene.h"
#include "ClearScene.h"


void runLauncher(const char* path)
{

	char fullPathexe[512];
#pragma warning (disable:4996)
	sprintf(fullPathexe, "%s%s", path, "Launcher.exe");

	// �v���Z�X�N������
	PROCESS_INFORMATION pi = { 0 };
	STARTUPINFO si = { 0 };
	si.cb = sizeof(STARTUPINFO);

	CreateProcess(fullPathexe, (LPSTR)"", NULL, NULL, FALSE, NORMAL_PRIORITY_CLASS, NULL, path, &si, &pi);
}


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPreInst, LPSTR     CmdLine, int CmdShow)
{
	// �X�N���[���Z�b�g
	GAMEINSTANCE.setScreen(1920, 1080, false);
	GAMEINSTANCE.setFirstScene(new TitleScene);

	// DirectX11���g�p����悤�ɂ���B(DirectX9����)
	// Effekseer���g�p����ɂ͕K���ݒ肷��B
	SetUseDirect3DVersion(DX_DIRECT3D_11);

	// �t���X�N���[���E�C���h�E�̐؂�ւ��Ń��\�[�X��������̂�h���B
	// Effekseer���g�p����ꍇ�͕K���ݒ肷��B
	SetChangeScreenModeGraphicsSystemResetFlag(FALSE);


	// �Q�[���J�n
	GAMEINSTANCE.Run();
	//runLauncher("../../");
	return 0;
}

