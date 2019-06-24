#pragma once
#include "Roslina.h"
class BarszczSosnowskiego:public Roslina
{
public:
	BarszczSosnowskiego(Swiat& ref, Organizm*** moj_swiat, int x, int y);
	~BarszczSosnowskiego();
	private:
	Organizm *** moj_swiat;
	Swiat& referencja;
	bool kolizja(int pozx, int pozy) override;
	void akcja() override;
};

