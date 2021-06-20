#include "Window.h"
#include "DxLib.h"

int typigon::windowWidth = 1000;
int typigon::windowHeight = 600;

int typigon::dxlib_init() {
	// -1ÇreturnÇ≈ÉAÉvÉäèIóπ

	DxLib::ChangeWindowMode(TRUE);
	DxLib::SetGraphMode(typigon::windowWidth, typigon::windowHeight, 16);
	DxLib::SetMainWindowText("Typigon");
	DxLib::SetDrawScreen(DX_SCREEN_BACK);

	if (DxLib_Init() == -1){
		return -1;
	}

	return 0;
}
