#include "DxLib.h"
#include "Credit.h"
#include "BaseScene.h"
#include "SceneChanger.h"

Credit::Credit(SceneChanger* Changer) : BaseScene() {
	this->Changer = Changer;
	this->back = DxLib::LoadGraph("./img/menu.jpg");
}

void Credit::initialize() {

}

void Credit::finalize() {
	DxLib::DeleteGraph(this->back);
}

void Credit::update() {
	if (DxLib::CheckHitKey(KEY_INPUT_BACK) == 1) Changer->ChangeScene(Scene_Menu);
}

void Credit::draw() {
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);
	DxLib::DrawGraph(0, 0, this->back, FALSE);

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
	DxLib::SetFontSize(30);
	DxLib::ChangeFont("ＭＳ 明朝");
	DxLib::ChangeFontType(DX_FONTTYPE_ANTIALIASING_EDGE);
	DxLib::DrawFormatString(240, 30, DxLib::GetColor(255, 0, 0), "クレジット");

	DxLib::SetFontSize(20);
	DxLib::DrawFormatString(20, 70, DxLib::GetColor(255, 0, 0), "ゲームエンジン");

	DxLib::SetFontSize(15);
	DxLib::DrawFormatString(30, 120, DxLib::GetColor(255, 0, 0), "Dxライブラリ様: https://dxlib.xsrv.jp/");

	DxLib::SetFontSize(20);
	DxLib::DrawFormatString(20, 170, DxLib::GetColor(255, 0, 0), "画像");

	DxLib::SetFontSize(15);
	DxLib::DrawFormatString(30, 220, DxLib::GetColor(255, 0, 0), "イラストAC様: https://www.ac-illust.com/");

	DxLib::SetFontSize(20);
	DxLib::DrawFormatString(20, 270, DxLib::GetColor(255, 0, 0), "BGM、効果音");

	DxLib::SetFontSize(15);
	DxLib::DrawFormatString(30, 320, DxLib::GetColor(255, 0, 0), "魔王魂様: https://maou.audio/");
	DxLib::DrawFormatString(30, 370, DxLib::GetColor(255, 0, 0), "Senses Circuit様: https://www.senses-circuit.com/");

	DxLib::SetFontSize(20);
	DxLib::DrawFormatString(30, 450, DxLib::GetColor(255, 0, 0), "Backspace:メニュー画面");
}