#pragma once
#ifndef ZWIERZE_H
#define ZWIERZE_H
#include "Organizm.h"
#include <stdlib.h> 
#include <typeinfo>
#include"Pustka.h"

class Zwierze : public Organizm
{
public:
	Zwierze( Swiat&   ref, Organizm*** moj_swiat);
	~Zwierze();

protected:
	virtual void akcja();
	 Swiat&  referencja;
	Organizm*** moj_swiat;
	void ruch(Organizm*** moj_swiat, int x, int y);
	void losujRuch();
	virtual void walka(Organizm*** moj_swiat, int pozx, int pozy);
	bool czyWalka(Organizm*** moj_swiat, int pozx, int pozy);
	void rozmnazanie(Organizm*** moj_swiat, int pozx1, int pozy1, int pozx2, int pozy2);
	POZYCJA znajdzWolne(int pozx1, int pozy1, int pozx2, int pozy2);
};

#endif		//!ZWIERZE_H