#include "BLOCK.h"
#include "GAME.h"
#include "BLOCK_STAGE.h"
#include <DxLib.h>
//#include "BLOCK_STAGE.h"
//#include "GAME_OBJECT.h"

BLOCK::BLOCK(class GAME* game):
GAME_OBJECT(game){}

BLOCK::~BLOCK() {}

void BLOCK::create()
{
	LoadDivGraph("photo/block.png", 20, 10, 2, 32, 32, _block[0].blockHandle);
}

void BLOCK::init()
{
    //getGame()->block_stage()->set_stageMap(0, _block[0].vecMap.x, _block[0].vecMap.y);


    /*for (int i = 0; i < 4;++i)
    {
        for (int j = 0; j < 4; ++j)
        {
            if (_block[0].blockMap[0][0][i][j] == 0)
                getGame()->block_stage()->set_stageMap(0, 0+i, 4+j);                
        }
    }*/


    _block[0].vecMap.x = 4;
    _block[0].vecMap.y = 0;

    int n = getGame()->get_random_block_number();
    _block[0].g = getGame()->get_random_block(n) % GAME::BLOCK_TYPE_NUM;
    //_block[0].g = getGame()->get_random_block(getGame()->get_random_block_number()) % GAME::BLOCK_TYPE_NUM;
    if (n == 999) n = -1;
    //if (getGame()->get_random_block_number() == 999) getGame()->set_random_block_number(0);
    
    getGame()->set_random_block_number(++n);
    
}

