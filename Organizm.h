#pragma once
#ifndef ORGANIZM_H
#define ORGANIZM_H
#include "Swiat.h"

struct POZYCJA {	//potrzebne do metody rozmnazanie
	int x; 
	int y;
};

class Organizm
{
	friend class Swiat;
	friend class Zwierze;
public:
	Organizm( Swiat&  ref);
	~Organizm();

	int getX() const;
	int getY() const;
	int getSila() const;
	bool getMozliwoscRozmnazania() const;
	void setMozliwoscRozmnazania(bool check);
	bool getMozliwoscRuchu() const;
	void setMozliwoscRuchu(bool check);
	
	void setSila(int wartosc);
	std::string nazwa;
protected:
	Organizm *** moj_swiat;
	Swiat& referencja;
	int  inicjatywa, x, y;
	char znak;
	int sila;
	bool mozliwosc_rozmnazania;
	bool mozliwosc_ruchu;
	virtual void akcja() = 0;
	virtual bool kolizja(int pozx, int pozy) = 0;
	void setX(int x);
	void setY(int y);
	void zamienPozycje(Organizm* left, Organizm* right);
	void zamienPozycje(Organizm* right);
	int indeks;
};

#endif