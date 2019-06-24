#include <iostream>
#include "Swiat.h"
#include "moje_define.h"	//wszystkie define znajduja sie w moje_funkcje.h
#include"conio.h"		
#include <time.h> 

int main() {
	srand(time(NULL));
	using namespace std;


	Swiat gra(Y_ROZMIAR, X_ROZMIAR);
	
	bool wcisnieto_klawisz = false;
	int input;
	while (gra.getKoniecGry()== false) {
		
		gra.rysujSwiat();

		wcisnieto_klawisz = false;		//aby tura sie nie wykonywala gdy wcisniemy przycisk a nie mozemy wykonac ruchu
		while (wcisnieto_klawisz == false) {
			input = _getch();
			if (gra.getCzlowiekZywy() == true) {
				if (input == 0 || input == 224)
				{
					switch (_getch())
					{

					case KEY_UP:
						if (gra.wGranicach(gra.getCzlowiekX(), gra.getCzlowiekY() - 1)) {
							wcisnieto_klawisz = true;
							gra.setCzlowiekNowyY(gra.getCzlowiekY() - 1) ;
						}
						break;

					case KEY_DOWN:
						if (gra.wGranicach(gra.getCzlowiekX(), gra.getCzlowiekY() + 1)) {
							wcisnieto_klawisz = true;
							gra.setCzlowiekNowyY(gra.getCzlowiekY() + 1) ;
						}
						break;

					case KEY_LEFT:
						if (gra.wGranicach(gra.getCzlowiekX() - 1, gra.getCzlowiekY())) {
							wcisnieto_klawisz = true;
							gra.setCzlowiekNowyX(gra.getCzlowiekX() - 1) ;
						}
						break;

					case KEY_RIGHT:
						if (gra.wGranicach(gra.getCzlowiekX() + 1, gra.getCzlowiekY())) {
							wcisnieto_klawisz = true;
							gra.setCzlowiekNowyX(gra.getCzlowiekX() + 1) ;
						}
						break;
					}
				}
				if (input == 116)		//litera t
					if (gra.getTarczaAlzura() <= -4) {		//oznacza to, ze uplynelo 5 tur od zakonczenia dzialania tarczy
						gra.setTarczaAlzura(5);
						wcisnieto_klawisz = true;
					}
			}
			if (input == 110)		//litera n
				wcisnieto_klawisz = true;

			if (input == 122) {	//litera z
				gra.inicjalizujSave();
				gra.setSaveLicznikTur(gra.getLicznikTur());
				gra.setSaveTarczaAlzura(gra.getTarczaAlzura());
				wcisnieto_klawisz = false;
			}

			if (input == 119) {		//litera w
				gra.wczytajSave();
				wcisnieto_klawisz = false;
			}

			if (input == 113)		//litera q
				return 0;
		}
		
	}
	return 0;
}