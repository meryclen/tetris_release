#pragma once

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

