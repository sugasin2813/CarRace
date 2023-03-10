#include <iostream>
#include "SceneManager.h"
#include "BaseScene.h"
#include "menu.h"
#include "Difficulty.h"
#include "game.h"
#include "Help.h"
#include "Credit.h"

SceneManager::SceneManager() {
	this->finish = false;
	this->Changer = new SceneChanger();
	this->Scene = (BaseScene*)new menu(this->Changer);
	this->NextScene = Scene_None;
}

void SceneManager::initialize() {
	this->Scene->initialize();
}

void SceneManager::finalize() {
	this->Scene->finalize();
	delete(this->Scene);
}

void SceneManager::update() {
	Scenes Next_Scene = this->Changer->Get_Scene();
	if ( Next_Scene != Scene_None) {
		this->Scene->finalize();
		delete(this->Scene);
		switch (Next_Scene) {
		case Scene_Menu:
			this->Scene = (BaseScene*)new menu(this->Changer);
			break;
		case Scene_Difficulty:
			this->Scene = (BaseScene*)new Difficulty(this->Changer);
			break;
		case Scene_Game:
			this->Scene = (BaseScene*)new Game(this->Changer, this->Changer->GetDifficulty());
			break;
		case Scene_Help:
			this->Scene = (BaseScene*)new Help(this->Changer);
			break;
		case Scene_Credit:
			this->Scene = (BaseScene*)new Credit(this->Changer);
			break;
		case Scene_Finish:
			this->Scene = (BaseScene*)new menu(this->Changer);
			this->finish = true;
			break;
		}
		this->Changer->ChangeScene(Scene_None);
		this->Scene->initialize();
	}
	this->Scene->update();
}

void SceneManager::draw() {
	this->Scene->draw();
}

bool SceneManager::isfinish() {
	return this->finish;
}