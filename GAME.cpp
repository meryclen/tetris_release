#include "GAME.h"
#include <DxLib.h>
#include "BLOCK_STAGE.h"
#include "BLOCK.h"

GAME::GAME()
{
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dist(1, 7);
	
	for (int i = 0; i < 1000; ++i)
	{
		random_block[i] = dist(gen);
	}

	//aaa
	_block_stage = new BLOCK_STAGE(this);
	
	for (int i = 0; i < BLOCK_TYPE_NUM; ++i)
	{
		_block[i] = new BLOCK(this);
	}


}

GAME::~GAME()
{
	delete _block_stage;

	for (int i = 0; i < BLOCK_TYPE_NUM; ++i)
	{
		if (_block[i] != nullptr)
			delete _block[i];
	}
}

void GAME::run()
{
	startTime = GetNowCount();

	_block_stage->create();
	_block[0]->create();
	_block[0]->init();


	while (ProcessMessage() == 0)
	{
		if (CheckHitKey(KEY_INPUT_X) == 0)
			pressX = 0;

		if (CheckHitKey(KEY_INPUT_LEFT) == 0)
			pressLeft = 0;

		if (CheckHitKey(KEY_INPUT_RIGHT) == 0)
			pressRight = 0;

		if (CheckHitKey(KEY_INPUT_DOWN) == 0)
			pressDown = 0;
		

		if (!(block(0)->get_blockStatus(0)))
		{
			delete block(0);
			_block[0] = nullptr;
			_block[0] = new BLOCK(this);
			_block[0]->create();
			_block[0]->init();
		}

		updateDeltaTime();

		ClearDrawScreen();


		_block_stage->draw();
		_block[0]->update();
		_block[0]->draw();

		DrawFormatString(500, 650, GetColor(200, 0, 0), "Press Escape Button\n");

		if (CheckHitKey(KEY_INPUT_ESCAPE)) break;

		ScreenFlip();
		
	}

}

void GAME::updateDeltaTime()
{
	int now = GetNowCount();
	deltaTime = (now - previousTime) / 1000.0;
	previousTime = now;
}