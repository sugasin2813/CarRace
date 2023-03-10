#include "SceneChanger.h"

SceneChanger::SceneChanger() {
	this->NextScene = Scene_None;
	this->Difficulty = 0;
}

void SceneChanger::ChangeScene(Scenes NextScene) {
	this->NextScene = NextScene;
}

Scenes SceneChanger::Get_Scene() {
	return this->NextScene;
}

void SceneChanger::SetDifficulty(int difficulty) {
	this->Difficulty = difficulty;
}

int SceneChanger::GetDifficulty() {
	return this->Difficulty;
}