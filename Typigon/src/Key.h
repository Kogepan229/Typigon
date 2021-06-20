#pragma once
#include <string>

namespace typigon {
	extern void updateKeyState();
	extern bool detectKeyInput(int DXkeyCode);
	extern bool checkInputLetter(std::string letter);
	extern bool checkMissType(std::string trueLetter);
}
