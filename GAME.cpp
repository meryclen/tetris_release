#include "GAME.h"
#include <DxLib.h>
#include "BLOCK_STAGE.h"
#include "BLOCK.h"

#include <vector>
#include <thread>
#include <mutex>

#include <iostream>
#include <fstream>
#include <string>

#include <time.h>

#include <cstdlib>


double _deltaTime = 0.0;
int _previousTime = 0;


//void heavyTask();
//void heavyTask1();


GAME::GAME()
{
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dist(1, 7);
	
	for (int i = 0; i < 1000; ++i)
	{
		random_block[i] = dist(gen);
	}

	
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

	
	int full_array[4] = { -1,-1,-1,-1 };

	
	while (ProcessMessage() == 0)
	{
		int a = 0;
		

		if (CheckHitKey(KEY_INPUT_X) == 0)
			pressX = 0;

		if (CheckHitKey(KEY_INPUT_Z) == 0)
			pressZ = 0;

		if (CheckHitKey(KEY_INPUT_LEFT) == 0)
			pressLeft = 0;

		if (CheckHitKey(KEY_INPUT_RIGHT) == 0)
			pressRight = 0;

		if (CheckHitKey(KEY_INPUT_DOWN) == 0)
			pressDown = 0;
		
		if (CheckHitKey(KEY_INPUT_UP) == 0)
			pressUp = 0;

		ClearDrawScreen();

		if (!(block(0)->get_blockStatus(0)))
		{
			
			isFull = true;

			
			for (int l = 19; l >= 0; --l)
			{
				for (int k = 1; k <= 10; ++k)
				{
					if (isFull && (block_stage()->get_stageMap(l, k) != 18))
					{
						//DrawFormatString(700, 500, GetColor(255, 255, 255), "isFull true");
						isFull = true;
						
					}
					else
					{
						isFull = false;
						//DrawFormatString(700, 600, GetColor(255, 255, 255), "isFull false");
						break;
					}
				}
				if (isFull)
				{
					full_array[a] = l;
					++a;
				}
				isFull = true;
			}


			isFull = false;


			int b = 19;

			if (a != 0)
			for (int i = 19; i >= 0; --i)
			{
				for (int l = 0; l < 4; ++l)
				{
					if (i == full_array[l])
					{
						isFull = true;
						
						break;
					}
				}


				if (!isFull)
				{
					for (int k = 1; k <= 10; ++k)
						block_stage()->set_stageMap1(block_stage()->get_stageMap(i, k), b, k);
												
						--b;
				}
				isFull = false;
			}

			
			delete block(0);
			_block[0] = nullptr;

			
			_block[0] = new BLOCK(this);


			for (int i = 0; i < 4; ++i)
				full_array[i] = -1;


			_block[0]->create();
			_block[0]->init();

									
		}

						

		std::vector<std::thread> threads;
		
		if (a != 0)
		{
			threads.emplace_back(&GAME::kari,this);
			//threads.emplace_back(&heavyTask);
			//threads.emplace_back(&heavyTask1);
			
			for(int i=0; i<1; ++i)
				threads[i].join();

		}

		//threads[0].join();

		//threads.emplace_back(heavyTask);
		//threads[1].join();
		
		
		if (a == 1)
		{
			a = 0;
			PlaySoundMem(block(0)->get_soundHandle(GAME::DON), DX_PLAYTYPE_BACK);
		
			score += 40;
		}

		if (a == 2)
		{
			a = 0;
			PlaySoundMem(block(0)->get_soundHandle(GAME::DON), DX_PLAYTYPE_BACK);
			score += 100;
		}

		if (a == 3)
		{
			a = 0;
			PlaySoundMem(block(0)->get_soundHandle(GAME::DON), DX_PLAYTYPE_BACK);
			score += 300;
		}

		if (a == 4)
		{
			a = 0;
			PlaySoundMem(block(0)->get_soundHandle(GAME::PIRORON), DX_PLAYTYPE_BACK);
			score += 1200;
		}


		sprintf_s(buffer, "SCORE: %d", score);
		DrawStringToHandle(500, 300, buffer, GetColor(255, 127, 127), fontHandle);

		std::ifstream stream("score.txt");
		


		//stream.read((char*)buffer1, sizeof(buffer1));
		//DrawStringToHandle(500, 350, buffer1, GetColor(255, 255, 255), fontHandle);
				


		for (int i = 0; i < 4;++i)
		{
			for (int j = 0; j < 4; ++j)
			{
				if (block(0)->get_block_gh(i, j) == block(0)->get_block_g())
					if (block_stage()->get_stageMap(i + block(0)->get_vecMap_y(), j + block(0)->get_vecMap_x()) != 18)
					{
						gameStatus = 1;
						
					}
				
			}
		}

		_block_stage->draw();


if (gameStatus == 1)
	{
		_block[0]->draw();
		gameStatus = 0;
		
		sprintf_s(buffer, "Game Over");
		DrawStringToHandle(400, 250, buffer, GetColor(255, 127, 127), fontHandle);
		ScreenFlip();
			
	
		time_t jikan = time(NULL);
		struct tm imanojikan {};
		errno_t error;
	
		error = localtime_s(&imanojikan, &jikan);
	
			
		std::ofstream scoreFile("score.txt", std::ios::app);
		scoreFile//(_Filename, std::ios::app) 
			<< jikan << " " << imanojikan.tm_year + 1900 << ":" << imanojikan.tm_mon + 1 << ":" << imanojikan.tm_mday << ":" << imanojikan.tm_hour << ":" << imanojikan.tm_min << ":" << imanojikan.tm_sec << " " << score << std::endl;
		scoreFile.close();
		stream.close();
		break;
		
	}


	_block[0]->update();
	_block[0]->draw();
	
	DrawFormatString(500, 540, GetColor(200, 0, 0), "※スコアのログは、score.txtに出力されます");
	DrawFormatString(500, 600, GetColor(200, 0, 0), "エスケープキーを押した後、エンターキーで終了");
	DrawFormatString(500, 630, GetColor(200, 0, 0), "エスケープキーを押した後、スペースキーで続行");
	
	if (CheckHitKey(KEY_INPUT_ESCAPE))
	{
		bool breakFlagTemp = false;
		
		while (!0)
		{
			if (CheckHitKey(KEY_INPUT_SPACE)) break;
	
				if (CheckHitKey(KEY_INPUT_RETURN))
				{
					breakFlagTemp = true;
					break;
				}
		}
	
		if (breakFlagTemp) break;
	}
	
	
	ScreenFlip();
		}

}


void GAME::kari()
{
	

	for (int i = 0; i < 20; ++i)
		for (int j = 1; j <= 10; ++j)
			block_stage()->set_stageMap(block_stage()->get_stageMap1(i, j), i, j);

	for (int i = 0; i < 20; ++i)
		for (int j = 1; j <= 10; ++j)
			block_stage()->set_stageMap1(18, i, j);
}


/*
void heavyTask()
{
			
		int count = 0;
	
	for (int i = 0; i < 100000000; ++i)
	{
		++count;
	}
		
}

void heavyTask1()
{
	
	int count = 0;

	for (int i = 0; i < 105000000; ++i)
	{
		++count;
	}
		
}
*/