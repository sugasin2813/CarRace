#include <random>
#include <tuple>
#include "game.h"
#include "DxLib.h"
#include "config.h"
#include "SceneChanger.h"

Game::Game(SceneChanger *Changer, int Difficulty) : BaseScene(){
	this->road = 0;
	this->goal = 0;
	this->vehicles = new int[8];

	this->max_x = 290;
	this->min_x = 39;
	this->max_y = 469;
	this->min_y = 0;
	this->size_x = 68;
	this->size_y = 120;
	this->speed = 4;

	this->player_x = 159;
	this->player_y = 348;
	this->life = 3;

	this->npc_x = this->min_x;
	this->npc_y = 0;
	this->npcs = nullptr;
	this->type = nullptr;
	this->number_npc = 0;

	this->score = 0;
	this->difficulty = Difficulty;
	this->goal_judge = 0;

	this->goal_x = 120;
	this->goal_y = -60;
	this->goal_generate = false;

	this->Changer = Changer;
	this->pause = false;
	this->crash = DxLib::LoadSoundMem("./bgm/crash.ogg");
	this->gameclear = DxLib::LoadSoundMem("./bgm/GameClear.ogg");
	this->gameover = DxLib::LoadSoundMem("./bgm/GameOver.ogg");
}

void Game::initialize() {
	// 効果音の設定
	DxLib::ChangeVolumeSoundMem(200, this->crash);
	DxLib::ChangeVolumeSoundMem(100, this->gameclear);
	DxLib::ChangeVolumeSoundMem(100, this->gameover);

	// グラフィックの設定
	this->road = DxLib::LoadGraph("./img/road.jpg");
	this->goal = DxLib::LoadGraph("./img/goal.jpg");
	DxLib::LoadDivGraph("./img/vehicles.png", 8, 4, 2, 589, 902, this->vehicles);
	this->score = 0;
	std::tie(this->npcs, this->number_npc, this->type) = npc_generate();
}

void Game::finalize() {
	DxLib::DeleteGraph(this->road);
	DxLib::DeleteSoundMem(this->crash);
	delete(this->vehicles);
	delete(npcs);
	delete(type);
}

void Game::update() {
	char Key[256];
	if (DxLib::GetHitKeyStateAll(Key) != 0) finalize();

	if (Key[KEY_INPUT_ESCAPE] == 1) {
		Changer->ChangeScene(Scene_Menu);
	}

	if (pause == false) {
		if (Key[KEY_INPUT_LEFT] == 1) {
			if (this->player_x <= this->min_x) this->player_x = this->min_x;
			else this->player_x -= this->speed;
		}

		if (Key[KEY_INPUT_RIGHT] == 1) {
			if (this->player_x >= this->max_x) this->player_x = this->max_x;
			else this->player_x += this->speed;
		}

		if (Key[KEY_INPUT_UP] == 1) {
			if (this->player_y <= this->min_y) this->player_y = this->min_y;
			else this->player_y -= this->speed;
		}

		if (Key[KEY_INPUT_DOWN] == 1) {
			if (this->player_y >= this->max_y) this->player_y = this->max_y;
			else this->player_y += this->speed;
		}

		int crush;
		bool flag = false;
		std::tie(flag, crush) = judgement(this->npcs, this->number_npc, this->player_x, this->player_y, this->npc_x, this->npc_y, this->size_x, this->size_y);
		if (flag == true) {
			this->life--;
			if (this->life < 0) {
				DxLib::PlaySoundMem(this->gameover, DX_PLAYTYPE_BACK);
				this->pause = true;
			}
			else DxLib::PlaySoundMem(this->crash, DX_PLAYTYPE_BACK);
			this->npcs[crush] = NULL;

		}

		if (this->goal_generate == false) this->npc_y += 3;
		if (this->npc_y > this->max_y) {
			int cnt = 0;
			for (int i = 0;i < this->number_npc;i++) {
				if (this->npcs[i] != NULL) cnt++;
			}
			this->score += cnt * 100;
			delete(this->npcs);
			delete(this->type);
			std::tie(this->npcs, this->number_npc, this->type) = npc_generate();
			this->npc_y = -1 * this->size_y;
		}

		if (this->score / 1000 == this->goal_judge + 1) {
			this->goal_generate = true;
			this->goal_judge++;
		}
		if (this->goal_generate == true) {
			std::tie(flag, crush) = judgement(nullptr, NULL, this->player_x, this->player_y, this->goal_x, this->goal_y, this->size_x, this->size_y);
			if (flag) {
				pause = true;
				DxLib::PlaySoundMem(this->gameclear, DX_PLAYTYPE_BACK);
			}
			this->goal_y += 3;
		}
		if (this->goal_y > this->max_y) {
			this->goal_generate = false;
			this->goal_y = -60;
		}
	}
}

