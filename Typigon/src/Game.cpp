#include "Game.h"
#include <string>
#include <iostream>
#include <vector>
#include <random>
#include "DxLib.h"

#include "Window.h"
#include "Key.h"
#include "Font.h"

bool Game::enableShuffle;
bool Game::infiniteLoop;

std::vector<std::string> Game::strEN;
std::vector<std::string> Game::strJA;
int Game::strNumber;
int Game::inputedLetterNum;
int Game::missCount;
bool Game::finished;

// シャッフル系
uint64_t Game::get_rand_range(uint64_t min_val, uint64_t max_val) {
	// 乱数生成器
	std::random_device rand;

	// [min_val, max_val] の一様分布整数 (int) の分布生成器
	std::uniform_int_distribution<uint64_t> get_rand_uni_int(min_val, max_val);

	// 乱数を生成
	return get_rand_uni_int(rand);
}
void Game::shuffle1(std::vector<std::string>& str1, int size) {
	for (int i = 0; i < size; i++) {
		int r = Game::get_rand_range(i, size-1);

		std::string tmp1 = str1[i];
		str1[i] = str1[r];
		str1[r] = tmp1;
	}
}
void Game::shuffle2(std::vector<std::string>& str1, std::vector<std::string>& str2, int size) {
	for (int i = 0; i < size; i++) {
		int r = Game::get_rand_range(i, size-1);

		std::string tmp1 = str1[i];
		str1[i] = str1[r];
		str1[r] = tmp1;

		std::string tmp2 = str2[i];
		str2[i] = str2[r];
		str2[r] = tmp2;
	}
}
void Game::shuffle(int mode) {
	if (Game::enableShuffle) {
		if (mode == Game::MODE_EN) {
			std::cout << "EN_Shuffle" << std::endl;
			Game::shuffle1(Game::strEN, Game::strEN.size());
		}
		if (mode == Game::MODE_ROMA) {
			std::cout << "Roma_Shuffle" << std::endl;
			Game::shuffle2(Game::strEN, Game::strJA, Game::strEN.size());
		}
	}
}

void Game::game(int mode) {

	Game::strNumber = 0;
	Game::inputedLetterNum = 0;
	Game::missCount = 0;
	Game::finished = false;

	Game::loadString(mode, Game::strEN, Game::strJA); // テキストファイルから文字列をよみこみ

	if (strEN.size() == 0) {
		return;
	}

	shuffle(mode); // シャッフル

	while (DxLib::ProcessMessage() == 0) {

		typigon::updateKeyState(); // キー情報の更新

		// ミスタイプを判定
		if (typigon::checkMissType(Game::strEN[Game::strNumber].substr(inputedLetterNum, 1))) {
			Game::missCount++;
		}
		// 正しい入力を判定
		if (typigon::checkInputLetter(Game::strEN[Game::strNumber].substr(inputedLetterNum, 1))) {
			inputedLetterNum++;
		}
		// 文字列を入力し終わったら、次の文字列へ
		if (Game::inputedLetterNum == strlen(Game::strEN[Game::strNumber].c_str()) && Game::strNumber < strEN.size()-1) {
			Game::strNumber++;
			Game::inputedLetterNum = 0;
		}
		// Finish
		if (Game::inputedLetterNum == strlen(Game::strEN[Game::strNumber].c_str()) && Game::strNumber == strEN.size() - 1) {
			if (Game::infiniteLoop) {
				Game::strNumber = 0;
				Game::inputedLetterNum = 0;
				shuffle(mode);
			}
			else {
				Game::finished = true;
			}
		}
		// Escでメニューに戻る
		if (typigon::detectKeyInput(KEY_INPUT_ESCAPE)) {
			return;
		}

		gameRender(mode, false);
	}
}

