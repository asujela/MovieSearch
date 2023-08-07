#pragma once 
#include <iostream>
#include <string>
class Date
{
private:
	int day, month, year;
public:
	Date() { day = 0; month = 0; year = 0; }
	Date(int d, int m, int y) { day = d; month = m; year = y; }
	void setDay(int d) { day = d; }
	void setMonth(int m) { month = m; }
	void setYear(int y) { year = y; }
	int getDay() { return day; }
	int getMonth() { return month; }
	int getYear() { return year; }

	friend std::istream &operator>>(std::istream  &input, Date &d);
	friend std::ostream &operator<<(std::ostream &output, const Date &d);
	friend bool operator<(const Date &d1, const Date &d2);
};