#pragma once

typedef enum {
	Scene_Menu,
	Scene_Difficulty,
	Scene_Game,
	Scene_Help,
	Scene_Credit,
	Scene_Finish,
	Scene_None,
} Scenes;

class SceneChanger {
private:
	int Difficulty;
	Scenes NextScene;
public:
	SceneChanger();
	void ChangeScene(Scenes);
	Scenes Get_Scene();
	void SetDifficulty(int);
	int GetDifficulty();
};