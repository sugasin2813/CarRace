#include "DxLib.h"
#include "Help.h"
#include "BaseScene.h"
#include "SceneChanger.h"

Help::Help(SceneChanger* Changer) : BaseScene() {
	this->Changer = Changer;
	this->back = DxLib::LoadGraph("./img/menu.jpg");
	this->page = 0;
}

void Help::initialize() {

}

void Help::finalize() {
	DxLib::DeleteGraph(this->back);
}

void Help::update() {
	if (DxLib::CheckHitKey(KEY_INPUT_BACK) == 1) Changer->ChangeScene(Scene_Menu);
}

void Help::draw() {
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);
	DxLib::DrawGraph(0, 0, this->back, FALSE);

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
	DxLib::SetFontSize(30);
	DxLib::ChangeFont("ＭＳ 明朝");
	DxLib::ChangeFontType(DX_FONTTYPE_ANTIALIASING_EDGE);
	DxLib::DrawFormatString(280, 30, DxLib::GetColor(255, 0, 0), "ヘルプ");

	DxLib::SetFontSize(20);
	if (this->page == 0) {
		DxLib::DrawFormatString(20, 70, DxLib::GetColor(255, 0, 0), "ゲーム説明");
		DxLib::DrawFormatString(30, 120, DxLib::GetColor(255, 0, 0), "十字キー操作によるカーレースゲーです。");
		DxLib::DrawFormatString(30, 170, DxLib::GetColor(255, 0, 0), "他の車にぶつからないようにゴールを目指してください！");

		DxLib::DrawFormatString(20, 240, DxLib::GetColor(255, 0, 0), "基本操作");
		DxLib::DrawFormatString(30, 290, DxLib::GetColor(255, 0, 0), "← →キー:左右移動");
		DxLib::DrawFormatString(30, 340, DxLib::GetColor(255, 0, 0), "↑ ↓キー:上下移動");

		DxLib::SetFontSize(20);
		DxLib::DrawFormatString(30, 450, DxLib::GetColor(255, 0, 0), "Backspace:メニュー画面");
	}
	
}