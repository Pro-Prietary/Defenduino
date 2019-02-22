#include "Flaggable.h"

bool Flaggable::isFlagSet(byte flagToCheck)
{
	return (flags & flagToCheck) != 0;
}

void Flaggable::setFlag(byte flagToSet)
{
	flags = flags | flagToSet;
}

void Flaggable::unsetFlag(byte flagToUnset)
{
	flags = flags & ~flagToUnset;
}

void Flaggable::setFlag(byte flagToSet, bool setValue)
{
	if (setValue)
	{
		setFlag(flagToSet);
	}
	else
	{
		unsetFlag(flagToSet);
	}
}