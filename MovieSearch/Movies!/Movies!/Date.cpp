#include "Date.h"

/*
PRE: istream and date object
POST: istream
Accepts input to date object's month, day and year attributes
*/
std::istream &operator>>(std::istream  &input, Date &d)
{
	std::string str;
	input >> str;
	d.setMonth(std::stoi(str.substr(0, 2)));
	d.setDay(std::stoi(str.substr(3, 2)));
	d.setYear(std::stoi(str.substr(6, 4)));
	return input;
}

/*
PRE: ostream and a const date object
POST: ostream
Returns the date formatted as 'month/day/year'
*/
std::ostream &operator<<(std::ostream &output, const Date &d)
{
	output << d.month << "/" << d.day << "/" << d.year << std::endl;
	return output;
}

/*
PRE: constant date object to compare and constant date obj to compare with
POST: true or false
Compares the years, months and days of each date and returns the true if the first
date obj's attributes are lower (older)
*/
bool operator<(const Date &d1, const Date &d2)
{
	if (d1.year < d2.year)
		return true;
	if (d1.year > d2.year)
		return false;
	if (d1.month < d2.month)
		return true;
	if (d1.month > d2.month)
		return false;
	if (d1.day < d2.day)
		return true;
	if (d1.day > d2.day)
		return false;
	return false;
}