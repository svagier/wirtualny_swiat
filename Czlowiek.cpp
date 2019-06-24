#include "Czlowiek.h"

Czlowiek::Czlowiek(Swiat& ref, Organizm*** moj_swiat, int x, int y)
	:Zwierze(ref, moj_swiat), referencja(ref)
{
	this->x = x;
	this->y = y;
	this->sila = 5;
	this->inicjatywa = 4;
	this->znak = 'c';
	this->moj_swiat = moj_swiat;
	this->referencja.setCzlowiekX ( this->x);
	this->referencja.setCzlowiekY ( this->y);
	this->referencja.setCzlowiekNowyX ( this->x);
	this->referencja.setCzlowiekNowyY ( this->y);
	this->nazwa = "Czlowiek";
	this->referencja.setCzlowiekZywy(true);
	this->mozliwosc_rozmnazania = false;
}

Czlowiek::~Czlowiek()
{
}

void Czlowiek::akcja() {
	this->mozliwosc_rozmnazania = false;
	this->ruch(this->moj_swiat, this->referencja.getCzlowiekNowyX(), this->referencja.getCzlowiekNowyY());
}

bool Czlowiek::kolizja(int pozx, int pozy) {
	if (this->referencja.getTarczaAlzura()>0) {
		POZYCJA temp;
		temp = this->znajdzWolne(this->x, this->y, pozx, pozy);			
		if (temp.x != BRAK_WOLNYCH_POL && temp.y != BRAK_WOLNYCH_POL) {
			std::ofstream outfile;
			outfile.open("logs.txt", std::ios_base::app);
			outfile << this->moj_swiat[pozy][pozx]->nazwa << "(" << pozx << "," << pozy << ") probowal/a zaatakowac Czlowieka, ale ten odbil atak Tarcza Alzura.\n";
			outfile.close();

			zamienPozycje(moj_swiat[temp.y][temp.x], moj_swiat[pozy][pozx]);
			std::swap(moj_swiat[temp.y][temp.x], moj_swiat[pozy][pozx]);
		}
		else{
			std::ofstream outfile;
			outfile.open("logs.txt", std::ios_base::app);
			outfile << "Czlowiek probowal bronic sie Tarcza Alzura przed atakiem "<< this->moj_swiat[pozy][pozx]->nazwa<<", jednak nie mial gdzie odbic tego ataku.\n";
			outfile.close();
			return true;
		}
		return false;
	}
	else return true; 
}