#pragma once
#ifndef LIS_H
#define LIS_H

#include "Zwierze.h"
class Lis : public Zwierze
{
public:
	Lis(Swiat&  ref, Organizm*** moj_swiat, int x, int y);
	~Lis();
private:
	Swiat & referencja;//czy private?

	Organizm*** moj_swiat; //prot czy priv?
	void walka(Organizm*** moj_swiat, int pozx, int pozy) override;
	bool kolizja(int pozx, int pozy) { return true; };
};
#endif // !LIS_H