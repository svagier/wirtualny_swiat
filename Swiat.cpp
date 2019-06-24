#include "Swiat.h"
#include "Pustka.h"
#include "Owca.h"
#include "Wilk.h"
#include "Lis.h"
#include "Antylopa.h"
#include "Zolw.h"
#include "Trawa.h"
#include "Czlowiek.h"
#include "Guarana.h"
#include "Mlecz.h"
#include "WilczeJagody.h"
#include "BarszczSosnowskiego.h"

//organizmy wpisane s¹ w pola od 1 do 20 wlacznie
Swiat::Swiat(int szerokosc, int wysokosc)
	: szerokosc(szerokosc), wysokosc(wysokosc)
{
	koniec_gry = false;
	this->czlowiekX = BLAD;
	this->czlowiekY = BLAD;
	this->czlowiekNowyX = BLAD;
	this->czlowiekNowyY = BLAD;
	this->czlowiek_zywy = false;
	swiat = new Organizm**[wysokosc+1];
	for (int i = 0; i <= wysokosc; i++) {		
		swiat[i] = new Organizm*[szerokosc+1];
		for (int j = 0; j <= szerokosc; j++) {
			if (i!=0 && j!=0)
				swiat[i][j] = new Pustka(j, i, *this, swiat);
		}	
	}
	this->lista_inicjatywy= inicjalizujInicjatywe(this->lista_inicjatywy);
	this->tarcza_alzura = -10;
	this->licznik_zwierzat = 0;
	poczatkoweOrganizmy();
	this->zaladowano_save = false;


	std::ofstream ofstr;
	ofstr.open("save.txt", std::ofstream::out | std::ofstream::trunc);		//czyszczenie pliku txt logow przed pierwsza tura
	ofstr.close();
}

void Swiat::poczatkoweOrganizmy() {
	delete swiat[Y_CZLOWIEK][X_CZLOWIEK];
	swiat[Y_CZLOWIEK][X_CZLOWIEK] = new Czlowiek(*this, swiat, X_CZLOWIEK, Y_CZLOWIEK);	//x i y odwortnie!

	delete swiat[19][19];
	swiat[19][19] = new Antylopa(*this, swiat, 19, 19);//temp
	delete swiat[1][2];
	swiat[1][2] = new Guarana(*this, swiat, 2, 1);//temp
	delete swiat[3][1];
	swiat[3][1] = new Owca(*this, swiat, 1, 3);//temp
	delete swiat[2][1];
	swiat[2][1] = new Lis(*this, swiat, 1, 2);//temp
	delete swiat[4][1];
	swiat[4][1] = new Mlecz(*this, swiat, 1, 4);//temp
	delete swiat[2][2];
	swiat[2][2] = new Wilk(*this, swiat, 2, 2);//temp
	delete swiat[20][17];
	swiat[20][17] = new Owca(*this, swiat, 17, 20);//temp
	delete swiat[20][14];
	swiat[20][14] = new Owca(*this, swiat, 14, 20);//temp
	delete swiat[19][1];
	swiat[19][1] = new BarszczSosnowskiego(*this, swiat, 1, 19);//temp
	delete swiat[20][1];
	swiat[20][1] = new Antylopa(*this, swiat, 1, 20);//temp
	delete swiat[19][2];
	swiat[19][2] = new Zolw(*this, swiat, 2, 19);//temp
	delete swiat[20][9];
	swiat[20][9] = new Trawa(*this, swiat, 9, 20);//temp
	delete swiat[20][20];
	swiat[20][20] = new WilczeJagody(*this, swiat, 20, 20);//temp

}

Swiat::~Swiat()
{	//zwalnianie pamieci z listy inicjatywy
	for (int k = 0; k < this->wysokosc; k++) 
		for (int j = 0; j < this->szerokosc; j++) 
			delete[] lista_inicjatywy[k*this->wysokosc + j];

	delete[] this->lista_inicjatywy;

	//zwalnianie pamieci tablicy organizmow
	for (int i = 0; i <= wysokosc; i++) {
		for (int j = 0; j <= wysokosc; j++)
			if (i != 0 && j != 0)
				delete swiat[i][j];
		delete[] swiat[i];
	}
	delete[] swiat;
}

const Organizm& Swiat::	operator[](std::size_t i) const
{
	return **swiat[i];
}

