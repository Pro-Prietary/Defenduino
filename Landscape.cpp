#include "Landscape.h"
#include "Globals.h"
#include <EEPROM.h>

void Landscape::render(int cameraXPos)
{
	int xPos = cameraXPos - 64;
	if (xPos < 0)
	{
		xPos += 1024;
	}

	for (uint8_t i = 0; i < 128; i++)
	{
		arduboy.drawPixel(i, getHeight(xPos++));
		if (xPos == 1024)
		{
			xPos = 0;
		}
	}
}

byte Landscape::getHeight(int xPos)
{
	return EEPROM.read(EEPROM_STORAGE_SPACE_START + 4 + xPos);
}
