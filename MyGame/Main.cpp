#include "DxLib.h"
#include "GameControl.h"

int cnt = 0;

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
	
	SetGraphMode(32 * FIELD_X, 32 * FIELD_Y + MARGIN_TOP, 32);
	ChangeWindowMode(TRUE), DxLib_Init(), SetDrawScreen(DX_SCREEN_BACK); //�E�B���h�E���[�h�ύX,������,����ʐݒ�

	GameControl game;
	game.mainControl();
	DxLib_End();
	return 0;
}