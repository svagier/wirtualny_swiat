#pragma once
#include "Organizm.h"
class Roslina : public Organizm
{
public:
	Roslina(Swiat& ref, Organizm*** moj_swiat);
	~Roslina();
	void akcja() override;
	void rozmnazanie();
protected:
	 Swiat&  referencja;
	 Organizm*** moj_swiat;

	 POZYCJA znajdzWolne();
};

