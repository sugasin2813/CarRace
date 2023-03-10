#include "DxLib.h"
#include "Difficulty.h"
#include "SceneChanger.h"

Difficulty::Difficulty(SceneChanger* Changer) : BaseScene(){
	this->back = DxLib::LoadGraph("./img/menu.jpg");
	this->SelectNum = 0;
	this->FigureDifficulty = 1;
	this->DifficultyElement = new DifficultyElement_t[this->FigureDifficulty];
	this->DifficultyElement[0] = { 80,100, "‰‹‰" };
	this->Changer = Changer;
}

void Difficulty::initialize() {
	this->SelectNum = -1;
	DxLib::DrawGraph(0, 0, this->back, FALSE);
}

void Difficulty::finalize() {
	DxLib::DeleteGraph(this->back);
}

void Difficulty::update() {
	if (gpUpdateKey() != 0) finalize();

	if (this->Key[KEY_INPUT_DOWN] == 1) this->SelectNum = (this->SelectNum + 1) % this->FigureDifficulty;
	if (this->Key[KEY_INPUT_UP] == 1) this->SelectNum = (this->SelectNum + this->FigureDifficulty - 1) % this->FigureDifficulty;

	if (DxLib::CheckHitKey(KEY_INPUT_DOWN) == 1 || DxLib::CheckHitKey(KEY_INPUT_UP) == 1) {
		for (int i = 0;i < this->FigureDifficulty;i++) {
			if (i == this->SelectNum) this->DifficultyElement[i].x = 80;
			else this->DifficultyElement[i].x = 100;
		}
	}

	if (DxLib::CheckHitKey(KEY_INPUT_RETURN) == 1 && this->SelectNum == 0) {
		this->Changer->SetDifficulty(this->SelectNum);
		this->Changer->ChangeScene(Scene_Game);
	}

	if (DxLib::CheckHitKey(KEY_INPUT_ESCAPE) == 1) {
		this->Changer->ChangeScene(Scene_Menu);
	}
	
}


void Difficulty::draw() {
	DxLib::DrawGraph(0, 0, this->back, FALSE);
	DxLib::DrawGraph(0, 0, this->back, FALSE);
	DxLib::SetFontSize(40);
	DxLib::ChangeFont("‚l‚r –¾’©");
	DxLib::DrawFormatString(280, 30, DxLib::GetColor(255, 0, 0), "“ïˆÕ“x");
	for (int i = 0; i < this->FigureDifficulty;i++) {
		DxLib::SetFontSize(30);
		DxLib::DrawFormatString(this->DifficultyElement[i].x, this->DifficultyElement[i].y, GetColor(255, 0, 0), this->DifficultyElement[i].level);
	}
}

int Difficulty::gpUpdateKey() {
	char tmpKey[256];
	DxLib::GetHitKeyStateAll(tmpKey);
	for (int i = 0;i < 256;i++) {
		if (tmpKey[i] != 0) this->Key[i]++;
		else this->Key[i] = 0;
	}
	return 0;
}