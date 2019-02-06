#include "GameState.h"
#include "StateManager.h"
#include "Globals.h"


const byte segmentPoints1[] PROGMEM = { 0,45, 10,60, 100,50, 127,45 };
const byte segmentPoints2[] PROGMEM  = { 0,45, 25,50, 75,57, 92,61, 110,49, 127,60 };
const byte segmentPoints3[] PROGMEM = { 0,60, 20,48, 42,59, 60,49, 72,60, 100,60, 127,55 };
const byte segmentPoints4[] PROGMEM = { 0,55, 40,60, 95,46, 115,61, 127,44 };
const byte segmentPoints5[] PROGMEM = { 0,45, 10,60, 100,50, 127,45 };
const byte segmentPoints6[] PROGMEM = { 0,45, 25,50, 75,57, 92,61, 110,49, 127,60 };
const byte segmentPoints7[] PROGMEM = { 0,60, 20,48, 42,59, 60,49, 72,60, 100,60, 127,55 };
const byte segmentPoints8[] PROGMEM = { 0,55, 40,60, 95,46, 115,61, 127,44 };

#define TOTAL_LANDSCAPE_COORDS_1 8
#define TOTAL_LANDSCAPE_COORDS_2 12
#define TOTAL_LANDSCAPE_COORDS_3 14
#define TOTAL_LANDSCAPE_COORDS_4 10
#define TOTAL_LANDSCAPE_COORDS_5 8
#define TOTAL_LANDSCAPE_COORDS_6 12
#define TOTAL_LANDSCAPE_COORDS_7 14
#define TOTAL_LANDSCAPE_COORDS_8 10


GameState::GameState() : State(&camera)
{
	testText.setText(F("Game State"));
	camera.setPlayerShip(&playerShip);

	landscape[0].setData(segmentPoints1, TOTAL_LANDSCAPE_COORDS_1);
	landscape[1].setData(segmentPoints2, TOTAL_LANDSCAPE_COORDS_2);
	landscape[2].setData(segmentPoints3, TOTAL_LANDSCAPE_COORDS_3);
	landscape[3].setData(segmentPoints4, TOTAL_LANDSCAPE_COORDS_4);
	landscape[4].setData(segmentPoints5, TOTAL_LANDSCAPE_COORDS_5);
	landscape[5].setData(segmentPoints6, TOTAL_LANDSCAPE_COORDS_6);
	landscape[6].setData(segmentPoints7, TOTAL_LANDSCAPE_COORDS_7);
	landscape[7].setData(segmentPoints8, TOTAL_LANDSCAPE_COORDS_8);

	for (int i = 0; i < 8; i++)
	{
		landscape[i].worldPos.x = i * 128;
		addObject(&landscape[i]);
	}

	for (int i = 0; i < 10; i++)
	{
		humanoids[i].worldPos.x = rand() % 1024;
		humanoids[i].worldPos.y = 29;
		if (rand() % 2 == 0)
		{
			humanoids[i].velocity.x = 0.05;
		}
		else
		{
			humanoids[i].velocity.x = -0.05;
		}
		addObject(&humanoids[i]);
	}

	addObject(&playerShip);
	
	for (int i = 0; i < 4; i++)
	{
		laserPool.pool(&lasers[i]);
	}
}

PlayerShip* GameState::getPlayerShip()
{
	return &playerShip;
}

void GameState::pool(PlayerShot* pLaser)
{
	laserPool.pool(pLaser);
}

PlayerShot* GameState::getPlayerShot()
{
	return laserPool.get();
}