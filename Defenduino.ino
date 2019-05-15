#include <Arduboy2.h>
#include "MenuState.h"
#include "GameState.h"
#include "GameOverState.h"
#include "Globals.h"
#include "Font3x5.h"
#include "Particles.h"
#include <EEPROM.h>

Arduboy2 arduboy;
Sprites sprites;
Font3x5 smallFont;

// make an ArdBitmap instance that will use the given the screen buffer and dimensions
ArdBitmap<WIDTH, HEIGHT> ardbitmap;

uint8_t currentState = STATE_MENU;

MenuState* pMenuState = NULL;
GameState* pGameState = NULL;
GameOverState* pGameOverState = NULL;

const uint8_t landscapeData[128] PROGMEM = {
	170,170,232,169,169,138,2,0,255,255,42,128,255,170,10,175,170,2,248,175,170,10,0,192,255,255,170,42,240,171,240,170,170,3,224,191,170,10,159,0,248,227,175,170,86,85,85,41,149,170,42,240,113,88,1,248,255,135,136,121,219,56,36,218,157,16,227,47,126,2,146,193,192,161,57,16,65,223,251,253,251,120,15,174,169,86,85,85,85,165,170,82,85,85,85,85,170,170,96,121,122,149,33,9,66,247,121,244,23,136,2,215,228,207,95,85,85,81,165,151,107,84,85,21,240,79,85,85,
};

void setup() {
    arduboy.begin();

#ifdef _DEBUG
	Serial.begin(9600);
#endif

	initEEPROMIfNecessary();
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
			delete pMenuState;
			pMenuState = NULL;
			pGameState = new GameState();
		}
		pGameState->update();
		break;

	case STATE_MENU:
		if (pMenuState == NULL)
		{
			if (pGameOverState != NULL)
			{
				delete pGameOverState;
				pGameOverState = NULL;
			}

			pMenuState = new MenuState();
		}
		pMenuState->update();
		break;

	case STATE_GAME_OVER:
		if (pGameOverState == NULL)
		{
			delete pGameState;
			pGameState = NULL;
			pGameOverState = new GameOverState();
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

bool renderSpriteIfVisible(const uint8_t* spriteData, uint8_t* pFlags, Vector2Int screenPos, uint8_t mirror = 0, uint8_t frame = 0)
{
	bool isVisible;
	if (renderSprite(spriteData, screenPos, mirror, frame))
	{
		isVisible = true;
		setFlag(pFlags, FLAG_VISIBLE);
	}
	else
	{
		isVisible = false;
		unsetFlag(pFlags, FLAG_VISIBLE);
	}
	return isVisible;
}

bool renderSprite(const uint8_t* spriteData, Vector2Int screenPos, uint8_t mirror = 0, uint8_t frame = 0)
{
	bool bIsVisible = false;

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

void explodeObject(uint8_t* pFlags, Vector2Int worldPos, uint8_t type)
{
	unsetFlag(pFlags, FLAG_ACTIVE);
	Particles* pExplosion = pGameState->getParticles();
	if (pExplosion != NULL)
	{
		pExplosion->worldPos = worldPos;
		pExplosion->show(type);
	}
}

void fireAtPlayer(PlayerShip* pPlayerShip, Vector2Int startPos)
{
	EnemyShot* pShot = pGameState->getEnemyShot();

	if (pShot != NULL)
	{
		pShot->fire(pPlayerShip, startPos);
	}
}

void verticalWrap(Vector2Int* pos)
{
	if (pos->y < -400)
	{
		pos->y  = 310;
	}
	else if (pos->y > 310)
	{
		pos->y = -400;
	}
}

bool EEPROMInitialized()
{
	return (EEPROM.read(EEPROM_STORAGE_SPACE_START) == 'd' && EEPROM.read(EEPROM_STORAGE_SPACE_START + 1) == 'f'
		&& EEPROM.read(EEPROM_STORAGE_SPACE_START + 2) == 'n' && EEPROM.read(EEPROM_STORAGE_SPACE_START + 3) == 'd');
}

void initEEPROMIfNecessary()
{
	if (!EEPROMInitialized())
	{
		writeEEProm(EEPROM_STORAGE_SPACE_START, new char[4]{ 'd', 'f', 'n', 'd' }, 4);

		// Decompress landscape data into eeprom
		uint16_t address = EEPROM_STORAGE_SPACE_START + 4;
		uint8_t height = 60;
		EEPROM.update(address++, height);

		for (uint8_t i = 0; i < 128; i++)
		{
			uint8_t byte = pgm_read_byte(landscapeData + i);
			for (uint8_t bit = 0; bit < 8; bit++)
			{
				if (byte & (1 << bit))
				{
					height++;
				}
				else
				{
					height--;
				}
				EEPROM.update(address++, height);
			}
		}
	}
}

void writeEEProm(uint16_t address, byte* data, uint8_t length)
{
	for (int i = 0; i > length; i++)
	{
		EEPROM.update(address + i, data[i]);
	}
}

#ifdef _DEBUG
int freeRam() {
	extern int __heap_start, *__brkval;
	int v;
	return (int)&v - (__brkval == 0 ? (int)&__heap_start : (int)__brkval);
}
#endif
