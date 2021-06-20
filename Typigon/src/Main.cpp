#include "Main.h"
#include "DxLib.h"
#include "Window.h"
#include "Menu.h"
#include "Font.h"

// �v���O������ WinMain ����n�܂�܂�
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_  HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd)
{
	//�R���\�[����ʂ̌Ăяo��
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

	DxLib_End();				// �c�w���C�u�����g�p�̏I������

	return 0;				// �\�t�g�̏I��
}