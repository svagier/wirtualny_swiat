#pragma once
#include "Zwierze.h"
class Czlowiek : public Zwierze
{
public:
	~Czlowiek();
	Czlowiek(Swiat& ref, Organizm*** moj_swiat, int x, int y);

private:
	void akcja() override;
	Swiat& referencja;
	bool kolizja(int pozx, int pozy);
};

