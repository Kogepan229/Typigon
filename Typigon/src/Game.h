#pragma once

#include <vector>
#include <string>

class Game {
public:
	static constexpr int MODE_EN = 0;
	static constexpr int MODE_ROMA = 1;
	static bool enableShuffle;
	static bool infiniteLoop;
	static void game(int mode);
private:
	static uint64_t get_rand_range(uint64_t min_val, uint64_t max_val);
	static void shuffle1(std::vector<std::string>& str1, int size);
	static void shuffle2(std::vector<std::string>& str1, std::vector<std::string>& str2, int size);
	static void shuffle(int mode);

	static std::vector<std::string> strEN;
	static std::vector<std::string> strJA;
	static int strNumber;
	static int inputedLetterNum;
	static int missCount;
	static bool finished;
	static void gameRender(int mode, bool finished);
	static void loadString(int mode, std::vector<std::string> &strEN, std::vector<std::string> &strJA);
	static bool splitString(std::string str, std::string splitChar, std::string& splitedStr1, std::string& splitedStr2);
};