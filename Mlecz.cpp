#include "Mlecz.h"

Mlecz::Mlecz(Swiat& ref, Organizm*** moj_swiat, int x, int y)
	:Roslina(ref, moj_swiat), referencja(ref), moj_swiat(moj_swiat)
{
	this->x = x;
	this->y = y;
	this->znak = 'm';
	this->nazwa = "Mlecz";
	this->mozliwosc_rozmnazania = true;//?
}

Mlecz::~Mlecz()
{
}

void Mlecz::akcja() {
	if (this->getMozliwoscRozmnazania() == true) {
		for (int i = 0; i < 3; i++) {
			int var = (rand() % 100) + 1;
			if (var <= PRAWD_ROZSIEWANIA)
				this->rozmnazanie();
		}
	}

}
