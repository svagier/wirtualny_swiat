#include "Organizm.h"

Organizm::Organizm(Swiat& ref)
	: referencja((Swiat&)ref) 
{
	
}

Organizm::~Organizm()
{
}

void Organizm::setX(int x) {
	this->x = x;
}
void Organizm::setY(int y) {
	this->y = y;
}
int Organizm::getX() const {
	return this->x;
}

void Organizm::setSila(int wartosc) {
	this->sila = wartosc;
}
int Organizm::getY() const {
	return this->y;
}

void Organizm::zamienPozycje(Organizm* right) {
	int tmpx = right->x;
	int tmpy = right->y;
	right->x = this->x;
	right->y = this->y;
	this->x = tmpx;
	this->y = tmpy;
}

void Organizm::zamienPozycje(Organizm* left, Organizm* right) {
	int tmpx = right->x;
	int tmpy = right->y;
	right->x = left->x;
	right->y = left->y;
	left->x = tmpx;
	left->y = tmpy;
}

int Organizm::getSila() const {
	return this->sila;
}

bool Organizm::getMozliwoscRozmnazania() const {
	return this->mozliwosc_rozmnazania;
}
void Organizm::setMozliwoscRozmnazania(bool check) {
	this->mozliwosc_rozmnazania = check;
}
bool Organizm::getMozliwoscRuchu() const {
	return this->mozliwosc_ruchu;
}
void Organizm::setMozliwoscRuchu(bool check) {
	this->mozliwosc_ruchu = check;
}