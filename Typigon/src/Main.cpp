#include "Main.h"
#include "DxLib.h"
#include "Window.h"
#include "Menu.h"
#include "Font.h"

// プログラムは WinMain から始まります
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_  HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd)
{
	//コンソール画面の呼び出し
#if _DEBUG
	AllocConsole();
	FILE* fp;
	freopen_s(&fp, "CONOUT$", "w", stdout);
	freopen_s(&fp, "CONIN$", "r", stdin);
#endif

	Main();
}

int Main() {
	if (typigon::dxlib_init() == -1) {
		return -1;
	}
	typigon::initFont();

	menu();

	DxLib_End();				// ＤＸライブラリ使用の終了処理

	return 0;				// ソフトの終了
}