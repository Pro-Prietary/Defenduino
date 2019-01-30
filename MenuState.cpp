#include "MenuState.h"

extern Arduboy2 arduboy;

MenuState::MenuState() : State(&camera)
{
	TextObject obj(F("test"));
}