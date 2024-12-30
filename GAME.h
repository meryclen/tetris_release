#pragma once
#include <random>
#include <thread>
#include <mutex>



class GAME
{
//public:
	int startTime = 0;
	int previousTime = 0;
	int gameTime = 0;
	int passTime = 0;

	double deltaTime = 0.0;
	//static const int e_passTime = 0;

	int pressX = 0;
	int pressLeft = 0;
	int pressRight = 0;
	int pressDown = 0;
	//int pressDown1 = 0;

	std::random_device rd;
	int random_block[1000];
	int random_block_number = 0;

	//std::thread threads;
	//std::mutex mtx;


public:

	enum BLOCK_TYPE
	{
		//BLOCK_TYPE_NULL,
		BLOCK_TYPE_I,
		BLOCK_TYPE_O,
		BLOCK_TYPE_S,
		BLOCK_TYPE_Z,
		BLOCK_TYPE_J,
		BLOCK_TYPE_L,
		BLOCK_TYPE_T,
		BLOCK_TYPE_NUM

	};

	enum BLOCK_ANGLE
	{
		BLOCK_ANGLE_0,
		BLOCK_ANGLE_90,
		BLOCK_ANGLE_180,
		BLOCK_ANGLE_270,
		BLOCK_ANGLE_NUM
	};


private:
	class BLOCK_STAGE* _block_stage;
	class BLOCK* _block[BLOCK_TYPE_NUM];


public:
	
	GAME();
	~GAME();
	void run();

	class BLOCK_STAGE* block_stage() { return _block_stage; }
	class BLOCK* block(int i) { return _block[i]; }

	//static void updateDeltaTime();

	double getDeltaTime() //const
	{
		return deltaTime;
	}

	int get_startTime() { return startTime; }

	int get_passTime() { return passTime; }
	void set_passTime(int t) { passTime = t; }

	
	int get_pressX() { return pressX; }
	void set_pressX(int n) { pressX = n; }

	int get_pressLeft() { return pressLeft; }
	void set_pressLeft(int n) { pressLeft = n; }

	int get_pressRight() { return pressRight; }
	void set_pressRight(int n) { pressRight = n; }

	int get_pressDown() { return pressDown; }
	void set_pressDown(int n) { pressDown = n; }


	int get_random_block(int i) { return random_block[i]; }


	int get_random_block_number() { return random_block_number; }
	void set_random_block_number(int n) { random_block_number = n; }
};
