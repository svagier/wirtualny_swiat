#pragma once
#ifndef SWIAT_H
#define SWIAT_H
#include "moje_define.h"
#include<windows.h>
#include "Organizm.h"
//#include "Zwierze.h"
class Organizm;
class Pustka;
class Swiat
{
	friend class Roslina;
	friend class Organizm;
	friend class Zwierze;
public:
	Swiat(const int szerokosc, const int wysokosc);
	~Swiat();

	int getWysokosc() const;
	int getSzerokosc() const;
	int getCzlowiekX() const;
	int getCzlowiekY() const;
	int getCzlowiekNowyX() const;
	int getCzlowiekNowyY() const;
	int getTarczaAlzura() const;
	int getLicznikTur() const;
	int getLicznikZwierzat() const;
	bool getKoniecGry() const;
	bool getCzlowiekZywy() const;
	void setCzlowiekNowyX(int x);
	void setCzlowiekNowyY(int y);
	void setCzlowiekX(int x);
	void setCzlowiekY(int y);
	void setTarczaAlzura(int x);
	void setLicznikTur(int tmp);
	void setKoniecGry(bool tmp);
	void setCzlowiekZywy(bool tmp);
	void setSaveLicznikTur(int x);
	void setSaveTarczaAlzura(int x);
	void increaseLicznikZwierzat();

	void rysujSwiat();
	Organizm* getTyp(int y, int x) const;
	const Organizm& operator[](std::size_t i) const;
	bool wGranicach(int x, int y);
	void zabijOrganizm(int x, int y);
	void inicjalizujSave();
	void wczytajSave();
	

private:
	const int szerokosc;
	const int wysokosc;
	int licznik_zwierzat;
	int licznik_tur;
	int czlowiekX, czlowiekY;		//zapamietuje pozycje czlowieka
	int czlowiekNowyX, czlowiekNowyY; //do zmiany pozycji czlowieka
	int tarcza_alzura;
	bool koniec_gry;
	bool czlowiek_zywy;

	int** sortujInicjatywe(int **arr);
	int** aktualizujInicjatywe(int **arr);
	int** inicjalizujInicjatywe(int** arr);
	int** lista_inicjatywy;

	void wypiszInicjatywe(int **arr);//do sprawdzania i debugowania
	void nowyOrganizm(int x, int y, int newx, int newy);
	void wyswietlLogi(int licznik);
	void gotoxy(int x, int y);
	void rysujLegende();
	void wykonajTure();
	void poczatkoweOrganizmy();
	void resetujFlagi();
	void switchZnak(char znak, int newx, int newy, Swiat& ref);
	Organizm *** swiat;
	bool zaladowano_save;
	int save_licznik_tur;
	int save_tarcza_alzura;
};
#endif

