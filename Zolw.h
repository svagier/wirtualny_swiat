#pragma once
#include "Zwierze.h"
class Zolw : public Zwierze
{
public:
	Zolw(Swiat& ref, Organizm*** moj_swiat, int x, int y);
	~Zolw();
private:
	Swiat &  referencja;
	Organizm*** moj_swiat;
	void akcja() override;
	bool kolizja(int pozx, int pozy) override;
};

