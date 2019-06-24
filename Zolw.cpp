#include "Zolw.h"

Zolw::Zolw(Swiat& ref, Organizm*** moj_swiat, int x, int y)
	: Zwierze(ref, moj_swiat), referencja(ref), moj_swiat(moj_swiat)
{
	this->x = x;
	this->y = y;
	this->sila = 2;
	this->inicjatywa = 1;
	this->znak = 'z';
	this->nazwa = "Zolw";

}

Zolw::~Zolw()
{
}

void Zolw::akcja() {
	int var = (rand() % 100)+1;
	if (var > 75) 
		this->losujRuch();
}

bool Zolw::kolizja(int pozx, int pozy) {		//odpiera atak o sile <5
	if (this->moj_swiat[pozy][pozx]->getSila() < 5) {
		std::ofstream outfile;
		outfile.open("logs.txt", std::ios_base::app);
		outfile << this->moj_swiat[pozy][pozx]->nazwa << "(" << pozx << "," << pozy << ") probowal/a zaatakowac  " << this->nazwa << "(" << this->x << "," << this->y << "), ale ten odbil atak.\n";
		outfile.close();

		return false;
	}
		
	else return true;
}