#pragma once
//extern int e_passTime = 0;
class GAME_OBJECT
{
	class GAME* Game = 0;
public:
	GAME_OBJECT(class GAME*);
	virtual ~GAME_OBJECT();

	class GAME* getGame()
	{
		return Game;
	}

};

