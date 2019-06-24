#include "WilczeJagody.h"

WilczeJagody::WilczeJagody(Swiat& ref, Organizm*** moj_swiat, int x, int y)
	:Roslina(ref, moj_swiat), referencja(ref), moj_swiat(moj_swiat)
{
	this->x = x;
	this->y = y;
	this->znak = 'j';
	this->nazwa = "Wilcze Jagody";
	this->sila = 99;
}

WilczeJagody::~WilczeJagody()
{
}

bool WilczeJagody::kolizja(int pozx, int pozy) {
	std::ofstream outfile;
	outfile.open("logs.txt", std::ios_base::app);
	outfile << this->moj_swiat[pozy][pozx]->nazwa << "(" << pozx << "," << pozy << ") zjadl/a " << this->nazwa << "(" << this->x << "," << this->y << ") i umarl/a.\n";
	outfile.close();

	this->referencja.zabijOrganizm(pozx, pozy); //zabij zwierze
	this->referencja.zabijOrganizm(this->x, this->y); //zabij siebie
	return false;
}