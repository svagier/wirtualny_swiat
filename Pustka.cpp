#include "Pustka.h"

Pustka::Pustka(int x, int y, Swiat& ref, Organizm*** moj_swiat)
	:	Organizm(ref),  referencja(ref), moj_swiat(moj_swiat)
{
	this->x = x;
	this->y = y;
	this->nazwa = "pustka";
	this->znak = '.';
	this->mozliwosc_ruchu = false;
	this->mozliwosc_rozmnazania = false;
	this->moj_swiat = moj_swiat;
}

Pustka::Pustka(Swiat& ref, Organizm*** moj_swiat, int x, int y)
	: Organizm(ref), referencja(ref), moj_swiat(moj_swiat)
{
	this->x = x;
	this->y = y;
	this->znak = '.';
	this->nazwa = "pustka";
	this->moj_swiat = moj_swiat;
	this->mozliwosc_ruchu = false;
	this->mozliwosc_rozmnazania = false;
}

Pustka::~Pustka()
{
}

void Pustka::akcja() {};
