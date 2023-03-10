#pragma once
#include "BaseScene.h"
#include "SceneChanger.h"

class Help : public BaseScene {
private:
	int back,page;
	SceneChanger* Changer;

public:
	Help(SceneChanger*);
	void initialize() override;
	void finalize() override;
	void update() override;
	void draw() override;
};