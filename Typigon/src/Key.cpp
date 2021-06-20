#include "Key.h"
#include <string>
#include <map>
#include <vector>
#include <DxLib.h>

std::map<std::string, int> letterToKeyCode{
	{"a", KEY_INPUT_A},
	{"b", KEY_INPUT_B},
	{"c", KEY_INPUT_C},
	{"d", KEY_INPUT_D},
	{"e", KEY_INPUT_E},
	{"f", KEY_INPUT_F},
	{"g", KEY_INPUT_G},
	{"h", KEY_INPUT_H},
	{"i", KEY_INPUT_I},
	{"j", KEY_INPUT_J},
	{"k", KEY_INPUT_K},
	{"l", KEY_INPUT_L},
	{"m", KEY_INPUT_M},
	{"n", KEY_INPUT_N},
	{"o", KEY_INPUT_O},
	{"p", KEY_INPUT_P},
	{"q", KEY_INPUT_Q},
	{"r", KEY_INPUT_R},
	{"s", KEY_INPUT_S},
	{"t", KEY_INPUT_T},
	{"u", KEY_INPUT_U},
	{"v", KEY_INPUT_V},
	{"w", KEY_INPUT_W},
	{"x", KEY_INPUT_X},
	{"y", KEY_INPUT_Y},
	{"z", KEY_INPUT_Z},
	{"-", KEY_INPUT_MINUS},
};

std::vector<int> keyCode{
	KEY_INPUT_A,
	KEY_INPUT_B,
	KEY_INPUT_C,
	KEY_INPUT_D,
	KEY_INPUT_E,
	KEY_INPUT_F,
	KEY_INPUT_G,
	KEY_INPUT_H,
	KEY_INPUT_I,
	KEY_INPUT_J,
	KEY_INPUT_K,
	KEY_INPUT_L,
	KEY_INPUT_M,
	KEY_INPUT_N,
	KEY_INPUT_O,
	KEY_INPUT_P,
	KEY_INPUT_Q,
	KEY_INPUT_R,
	KEY_INPUT_S,
	KEY_INPUT_T,
	KEY_INPUT_U,
	KEY_INPUT_V,
	KEY_INPUT_W,
	KEY_INPUT_X,
	KEY_INPUT_Y,
	KEY_INPUT_Z,
	KEY_INPUT_MINUS,
};

char keyStateBuf[256];
char keyStateBufBefore[256];

void typigon::updateKeyState() {
	std::memcpy(keyStateBufBefore, keyStateBuf, 255);
	DxLib::GetHitKeyStateAll(keyStateBuf);
}

bool typigon::detectKeyInput(int DXkeyCode) {
	if (keyStateBuf[DXkeyCode] == 1 && keyStateBufBefore[DXkeyCode] == 0) {
		return true;
	}
	else {
		return false;
	}
}

// 引数に指定された文字のキーが押されている場合true, 押されていない場合はfalseを返す。
bool typigon::checkInputLetter(std::string letter) {
	if (letterToKeyCode[letter] != 0 && keyStateBuf[letterToKeyCode[letter]] == 1 && keyStateBufBefore[letterToKeyCode[letter]] == 0) {
		return true;
	}
	else {
		return false;
	}
}

bool typigon::checkMissType(std::string trueLetter) {
	if (letterToKeyCode[trueLetter] != 0) {
		for (int i = 0; i < keyCode.size();i++) {
			if (keyCode[i] != letterToKeyCode[trueLetter] && keyStateBuf[keyCode[i]] == 1 && keyStateBufBefore[keyCode[i]] == 0) {
				return true;
			}
		}
	}

	return false;
}