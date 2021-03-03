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

	// プロセス起動準備
	PROCESS_INFORMATION pi = { 0 };
	STARTUPINFO si = { 0 };
	si.cb = sizeof(STARTUPINFO);

	CreateProcess(fullPathexe, (LPSTR)"", NULL, NULL, FALSE, NORMAL_PRIORITY_CLASS, NULL, path, &si, &pi);
}


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPreInst, LPSTR     CmdLine, int CmdShow)
{
	// スクリーンセット
	GAMEINSTANCE.setScreen(1920, 1080, false);
	GAMEINSTANCE.setFirstScene(new TitleScene);

	// DirectX11を使用するようにする。(DirectX9も可)
	// Effekseerを使用するには必ず設定する。
	SetUseDirect3DVersion(DX_DIRECT3D_11);

	// フルスクリーンウインドウの切り替えでリソースが消えるのを防ぐ。
	// Effekseerを使用する場合は必ず設定する。
	SetChangeScreenModeGraphicsSystemResetFlag(FALSE);


	// ゲーム開始
	GAMEINSTANCE.Run();
	//runLauncher("../../");
	return 0;
}

