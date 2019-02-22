#pragma once

#include <Arduboy2.h>

class Flaggable
{
protected:
	bool isFlagSet(byte flagToCheck);
	void setFlag(byte flagToSet);
	void unsetFlag(byte flagToUnset);
	void setFlag(byte flagToSet, bool setValue);

private:
	byte flags = 0;
};