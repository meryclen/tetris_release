#include "BLOCK_STAGE.h"
#include <DxLib.h>
#include "GAME.h"
#include "BLOCK.h"

BLOCK_STAGE::BLOCK_STAGE(class GAME* game):
    GAME_OBJECT(game)
{
}

BLOCK_STAGE::~BLOCK_STAGE(){}

void BLOCK_STAGE::create()
{
    //LoadGraph("/photo/block.png",blockHandle)
    LoadDivGraph("photo/block.png",20,10,2,32,32,_block_stage.blockHandle);
}

void BLOCK_STAGE::update(){}

void BLOCK_STAGE::draw()
{
    //DrawRotaGraph(300, 300, 2, 0, _block_stage.blockHandle[5], TRUE, FALSE);

    for (int i = 0; i < 21;++i)
    {
        for (int j = 0; j < 12; ++j)
        {
            //if(_block_stage.map[i][j] == 10)
            //DrawFormatString(700, 300, GetColor(255, 255, 255), "i: %d",i);
            //DrawFormatString(700, 350, GetColor(255, 255, 255), "j: %d", j);
            /*ScreenFlip();
            while (1)
                if (CheckHitKey(KEY_INPUT_SPACE)) break;

            while (1)
                if (CheckHitKey(KEY_INPUT_RETURN)) break;*/
            //ScreenFlip();
            DrawRotaGraph(48+32 * j, 48+32 * i, 1, 0, _block_stage.blockHandle[_block_stage.stageMap[i][j]], TRUE, FALSE);
        }
    }
}
