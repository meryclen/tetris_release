#include "main.h"
#include "GAME.h"
#include <DxLib.h>
//using namespace DxLib;


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR IpCmdLine, int nCmdShow)
{

	ChangeWindowMode(TRUE);

	SetGraphMode(1280, 720, 32);

	//垂直同期
	//SetWaitVSyncFlag(FALSE);

	
	SetAlwaysRunFlag(TRUE);

	if (DxLib_Init() == -1)
	{
		return -1;
	}

	SetDrawScreen(DX_SCREEN_BACK);

	
	ScreenFlip();

	int MoveFlag = 1;
	
	while (!(CheckHitKey(KEY_INPUT_SPACE)))
	{
		ClearDrawScreen();
		DrawFormatString(500, 650, GetColor(200, 0, 0), "Press Space Button\n");
		ScreenFlip();
	}
	
	//GAME* g = new GAME();
	{
		GAME gameObject;
		gameObject.run();
	}

	while (!(CheckHitKey((KEY_INPUT_RETURN))))
	{
		ClearDrawScreen();
		DrawFormatString(500, 700, GetColor(200, 0, 0), "エンターキーを押すと終了します\n");
		ScreenFlip();
	}

	
	DxLib_End();

	return _CrtDumpMemoryLeaks();
}

