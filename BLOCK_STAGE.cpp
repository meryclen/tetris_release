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
    LoadDivGraph("photo/block.png",20,10,2,32,32,_block_stage.blockHandle);
}

void BLOCK_STAGE::update(){}

void BLOCK_STAGE::draw()
{
    
    for (int i = 0; i < 21;++i)
    {
        for (int j = 0; j < 12; ++j)
        {            
            DrawRotaGraph(48+32 * j, 48+32 * i, 1, 0, _block_stage.blockHandle[_block_stage.stageMap[i][j]], TRUE, FALSE);
        }
    }
}
