#pragma once
#include <tuple>
#include "SceneChanger.h"
#include "BaseScene.h"

class Game : public BaseScene{
private:
	int road, *vehicles, goal; // 画像
	int player_x, player_y, life; // プレイヤー
	int npc_x, npc_y, *npcs, *type, number_npc; // NPC
	int max_x, min_x, max_y, min_y, size_x, size_y, speed; // 車
	int goal_x, goal_y; // ゴールテープ
	bool goal_generate, pause;
	int score, difficulty, goal_judge, crash, gameover, gameclear; // ゲーム

	SceneChanger* Changer;
public:
	Game(SceneChanger *,int);
	void initialize() override;
	void finalize() override;
	void update() override;
	void draw() override;
	std::tuple<bool, int> judgement(int*, int, int, int, int, int, int, int);
	std::tuple<int*, int, int*> npc_generate();
};