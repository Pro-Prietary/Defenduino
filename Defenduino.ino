#include <Arduboy2.h>
#include "StateManager.h"
#include "MenuState.h"
#include "Globals.h"

Arduboy2 arduboy;
StateManager stateManager;
MenuState menuState;
MenuState gameState;

void setup() {
    arduboy.begin();
}

void loop() {
   // pause render until it's time for the next frame
  if (!(arduboy.nextFrame()))
    return;

  arduboy.pollButtons();

  // first we clear our screen to black
  arduboy.clear();

  stateManager.setState(&menuState);
  stateManager.update();

  // then we finaly we tell the arduboy to display what we just wrote to the display
  arduboy.display();

}
