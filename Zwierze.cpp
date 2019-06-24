#include "Zwierze.h"

Zwierze::Zwierze(Swiat& ref, Organizm*** moj_swiat)
	:Organizm(ref), referencja(ref), moj_swiat(moj_swiat)
{
	this->mozliwosc_ruchu = true;
	this->mozliwosc_rozmnazania = true;
	this->referencja.increaseLicznikZwierzat();
	this->indeks = this->referencja.getLicznikZwierzat();
}

Zwierze::~Zwierze()
{
}

 void Zwierze::akcja()  {
	 this->losujRuch();
}

 void Zwierze::losujRuch() {
	 if (this->mozliwosc_ruchu == true) {
		 mozliwosc_ruchu = false;
		 int var = (rand() % 100) % 2;

		 if (var) {
			 if (var && this->y > 1 && this->referencja.wGranicach(this->x, this->y))
				 this->ruch(this->moj_swiat, this->x, this->y - 1);

			 else if (this->y < this->referencja.getWysokosc() && this->referencja.wGranicach(this->x, this->y))  //sprawdzamy aby nie wyjechac poza tablice
				 this->ruch(this->moj_swiat, this->x, this->y + 1);
		 }

		 else {
			 if (var && this->x > 1 && this->referencja.wGranicach(this->x, this->y))
				 this->ruch(this->moj_swiat, this->x - 1, this->y);
			 else if (this->x< this->referencja.getSzerokosc() && this->referencja.wGranicach(this->x, this->y)) //sprawdzamy aby nie wyjechac poza tablice
				 this->ruch(this->moj_swiat, this->x + 1, this->y);
		 }
	 }
 }

 void Zwierze::ruch(Organizm*** moj_swiat, int pozx, int pozy){
	 auto tmp = this->referencja.getTyp(pozy, pozx); //auto - zastêpczy typ zmiennej

	 if (this->referencja.wGranicach(pozx, pozy)) {
		 int tmpx = this->x;
		 int tmpy = this->y;
		 if (typeid(*tmp) == typeid(Pustka&)) {		//pustka, wiec mozna przejsc na to pole
			 zamienPozycje(moj_swiat[pozy][pozx]);
			 std::swap(moj_swiat[this->y][this->x], moj_swiat[tmpy][tmpx]);
		 }
		 else if (typeid(*tmp) == typeid(*this)) {		//ten sam organizm -> rozmnazanie
			 if (this->mozliwosc_rozmnazania == true && moj_swiat[pozy][pozx]->mozliwosc_rozmnazania == true) {
				 this->rozmnazanie(moj_swiat, pozx, pozy, this->x, this->y);		//przekazujemy wspolrzedne obu rodzicow
			 }
		 }
		 else this->walka(moj_swiat, pozx, pozy);
	 }
 }

 void Zwierze::walka(Organizm*** moj_swiat, int pozx, int pozy) {

	 if (moj_swiat[pozy][pozx]->kolizja(this->x, this->y) == true) {		//sprawdzamy czy do kolizji na pewno dojdzie (zwierze moze odbic lub uciec)
		 if (this->sila >= moj_swiat[pozy][pozx]->sila) { //this wygrywa(bo pierwszy zaatakowal albo sila wieksza)
			 if (moj_swiat[pozy][pozx]->inicjatywa > 0) {
				 std::ofstream outfile;
				 outfile.open("logs.txt", std::ios_base::app);
				 outfile << this->nazwa << "(" << this->x << "," << this->y << ") zaatakowal/a i zabil/a " << this->moj_swiat[pozy][pozx]->nazwa << "(" << pozx << "," << pozy << ").\n";
				 outfile.close();
			 }

			 int tmpx = this->x;
			 int tmpy = this->y;
			 this->referencja.zabijOrganizm(pozx, pozy);
			 zamienPozycje(moj_swiat[pozy][pozx]);
			 std::swap(moj_swiat[this->y][this->x], moj_swiat[tmpy][tmpx]);
		 }

		 else {		//drugi wygrywa, bo ma wieksza sile
				 std::ofstream outfile;
				 outfile.open("logs.txt", std::ios_base::app);
				 outfile << this->nazwa << "(" << this->x << "," << this->y << ") zaatakowal/a " << this->moj_swiat[pozy][pozx]->nazwa << "(" << pozx << "," << pozy << ") i umarl/a.\n";
				 outfile.close();
			 this->referencja.zabijOrganizm(this->x, this->y);		//zamienilemz  tym co ponizej
			 //moj_swiat[this->y][this->x] = new Pustka(this->x, this->y, referencja, moj_swiat);		//zmienielm bo chyba zle, pewnie errory beda
		 }
	 }
 }


 //pozx1 i pozx2 to odpowiedno wspolrzedne obu rodzicow
 //szukamy wolnego pola obok jednego z nich
 POZYCJA Zwierze:: znajdzWolne(int pozx1, int pozy1, int pozx2, int pozy2) {
	 
	 int dummy = (rand() % 800)+1;
	 POZYCJA wolne = { BRAK_WOLNYCH_POL , BRAK_WOLNYCH_POL };
	 int var = (rand() % dummy) + 1;
	 for (int i = 0; i < 8; i++) {
		 switch (var % 8) {
		 case 0: 
			 if (this->referencja.wGranicach(pozx1, pozy1+1) && typeid(*this->moj_swiat[pozy1 + 1][pozx1]) == typeid(Pustka&)) {
				 wolne = { pozx1, pozy1 + 1 };
				 return wolne;
			 }
			 break;
		 
		 case 1: 
			 if (this->referencja.wGranicach(pozx1, pozy1 - 1) && typeid(*this->moj_swiat[pozy1 - 1][pozx1]) == typeid(Pustka&)) {
				 wolne = { pozx1, pozy1 - 1 };
				 return wolne;
			 }
			 break;
		 
		 case 2: 
			 if (this->referencja.wGranicach(pozx1+1, pozy1) && typeid(*this->moj_swiat[pozy1][pozx1 + 1]) == typeid(Pustka&)) {
				 wolne = { pozx1 + 1, pozy1 };
				 return wolne;
			 }
			 break;
		 
		 case 3: 
			 if (this->referencja.wGranicach(pozx1-1, pozy1) && typeid(*this->moj_swiat[pozy1][pozx1-1]) == typeid(Pustka&)) {
				 wolne = { pozx1 - 1, pozy1};
				 return wolne;
			 }
			 break;
		 
		 case 4: 
			 if (this->referencja.wGranicach(pozx2, pozy2 + 1) && typeid(*this->moj_swiat[pozy2 + 1][pozx2]) == typeid(Pustka&)) {
				 wolne = { pozx2, pozy2 + 1 };
				 return wolne;
			 }
			 break;
		 
		 case 5: 
			 if (this->referencja.wGranicach(pozx2, pozy2 - 1) && typeid(*this->moj_swiat[pozy2 - 1][pozx2]) == typeid(Pustka&)) {
				 wolne = { pozx2, pozy2 - 1 };
				 return wolne;
			 }
			 break;
		 
		 case 6: 
			 if (this->referencja.wGranicach(pozx2 + 1, pozy2) && typeid(*this->moj_swiat[pozy2][pozx2 + 1]) == typeid(Pustka&)) {
				 wolne = { pozx2 + 1, pozy2 };
				 return wolne;
			 }
			 break;
		 
		 case 7: 
			 if (this->referencja.wGranicach(pozx2 - 1, pozy2) && typeid(*this->moj_swiat[pozy2][pozx2-1]) == typeid(Pustka&)) {
				 wolne = { pozx2 - 1, pozy2 };
				 return wolne;
			 }
			 break;
		 
		 default:
			 wolne= {BRAK_WOLNYCH_POL, BRAK_WOLNYCH_POL };
			 break;
			 }
		 
			 var++;
	 }
	 return wolne;
 }

 //pozx1 i pozx2 to odpowiednio wspolrzedne polozenia obu rodzicow
 void Zwierze::rozmnazanie(Organizm*** moj_swiat, int pozx1, int pozy1, int pozx2, int pozy2) {
	 POZYCJA tmp;
	 tmp = this->znajdzWolne(this->x, this->y, pozx1, pozy1);
	// int tmpx = this->znajdzWolne(this->x, this->y, pozx1, pozy1).x;
	// int tmpy = this->znajdzWolne(this->x, this->y, pozx1, pozy1).y;
	 if (tmp.x != BRAK_WOLNYCH_POL && tmp.y != BRAK_WOLNYCH_POL) {
		 this->referencja.nowyOrganizm(this->x, this->y, tmp.x, tmp.y); //nowonarodzony organizm moze rozmnazac sie dopiero
		 moj_swiat[pozy1][pozx1]->mozliwosc_rozmnazania = false;		//w kolejnej turze (zmiana wewnatrz nowyOrganizm).
		 moj_swiat[pozy2][pozx2]->mozliwosc_rozmnazania = false;		//rodzice organizmu nie moga do konca tury ponownie sie rozmanazac.

		 std::ofstream outfile;
		 outfile.open("logs.txt", std::ios_base::app);
		 outfile << this->nazwa << "(" << this->x << "," << this->y << ") rozmnozyl/a sie z  " << this->moj_swiat[pozy1][pozx1]->nazwa << "(" << pozx1 << "," << pozy1 << ").\n";
		 outfile.close();
	 }
 }