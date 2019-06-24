#include "Trawa.h"

Trawa::Trawa(Swiat& ref, Organizm*** moj_swiat, int x, int y)
	:Roslina(ref, moj_swiat), referencja(ref), moj_swiat(moj_swiat)
{
	this->x = x;
	this->y = y;
	this->znak = 't';
	this->nazwa = "Trawa";
}

Trawa::~Trawa()
{
}
