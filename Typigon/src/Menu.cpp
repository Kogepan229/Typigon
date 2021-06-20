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
	// 描画画面をクリア　最初
	DxLib::ClearDrawScreen();

	// タイトル描画
	DxLib::DrawStringToHandle((typigon::windowWidth - DxLib::GetDrawStringWidthToHandle("Typigon", strlen("Typigon"), typigon::font55))/2, 100, "Typigon", DxLib::GetColor(255, 255, 255), typigon::font55);

	// メニュー文字描画
	std::string menuStrShuffle = "シャッフル:" + strBool(Game::enableShuffle);
	std::string menuStrInfi = "無限ループ:" + strBool(Game::infiniteLoop);
	DxLib::DrawStringToHandle(440, MENU_STR_EN_Y, "英単語入力", DxLib::GetColor(255, 255, 255), typigon::font20);
	DxLib::DrawStringToHandle(440, MENU_STR_ROMA_Y, "ローマ字入力", DxLib::GetColor(255, 255, 255), typigon::font20);
	DxLib::DrawStringToHandle(440, MENU_STR_SHUFFLE_Y, menuStrShuffle.c_str(), DxLib::GetColor(255, 255, 255), typigon::font20);
	DxLib::DrawStringToHandle(440, MENU_STR_INFI_Y, menuStrInfi.c_str(), DxLib::GetColor(255, 255, 255), typigon::font20);
	DxLib::DrawStringToHandle(440, MENU_STR_END_Y, "終了", DxLib::GetColor(255, 255, 255), typigon::font20);

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
	DxLib::DrawStringToHandle(410, cursorPositionY, "▼", DxLib::GetColor(255, 255, 255), typigon::font20); // 文字描画
	// 描画画面を表に　最後
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
		typigon::updateKeyState(); // Key情報の更新

		// Escでカーソルを終了のところに
		if (typigon::detectKeyInput(KEY_INPUT_ESCAPE)) {
			modeCursor = 4;
		}
		// 終了
		if ((typigon::detectKeyInput(KEY_INPUT_SPACE) || typigon::detectKeyInput(KEY_INPUT_RETURN)) && modeCursor == 4) {
			return;
		}

		// モード選択
		if (modeCursor > 0 && (typigon::detectKeyInput(KEY_INPUT_W) || typigon::detectKeyInput(KEY_INPUT_UP))) {
			modeCursor--;
		}
		if (modeCursor < 4 && (typigon::detectKeyInput(KEY_INPUT_S) || typigon::detectKeyInput(KEY_INPUT_DOWN))) {
			modeCursor++;
		}

		// モード決定
		if ((typigon::detectKeyInput(KEY_INPUT_SPACE) || typigon::detectKeyInput(KEY_INPUT_RETURN)) && modeCursor < 2) {
			Game::game(modeCursor);
		}

		// 設定変更
		if ((typigon::detectKeyInput(KEY_INPUT_SPACE) || typigon::detectKeyInput(KEY_INPUT_RETURN)) && modeCursor == 2) {
			Game::enableShuffle = reverseBool(Game::enableShuffle);
		}
		if ((typigon::detectKeyInput(KEY_INPUT_SPACE) || typigon::detectKeyInput(KEY_INPUT_RETURN)) && modeCursor == 3) {
			Game::infiniteLoop = reverseBool(Game::infiniteLoop);
		}


		
		

		

		menuRender(modeCursor);
	}
}

