#include "DxLib.h"
#include "menu.h"
#include "SceneChanger.h"

#define VERSION 1.1

menu::menu(SceneChanger *changer) : BaseScene() {
	this->back = DxLib::LoadGraph("./img/menu.jpg");
	this->SelectNum = 0;
	this->FigureMenu = 4;
	this->MenuElement = new MenuElement_t[this->FigureMenu];
	this->MenuElement[0] = { 80, 150, "ゲームスタート" };
	this->MenuElement[1] = { 100, 220, "ヘルプ" };
	this->MenuElement[2] = { 100, 290, "クレジット" };
	this->MenuElement[3] = { 100, 360, "ゲーム終了" };
	this->Changer = changer;
}

void menu::initialize() {
	this->SelectNum = 0;
	DxLib::DrawGraph(0, 0, this->back, FALSE);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
}

void menu::finalize() {
	DxLib::DeleteGraph(this->back);
}

void menu::update() {
	if (gpUpdateKey() != 0) finalize();

	if (this->Key[KEY_INPUT_DOWN] == 1) this->SelectNum = (this->SelectNum + 1) % this->FigureMenu;
	if (this->Key[KEY_INPUT_UP] == 1) this->SelectNum = (this->SelectNum + this->FigureMenu - 1) % this->FigureMenu;

	if (DxLib::CheckHitKey(KEY_INPUT_DOWN) == 1 || DxLib::CheckHitKey(KEY_INPUT_UP) == 1) {
		for (int i = 0;i < this->FigureMenu;i++) {
			if (i == this->SelectNum) this->MenuElement[i].x = 80;
			else this->MenuElement[i].x = 100;
		}
	}

	if (DxLib::CheckHitKey(KEY_INPUT_RETURN) == 1 && this->SelectNum == 0) this->Changer->ChangeScene(Scene_Difficulty);
	if (DxLib::CheckHitKey(KEY_INPUT_RETURN) == 1 && this->SelectNum == 1) this->Changer->ChangeScene(Scene_Help);
	if (DxLib::CheckHitKey(KEY_INPUT_RETURN) == 1 && this->SelectNum == 2) this->Changer->ChangeScene(Scene_Credit);
	if (DxLib::CheckHitKey(KEY_INPUT_RETURN) == 1 && this->SelectNum == 3) this->Changer->ChangeScene(Scene_Finish);
}


void menu::draw() {
	DxLib::DrawGraph(0, 0, this->back, FALSE);
	DxLib::SetFontSize(40);
	DxLib::ChangeFont("ＭＳ 明朝");
	DxLib::ChangeFontType(DX_FONTTYPE_ANTIALIASING_EDGE);
	DxLib::DrawFormatString(30, 50, GetColor(255, 0, 0), "避けろ！炎のカーレース");
	DxLib::SetFontSize(15);
	DxLib::DrawFormatString(520, 68, GetColor(255, 0, 0), "Ver %.1f", VERSION);
	DxLib::SetFontSize(40);

	DxLib::SetFontSize(30);
	for (int i = 0; i < this->FigureMenu;i++) {
		DxLib::DrawFormatString(this->MenuElement[i].x, this->MenuElement[i].y, GetColor(255, 0, 0), this->MenuElement[i].name);
	}	
}

int menu::gpUpdateKey() {
	char tmpKey[256];
	DxLib::GetHitKeyStateAll(tmpKey);
	for (int i = 0;i < 256;i++) {
		if (tmpKey[i] != 0) this->Key[i]++;
		else this->Key[i] = 0;
	}
	return 0;
}