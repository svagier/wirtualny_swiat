#include "Owca.h"

Owca::Owca( Swiat& ref, Organizm*** moj_swiat, int x, int y)
	:Zwierze(ref, moj_swiat), referencja(ref), moj_swiat(moj_swiat)
{
	this->x = x;
	this->y = y;
	this->sila = 4;
	this->inicjatywa = 4;
	this->znak = 'o';
	this->nazwa = "Owca";

}

Owca::~Owca()
{
}

void rysowanie() {};

