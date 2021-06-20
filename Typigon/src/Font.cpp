#include "Font.h"
#include "DxLib.h"

int typigon::font10;
int typigon::font20;
int typigon::font25;
int typigon::font30;
int typigon::font55;

void typigon::initFont() {
	typigon::font10 = DxLib::CreateFontToHandle(NULL, 10, -1, DX_FONTTYPE_ANTIALIASING_4X4);
	typigon::font20 = DxLib::CreateFontToHandle(NULL, 20, -1, DX_FONTTYPE_ANTIALIASING_4X4);
	typigon::font25 = DxLib::CreateFontToHandle(NULL, 25, -1, DX_FONTTYPE_ANTIALIASING_4X4);
	typigon::font30 = DxLib::CreateFontToHandle(NULL, 30, -1, DX_FONTTYPE_ANTIALIASING_4X4);
	typigon::font55 = DxLib::CreateFontToHandle("Bahnschrift", 55, -1, DX_FONTTYPE_ANTIALIASING_4X4);
}