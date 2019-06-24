#pragma once
#ifndef OWCA_H
#define OWCA_H

#include "Zwierze.h"
class Zwierze; 
class Owca : public Zwierze
{
public:
	Owca( Swiat&  ref, Organizm*** moj_swiat, int x, int y);
	~Owca();

private:
	Swiat &  referencja;
	Organizm*** moj_swiat;
	bool kolizja(int pozx, int pozy) { return true; };
	
};
#endif // !OWCA_H