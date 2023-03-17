#include "DxLib.h"
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
	this->bgm[0] = DxLib::LoadSoundMem("./bgm/menu.ogg");
	this->bgm[1] = DxLib::LoadSoundMem("./bgm/race.wav");
}

void SceneManager::initialize() {
	this->Scene->initialize();
	DxLib::ChangeVolumeSoundMem(100, this->bgm[0]);
	DxLib::ChangeVolumeSoundMem(100, this->bgm[1]);
	DxLib::PlaySoundMem(this->bgm[0], DX_PLAYTYPE_LOOP, TRUE);
}

void SceneManager::finalize() {
	this->Scene->finalize();
	DxLib::DeleteSoundMem(this->bgm[0]);
	DxLib::DeleteSoundMem(this->bgm[1]);
	delete(this->Scene);
}

void SceneManager::update() {
	Scenes Next_Scene = this->Changer->Get_Scene();
	if ( Next_Scene != Scene_None) {
		this->Scene->finalize();
		delete(this->Scene);
		switch (Next_Scene) {
		case Scene_Menu:
			if (DxLib::CheckSoundMem(this->bgm[1]) == 1) {
				DxLib::StopSoundMem(this->bgm[1]);
				DxLib::PlaySoundMem(this->bgm[0], DX_PLAYTYPE_LOOP, TRUE);
			}
			this->Scene = (BaseScene*)new menu(this->Changer);
			break;
		case Scene_Difficulty:
			this->Scene = (BaseScene*)new Difficulty(this->Changer);
			break;
		case Scene_Game:
			if (DxLib::CheckSoundMem(this->bgm[0]) == 1) {
				DxLib::StopSoundMem(this->bgm[0]);
				DxLib::PlaySoundMem(this->bgm[1], DX_PLAYTYPE_LOOP, TRUE);
			}
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