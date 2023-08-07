#pragma once
#include <string>
#include <iostream>
class Movie
{
private:
	std::string title, releaseDate, director, genre, length;
	int productionBudget, domesticGross, worldGross;
public:
    Movie();
	Movie(std::string t, std::string rd, std::string d, std::string g, std::string l, int cs, int b, int ts);
	Movie(const Movie &m);
	void setTitle(std::string t) { title = t; }	
	void setReleaseDate(std::string rd) { releaseDate = rd; }
	void setDirector(std::string d) { director = d; }
	void setGenre(std::string g) { genre = g; }
	void setLength(std::string l) { length = l; }
	void setProductionBudget(int pb) { productionBudget = pb; }
	void setDomesticGross(int dg) { domesticGross = dg; }
	void setWorldGross(int wg) { worldGross = wg; }
	std::string getTitle() { return title; }
	std::string getReleaseDate() { return releaseDate; }
	std::string getDirector() { return director; }
	std::string getGenre() { return genre; }
	std::string getLength() { return length; }
	int getProductionBudget() { return productionBudget; }
	int getDomesticGross() { return domesticGross; }
	int getWorldGross() { return worldGross; }
    int getProfitPercentage(); // special function

	void operator=(const Movie& m);
	
	friend bool operator>(const Movie &m1, const Movie &m2);
	friend bool operator<(const Movie &m1, const Movie &m2);
	friend bool operator==(const Movie &m1, const Movie &m2);
	friend std::ostream& operator<<(std::ostream &out, const Movie &m);
};
