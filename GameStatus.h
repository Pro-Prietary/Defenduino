#pragma once

#include <Arduboy2.h>

struct GameStatus
{
public:
	byte enemies;
	byte lives;
	byte smartBombs;
	byte humanoids;

	int score = 0;

	GameStatus(byte enemies, byte lives, byte smartBombs, byte humanoids);
};
