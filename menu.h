#pragma once
#include "BaseScene.h"
#include "SceneChanger.h"

typedef struct {
	int x, y;
	char name[128];
} MenuElement_t;

class menu : public BaseScene{
private:
	int back, SelectNum, Key[256],FigureMenu;
	MenuElement_t* MenuElement;
	SceneChanger* Changer;

public:
	menu(SceneChanger *);
	void initialize() override;
	void finalize() override;
	void update() override;
	void draw() override;
	int gpUpdateKey();
};