#include "Lis.h"

Lis::Lis(Swiat& ref, Organizm*** moj_swiat, int x, int y)
	:Zwierze(ref, moj_swiat), referencja(ref)
{
	this->x = x;
	this->y = y;
	this->sila = 3;
	this->inicjatywa = 7;
	this->znak = 'l';
	this->nazwa = "Lis";
	this->moj_swiat = moj_swiat;
}

Lis::~Lis()
{
}

void Lis::walka(Organizm*** moj_swiat, int pozx, int pozy) {
	if (this->sila >= moj_swiat[pozy][pozx]->getSila()) {
		std::ofstream outfile;
		outfile.open("logs.txt", std::ios_base::app);
		outfile << "Lis (" << this->x << "," << this->y << ") zaatakowal i zabil " << this->moj_swiat[pozy][pozx]->nazwa << "(" << pozx << "," << pozy << ").\n";
		outfile.close();
		int tmpx = this->x;
		int tmpy = this->y;
		//this wygrywa(bo pierwszy zaatakowal albo sila wieksza)
		moj_swiat[pozy][pozx] = new Pustka(pozx, pozy, referencja, moj_swiat);
		zamienPozycje(moj_swiat[pozy][pozx]);
		std::swap(moj_swiat[this->y][this->x], moj_swiat[tmpy][tmpx]);
	}
	//jedyna opcja - lis nie ruszy sie, jesli przeciwnik jest silniejszy
}