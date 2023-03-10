#include <tuple>
#include <random>
#include "DxLib.h"
#include "SceneManager.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	ChangeWindowMode(TRUE);
	if (DxLib_Init() == -1) return -1;
	SetDrawScreen(DX_SCREEN_BACK);

	SceneManager manager = SceneManager::SceneManager();
	manager.initialize();

	while (ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0) {
		manager.update();
		if (manager.isfinish()) break;
		manager.draw();
	}

	manager.finalize();

	DxLib_End();
	return 0;
}

