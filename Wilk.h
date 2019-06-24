#pragma once
#ifndef WILK_H
#define WILK_H
#include "Zwierze.h"

class Wilk: public Zwierze
{
public:
	Wilk(Swiat&  ref, Organizm*** moj_swiat, int x, int y);
	~Wilk();

private:
	Swiat &  referencja;
	Organizm*** moj_swiat;
	bool kolizja(int pozx, int pozy) { return true; };
};

#endif // !WILK_H