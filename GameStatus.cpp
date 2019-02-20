#pragma once

#include "GameStatus.h"

GameStatus::GameStatus(byte enemies, byte lives, byte smartBombs, byte humanoids)
{
	this->enemies = enemies;
	this->lives = lives;
	this->smartBombs = smartBombs;
	this->humanoids = humanoids;
}