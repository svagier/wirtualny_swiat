#pragma once

#include <iostream>
#include <fstream>	
#include <string>

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77

#define X_START 2		//punkt odniesienia do rysowania planszy
#define Y_START 2		
#define X_ROZMIAR 20
#define Y_ROZMIAR 20
#define BRAK_WOLNYCH_POL 99999
#define BLAD 999999

#define X_LOG 70		//pozycja logow
#define Y_LOG 5
#define X_CZLOWIEK 1		//musi miescic sie w wymiarach tablicy
#define Y_CZLOWIEK 1

#define PRAWD_ROZSIEWANIA 30  //okresla prawdopodob. na podjecie proby rozsiewu przez rosline
//przyjmuje wartosci od 1 do 100 (procenty)
