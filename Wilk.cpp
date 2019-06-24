#include "Wilk.h"

Wilk::Wilk( Swiat& ref, Organizm*** moj_swiat, int x, int y)
	:Zwierze(ref, moj_swiat), referencja(ref), moj_swiat(moj_swiat)
{
	this->x = x;
	this->y = y;
	this->sila = 9;
	this->inicjatywa = 5;
	this->znak = 'w';
	this->nazwa = "Wilk";

}

Wilk::~Wilk()
{
}