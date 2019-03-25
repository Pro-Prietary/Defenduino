#include <Arduboy2.h>
#include <Sprites.h>
#include "MenuState.h"
#include "Globals.h"
#include "Font3x5.h"

Arduboy2 arduboy;
Sprites sprites;
Font3x5 smallFont;

State* pCurrentState;
State* pNextState;

void setup() {
    arduboy.begin();
	setState(new MenuState());

#ifdef _DEBUG
	Serial.begin(9600);
	Serial.println(F("Starting"));
#endif
}

void globalMethod()
{
	Serial.println("Public!");
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
	// Time to move to a new state?
	if (pNextState != NULL)
	{
		delete pCurrentState;
		pCurrentState = pNextState;
		pNextState = NULL;
	}

	pCurrentState->update();
}

void setState(State* state)
{
	pNextState = state;
}

State* getCurrentState()
{
	return pCurrentState;
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

bool renderSprite(const uint8_t* spriteData, Vector2Int screenPos, uint8_t frame = 0)
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
		sprites.drawSelfMasked(screenPos.x, screenPos.y, (const uint8_t *)spriteData, frame);
		bIsVisible = true;
	}

	return bIsVisible;
}

#ifdef _DEBUG
int freeRam() {
	extern int __heap_start, *__brkval;
	int v;
	return (int)&v - (__brkval == 0 ? (int)&__heap_start : (int)__brkval);
}
#endif
