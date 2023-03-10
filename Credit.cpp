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
	DxLib::ChangeFont("�l�r ����");
	DxLib::ChangeFontType(DX_FONTTYPE_ANTIALIASING_EDGE);
	DxLib::DrawFormatString(240, 30, DxLib::GetColor(255, 0, 0), "�N���W�b�g");

	DxLib::SetFontSize(20);

	DxLib::DrawFormatString(20, 70, DxLib::GetColor(255, 0, 0), "�Q�[���G���W��");
	DxLib::DrawFormatString(30, 120, DxLib::GetColor(255, 0, 0), "Dx���C�u�����l: https://dxlib.xsrv.jp/");
	//DxLib::DrawFormatString(30, 170, DxLib::GetColor(255, 0, 0), "");

	DxLib::DrawFormatString(20, 240, DxLib::GetColor(255, 0, 0), "�摜");
	DxLib::DrawFormatString(30, 290, DxLib::GetColor(255, 0, 0), "�C���X�gAC�l: https://www.ac-illust.com/");
	//DxLib::DrawFormatString(30, 340, DxLib::GetColor(255, 0, 0), "");

	DxLib::SetFontSize(20);
	DxLib::DrawFormatString(30, 450, DxLib::GetColor(255, 0, 0), "Backspace:���j���[���");
}