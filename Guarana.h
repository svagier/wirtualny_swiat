#pragma once
#include "Roslina.h"
class Guarana : public Roslina
{
public:
	Guarana(Swiat& ref, Organizm*** moj_swiat, int x, int y);
	~Guarana();
private:
	Organizm * ** moj_swiat;
	Swiat& referencja;
	bool kolizja(int pozx, int pozy);
};

