#pragma once
#include "Roslina.h"
class Trawa : public Roslina
{
public:
	Trawa(Swiat& ref, Organizm*** moj_swiat, int x, int y);
	~Trawa();
private:
	Organizm *** moj_swiat;
	Swiat& referencja;
	bool kolizja(int pozx, int pozy) { return true; };
};

