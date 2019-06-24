#pragma once
#include "Roslina.h"
class WilczeJagody : public Roslina
{
public:
	WilczeJagody(Swiat& ref, Organizm*** moj_swiat, int x, int y);
	~WilczeJagody();
private:
	Organizm *** moj_swiat;
	Swiat& referencja;
	bool kolizja(int pozx, int pozy) override;
};