void Game::draw() {
	// フォント設定
	DxLib::ChangeFont("ＭＳ 明朝");
	DxLib::ChangeFontType(DX_FONTTYPE_ANTIALIASING_EDGE);
	// 停止中は背景を透過させる
	if (this->pause == true) {
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);
	}

	// 道路とプレーヤーの表示
	DxLib::DrawGraph(0, 1, road, TRUE);
	DxLib::DrawExtendGraph(this->player_x, this->player_y, this->player_x + this->size_x, this->player_y + this->size_y, this->vehicles[0], TRUE);

	// 難易度とスコアの表示
	DxLib::SetFontSize(20);
	if(this->difficulty == 0) DxLib::DrawFormatString(420, 100, DxLib::GetColor(0, 255, 0), "カーレース[初級]");
	DxLib::DrawFormatString(420, 150, DxLib::GetColor(0, 255, 0), "Score: %d", this->score);

	// 残基数の表示
	DxLib::DrawFormatString(420, 200, DxLib::GetColor(0, 255, 0), "Life: ");
	for (int i = 0;i < life;i++) {
		unsigned int color = DxLib::GetColor(0, 255, 0);
		if (life == 3) color = DxLib::GetColor(0, 255, 0);
		else if (life == 2) color = DxLib::GetColor(255, 165, 0);
		else if (life == 1) color = DxLib::GetColor(255, 0, 0);
		DxLib::DrawFormatString(490 + i * 15, 200, color, "・");
	}

	// ゴールの生成
	if (this->goal_generate == true) {
		DxLib::DrawExtendGraph(this->goal_x, this->goal_y, this->goal_x + 150, this->goal_y + 60, this->goal, FALSE);
	}

	// NPCの生成
	if (this->goal_generate == false) {
		for (int i = 0;i < this->number_npc;i++) {
			if (npcs[i] != NULL) {
				DrawExtendGraph(this->npc_x * this->npcs[i], this->npc_y, this->npc_x * this->npcs[i] + this->size_x, this->npc_y + this->size_y, this->vehicles[this->type[i]], TRUE);
			}
		}
	}

	// GAME OVERとGAME CLEARの表示
	if (this->pause == true) {
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
		DxLib::SetFontSize(70);
		if (this->life < 0) DxLib::DrawFormatString(20, 200, DxLib::GetColor(255, 0, 0), "GAME OVER");
		else DxLib::DrawFormatString(20, 200, DxLib::GetColor(0, 255, 0), "GAME CLEAR");
	}
}


std::tuple<bool,int> Game::judgement(int* npcs, int number, int x, int y, int npc_x, int npc_y, int size_x, int size_y) {
	// ゴールの判定
	if (npcs == nullptr) {
		int goal_size_x = 150, goal_size_y = 60;
		if (x > npc_x && x < npc_x + goal_size_x) {
			if (y > npc_y && y < npc_y + goal_size_y) return std::forward_as_tuple(true, NULL);
			else if (y + size_y > npc_y && y + size_y < npc_y + goal_size_y) return std::forward_as_tuple(true, NULL);
		}
		else if (x + size_x > npc_x && x + size_x < npc_x + goal_size_x) {
			if (y > npc_y && y < npc_y + goal_size_y) return std::forward_as_tuple(true, NULL);
			else if (y + size_y > npc_y && y + size_y < npc_y + goal_size_y) return std::forward_as_tuple(true, NULL);
		}
		return std::forward_as_tuple(false, NULL);
	}

	// NPCの衝突判定
	int npc_ori_x, npc_ori_y;
	for (int i = 0;i < number;i++) {
		if (npcs[i] != NULL) {
			npc_ori_x = npc_x * npcs[i];
			npc_ori_y = npc_y;
			if (x > npc_ori_x && x < npc_ori_x + size_x) {
				if (y > npc_ori_y && y < npc_ori_y + size_y) return std::forward_as_tuple(true,i);
				else if (y + size_y > npc_ori_y && y + size_y < npc_ori_y + size_y) return std::forward_as_tuple(true,i);
			}
			else if (x + size_x > npc_ori_x && x + size_x < npc_ori_x + size_x) {
				if (y > npc_ori_y && y < npc_ori_y + size_y) return std::forward_as_tuple(true,i);
				else if (y + size_y > npc_ori_y && y + size_y < npc_ori_y + size_y) return std::forward_as_tuple(true,i);
			}
		}
	}
	return std::forward_as_tuple(false,NULL);
}

// NPC生成
std::tuple<int*, int, int*> Game::npc_generate() {
	int total, randoms, color, * npc, * type;
	std::random_device rnd;
	std::default_random_engine seed(rnd());
	std::uniform_int_distribution<> rand_generate(1, 4);
	std::uniform_int_distribution<> car_generate(1, 7);

	total = rnd() % 3 + 1;
	npc = new int[total];
	type = new int[total];
	for (int i = 0;i < total;i++) {
		while (true) {
			randoms = rand_generate(seed);
			color = car_generate(seed);
			randoms = 2 * randoms - 1;
			if (std::find(npc, npc + i, randoms) == npc + i) {
				npc[i] = randoms;
				type[i] = color;
				break;
			}
		}
	}
	return std::forward_as_tuple(npc, total, type);
}