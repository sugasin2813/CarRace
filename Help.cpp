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
	DxLib::ChangeFont("�l�r ����");
	DxLib::ChangeFontType(DX_FONTTYPE_ANTIALIASING_EDGE);
	DxLib::DrawFormatString(280, 30, DxLib::GetColor(255, 0, 0), "�w���v");

	DxLib::SetFontSize(20);
	if (this->page == 0) {
		DxLib::DrawFormatString(20, 70, DxLib::GetColor(255, 0, 0), "�Q�[������");
		DxLib::DrawFormatString(30, 120, DxLib::GetColor(255, 0, 0), "�\���L�[����ɂ��J�[���[�X�Q�[�ł��B");
		DxLib::DrawFormatString(30, 170, DxLib::GetColor(255, 0, 0), "���̎ԂɂԂ���Ȃ��悤�ɃS�[����ڎw���Ă��������I");

		DxLib::DrawFormatString(20, 240, DxLib::GetColor(255, 0, 0), "��{����");
		DxLib::DrawFormatString(30, 290, DxLib::GetColor(255, 0, 0), "�� ���L�[:���E�ړ�");
		DxLib::DrawFormatString(30, 340, DxLib::GetColor(255, 0, 0), "�� ���L�[:�㉺�ړ�");

		DxLib::SetFontSize(20);
		DxLib::DrawFormatString(30, 450, DxLib::GetColor(255, 0, 0), "Backspace:���j���[���");
	}
	
}