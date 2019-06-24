#pragma once
#ifndef PUSTKA_H
#define PUSTKA_H

#include "Organizm.h"
class Organizm;
class Pustka : public Organizm
{
public:
	Pustka(int x, int y, Swiat&  ref, Organizm*** moj_swiat);
	Pustka(Swiat& ref, Organizm*** moj_swiat, int x, int y);
	~Pustka();

private:
	 Organizm *** moj_swiat;
	 Swiat&  referencja;
	 void akcja() override;
	 bool kolizja(int pozx, int pozy) { return false; };
};

#endif // !PUSTKA_H