void Swiat::rysujSwiat() {
	system("cls");
	if (this->zaladowano_save == true) {		//jesli dopiero co wczytalismy save to ma sie tylko narysowac, a nie wykonywac tura
		this->zaladowano_save = false;
		gotoxy(X_LOG, Y_LOG + 2);
		std::cout << "----- WCZYTANO ZAPIS GRY -----";
	}

	else if(this->getLicznikTur()>0)
		this->wykonajTure();
	for (int i = 0; i <= wysokosc+1; i++) {
		for (int j = 0; j <= szerokosc+1; j++) {
			if (i == 0 || j == 0 || i == wysokosc+1 || j == szerokosc+1) {
				gotoxy(j + X_START, i + Y_START);
				std::cout << "X";
			}
				
			else {
				gotoxy(j + X_START, i + Y_START);
				std::cout << swiat[i][j]->znak;
			}	
		}
	}
	this->rysujLegende();
	this->wyswietlLogi(this->getLicznikTur());
	this->licznik_tur++;
}

void Swiat::wykonajTure() {
	resetujFlagi();
	this->lista_inicjatywy = aktualizujInicjatywe(this->lista_inicjatywy);
	this->lista_inicjatywy = sortujInicjatywe(this->lista_inicjatywy);
	for (int i = 0; i < this->wysokosc*this->szerokosc; i++) {	//kolejnosc wg posortowanej inicjatywy i wieku
			int tmpx = this->lista_inicjatywy[i][2];		//ustawiamy x wedlug kolejnosci inicjatywy
			int tmpy = this->lista_inicjatywy[i][3];		//ustawiamy y wedlug kolejnosci inicjatywy
			if (tmpx != BLAD && tmpy != BLAD) {
				if (swiat[tmpy][tmpx]->inicjatywa==0)
					swiat[tmpy][tmpx]->akcja();		//jesli to roslina to sie rusza bez warunkow
				else if (swiat[tmpy][tmpx]->mozliwosc_ruchu == true)	//jesli to zwierze to
					swiat[tmpy][tmpx]->akcja();							//sprawdzamy czy po ruchu nie zajelo innego pola
			} 
			
	}
	this->czlowiekX = this->czlowiekNowyX;
	this->czlowiekY = this->czlowiekNowyY;
	this->tarcza_alzura--;

}

int** Swiat::inicjalizujInicjatywe(int **arr) {
	arr = new int*[this->wysokosc*this->szerokosc];
	for (int k = 0; k < this->wysokosc; k++) {
		for (int j = 0; j < this->szerokosc; j++) {
			arr[k*this->wysokosc+j] = new int[4];		
			arr[k*this->wysokosc + j][0] = swiat[k+1][j+1]->inicjatywa;		
			arr[k*this->wysokosc + j][1] = swiat[k+1][j+1]->indeks;		//im mniejszy tym starszy
			arr[k*this->wysokosc + j][2] = j + 1;		//X
			arr[k*this->wysokosc + j][3] = k + 1;		//Y
		}		
	}
	return arr;
}

int** Swiat::aktualizujInicjatywe(int **arr) {
	for (int k = 0; k < this->wysokosc; k++) {
		for (int j = 0; j < this->szerokosc; j++) {
			arr[k*this->wysokosc + j][0] = swiat[k + 1][j + 1]->inicjatywa;
			arr[k*this->wysokosc + j][1] = swiat[k + 1][j + 1]->indeks;		//im mniejszy tym starszy
			arr[k*this->wysokosc + j][2] = j + 1;		//X
			arr[k*this->wysokosc + j][3] = k + 1;		//Y
		}
	}
	return arr;
}

int** Swiat::sortujInicjatywe(int **arr) {									//sortowanie: najwieksza inicjatywa [0] na poczatku
	for (int k = 0; k < this->wysokosc*this->szerokosc; k++) {				//jesli inicjatywy sa rowne decyduje kolejnosc [1]
		for (int j = 0; j < ((this->wysokosc*this->szerokosc)-1); j++) {	//im mniejsza wartosc[1] tym starsze
			if (arr[j][0] < arr[j + 1][0]) {
				std::swap(arr[j][0], arr[j + 1][0]);		//zamieniamy odpowiednie komorki miejscami
				std::swap(arr[j][1], arr[j + 1][1]);
				std::swap(arr[j][2], arr[j + 1][2]);
				std::swap(arr[j][3], arr[j + 1][3]);
			}

			if (arr[j][0] == arr[j + 1][0]) {		//jesli taka sama inicjatywa
				if (arr[j][1] > arr[j + 1][1]) {		//jesli jest mlodsze to zamien miejscami
					std::swap(arr[j][0], arr[j + 1][0]);
					std::swap(arr[j][1], arr[j + 1][1]);
					std::swap(arr[j][2], arr[j + 1][2]);
					std::swap(arr[j][3], arr[j + 1][3]);
				}
			}
		}
	}
	return arr;
}

