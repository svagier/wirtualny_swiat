#include "Roslina.h"
#include "Pustka.h"

Roslina::Roslina(Swiat& ref, Organizm*** moj_swiat)
	:Organizm(ref), referencja(ref), moj_swiat(moj_swiat)
{

	this->inicjatywa = 0;
	this->sila = 0;
	this->mozliwosc_rozmnazania = true;
	this->mozliwosc_ruchu = true;
}


Roslina::~Roslina()
{
}

POZYCJA Roslina::znajdzWolne() {

	int dummy = (rand() % 50) + 1;
	int var = (rand() % dummy) + 1;
	POZYCJA wolne = { BRAK_WOLNYCH_POL , BRAK_WOLNYCH_POL };

	for (int i = 0; i < 4; i++) {
		switch (var % 4) {
		case 0:
			if (this->referencja.wGranicach(this->x, this->y + 1) && typeid(*this->moj_swiat[this->y + 1][this->x]) == typeid(Pustka&)) {
				wolne = { this->x, this->y + 1 };
				return wolne;
			}
			break;

		case 1:
			if (this->referencja.wGranicach(this->x, this->y - 1) && typeid(*this->moj_swiat[this->y - 1][this->x]) == typeid(Pustka&)) {
				wolne = { this->x, this->y - 1 };
				return wolne;
			}
			break;

		case 2:
			if (this->referencja.wGranicach(this->x + 1, this->y) && typeid(*this->moj_swiat[this->y][this->x + 1]) == typeid(Pustka&)) {
				wolne = { this->x + 1, this->y };
				return wolne;
			}
			break;

		case 3:
			if (this->referencja.wGranicach(this->x - 1, this->y) && typeid(*this->moj_swiat[this->y][this->x - 1]) == typeid(Pustka&)) {
				wolne = { this->x - 1, this->y };
				return wolne;
			}
			break;

		default:
			wolne = { BRAK_WOLNYCH_POL, BRAK_WOLNYCH_POL };
			break;
		}

		var++;
	}
	return wolne;
}


void Roslina::rozmnazanie() {
	if (this->getMozliwoscRozmnazania() == true) {
		POZYCJA tmp;
		tmp = this->znajdzWolne();
		if (tmp.x != BRAK_WOLNYCH_POL && tmp.y != BRAK_WOLNYCH_POL) {
			this->referencja.nowyOrganizm(this->x, this->y, tmp.x, tmp.y); //nowostworzony organizm moze rozmnazac sie dopiero
			moj_swiat[tmp.y][tmp.x]->setMozliwoscRozmnazania(false);		//w kolejnej turze (zmiana wewnatrz nowyOrganizm).
			this->setMozliwoscRozmnazania(false);						//roslina pierwotna nie moze do konca tury ponownie sie rozmanazac.
		}
	}

}

void Roslina:: akcja() {
	int var = (rand() % 100) + 1;
	if (var<=PRAWD_ROZSIEWANIA)
		this->rozmnazanie();
}

