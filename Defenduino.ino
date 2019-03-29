#include <Arduboy2.h>
#include "MenuState.h"
#include "GameState.h"
#include "GameOverState.h"
#include "Globals.h"
#include "Font3x5.h"
#include "Particles.h"

Arduboy2 arduboy;
Sprites sprites;
Font3x5 smallFont;

// make an ArdBitmap instance that will use the given the screen buffer and dimensions
ArdBitmap<WIDTH, HEIGHT> ardbitmap;

uint8_t currentState = STATE_MENU;

MenuState* pMenuState = NULL;
GameState* pGameState = NULL;
GameOverState* pGameOverState = NULL;

void setup() {
    arduboy.begin();

#ifdef _DEBUG
	Serial.begin(9600);
	Serial.println(F("Starting"));
#endif
}

void loop() {
   // pause render until it's time for the next frame

#ifdef _DEBUG
  if (!(arduboy.nextFrameDEV()))
    return;
#else
	if (!(arduboy.nextFrame()))
		return;
#endif

#ifdef _DEBUG
  if (arduboy.frameCount % 300 == 0)
  {
	  Serial.print(F("Free memory: "));
	  Serial.println(freeRam());
  }
#endif

  arduboy.pollButtons();

  // first we clear our screen to black
  arduboy.clear();

  update();

  // then we finaly we tell the arduboy to display what we just wrote to the display
  arduboy.display();
}

void update()
{
	switch (currentState)
	{
	case STATE_GAME:
		if (pGameState == NULL)
		{
			pGameState = new GameState();
			delete pMenuState;
			pMenuState = NULL;
		}
		pGameState->update();
		break;

	case STATE_MENU:
		if (pMenuState == NULL)
		{
			pMenuState = new MenuState();

			if (pGameOverState != NULL)
			{
				delete pGameOverState;
				pGameOverState = NULL;
			}
		}
		pMenuState->update();
		break;

	case STATE_GAME_OVER:
		if (pGameOverState == NULL)
		{
			pGameOverState = new GameOverState();
			delete pGameState;
			pGameState = NULL;
		}
		pGameOverState->update();
		break;
	}
}

void setState(uint8_t state)
{
	currentState = state;
}

bool isFlagSet(uint8_t flags, uint8_t flagToCheck)
{
	return (flags & flagToCheck) != 0;
}

void setFlag(uint8_t* pFlags, uint8_t flagToSet)
{
	*pFlags = *pFlags | flagToSet;
}

void unsetFlag(uint8_t* pFlags, byte flagToUnset)
{
	*pFlags = *pFlags & ~flagToUnset;
}

void setFlag(uint8_t* pFlags, uint8_t flagToSet, bool setValue)
{
	if (setValue)
	{
		setFlag(pFlags, flagToSet);
	}
	else
	{
		unsetFlag(pFlags, flagToSet);
	}
}

bool renderSprite(const uint8_t* spriteData, Vector2Int screenPos, uint8_t mirror = 0, uint8_t frame = 0)
{
	bool bIsVisible = false;
	// If far from the camera, flip to the other side for wrapping
	if (screenPos.x < -HALF_WORLD_WIDTH)
	{
		screenPos.x += WORLD_WIDTH;
	}
	else if (screenPos.x > HALF_WORLD_WIDTH)
	{
		screenPos.x -= WORLD_WIDTH;
	}

	int leftEdge = screenPos.x;
	int rightEdge = screenPos.x + pgm_read_byte(spriteData);

	if ((leftEdge < SCREEN_WIDTH && leftEdge >= 0) ||
		(rightEdge < SCREEN_WIDTH && rightEdge >= 0))
	{
		//sprites.drawSelfMasked(screenPos.x, screenPos.y, (const uint8_t *)spriteData, frame);

		uint8_t width = pgm_read_byte(spriteData);
		uint8_t height = pgm_read_byte(spriteData+1);

		uint8_t dataOffset = 2 + (frame * width);

		ardbitmap.drawBitmap(screenPos.x, screenPos.y, spriteData+dataOffset, width, height, WHITE, ALIGN_NONE, mirror);

		bIsVisible = true;
	}

	return bIsVisible;
}

void explodeObject(uint8_t* pFlags, Vector2 worldPos, uint8_t type)
{
	unsetFlag(pFlags, FLAG_ACTIVE);
	Particles* pExplosion = pGameState->getParticles();
	if (pExplosion != NULL)
	{
		pExplosion->worldPos.x = worldPos.x;
		pExplosion->worldPos.y = worldPos.y;
		pExplosion->show(type);
	}
}

#ifdef _DEBUG
int freeRam() {
	extern int __heap_start, *__brkval;
	int v;
	return (int)&v - (__brkval == 0 ? (int)&__heap_start : (int)__brkval);
}
#endif
