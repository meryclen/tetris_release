#include "GAME.h"
#include <DxLib.h>
#include "BLOCK_STAGE.h"
#include "BLOCK.h"
//extern int e_passTime = 0;
#include <vector>
#include <thread>
#include <mutex>

#include <iostream>
#include <fstream>
#include <string>

#include <time.h>

#include <cstdlib>
//std::mutex mtx;
//std::vector<std::thread> threads;

//void updateDeltaTime();

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

	//soundHandle[GAME::DON] = LoadSoundMem("sound/don.mp3");
	
	//scoreFile("score.txt", std::ios::app);
	//Now = std::time(nullptr);
	//std::ifstream stream("score.txt");
}

GAME::~GAME()
{
	delete _block_stage;

	for (int i = 0; i < BLOCK_TYPE_NUM; ++i)
	{
		if (_block[i] != nullptr)
			delete _block[i];
	}
	//std::ofstream scoreFile("score.txt", std::ios::app);
	//scoreFile.close();
	//scoreFile("score.txt", std::ios::app).close();
}

void GAME::run()
{
	startTime = GetNowCount();

	_block_stage->create();
	_block[0]->create();
	_block[0]->init();

	//std::vector<std::vector<int>> Vstage(21, std::vector<int>(12));
	//std::vector<int> full_array(4, 0);

	int full_array[4] = { -1,-1,-1,-1 };

	//scoreFile.close();
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

			//PlaySoundMem(soundHandle[GAME::DON], DX_PLAYTYPE_BACK);


			/*
			
			*/
			

			isFull = true;

			//for (int i = 19; i >= 0; --i)
			//{
			//int a = 0;
			for (int l = 19; l >= 0; --l)
			{
				for (int k = 1; k <= 10; ++k)
				{
					if (isFull && (block_stage()->get_stageMap(l, k) != 18))
					{
						DrawFormatString(700, 500, GetColor(255, 255, 255), "isFull true");
						isFull = true;
						
					}
					else
					{
						isFull = false;
						DrawFormatString(700, 600, GetColor(255, 255, 255), "isFull false");
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

					//isFull = true;

				//for (int j = 1; j <= 10; ++j)
				//{

			isFull = false;


			int b = 19;
			
			for (int i = 19; i >= 0; --i)
			{
				for (int l = 0; l < 4; ++l)
				{
					if (i == full_array[l])
					{
						isFull = true;
						//for (int k = 1; k <= 10; ++k)
							//block_stage()->set_stageMap1(block_stage()->get_stageMap(i - b, k), i, k);
						break;
					}
				}


				if (!isFull)
				{
					for (int k = 1; k <= 10; ++k)
						block_stage()->set_stageMap1(block_stage()->get_stageMap(i, k), b, k);
						DrawFormatString(800, 450, GetColor(255, 255, 255), "b: %d",b);
						DrawFormatString(800, 470, GetColor(255, 255, 255), "i: %d", i);
						if(isFull) DrawFormatString(800, 490, GetColor(255, 255, 255), "isFull : true");
						DrawFormatString(800, 470, GetColor(255, 255, 255), "full_array[0]: %d", full_array[0]);
						DrawFormatString(800, 490, GetColor(255, 255, 255), "full_array[1]: %d", full_array[1]);
						DrawFormatString(800, 510, GetColor(255, 255, 255), "full_array[2]: %d", full_array[2]);
						DrawFormatString(800, 530, GetColor(255, 255, 255), "full_array[3]: %d", full_array[3]);
						//ScreenFlip();
					//while (1)
						DrawFormatString(800, 550, GetColor(255, 255, 255), "bbb: " );
					--b;
				}
				isFull = false;
			}



			/*
				for (int j = 0; j < 4; ++j)
				{
					if (i == full_array[j])
					{
						isFull = true;

						for (int k = 1; k <= 10; ++k)
							block_stage()->set_stageMap1(block_stage()->get_stageMap(i - b, k), i, k);
					}
					b = j + 1;
					break;
				}


				if (!isFull)
				{
					for (int k = 1; k <= 10; ++k)
						block_stage()->set_stageMap1(block_stage()->get_stageMap(i - b, k), i, k);
				}

				isFull = false;
			}


			for (int i = 19; i >= 0; --i)
			{
				for (int j = 0; j < 4; ++j)
				{
					if (i == full_array[j])
					{
						isFull = true;

						for (int k = 1; k <= 10; ++k)
							block_stage()->set_stageMap1(block_stage()->get_stageMap(i - b, k), i, k);
					}
					b = j + 1;
					break;
				}


				if (!isFull)
				{
					for (int k = 1; k <= 10; ++k)
						block_stage()->set_stageMap1(block_stage()->get_stageMap(i - b, k), i, k);
				}

				isFull = false;
			}



			for (int i = 0; i < 20; ++i)
				for (int j=1; j<=10; ++j)
					block_stage()->set_stageMap(block_stage()->get_stageMap1(i,j), i, j);


			


			//int a = 0;
			//int b = 0;
			/*for (int i = 19; i >= 0; --i)
			{
				for (int j = 0; j < 4; ++j)
				{
					if (i == full_array[j])
					{
						isFull = true;
						//++a;
						if (i - j - 1 < 0)
						{
							while(1) if(CheckHitKey(KEY_INPUT_RETURN)) break;
							//for (int k=1; k<=10; ++k)
							//block_stage()->set_stageMap(18, i, k);
						}
						else
						{
							for (int k = 1; k <= 10; ++k)
							block_stage()->set_stageMap(block_stage()->get_stageMap(i - j - 1-a, k), i, k);
						}
					b = j+1;
							break;
					}
				}

				if (!isFull)
				{
					for (int k = 1; k <= 10; ++k)
						block_stage()->set_stageMap(block_stage()->get_stageMap(i - b , k), i, k);
				}

				isFull = false;
			}*/


			
			delete block(0);
			_block[0] = nullptr;

			_block[0] = new BLOCK(this);


			for (int i=0; i<4; ++i)
			full_array[i] = -1;


			_block[0]->create();
			_block[0]->init();			

			

			for (int i = 0; i < 4;++i)
			{
				for (int j = 0; j < 4; ++j)
				{
					if (block(0)->get_block_gh(i, j) == block(0)->get_block_g())
						if (block_stage()->get_stageMap(i + block(0)->get_vecMap_y(), j + block(0)->get_vecMap_x()) != 18)
						{
							gameStatus = 1;
							//_block[0]->update();
							//_block[0]->draw();
							//ScreenFlip();
						}

						//DrawRotaGraph(48 + 32 * j + 32 * (int)_block[0].vecMap.x, 48 + 32 * i + 32 * (int)_block[0].vecMap.y, 1, 0, _block[0].blockHandle[_block[0].blockMap[_block[0].g][_block[0].h][i][j]], TRUE, FALSE);
				}
			}


			/*if (gameStatus == 1)
			{
				DrawFormatString(400, 300, GetColor(255, 255, 255), "Game Over");

			}*/




					/*
					if (isFull)
					{
						if (i - a < 0)
						{
							for (int j = 1; j <= 10; ++j)
							block_stage()->set_stageMap(18, i, j);
						}
						else
						{
							//++a;
							for (int j = 1; j <= 10; ++j)
							block_stage()->set_stageMap(block_stage()->get_stageMap(i - a, j), i, j);
						}
					}
					*/

					/*
					else
					{
						if (i - a < 0)
						{
							for (int j = 1; j <= 10; ++j)
							block_stage()->set_stageMap(18, i, j);
						}
						else
						{
							for (int j = 1; j <= 10; ++j)
							block_stage()->set_stageMap(block_stage()->get_stageMap(i - a, j), i, j);
						}

					}
					*/

				//}
			//}

			

			/*
					
					for (int k = 19; k >= 0; --k)
						for (int l = 1; l <= 10; ++l)
						{
							++a;
							block_stage()->set_stageMap(block_stage()->get_stageMap(i - a, l), k, l);

						}
				}
				else isFull = true;
			}*/


		/*
			int k = 0;


			for (int i = 0; i <= 19; ++i)
			{
				
				for (int j = 1; j <= 10; ++j)
				{
					if (isFull && (block_stage()->get_stageMap(i, j) != 18))
					{
						DrawFormatString(700, 500, GetColor(255, 255, 255), "hitotuOK");
						isFull = true;
					}
					else
					{
						isFull = false;
						DrawFormatString(700, 600, GetColor(255, 255, 255), "kokomadeOK");
						break;
					}

				}
				if (isFull)
				{
					full_array[k] = i;
					++k;
				}
				else isFull = true;
			}


			DrawFormatString(700, 400, GetColor(255, 255, 255), "%d", full_array[0]);
			DrawFormatString(700, 420, GetColor(255, 255, 255), "%d", full_array[1]);
			DrawFormatString(700, 440, GetColor(255, 255, 255), "%d", full_array[2]);
			DrawFormatString(700, 460, GetColor(255, 255, 255), "%d", full_array[3]);
			//DrawFormatString(700, 480, GetColor(255, 255, 255), "%d", full_array[4]);
			
			DrawFormatString(700, 680, GetColor(255, 255, 255), "%d", k);
			DrawFormatString(700, 700, GetColor(255, 255, 255), "%d", full_array.size());

			for (int i = 0; i < 21; ++i)
			{
				for (int j = 0; j < 12; ++j)
				{
					Vstage[i][j] = block_stage()->get_stageMap(i, j);
				}
			}


			//while (1)
			//{
			//	ScreenFlip();
			//	if (CheckHitKey(KEY_INPUT_SPACE)) break;
			//}


			for (int n = 0; n < k; ++n)
			{
				if (full_array[n] - n > 15)
					Vstage.erase(Vstage.begin() + 15);
				else
				Vstage.erase(Vstage.begin() + full_array[n] -n);
				
			}

			for (int n = 0; n < k; ++n)
			{
				Vstage.insert(Vstage.begin(), { 10,18,18,18,18,18,18,18,18,18,18,10 });
			}


			for (int i = 0; i < 4; ++i)
				full_array[i] = 0;


			for (int i = 0; i < 21; ++i)
			{
				for (int j = 0; j < 12; ++j)
				{
					block_stage()->set_stageMap(Vstage[i][j], i, j);
				}
			}


			//while (!CheckHitKey(KEY_INPUT_SPACE))
			//{
				//DrawFormatString(500, 700, GetColor(255, 255, 255), "%s","kokomadeOK");
				//ScreenFlip();
			//}

			//DrawFormatString(500, 700, GetColor(255, 255, 255), "%s","komadeOFF");
			//std::string str = "koko";

				//if (isFull)
				//{
			/*for (int n = 0; n < full_array.size(); ++n)
			{
				for (int m = 1; m <= 10; ++m)
					block_stage()->set_stageMap(18, full_array[n], m);
			}*/
			
			/*
					//for (int k = 19; k >= 0; --k)
					//{
						//for (int l = 1; l <= 10; ++l)
						//{
							//for (int b = 19; b >= 0; --b)
							//{
								//for (int l = 1; l <= 10; ++l)
								//{
									for (int a = full_array.size() - 1; a >= 0; --a)
									{
										for (int b = 19; b >= 0; --b)
										{
											for (int l = 1 ; l <= 10; ++l)
											{
												if (b == full_array[a]) ++zure;
												else
													block_stage()->set_stageMap(block_stage()->get_stageMap(b, l), b + zure, l); //block_stage()->get_stageMap(k, l)
											}
										}
									}
								//}
							//}

						//}
					//}					
				//}				
				*/




			
		}

		DrawFormatString(500, 400, GetColor(255, 255, 255), "kokomadeOKkkkkk");
		//std::thread threads;
		//std::mutex mtx;

		

		//std::thread threads(updateDeltaTime);
		//threads.join();

		_block_stage->draw();
		//DrawFormatString(400, 200, GetColor(255, 255, 255), "Game Over Flag: %d",gameStatus);
		

		
		if (a == 1)
		{
			a = 0;
			PlaySoundMem(block(0)->get_soundHandle(GAME::DON), DX_PLAYTYPE_BACK);
			//isTetris = true;
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
		//stream.open("score.txt", std::ios::in) ;
		//stream >> buffer1;

		//sprintf_s(buffer1, "%s", stream);
		//DrawStringToHandle(500, 350, buffer1, GetColor(255, 255, 255), fontHandle);


		stream.read((char*)buffer1, sizeof(buffer1));
		DrawStringToHandle(500, 350, buffer1, GetColor(255, 255, 255), fontHandle);

		//while (!stream.eof())
		//{
			//int i = 0;
			//for (int i = 0; i < 2; ++i)
			//{
			//stream >> line;
			//stream >> buffer1;
			//std::getline(stream, line);
			//line >> buffer1;
			//sprintf_s(buffer1, "%s", line);
			//sprintf_s(buffer1,line);
			//DrawStringToHandle(500, 350, buffer1, GetColor(255, 255, 255), fontHandle);
			//}
			//}
			//i += 20;
		//}

		//scoreFile("score.txt", std::ios::app);
		//scoreFile.close();
		
		for (int i = 0; i < 20; ++i)
			for (int j = 1; j <= 10; ++j)
				block_stage()->set_stageMap(block_stage()->get_stageMap1(i, j), i, j);



		if (gameStatus == 1)
		{
			_block[0]->draw();
			gameStatus = 0;
			//DrawFormatString(400, 300, GetColor(255, 255, 255), "Game Over");
			sprintf_s(buffer, "Game Over");
			DrawStringToHandle(400, 250, buffer, GetColor(255, 127, 127), fontHandle);
			ScreenFlip();

			//scoreFile(
			//scoreFile("score.txt", std::ios::app);

			time_t jikan = time(NULL);
			struct tm imanojikan {};
			errno_t error;

			error = localtime_s(&imanojikan, &jikan);


			//std::time_t t(NULL);
			//struct tm tim = *localtime(&t);

			//std::time_t* Now;
			//std::time_t time(&Now);
			//time_t 
			//_Filename = "score.txt";
			std::ofstream scoreFile("score.txt", std::ios::app);
			scoreFile//(_Filename, std::ios::app) 
			<< jikan << " " << imanojikan.tm_year + 1900 << ":" << imanojikan.tm_mon + 1 << ":" << imanojikan.tm_mday << ":" << imanojikan.tm_hour << ":" << imanojikan.tm_min << ":" << imanojikan.tm_sec << " " << score << std::endl;
			scoreFile.close();
			stream.close();
			break;
			//if (CheckHitKey(KEY_INPUT_ESCAPE)) break;
		}


		_block[0]->update();
		_block[0]->draw();


		DrawFormatString(500, 650, GetColor(200, 0, 0), "Press Escape Button\n");

		if (CheckHitKey(KEY_INPUT_ESCAPE)) break;

		//threads.join();
		ScreenFlip();
	}

}

//void updateDeltaTime()
//{
//	//mtx.lock();
//	//int now = GetNowCount();
//	//deltaTime = (now - previousTime) / 1000.0;
//	//deltaTime = (now - previousTime) / 1000.0;
//	//previousTime = now;
//
//	int now = GetNowCount();
//	_deltaTime = (now - _previousTime) / 1000.0;
//	_previousTime = now;
//
//	DrawFormatString(700, 250, GetColor(255, 255, 255), "debug: deltaTime: %ld", _deltaTime);
//	DrawFormatString(700, 270, GetColor(255, 255, 255), "debug: deltaTime: %f", _deltaTime);
//	DrawFormatString(700, 300, GetColor(255, 255, 255), "debug: fps?: %d", (int)(1.0/_deltaTime));
//
//	DrawFormatString(700, 330, GetColor(255, 255, 255), "-1 % 4 : %d", -1 % 4);
//	DrawFormatString(700, 350, GetColor(255, 255, 255), "-2 % 4 : %d", -2 % 4);
//	//mtx.unlock();
//}

//void kari()
//{
//	getGame()->block_stage()->draw();
//	_block[0]->update();
//	_block[0]->draw();
//}