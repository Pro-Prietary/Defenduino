#include <Arduboy2.h>
#include "StateManager.h"

Arduboy2 arduboy;
StateManager* pStateManager;

void setup() {
    arduboy.begin();
    pStateManager = &StateManager::instance();
}

void loop() {
   // pause render until it's time for the next frame
  if (!(arduboy.nextFrame()))
    return;

  // first we clear our screen to black
  arduboy.clear();

  pStateManager->update();

  // then we finaly we tell the arduboy to display what we just wrote to the display
  arduboy.display();

}
