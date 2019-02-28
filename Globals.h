#pragma once

#include <Arduboy2.h>
#include "StateManager.h"
#include "MenuState.h"
#include "GameState.h"
#include "Font3x5.h"

#define WORLD_WIDTH 1024
#define HALF_WORLD_WIDTH 512

extern Arduboy2 arduboy;
extern StateManager stateManager;
extern Font3x5 smallFont;