void BLOCK::update()
{
    DrawFormatString(700, 550, GetColor(255, 255, 255), "debug: random_block_number: %d", getGame()->get_random_block_number());
    DrawFormatString(700, 570, GetColor(255, 255, 255), "debug: _block[0].g: %d", _block[0].g);

    if (CheckHitKey(KEY_INPUT_X))
        if (getGame()->get_pressX() == 0)
    {

            for (int i = 0; i < 4;++i)
            {
                for (int j = 0; j < 4; ++j)
                {
                    if (_block[0].blockMap[_block[0].g][(_block[0].h+1)%4][i][j] == _block[0].g)
                        if (getGame()->block_stage()->get_stageMap(i + _block[0].vecMap.y, j + _block[0].vecMap.x) != 18)
                        {
                            _block[0].movableX = false;
                            break;
                        }

                }
                if (!_block[0].movableX) break;

            }

            if (_block[0].movableX)
            {
                //_block[0].vecMap.y += 1;

                _block[0].h = (_block[0].h + 1) % 4;
            }
            else
            {
                _block[0].movableX = true;
            }

                getGame()->set_pressX(1);
    }




    if (CheckHitKey(KEY_INPUT_LEFT))
        if (getGame()->get_pressLeft() == 0)
        {
            for (int i = 0; i < 4;++i)
            {
                for (int j = 0; j < 4; ++j)
                {
                    if (_block[0].blockMap[_block[0].g][_block[0].h][i][j] == _block[0].g)
                        if (getGame()->block_stage()->get_stageMap(i + _block[0].vecMap.y, j + _block[0].vecMap.x - 1) != 18)
                        {
                            _block[0].movableLeft = false;
                            break;
                        }

                }
                if (!_block[0].movableLeft) break;

            }
            if (_block[0].movableLeft)
                _block[0].vecMap.x += -1;
            else _block[0].movableLeft = true;

            getGame()->set_pressLeft(1);
        }

    
    if (CheckHitKey(KEY_INPUT_RIGHT))
        if (getGame()->get_pressRight() == 0)
        {
            for (int i = 0; i < 4;++i)
            {
                for (int j = 0; j < 4; ++j)
                {
                    if (_block[0].blockMap[_block[0].g][_block[0].h][i][j] == _block[0].g)
                        if (getGame()->block_stage()->get_stageMap(i + _block[0].vecMap.y, j + _block[0].vecMap.x + 1) != 18)
                        {
                            _block[0].movableRight = false;
                            break;
                        }

                }
                if (!_block[0].movableRight) break;

            }
            if (_block[0].movableRight)
                _block[0].vecMap.x += 1;
            else _block[0].movableRight = true;

            getGame()->set_pressRight(1);
        }

    
    if (CheckHitKey(KEY_INPUT_DOWN))
        if(getGame()->get_pressDown() == 0)
    {
        for (int i = 0; i < 4;++i)
        {
            for (int j = 0; j < 4; ++j)
            {
                if (_block[0].blockMap[_block[0].g][_block[0].h][i][j] == _block[0].g)
                    if (getGame()->block_stage()->get_stageMap(i + _block[0].vecMap.y + 1, j + _block[0].vecMap.x) != 18)
                    {
                        _block[0].movableDown = false;

                        for (int i = 0; i < 4; ++i) //êœÇ›è„Ç™ÇÈ
                        {
                            for (int j = 0; j < 4; ++j)
                            {
                                if (_block[0].blockMap[_block[0].g][_block[0].h][i][j] == _block[0].g)
                                    getGame()->block_stage()->set_stageMap(_block[0].g, _block[0].vecMap.y + i, _block[0].vecMap.x + j);
                            }
                        }
                        _block[0].blockStatus = 0; //êœÇ›è„Ç™ÇÈ

                        break;
                    }

            }
            if (!_block[0].movableDown) break;
            
        }
        if (_block[0].movableDown)
        _block[0].vecMap.y += 1;
        
        getGame()->set_pressDown(1);
    }


    int now = GetNowCount();
    
    if (now - getGame()->get_passTime() > 1000)//(now - e_passTime() > 1000)
    {
        _block[0].movableDown = true;
        //_block[0].vec.y += 32.0f;
        getGame()->set_passTime(now);

        for (int i = 0; i < 4;++i)
        {
            for (int j = 0; j < 4; ++j)
            {
                if (_block[0].blockMap[_block[0].g][_block[0].h][i][j] == _block[0].g)
                    if (getGame()->block_stage()->get_stageMap(i + _block[0].vecMap.y+1, j + _block[0].vecMap.x) != 18)
                    {
                        _block[0].movableDown = false;

                        for (int i = 0; i < 4; ++i) //êœÇ›è„Ç™ÇÈ
                        {
                            for (int j = 0; j < 4; ++j)
                            {
                                if (_block[0].blockMap[_block[0].g][_block[0].h][i][j] == _block[0].g)
                                    getGame()->block_stage()->set_stageMap(_block[0].g, _block[0].vecMap.y + i, _block[0].vecMap.x + j);
                            }
                        }
                        _block[0].blockStatus = 0; //êœÇ›è„Ç™ÇÈ

                        break;
                    }

            }
            if (!_block[0].movableDown) break;
        }

        //if(_block[0].movableDown) //êœÇ›è„Ç™ÇÁÇ»Ç¢
        _block[0].vecMap.y += 1; //êœÇ›è„Ç™ÇÁÇ»Ç¢
        //else //êœÇ›è„Ç™ÇÈ
        //{
        //    for (int i = 0; i < 4; ++i)
        //    {
        //        for (int j = 0; j < 4; ++j)
        //        {
        //            if (_block[0].blockMap[_block[0].g][_block[0].h][i][j] == _block[0].g)
        //                getGame()->block_stage()->set_stageMap(_block[0].g, _block[0].vecMap.y +i, _block[0].vecMap.x +j);
        //        }
        //    }
        //    _block[0].blockStatus = 0;
        //}

        //_block[0].vecMap.y += 1;
        //getGame()->block_stage()->set_stageMap(0, _block[0].vecMap.y)
    }
}

void BLOCK::draw()
{
    DrawFormatString(500, 500, GetColor(255, 255, 255), "debug");
    DrawRotaGraph(200, 200, 2, 0, _block[0].blockHandle[5], TRUE, FALSE);

    


    for (int i = 0; i < 4;++i)
    {
        for (int j = 0; j < 4; ++j)
        {
            if(_block[0].blockMap[_block[0].g][_block[0].h][i][j] == _block[0].g)
            DrawRotaGraph(48 + 32 * j + 32 * (int)_block[0].vecMap.x, 48 + 32 * i + 32 * (int)_block[0].vecMap.y, 1, 0, _block[0].blockHandle[_block[0].blockMap[_block[0].g][_block[0].h][i][j]], TRUE, FALSE);
        }
    }

    //for (int i = 0; i < 21;++i)
    //{
    //    for (int j = 0; j < 12; ++j)
    //    {
    //        //if(_block_stage.map[i][j] == 10)
    //        DrawRotaGraph(48 + 32 * j, 48 + 32 * i, 1, 0, getGame()->block_stage()->get_stageMap(0,0), TRUE, FALSE);//getGame()->block_stage().stageMap[i][j]], TRUE, FALSE);
    //    }
    //}

}
