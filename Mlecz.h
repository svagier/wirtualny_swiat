#pragma once
#include "Roslina.h"
class Mlecz : public Roslina
{
public:
	Mlecz(Swiat& ref, Organizm*** moj_swiat, int x, int y);
	~Mlecz();
	private:
	Organizm * ** moj_swiat;
	Swiat& referencja;
	bool kolizja(int pozx, int pozy) { return true; };
	void akcja() override;
};