void Game::gameRender(int mode, bool finished) {
	// 描画画面をクリア　最初
	DxLib::ClearDrawScreen();

	int strDrawWidth;
	int strDrawX;

	strDrawWidth = DxLib::GetDrawStringWidthToHandle(Game::strEN[Game::strNumber].c_str(), strlen(Game::strEN[Game::strNumber].c_str()), typigon::font30); // 描画する文字列の幅を取得
	strDrawX = (typigon::windowWidth - strDrawWidth) / 2; // 文字列の描画開始X座標

	unsigned int color = DxLib::GetColor(255, 255, 255); // 文字の色

	// 文字描画EN
	for (int i = 0; i < Game::strEN[Game::strNumber].size(); i++) {
		// 入力した文字に色をつける
		if (Game::inputedLetterNum != 0 && i < Game::inputedLetterNum) {
			color = DxLib::GetColor(0, 0, 255); // 青
		}
		else {
			color = DxLib::GetColor(255, 255, 255); // 白
		}
		
		std::string drawStr = Game::strEN[Game::strNumber].substr(i, 1); // 描画する1文字を取得
		DxLib::DrawStringToHandle(strDrawX, 280, drawStr.c_str(), color, typigon::font30); // 描画
		strDrawX += DxLib::GetDrawStringWidthToHandle(drawStr.c_str(), 1, typigon::font30); // 描画した分X座標をずらす
		
	}

	// 文字描画JA
	if (mode == Game::MODE_ROMA) {
		strDrawWidth = DxLib::GetDrawStringWidthToHandle(Game::strJA[Game::strNumber].c_str(), strlen(Game::strJA[Game::strNumber].c_str()), typigon::font30); // 描画する文字列の幅を取得
		strDrawX = (typigon::windowWidth - strDrawWidth) / 2; // 文字列の描画開始X座標
		DxLib::DrawStringToHandle(strDrawX, 220, Game::strJA[Game::strNumber].c_str(), DxLib::GetColor(255, 255, 255), typigon::font30);
	}

	// モード表示
	if (mode == Game::MODE_EN) {
		DxLib::DrawStringToHandle(10, 10, "英単語入力", GetColor(255, 255, 255), typigon::font25);
	}
	if (mode == Game::MODE_ROMA) {
		DxLib::DrawStringToHandle(10, 10, "ローマ字入力", GetColor(255, 255, 255), typigon::font25);
	}

	// Menuに戻る説明
	DxLib::DrawStringToHandle(10, typigon::windowHeight - 30, "Escでメニューに戻る", GetColor(255, 255, 255), typigon::font20);

	// ミス回数表示
	DxLib::DrawStringToHandle(600, 10, ("ミス:" + std::to_string(Game::missCount)).c_str(), GetColor(255, 255, 255), typigon::font30);

	// Finished表示
	if (Game::finished) {
		DxLib::DrawStringToHandle((typigon::windowWidth - DxLib::GetDrawStringWidthToHandle("Finished", strlen("Finished"), typigon::font30))/2, 400, "Finished", GetColor(0, 255, 0), typigon::font30);
	}

	// 描画画面を表に　最後
	DxLib::ScreenFlip();
}

// テキストファイルから文字列を読み込む
void Game::loadString(int mode, std::vector<std::string> &strEN, std::vector<std::string> &strJA) {
	strEN.clear();
	strJA.clear();

	if (mode == Game::MODE_EN) {
		int fileEN = DxLib::FileRead_open("TypeString\\EN.txt");
		std::cout << "load_EN_File:" << fileEN << std::endl;

		while (DxLib::FileRead_eof(fileEN) == 0) {
			char str[256];
			DxLib::FileRead_gets(str, 256, fileEN);
			strEN.push_back(str);
		}
		DxLib::FileRead_close(fileEN);
	}
	else if (mode == Game::MODE_ROMA) {
		int fileRoma = DxLib::FileRead_open("TypeString\\Roma.txt");
		std::cout << "load_Roma_File:" << fileRoma << std::endl;

		while (DxLib::FileRead_eof(fileRoma) == 0) {
			char str[256];
			DxLib::FileRead_gets(str, 256, fileRoma);

			std::string s_JA, s_EN;
			if (Game::splitString(str, ",", s_JA, s_EN)) {
				strJA.push_back(s_JA);
				strEN.push_back(s_EN);
			}
		}
		DxLib::FileRead_close(fileRoma);
	}
}

// 文字列strをsplitCharでくぎり、splitedStr1、splitedStr2に代入する
bool Game::splitString(std::string str, std::string splitChar, std::string& splitedStr1, std::string& splitedStr2) {
	int first = 0;
	int splitCharIndex = str.find_first_of(splitChar);
	if (splitCharIndex == std::string::npos) {
		return false;
	}

	splitedStr1 = str.substr(first, splitCharIndex);
	splitedStr2 = str.substr((size_t)splitCharIndex + 1, str.length() - splitCharIndex);
	return true;
}




