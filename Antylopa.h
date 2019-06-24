#pragma once
#include "Zwierze.h"
class Antylopa : public Zwierze
{
public:
	Antylopa(Swiat& ref, Organizm*** moj_swiat, int x, int y);
	~Antylopa();
private:
	Swiat &  referencja;
	Organizm*** moj_swiat;
	void akcja() override;
	bool kolizja(int pozx, int pozy) override;
	void losujRuch();
};

