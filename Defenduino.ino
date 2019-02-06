#include <Arduboy2.h>
#include "StateManager.h"
#include "MenuState.h"
#include "Globals.h"

Arduboy2 arduboy;
StateManager stateManager;

#ifdef _DEBUG
int frameCount = 0;
#endif

void setup() {
    arduboy.begin();
	stateManager.setState(new MenuState());

#ifdef _DEBUG
	Serial.begin(9600);
	Serial.println("Starting");
#endif
}

void loop() {
   // pause render until it's time for the next frame
  if (!(arduboy.nextFrame()))
    return;

#ifdef _DEBUG
  frameCount++;
  if (frameCount == 60*5)
  {
	  frameCount = 0;
	  Serial.print("Free memory: ");
	  Serial.println(freeRam());
  }
#endif

  arduboy.pollButtons();

  // first we clear our screen to black
  arduboy.clear();

  stateManager.update();

  // then we finaly we tell the arduboy to display what we just wrote to the display
  arduboy.display();
}

#ifdef _DEBUG
int freeRam() {
	extern int __heap_start, *__brkval;
	int v;
	return (int)&v - (__brkval == 0 ? (int)&__heap_start : (int)__brkval);
}
#endif
