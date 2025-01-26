#include "BLOCK.h"
#include "GAME.h"
#include "BLOCK_STAGE.h"
#include <DxLib.h>
//#include "BLOCK_STAGE.h"
//#include "GAME_OBJECT.h"
#include <string>

BLOCK::BLOCK(class GAME* game):
GAME_OBJECT(game)
{
    _block[0].soundHandle[GAME::KOKA] = LoadSoundMem("sound/koka.mp3");
    _block[0].soundHandle[GAME::KAKO] = LoadSoundMem("sound/kako.mp3");
    _block[0].soundHandle[GAME::KA] = LoadSoundMem("sound/ka.mp3");
    _block[0].soundHandle[GAME::DON] = LoadSoundMem("sound/don.mp3");
    _block[0].soundHandle[GAME::PIRORON] = LoadSoundMem("sound/piroron.mp3");
}

BLOCK::~BLOCK()
{
    DeleteFontToHandle(fontHandle);
}

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

    for (int i = 0; i < 4;++i)
    {
        for (int j = 0; j < 4; ++j)
        {
            if (_block[0].blockMap[getGame()->get_random_block(getGame()->get_random_block_number()) % GAME::BLOCK_TYPE_NUM][0][i][j] == getGame()->get_random_block(getGame()->get_random_block_number()) % GAME::BLOCK_TYPE_NUM)
                DrawRotaGraph(450 + 32 * j, 50 + 32 * i, 1, 0, _block[0].blockHandle[_block[0].blockMap[getGame()->get_random_block(getGame()->get_random_block_number()) % GAME::BLOCK_TYPE_NUM][0][i][j]], TRUE, FALSE);

        }

    }


    int now = GetNowCount();

    char buffer[128];
 
    //sprintf_s(buffer, "特定ポイント１通過中　blockStatus: %d　_block[0].is2: %d", _block[0].blockStatus, _block[0].is2);
    //DrawStringToHandle(200, 180, buffer, GetColor(255, 255, 255), fontHandle);
    //int a = 5;
    //const char* c = "55";
    //DrawStringToHandle(600, 200, c, GetColor(255, 255, 255), fontHandle);


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

                if (getGame()->get_pressX() == 0)
                {
                    PlaySoundMem(_block[0].soundHandle[GAME::KOKA], DX_PLAYTYPE_BACK);
                    //getGame()->set_soundON(0,1);
                }

                getGame()->set_pressX(1);

    }


    if (CheckHitKey(KEY_INPUT_Z))
        if (getGame()->get_pressZ() == 0)
        {

            for (int i = 0; i < 4;++i)
            {
                for (int j = 0; j < 4; ++j)
                {
                    if (_block[0].blockMap[_block[0].g][(_block[0].h + 3) % 4][i][j] == _block[0].g)
                        if (getGame()->block_stage()->get_stageMap(i + _block[0].vecMap.y, j + _block[0].vecMap.x) != 18)
                        {
                            _block[0].movableZ = false;
                            break;
                        }

                }
                if (!_block[0].movableZ) break;

            }

            if (_block[0].movableZ)
            {
                _block[0].h = (_block[0].h + 3) % 4;
            }
            else
            {
                _block[0].movableZ = true;
            }

            if (getGame()->get_pressX() == 0)
            {
                PlaySoundMem(_block[0].soundHandle[GAME::KAKO], DX_PLAYTYPE_BACK);
                //getGame()->set_soundON(0,1);
            }

            getGame()->set_pressZ(1);
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
            getGame()->set_pressLeftTime(now);
        }
        else if(now - getGame()->get_pressLeftTime() > 200)
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
            getGame()->set_pressRightTime(now);
        }
        else if (now - getGame()->get_pressRightTime() > 200)
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

                        for (int i = 0; i < 4; ++i) //積み上がる
                        {
                            for (int j = 0; j < 4; ++j)
                            {
                                if (_block[0].blockMap[_block[0].g][_block[0].h][i][j] == _block[0].g)
                                    getGame()->block_stage()->set_stageMap(_block[0].g, _block[0].vecMap.y + i, _block[0].vecMap.x + j);
                            }
                        }
                        _block[0].blockStatus = 0; //積み上がる
                        PlaySoundMem(_block[0].soundHandle[GAME::KA], DX_PLAYTYPE_BACK);
                        _block[0].is2 = false;
                        //break;
                        return;
                    }

            }
            if (!_block[0].movableDown) break;
            
        }
        if (_block[0].movableDown)
        _block[0].vecMap.y += 1;
        _block[0].is2 = false;
        getGame()->set_pressDown(1);
    }


    if (CheckHitKey(KEY_INPUT_UP))
        if (getGame()->get_pressUp() == 0)
        {
            int k = 1;
            while (1)
            {
                for (int i = 0; i < 4;++i)
                {
                    for (int j = 0; j < 4; ++j)
                    {

                        if (_block[0].blockMap[_block[0].g][_block[0].h][i][j] == _block[0].g)
                            if (getGame()->block_stage()->get_stageMap(i + _block[0].vecMap.y + k, j + _block[0].vecMap.x) != 18)
                            {
                                //_block[0].blockStatus = 0; //積み上がる
                                //_block[0].movableDown = false;

                                for (int i = 0; i < 4; ++i) //積み上がる
                                {
                                    for (int j = 0; j < 4; ++j)
                                    {
                                        if (_block[0].blockMap[_block[0].g][_block[0].h][i][j] == _block[0].g)
                                            getGame()->block_stage()->set_stageMap(_block[0].g, _block[0].vecMap.y + i + k - 1, _block[0].vecMap.x + j);
                                    }
                                }
                                _block[0].blockStatus = 0; //積み上がる
                                PlaySoundMem(_block[0].soundHandle[GAME::KA], DX_PLAYTYPE_BACK);
                                //break;
                                getGame()->set_pressUp(1);
                                _block[0].is2 = false;
                                return;
                            }


                    }
                    //if (!_block[0].movableDown) break;

                }
                ++k;
                if (!(_block[0].blockStatus)) break;
            }
            //if (_block[0].movableDown)
            //    _block[0].vecMap.y += 1;

            getGame()->set_pressUp(1);
        }


    

    
        for (int i = 0; i < 4;++i)
        {
            bool J1breakFlag = false;
            bool J2breakFlag = false;

            for (int j = 0; j < 4; ++j)
            {
                if (_block[0].blockMap[_block[0].g][_block[0].h][i][j] == _block[0].g)
                {
                    if (getGame()->block_stage()->get_stageMap(i + _block[0].vecMap.y + 1, j + _block[0].vecMap.x) != 18)
                    {
                        //if (_block[0].blockStatus == 1)
                        //{

                        //int now = GetNowCount();
                        //getGame()->set_gameTime(now);
                        if (!_block[0].is2)
                        {
                            _block[0].blockStatus = 2;
                            _block[0].is2 = true;
                            getGame()->set_gameTime(now);
                            getGame()->set_passTime(now);

                            //sprintf_s(buffer, "特定ポイント２通過中　blockStatus: %d　_block[0].is2: %d", _block[0].blockStatus, _block[0].is2);
                            //DrawStringToHandle(200, 260, buffer, GetColor(255, 255, 255), fontHandle);

                            J2breakFlag = true;
                            break;
                        }
                        else
                        {
                            J2breakFlag = true;
                            break;
                        }
                        
                        //}

                        //_block[0].blockStatus = 2;

                        //_block[0].movableDown = false;
                        //
                        //for (int i = 0; i < 4; ++i) //積み上がる
                        //{
                        //    for (int j = 0; j < 4; ++j)
                        //    {
                        //        if (_block[0].blockMap[_block[0].g][_block[0].h][i][j] == _block[0].g)
                        //            getGame()->block_stage()->set_stageMap(_block[0].g, _block[0].vecMap.y + i, _block[0].vecMap.x + j);
                        //    }
                        //}
                        //_block[0].blockStatus = 0; //積み上がる
                        //PlaySoundMem(soundHandle[GAME::DON], DX_PLAYTYPE_BACK);
                        //break;
                    }
                    else
                    {
                        //_block[0].blockStatus = 1;
                        //sprintf_s(buffer, "特定ポイント３通過中　blockStatus: %d", _block[0].blockStatus);
                        //DrawStringToHandle(400, 230, buffer, GetColor(255, 255, 255), fontHandle);
                    }
                }
                    if (j == 3) J1breakFlag = true;

                //if (_block[0].blockStatus == 2) break;

                //if (i == 3) _block[0].blockStatus = 1;

            }
            //if (_block[0].blockStatus == 2) break;
            //if (!_block[0].movableDown) break;

            if (i==3 && J1breakFlag)
            {
                _block[0].blockStatus = 1;
                //_block[0].is2 = true;
                //getGame()->set_gameTime(GetNowCount());
                //sprintf_s(buffer, "特定ポイント４通過中　blockStatus: %d　_block[0].is2: %d", _block[0].blockStatus, _block[0].is2);
                //DrawStringToHandle(200, 300, buffer, GetColor(255, 255, 255), fontHandle);
            }
            if (_block[0].blockStatus == 2 && J2breakFlag) break;
        }
    
    


    if (_block[0].blockStatus == 2)
        if(now - getGame()->get_gameTime() > 500)
    {
            _block[0].blockStatus = 0;

            for (int i = 0; i < 4; ++i) //積み上がる
            {
                for (int j = 0; j < 4; ++j)
                {
                    if (_block[0].blockMap[_block[0].g][_block[0].h][i][j] == _block[0].g)
                        getGame()->block_stage()->set_stageMap(_block[0].g, _block[0].vecMap.y + i, _block[0].vecMap.x + j);
                }
            }
            //_block[0].blockStatus = 0; //積み上がる
            PlaySoundMem(_block[0].soundHandle[GAME::KA], DX_PLAYTYPE_BACK);
            _block[0].is2 = false;
            return;
    }



    /*
    if (_block[0].blockStatus == 2)
    {
            for(int i=0; i<4; ++i)
                for(int j=0; j<4; ++j)
            if (_block[0].blockMap[_block[0].g][_block[0].h][i][j] == _block[0].g)
            {
                if (getGame()->block_stage()->get_stageMap(i + _block[0].vecMap.y + 1, j + _block[0].vecMap.x) != 18 &&
                    (now - getGame()->get_gameTime()) > 2000)
                {
                    _block[0].blockStatus = 0;

                    for (int i = 0; i < 4; ++i) //積み上がる
                    {
                        for (int j = 0; j < 4; ++j)
                        {
                            if (_block[0].blockMap[_block[0].g][_block[0].h][i][j] == _block[0].g)
                                getGame()->block_stage()->set_stageMap(_block[0].g, _block[0].vecMap.y + i, _block[0].vecMap.x + j);
                        }
                    }
                    //_block[0].blockStatus = 0; //積み上がる
                    PlaySoundMem(soundHandle[GAME::DON], DX_PLAYTYPE_BACK);
                    _block[0].is2 = false;
                    return;
                }
            }

            if (now - getGame()->get_passTime() > 500)
            {
                _block[0].blockStatus = 1;
                _block[0].is2 = false;
                //_block[0].vecMap.y += 1;
            }
    }
    */


    /*
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
                    if (getGame()->block_stage()->get_stageMap(i + _block[0].vecMap.y + 1, j + _block[0].vecMap.x) != 18)
                    {
                        _block[0].blockStatus = 2;
                        _block[0].movableDown = false;

                        for (int i = 0; i < 4; ++i) //積み上がる
                        {
                            for (int j = 0; j < 4; ++j)
                            {
                                if (_block[0].blockMap[_block[0].g][_block[0].h][i][j] == _block[0].g)
                                    getGame()->block_stage()->set_stageMap(_block[0].g, _block[0].vecMap.y + i, _block[0].vecMap.x + j);
                            }
                        }
                        _block[0].blockStatus = 0; //積み上がる
                        PlaySoundMem(soundHandle[GAME::DON], DX_PLAYTYPE_BACK);
                        break;
                    }

            }
            if (!_block[0].movableDown) break;
        }

        //if(_block[0].movableDown) //積み上がらない
        _block[0].vecMap.y += 1; //積み上がらない
        //else //積み上がる
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
    */

    
    if (_block[0].blockStatus == 1)
    {
    
    
    if (now - getGame()->get_passTime() > 125)//(now - e_passTime() > 1000)
    {
        _block[0].movableDown = true;
        //_block[0].vec.y += 32.0f;
        getGame()->set_passTime(now);

        for (int i = 0; i < 4;++i)
        {
            for (int j = 0; j < 4; ++j)
            {
                if (_block[0].blockMap[_block[0].g][_block[0].h][i][j] == _block[0].g)
                    if (getGame()->block_stage()->get_stageMap(i + _block[0].vecMap.y + 1, j + _block[0].vecMap.x) != 18)
                    {
                        _block[0].movableDown = false;

                        for (int i = 0; i < 4; ++i) //積み上がる
                        {
                            for (int j = 0; j < 4; ++j)
                            {
                                if (_block[0].blockMap[_block[0].g][_block[0].h][i][j] == _block[0].g)
                                    getGame()->block_stage()->set_stageMap(_block[0].g, _block[0].vecMap.y + i, _block[0].vecMap.x + j);
                            }
                        }
                        _block[0].blockStatus = 0; //積み上がる
                        PlaySoundMem(_block[0].soundHandle[GAME::KA], DX_PLAYTYPE_BACK);
                        _block[0].is2 = false;
                        return;
                        //break;
                    }

            }
            if (!_block[0].movableDown) break;
        }

        //if(_block[0].movableDown) //積み上がらない
        _block[0].vecMap.y += 1; //積み上がらない
        _block[0].is2 = false;
        //else //積み上がる
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
    //_block[0].vecMap.y += 1; //積み上がらない
    //_block[0].is2 = false;
    //getGame()->set_passTime(now);
    }
}


void BLOCK::draw()
{
    //DrawFormatString(500, 500, GetColor(255, 255, 255), "debug");
    //DrawRotaGraph(200, 200, 2, 0, _block[0].blockHandle[5], TRUE, FALSE);

    


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