void Swiat::wypiszInicjatywe(int **arr) {		//do sprawdzania
	std::cout << std::endl;
	for (int k = 0; k < this->wysokosc; k++) {
		for (int j = 0; j < this->szerokosc; j++) {
			std::cout << "i: " << arr[k*this->wysokosc + j][0] << " |w: " << arr[k*this->wysokosc + j][1] << " |x: " << arr[k*this->wysokosc + j][2] << " |y: " << arr[k*this->wysokosc + j][3] << std::endl;
		}
	}

}

void Swiat::resetujFlagi() {
	for (int i = 1; i <= wysokosc; i++) {
		for (int j = 1; j <= szerokosc; j++) {
			auto tmp = getTyp(i, j);		//auto - zastêpczy typ zmiennej
			if (typeid(*tmp) != typeid(Pustka&)) {		//resetujemy runde: 
				swiat[i][j]->mozliwosc_rozmnazania = true;		//kazde zwierze i roslina moze sie znow rozmnazac
				if (swiat[i][j]->inicjatywa>0)
					swiat[i][j]->mozliwosc_ruchu = true;			//kazde zwierze moze sie znow ruszac
								//nowonarodzone zwierzeta nie moga sie rozmnazac od razu po narodzinach.
			}
		}
	}
}


int Swiat::getSzerokosc() const {
	return this->szerokosc;
}

 int Swiat::getWysokosc() const{
	return this->wysokosc;
}

 Organizm* Swiat::getTyp(int y, int x) const {
	 //if (y>0 && x>0 && y<=wysokosc && x<=szerokosc)		//usuniete tymczasowo - beda errory?
	 return swiat[y][x];
 }


 void Swiat::nowyOrganizm(int x, int y, int newx, int newy)  {
	 if (wGranicach(x, y) && wGranicach(newx, newy)) {
		 this->switchZnak(swiat[y][x]->znak, newx, newy, swiat[y][x]->referencja);
		 swiat[newy][newx]->mozliwosc_rozmnazania = false;
	 }
 }

 void Swiat::switchZnak(char znak, int newx, int newy, Swiat& ref) {
	 switch (znak) {
	 case 'o': {
		 delete swiat[newy][newx];
		 swiat[newy][newx] = new Owca(ref, swiat, newx, newy);
		 break;
	 }
	 case 'w': {
		 delete swiat[newy][newx];
		 swiat[newy][newx] = new Wilk(ref, swiat, newx, newy);
		 break;
	 }
	 case 'l': {
		 delete swiat[newy][newx];
		 swiat[newy][newx] = new Lis(ref, swiat, newx, newy);
		 break;
	 }
	 case 'a': {
		 delete swiat[newy][newx];
		 swiat[newy][newx] = new Antylopa(ref, swiat, newx, newy);
		 break;
	 }
	 case 'z': {
		 delete swiat[newy][newx];
		 swiat[newy][newx] = new Zolw(ref, swiat, newx, newy);
		 break;
	 }
	 case 't': {
		 delete swiat[newy][newx];
		 swiat[newy][newx] = new Trawa(ref, swiat, newx, newy);
		 break;
	 }
	 case 'm': {
		 delete swiat[newy][newx];
		 swiat[newy][newx] = new Mlecz(ref, swiat, newx, newy);
		 break;
	 }
	 case 'g': {
		 delete swiat[newy][newx];
		 swiat[newy][newx] = new Guarana(ref, swiat, newx, newy);
		 break;
	 }
	 case 'j': {
		 delete swiat[newy][newx];
		 swiat[newy][newx] = new WilczeJagody(ref, swiat, newx, newy);
		 break;
	 }
	 case 'b': {
		 delete swiat[newy][newx];
		 swiat[newy][newx] = new BarszczSosnowskiego(ref, swiat, newx, newy);
		 break;
	 }
	 case '.': {
		 delete swiat[newy][newx];
		 swiat[newy][newx] = new Pustka(ref, swiat, newx, newy);
		 break;
	 }
	 case 'c': {
		 delete swiat[newy][newx];
		 swiat[newy][newx] = new Czlowiek(ref, swiat, newx, newy);
		 break;
	 }
	 }

 }

 bool Swiat::wGranicach(int x, int y) {		//sprawdza czy nie probujemy sie dostac poza tablice
	 if (x > 0 && x <= getSzerokosc())
		 if (y > 0 && y <= getWysokosc())
			 return true;
		 else return false;
	 else return false;
 }

 void Swiat::zabijOrganizm(int pozx, int pozy) {
	 auto tmp = getTyp(pozy, pozx);			 
	 if (typeid(*tmp) != typeid(Pustka&)) {
		 if(typeid(*tmp) == typeid(Czlowiek&))
			 this->czlowiek_zywy = false;
		 delete this->swiat[pozy][pozx];
		 this->swiat[pozy][pozx] = new Pustka(pozx, pozy, *this, swiat);
	 }
 }

 void Swiat::rysujLegende() {
	 using namespace std;
	 gotoxy(X_START, Y_START+this->wysokosc+6);
	 cout << "Piotr Danielczyk 171953";

	 int poziomo = X_START + this->szerokosc + 4;
	 int pionowo = Y_START  + 1;
	 gotoxy(poziomo, pionowo);
	 int i = 1;
	 cout << "Legenda:";
	 gotoxy(poziomo, pionowo + i); i++;
	 cout << "c - czlowiek";
	 gotoxy(poziomo, pionowo + i); i++;
	 cout << "a - antylopa";
	 gotoxy(poziomo, pionowo + i); i++;
	 cout << "o - owca";
	 gotoxy(poziomo, pionowo + i); i++;
	 cout << "z - zolw";
	 gotoxy(poziomo, pionowo + i); i++;
	 cout << "w - wilk";
	 gotoxy(poziomo, pionowo + i); i++;
	 cout << "l - lis";
	 gotoxy(poziomo, pionowo + i); i++;
	 cout << "t - trawa";
	 gotoxy(poziomo, pionowo + i); i++;
	 cout << "g - gurana";
	 gotoxy(poziomo, pionowo + i); i++;
	 cout << "m - mlecz";
	 gotoxy(poziomo, pionowo + i); i++;
	 cout << "j - wilcze jagody";
	 gotoxy(poziomo, pionowo + i); i++;
	 cout << "b - barszcz Sosnowskiego";
	 i++;
	 gotoxy(poziomo, pionowo + i); i++;
	 cout << "strzalki - sterowanie czlowiekiem";
	 gotoxy(poziomo, pionowo + i); i++;
	 cout << "t - aktywuj Tarcze Alzura";
	 gotoxy(poziomo, pionowo + i); i++;
	 cout << "n - nastepna runda (do symulacji)";
	 gotoxy(poziomo, pionowo + i); i++;
	 cout << "z - zapisz stan gry";
	 gotoxy(poziomo, pionowo + i); i++;
	 cout << "w - wczytaj ostatnia zapisana gre";
	 gotoxy(poziomo, pionowo + i); i++;
	 cout << "q - wyjdz z gry";
	 i++; i++;
	 gotoxy(poziomo, pionowo + i); i++;
	 if (this->czlowiek_zywy == true) {
		 if (this->tarcza_alzura > 0)
			 cout << "Tarcza Alzura aktywna jeszcze przez " << this->tarcza_alzura << " tury";
		 else if (this->tarcza_alzura <= 0 && this->tarcza_alzura>-5)
			 cout << "Tarcza Alzura niedostepna jeszcze przez " << 5 + this->tarcza_alzura << " tury";
		 else cout << "Tarcza Alzura dostepna";
		 gotoxy(poziomo, pionowo + i); i++;
		 cout << "Aktualna pozycja czlowieka to (x, y):";
		 gotoxy(poziomo, pionowo + i); i++;
		 cout<< "(" << this->czlowiekX << ", " << this->czlowiekY << ")";
	 }

	 else cout << "!!! Czlowiek umarl! Koniec gry. !!!";
	 gotoxy(poziomo, pionowo + i); i++;
 }

 int Swiat::getCzlowiekX() const {
	 return this->czlowiekX;
 }
 int Swiat::getCzlowiekY() const {
	 return this->czlowiekY;
 }
 int Swiat::getCzlowiekNowyX() const {
	 return this->czlowiekNowyX;
 }
 int Swiat::getCzlowiekNowyY() const {
	 return this->czlowiekNowyY;
 }
 void Swiat::setCzlowiekNowyX(int x) {
	 this->czlowiekNowyX = x;

 }
 void Swiat::setCzlowiekNowyY(int y) {
	 this->czlowiekNowyY = y;
 }

 void Swiat::setCzlowiekX(int x) {
	 this->czlowiekX = x;

 }
 void Swiat::setCzlowiekY(int y) {
	 this->czlowiekY = y;
 }

 int Swiat::getTarczaAlzura() const {
	 return this->tarcza_alzura;
 }
 int Swiat::getLicznikTur() const {
	 return this->licznik_tur;
 }
 bool Swiat::getKoniecGry() const {
	 return this->koniec_gry;
 }
 bool Swiat::getCzlowiekZywy() const {
	 return this->czlowiek_zywy;
 }
 int Swiat::getLicznikZwierzat() const {
	 return this->licznik_zwierzat;
 }

 void Swiat::setTarczaAlzura(int tmp) {
	 this->tarcza_alzura = tmp;
 }
 void Swiat::setLicznikTur(int tmp) {
	 this->licznik_tur = tmp;
 }
 void Swiat::setKoniecGry(bool tmp) {
	 this->koniec_gry = tmp;
 }
 void Swiat::setCzlowiekZywy(bool tmp) {
	 this->czlowiek_zywy = tmp;
 }

 void Swiat::increaseLicznikZwierzat() {
	 this->licznik_zwierzat++;
 }

 void Swiat::setSaveLicznikTur(int x) {
	 this->save_licznik_tur=x;
 }

 void Swiat::setSaveTarczaAlzura(int x) {
	 this->save_tarcza_alzura = x;
 }

 void Swiat::wyswietlLogi(int licznik) {
	 gotoxy(X_LOG, Y_LOG);
	 std::cout << "----- TURA NR " << licznik << " -----";
	 std::string line;
	 std::ifstream my_file("logs.txt");
	 int iterator = 2;
	 if (my_file.is_open()) {
		 while (getline(my_file, line)) {
			 gotoxy(X_LOG, Y_LOG + iterator);
			 std::cout << line;
			 iterator++;
		 }
		 my_file.close();
	 }
	 std::ofstream ofstr;
	 ofstr.open("logs.txt", std::ofstream::out | std::ofstream::trunc);		//czyszczenie pliku txt przed nastepnym otwarciem
	 ofstr.close();
 }

 void Swiat::gotoxy(int x, int y)
 {
	 COORD temp;
	 temp.X = x - 1;
	 temp.Y = y - 1;
	 SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), temp);
 }

 void Swiat::wczytajSave() {
	 using namespace std;

	 string s;
	 ifstream my_file("save.txt");
	 if (my_file.is_open()) {
		 int iter = 0;
		 gotoxy(0, 30 + 1);
		 for (int k = 0; k < this->wysokosc; k++) {
			 for (int j = 0; j < this->szerokosc; j++) {
				 int tmpx, tmpy, tmpindeks, tmpsila;
				 string tmpznak;
				 while (iter < 5) {
					 switch (iter) {
					 case 0:
						 if (my_file >> s)
							 tmpx = std::stoi(s);
						 break;
					 case 1:
						 if (my_file >> s)
							 tmpy = std::stoi(s);
						 break;
					 case 2:
						 if (my_file >> s)
							 tmpznak = s;

						 break;
					 case 3:
						 if (my_file >> s)
							 tmpindeks = std::stoi(s);
						 break;
					 case 4:
						 if (my_file >> s)
							 tmpsila = std::stoi(s);
						 break;
					 }


					 iter++;
				 }
				 iter = 0;
				 
				 //cout << tmpx << endl << tmpy << endl << tmpznak[0] << endl << tmpindeks << endl<<tmpsila<<endl;
				 this->switchZnak(tmpznak[0], tmpx, tmpy, *this);
			 }
		 }
	 }
	 my_file.close();


	 std::ofstream ofstr;
	 ofstr.open("logs.txt", std::ofstream::out | std::ofstream::trunc);		//czyszczenie logow
	 ofstr.close();

	 this->setLicznikTur(this->save_licznik_tur);
	 this->setTarczaAlzura(this->save_tarcza_alzura);
	 this->zaladowano_save = true;
	 this->rysujSwiat();
 }

void Swiat::inicjalizujSave() {
	std::ofstream ofstr;
	ofstr.open("save.txt", std::ofstream::out | std::ofstream::trunc);		//czyszczenie pliku txt przed nastepnym otwarciem
	ofstr.close();
	 std::ofstream outfile;
	 outfile.open("save.txt", std::ios_base::app);
	 for (int k = 0; k < this->wysokosc; k++) {
		 for (int j = 0; j < this->szerokosc; j++) {
			 outfile << j+1 << " " << k+1 << " " << swiat[k + 1][j + 1]->znak << " " << swiat[k + 1][j + 1]->indeks  << " " << swiat[k + 1][j + 1]->sila << " ";
		 }
	 }
	 outfile.close();
 }