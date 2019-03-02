#pragma once

#include <Arduboy2.h>
#include "MenuState.h"
#include "GameState.h"
#include "Font3x5.h"

#define WORLD_WIDTH 1024
#define HALF_WORLD_WIDTH 512

extern Arduboy2 arduboy;
extern Font3x5 smallFont;
extern void setState(State* state);
extern State* getCurrentState();
extern bool isFlagSet(uint8_t flags, uint8_t flagToCheck);
extern void setFlag(uint8_t* pFlags, uint8_t flagToSet);
extern void unsetFlag(uint8_t* pFlags, byte flagToUnset);
extern void setFlag(uint8_t* pFlags, uint8_t flagToSet, bool setValue);
