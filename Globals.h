#pragma once

#include <Arduboy2.h>
#include "MenuState.h"
#include "GameState.h"
#include "Font3x5.h"

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define HALF_SCREEN_WIDTH 64
#define HALF_SCREEN_HEIGHT 32
#define WORLD_WIDTH 1024
#define HALF_WORLD_WIDTH 512

extern Arduboy2 arduboy;
extern Sprites sprites;
extern Font3x5 smallFont;
extern void setState(State* state);
extern State* getCurrentState();
extern bool isFlagSet(uint8_t flags, uint8_t flagToCheck);
extern void setFlag(uint8_t* pFlags, uint8_t flagToSet);
extern void unsetFlag(uint8_t* pFlags, byte flagToUnset);
extern void setFlag(uint8_t* pFlags, uint8_t flagToSet, bool setValue);
extern bool renderSprite(const uint8_t* spriteData, Vector2Int screenPos, uint8_t frame = 0);

