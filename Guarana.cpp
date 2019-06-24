#include "Guarana.h"

Guarana::Guarana(Swiat& ref, Organizm*** moj_swiat, int x, int y)
	: Roslina(ref, moj_swiat), referencja(ref), moj_swiat(moj_swiat)
{
	this->x = x;
	this->y = y;
	this->znak = 'g';
	this->nazwa = "Guarana";
	//this->mozliwosc_rozmnazania = true;
}

Guarana::~Guarana()
{
}


bool Guarana::kolizja(int pozx, int pozy) {
	this->moj_swiat[pozy][pozx]->setSila(this->moj_swiat[pozy][pozx]->getSila() + 3);
	std::ofstream outfile;
	outfile.open("logs.txt", std::ios_base::app);
	outfile << this->moj_swiat[pozy][pozx]->nazwa << "(" << pozx << "," << pozy << ") zjadl/a Guarane i zwiekszyl/a swoja sile o 3!\n";
	outfile.close();
	return true;
}