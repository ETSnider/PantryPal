#pragma once
#include <vector>
#include "Recipe.h"
#include <ctime>

class Calendar {
private:
	vector<day> mealplan;
	float avgCal = 0;
public:
	Calendar();
	vector<day> getMealplan();
	vector<day> updateMealplan(Recipe meal, int mealnum, int day);
	Recipe getMeal(int day, int meal);
	float updateCalPerDay();
	vector<day> newDay();
};

/// <summary>
/// struct tm {
//int tm_sec;   // seconds of minutes from 0 to 61
//int tm_min;   // minutes of hour from 0 to 59
//int tm_hour;  // hours of day from 0 to 24
//int tm_mday;  // day of month from 1 to 31
//int tm_mon;   // month of year from 0 to 11
//int tm_year;  // year since 1900
//int tm_wday;  // days since sunday
//int tm_yday;  // days since January 1st
//int tm_isdst; // hours of daylight savings time
//}
/// </summary>
struct day {
	time_t now = time(0);
	tm *date = localtime(&now);
	bool used = false;
	Recipe meal1=Recipe();
	Recipe meal2=Recipe();
	Recipe snack1=Recipe();
	Recipe meal3=Recipe();
	Recipe snack2=Recipe();
};

class CalendarException {
public:
	CalendarException(const string&);
	string& what();
private:
	string message;
};
