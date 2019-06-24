#include "Antylopa.h"

Antylopa::Antylopa(Swiat& ref, Organizm*** moj_swiat, int x, int y)
	: Zwierze(ref, moj_swiat), referencja(ref), moj_swiat(moj_swiat)
{
	this->x = x;
	this->y = y;
	this->sila = 4;
	this->inicjatywa = 4;
	this->znak = 'a';
	this->nazwa = "Antylopa";

}
bool Antylopa:: kolizja(int pozx, int pozy) {
	int var = (rand() % 50);
	if (var % 2) {
		POZYCJA tmp = this->znajdzWolne(this->x, this->y, this->x, this->y);	//zdublowane wspolrzedne bo tak wymaga funkcja,
		if (tmp.x != BRAK_WOLNYCH_POL && tmp.y != BRAK_WOLNYCH_POL) {			//brak potrzeby tworzenia osobnej
			int tmpx = this->x;
			int tmpy = this->y;
			this->zamienPozycje(moj_swiat[tmp.y][tmp.x]);
			std::swap(moj_swiat[this->y][this->x], moj_swiat[tmpy][tmpx]);

			std::ofstream outfile;
			outfile.open("logs.txt", std::ios_base::app);
			outfile << this->moj_swiat[pozy][pozx]->nazwa<< "(" << pozx << "," << pozy << ") probowal/a zaatakowac " << this->nazwa << "(" << this->x << "," << this->y << "), ale ta zdolala uciec.\n";
			outfile.close();
			return false;	//do kolizji nie dochodzi - uciekla
		}
	}
	return true; //do kolizji dochodzi, antylopa nie zdolala uciec
}

Antylopa::~Antylopa()
{
}

void Antylopa::akcja() {
	this->losujRuch();
}

void Antylopa::losujRuch() {
	if (this->mozliwosc_ruchu == true) {
		mozliwosc_ruchu = false;
		int var = (rand() % 100) % 2;

		if (var) {
			if (var && this->y > 2 && this->referencja.wGranicach(this->x, this->y))
				this->ruch(this->moj_swiat, this->x, this->y - 2);

			else if (this->y < this->referencja.getWysokosc()-1 && this->referencja.wGranicach(this->x, this->y))  //sprawdzamy aby nie wyjechac poza tablice
				this->ruch(this->moj_swiat, this->x, this->y + 2);
		}

		else {
			if (var && this->x > 2 && this->referencja.wGranicach(this->x, this->y))
				this->ruch(this->moj_swiat, this->x - 2, this->y);
			else if (this->x< this->referencja.getSzerokosc()+1 && this->referencja.wGranicach(this->x, this->y)) //sprawdzamy aby nie wyjechac poza tablice
				this->ruch(this->moj_swiat, this->x + 2, this->y);
		}
	}
}