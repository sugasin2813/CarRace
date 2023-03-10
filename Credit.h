#pragma once
#include "BaseScene.h"
#include "SceneChanger.h"

class Credit : public BaseScene {
private:
	int back;
	SceneChanger* Changer;

public:
	Credit(SceneChanger*);
	void initialize() override;
	void finalize() override;
	void update() override;
	void draw() override;
};