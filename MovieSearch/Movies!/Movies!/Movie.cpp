#include "Movie.h"

Movie::Movie()
{
    title = "N/A";
    releaseDate = "00/00/0000";
    director = "N/A";
    genre = "N/A";
    length = "N/A";
    productionBudget = 0;
    domesticGross = 0;
    worldGross = 0;
}

Movie::Movie(std::string t, std::string rd, std::string d, std::string g, std::string l, int pb, int dg, int wg)
{
	title = t;
	releaseDate = rd;
	director = d;
	genre = g;
	length = l;
	productionBudget = pb;
	domesticGross = dg;
	worldGross = wg;
}

Movie::Movie(const Movie &m)
{
	this->title = m.title;
	this->releaseDate = m.releaseDate;
	this->director = m.director;
	this->genre = m.genre;
	this->length = m.length;
	this->productionBudget = m.productionBudget;
	this->domesticGross = m.domesticGross;
	this->worldGross = m.worldGross;
}

int Movie::getProfitPercentage()
{
    int profitP = 0;
    int profit = worldGross - productionBudget;
    profitP = (profit/productionBudget) * 100;
    return profitP;
}

void Movie::operator=(const Movie& m)
{
	this->title = m.title;
	this->releaseDate = m.releaseDate;
	this->director = m.director;
	this->genre = m.genre;
	this->length = m.length;
	this->productionBudget = m.productionBudget;
	this->domesticGross = m.domesticGross;
	this->worldGross = m.worldGross;
}

bool operator>(const Movie &m1, const Movie &m2)
{
	return m1.title.compare(m2.title) < 0;
}

bool operator<(const Movie &m1, const Movie &m2)
{
	return m1.title.compare(m2.title) > 0;
}

bool operator==(const Movie &m1, const Movie &m2)
{
	return m1.title.compare(m2.title) == 0;
}

std::ostream& operator<<(std::ostream &out, const Movie &m)
{
	out << m.title << "\t";
		/*<< m.releaseDate << "\t"
		<< m.director << "\t"
		<< m.genre << "\t"
		<< m.length << "\t"
		<< m.productionBudget << "\t"
		<< m.domesticGross << "\t"
		<< m.worldGross;*/
	return out;
}
