#pragma once
#include "BaseScene.h"
#include "SceneChanger.h"

class SceneManager {
private:
	int bgm[2];
	bool finish;
	BaseScene* Scene;
	SceneChanger* Changer;
	Scenes NextScene;
public:
	SceneManager();
	void initialize();
	void finalize();
	void update();
	void draw();
	bool isfinish();
};