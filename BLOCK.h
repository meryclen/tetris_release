#pragma once
#include "GAME_OBJECT.h"
#include "GAME.h"
#include <DxLib.h>


class BLOCK :
    public GAME_OBJECT
{

	//int pressDown = 0;

public:
	struct DATA
	{		

		int blockHandle[20];

		VECTOR vec = VGet(0.0f, 0.0f, 0.0f);
		VECTOR vecMap = VGet(0.0f, 0.0f, 0.0f);

		bool movableX = true;
		bool movableZ = true;
		bool movableLeft = true;
		bool movableRight = true;
		bool movableDown = true;

		//int blockAngle = GAME::BLOCK_ANGLE_0;
		int g = GAME::BLOCK_TYPE_I;
		int h = GAME::BLOCK_ANGLE_0;


		int blockStatus = 1; //0:delete 1:normal 

		int moveFlag;


		int blockMap[GAME::BLOCK_TYPE_NUM][GAME::BLOCK_ANGLE_NUM][4][4] =
		{ {{
				{9,9,9,9},
				{GAME::BLOCK_TYPE_I,0,0,0},
				{9,9,9,9},
				{9,9,9,9}
		},
			{
				{ 9,9,GAME::BLOCK_TYPE_I,9 },
				{9,9,0,9},
				{9,9,0,9},
				{9,9,0,9}
		},
			{
				{9,9,9,9},
				{9,9,9,9},
				{GAME::BLOCK_TYPE_I,0,0,0},
				{9,9,9,9}
		},
			{
				{ 9,GAME::BLOCK_TYPE_I,9,9},
				{9,0,9,9},
				{9,0,9,9},
				{9,0,9,9}
		}
			},
			{
		{
				{9,9,9,9},
				{9,GAME::BLOCK_TYPE_O,1,9},
				{9,1,1,9},
				{9,9,9,9}
		},
			{
				{9,9,9,9},
				{9,GAME::BLOCK_TYPE_O,1,9},
				{9,1,1,9},
				{9,9,9,9}		
		},
			{
				{9,9,9,9},
				{9,GAME::BLOCK_TYPE_O,1,9},
				{9,1,1,9},
				{9,9,9,9}		
		},
			{
				{9,9,9,9},
				{9,GAME::BLOCK_TYPE_O,1,9},
				{9,1,1,9},
				{9,9,9,9}
		}
			},
			{
		{
				{9,9,9,9},
				{9,9,9,9},
				{9,GAME::BLOCK_TYPE_S,2,9},
				{2,2,9,9}
		},
			{
				{9,9,9,9},
				{2,9,9,9},
				{2,GAME::BLOCK_TYPE_S,9,9},
				{9,2,9,9}
		},
			{
				{9,9,9,9},
				{9,2,2,9},
				{2,GAME::BLOCK_TYPE_S,2,9},
				{9,9,9,9}
		},
			{
				{9,9,9,9},
				{9,2,9,9},
				{9,GAME::BLOCK_TYPE_S,2,9},
				{9,9,2,9}
		}
			},
			{
		{
				{9,9,9,9},
				{9,9,9,9},
				{3,GAME::BLOCK_TYPE_Z,9,9},
				{9,3,3,9}
		},
			{
				{9,9,9,9},
				{9,3,9,9},
				{3,GAME::BLOCK_TYPE_Z,9,9},
				{3,9,9,9}
		},
			{
				{9,9,9,9},
				{3,3,9,9},
				{9,GAME::BLOCK_TYPE_Z,3,9},
				{9,9,9,9}
		},
			{
				{9,9,9,9},
				{9,9,3,9},
				{9,GAME::BLOCK_TYPE_Z,3,9},
				{9,3,9,9}
		}
			},
			{
		{
				{9,9,9,9},
				{9,9,9,9},
				{4,GAME::BLOCK_TYPE_J,4,9},
				{9,9,4,9}
		},
			{
				{9,9,9,9},
				{9,4,9,9},
				{9,GAME::BLOCK_TYPE_J,9,9},
				{4,4,9,9}
		},
			{
				{9,9,9,9},
				{4,9,9,9},
				{4,GAME::BLOCK_TYPE_J,4,9},
				{9,9,9,9}
		},
			{
				{9,9,9,9},
				{9,4,4,9},
				{9,GAME::BLOCK_TYPE_J,9,9},
				{9,4,9,9}
		}
			},
			{
		{
				{9,9,9,9},
				{9,9,9,9},
				{5,GAME::BLOCK_TYPE_L,5,9},
				{5,9,9,9}
		},
			{
				{9,9,9,9},
				{5,5,9,9},
				{9,GAME::BLOCK_TYPE_L,9,9},
				{9,5,9,9}
		},
			{
				{9,9,9,9},
				{9,9,5,9},
				{5,GAME::BLOCK_TYPE_L,5,9},
				{9,9,9,9}
		},
			{
				{9,9,9,9},
				{9,5,9,9},
				{9,GAME::BLOCK_TYPE_L,9,9},
				{9,5,5,9}
		}
			},
			{
		{
				{9,9,9,9},
				{9,9,9,9},
				{6,GAME::BLOCK_TYPE_T,6,9},
				{9,6,9,9}
		},
			{
				{9,9,9,9},
				{9,6,9,9},
				{6,GAME::BLOCK_TYPE_T,9,9},
				{9,6,9,9}
		},
			{
				{9,9,9,9},
				{9,6,9,9},
				{6,GAME::BLOCK_TYPE_T,6,9},
				{9,9,9,9}
		},
			{
				{9,9,9,9},
				{9,6,9,9},
				{9,GAME::BLOCK_TYPE_T,6,9},
				{9,6,9,9}
		}
			}				
				
		};
	};


private:

	DATA _block[GAME::BLOCK_TYPE_NUM];

public:
    BLOCK(class GAME*);
    ~BLOCK();

    void create();
    void init();
    void update();
    void draw();

	int get_blockStatus(int i) { return _block[i].blockStatus; }


	int get_block_g() { return _block[0].g; }
	int get_block_gh(int i, int j) { return _block[0].blockMap[_block[0].g][_block[0].h][i][j]; }

	int get_vecMap_x() { return _block[0].vecMap.x; }

	int get_vecMap_y() { return _block[0].vecMap.y; }

};
