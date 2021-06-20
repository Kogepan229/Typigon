#include "Menu.h"
#include <string>
#include "DxLib.h"

#include "Window.h"
#include "Key.h"
#include "Font.h"
#include "Game.h"

namespace {
	const int MENU_STR_EN_Y = 250;
	const int MENU_STR_ROMA_Y = MENU_STR_EN_Y + 30;
	const int MENU_STR_SHUFFLE_Y = MENU_STR_ROMA_Y + 50;
	const int MENU_STR_INFI_Y = MENU_STR_SHUFFLE_Y + 30;
	const int MENU_STR_END_Y = MENU_STR_INFI_Y + 50;
}

std::string strBool(bool value) {
	if (value) {
		return "True";
	}
	else {
		return "False";
	}
}

void menuRender(int modeCursor) {
	// �`���ʂ��N���A�@�ŏ�
	DxLib::ClearDrawScreen();

	// �^�C�g���`��
	DxLib::DrawStringToHandle((typigon::windowWidth - DxLib::GetDrawStringWidthToHandle("Typigon", strlen("Typigon"), typigon::font55))/2, 100, "Typigon", DxLib::GetColor(255, 255, 255), typigon::font55);

	// ���j���[�����`��
	std::string menuStrShuffle = "�V���b�t��:" + strBool(Game::enableShuffle);
	std::string menuStrInfi = "�������[�v:" + strBool(Game::infiniteLoop);
	DxLib::DrawStringToHandle(440, MENU_STR_EN_Y, "�p�P�����", DxLib::GetColor(255, 255, 255), typigon::font20);
	DxLib::DrawStringToHandle(440, MENU_STR_ROMA_Y, "���[�}������", DxLib::GetColor(255, 255, 255), typigon::font20);
	DxLib::DrawStringToHandle(440, MENU_STR_SHUFFLE_Y, menuStrShuffle.c_str(), DxLib::GetColor(255, 255, 255), typigon::font20);
	DxLib::DrawStringToHandle(440, MENU_STR_INFI_Y, menuStrInfi.c_str(), DxLib::GetColor(255, 255, 255), typigon::font20);
	DxLib::DrawStringToHandle(440, MENU_STR_END_Y, "�I��", DxLib::GetColor(255, 255, 255), typigon::font20);

	int cursorPositionY = 0;
	switch (modeCursor)
	{
	case 0:cursorPositionY = MENU_STR_EN_Y; break;
	case 1:cursorPositionY = MENU_STR_ROMA_Y; break;
	case 2:cursorPositionY = MENU_STR_SHUFFLE_Y; break;
	case 3:cursorPositionY = MENU_STR_INFI_Y; break;
	case 4:cursorPositionY = MENU_STR_END_Y; break;
	default:break;
	}
	DxLib::DrawStringToHandle(410, cursorPositionY, "��", DxLib::GetColor(255, 255, 255), typigon::font20); // �����`��
	// �`���ʂ�\�Ɂ@�Ō�
	DxLib::ScreenFlip();
}

bool reverseBool(bool value) {
	if (value) {
		return false;
	}
	else {
		return true;
	}
}

void menu() {
	Game::enableShuffle = false;
	Game::infiniteLoop = false;
	int modeCursor = 0;
	while (DxLib::ProcessMessage() == 0) {
		typigon::updateKeyState(); // Key���̍X�V

		// Esc�ŃJ�[�\�����I���̂Ƃ����
		if (typigon::detectKeyInput(KEY_INPUT_ESCAPE)) {
			modeCursor = 4;
		}
		// �I��
		if ((typigon::detectKeyInput(KEY_INPUT_SPACE) || typigon::detectKeyInput(KEY_INPUT_RETURN)) && modeCursor == 4) {
			return;
		}

		// ���[�h�I��
		if (modeCursor > 0 && (typigon::detectKeyInput(KEY_INPUT_W) || typigon::detectKeyInput(KEY_INPUT_UP))) {
			modeCursor--;
		}
		if (modeCursor < 4 && (typigon::detectKeyInput(KEY_INPUT_S) || typigon::detectKeyInput(KEY_INPUT_DOWN))) {
			modeCursor++;
		}

		// ���[�h����
		if ((typigon::detectKeyInput(KEY_INPUT_SPACE) || typigon::detectKeyInput(KEY_INPUT_RETURN)) && modeCursor < 2) {
			Game::game(modeCursor);
		}

		// �ݒ�ύX
		if ((typigon::detectKeyInput(KEY_INPUT_SPACE) || typigon::detectKeyInput(KEY_INPUT_RETURN)) && modeCursor == 2) {
			Game::enableShuffle = reverseBool(Game::enableShuffle);
		}
		if ((typigon::detectKeyInput(KEY_INPUT_SPACE) || typigon::detectKeyInput(KEY_INPUT_RETURN)) && modeCursor == 3) {
			Game::infiniteLoop = reverseBool(Game::infiniteLoop);
		}


		
		

		

		menuRender(modeCursor);
	}
}

