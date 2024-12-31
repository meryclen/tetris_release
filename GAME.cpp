#include "GAME.h"
#include <DxLib.h>
#include "BLOCK_STAGE.h"
#include "BLOCK.h"
//extern int e_passTime = 0;
#include <vector>
#include <thread>
//#include <mutex>
std::mutex mtx;
//std::vector<std::thread> threads;

void updateDeltaTime();

double _deltaTime = 0.0;
int _previousTime = 0;

//void kari();


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
		
		if (CheckHitKey(KEY_INPUT_UP) == 0)
			pressUp = 0;


		if (!(block(0)->get_blockStatus(0)))
		{
			delete block(0);
			_block[0] = nullptr;
			_block[0] = new BLOCK(this);
			_block[0]->create();
			_block[0]->init();
		}

		//std::thread threads;
		//std::mutex mtx;

		ClearDrawScreen();

		std::thread threads(updateDeltaTime);
		threads.join();

		_block_stage->draw();
		_block[0]->update();
		_block[0]->draw();

		DrawFormatString(500, 650, GetColor(200, 0, 0), "Press Escape Button\n");

		if (CheckHitKey(KEY_INPUT_ESCAPE)) break;

		//threads.join();
		ScreenFlip();
	}

}

void updateDeltaTime()
{
	//mtx.lock();
	//int now = GetNowCount();
	//deltaTime = (now - previousTime) / 1000.0;
	//deltaTime = (now - previousTime) / 1000.0;
	//previousTime = now;

	int now = GetNowCount();
	_deltaTime = (now - _previousTime) / 1000.0;
	_previousTime = now;

	DrawFormatString(700, 250, GetColor(255, 255, 255), "debug: deltaTime: %ld", _deltaTime);
	DrawFormatString(700, 270, GetColor(255, 255, 255), "debug: deltaTime: %f", _deltaTime);
	DrawFormatString(700, 300, GetColor(255, 255, 255), "debug: fps?: %d", (int)(1.0/_deltaTime));

	//mtx.unlock();
}

//void kari()
//{
//	getGame()->block_stage()->draw();
//	_block[0]->update();
//	_block[0]->draw();
//}