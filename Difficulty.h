#pragma once
#include "BaseScene.h"
#include "SceneChanger.h"

typedef struct {
	int x, y;
	char level[256];
} DifficultyElement_t;

class Difficulty : public BaseScene {
private:
	int back, SelectNum, Key[256], FigureDifficulty;
	DifficultyElement_t* DifficultyElement;
	SceneChanger* Changer;

public:
	Difficulty(SceneChanger*);
	void initialize() override;
	void finalize() override;
	void update() override;
	void draw() override;
	int gpUpdateKey();
};