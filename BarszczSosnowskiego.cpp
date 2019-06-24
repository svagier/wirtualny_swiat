#include "BarszczSosnowskiego.h"
#include "Pustka.h"

BarszczSosnowskiego::BarszczSosnowskiego(Swiat& ref, Organizm*** moj_swiat, int x, int y)
	: Roslina(ref, moj_swiat), referencja(ref), moj_swiat(moj_swiat)
{
	this->x = x;
	this->y = y;
	this->znak = 'b';
	this->nazwa = "Barszcz Sosnowskiego";
}

BarszczSosnowskiego::~BarszczSosnowskiego()
{
}

void BarszczSosnowskiego:: akcja() {
	int var = (rand() % 100) + 1;
	if (var <= PRAWD_ROZSIEWANIA)
		this->rozmnazanie();
	std::ofstream outfile;
	outfile.open("logs.txt", std::ios_base::app);
	
	if (this->referencja.wGranicach(this->x, this->y + 1)) {
		auto tmp1 = this->referencja.getTyp(this->y + 1, this->x);
		if (typeid(*tmp1) != typeid(BarszczSosnowskiego&) && typeid(*tmp1) != typeid(Pustka&)) {
			outfile << this->nazwa << "(" << this->x << "," << this->y << ") zabil "
			<< this->moj_swiat[this->y + 1][this->x]->nazwa << "(" << this->x << "," << this->y + 1 << ").\n";
			this->referencja.zabijOrganizm(this->x, this->y + 1);
		}	
	}
	 
	 if (this->referencja.wGranicach(this->x, this->y - 1)) {
		auto tmp2 = this->referencja.getTyp(this->y - 1, this->x);
		if (typeid(*tmp2) != typeid(BarszczSosnowskiego&) && typeid(*tmp2) != typeid(Pustka&)) {
			outfile << this->nazwa << "(" << this->x << "," << this->y << ") zabil "
			<< this->moj_swiat[this->y - 1][this->x]->nazwa << "(" << this->x << "," << this->y - 1 << ").\n";
			this->referencja.zabijOrganizm(this->x, this->y - 1);
		}	
	 }

	if (this->referencja.wGranicach(this->x + 1, this->y)) {
		auto tmp3 = this->referencja.getTyp(this->y, this->x + 1);
		if (typeid(*tmp3) != typeid(BarszczSosnowskiego&) && typeid(*tmp3) != typeid(Pustka&)) {
			outfile << this->nazwa << "(" << this->x << "," << this->y << ") zabil "
			<< this->moj_swiat[this->y][this->x+1]->nazwa << "(" << this->x+1 << "," << this->y << ").\n";
			this->referencja.zabijOrganizm(this->x + 1, this->y);
		}	
	}

	 if (this->referencja.wGranicach(this->x - 1, this->y)) {
		 auto tmp4 = this->referencja.getTyp(this->y, this->x - 1);
		 if (typeid(*tmp4) != typeid(BarszczSosnowskiego&) && typeid(*tmp4) != typeid(Pustka&)) {
			 outfile << this->nazwa << "(" << this->x << "," << this->y << ") zabil "
				 << this->moj_swiat[this->y][this->x - 1]->nazwa << "(" << this->x -1 << "," << this->y << ").\n";
			 this->referencja.zabijOrganizm(this->x - 1, this->y);
		 }	 
	}

	 outfile.close();
}

bool BarszczSosnowskiego::kolizja(int pozx, int pozy) {
	std::ofstream outfile;
	outfile.open("logs.txt", std::ios_base::app);
	outfile << this->moj_swiat[pozy][pozx]->nazwa << "(" << pozx << "," << pozy << ") zjadl/a " << this->nazwa << "(" << this->x << "," << this->y << ") i umarl/a.\n";
	outfile.close();
	this->referencja.zabijOrganizm(pozx, pozy);
	return false;
}