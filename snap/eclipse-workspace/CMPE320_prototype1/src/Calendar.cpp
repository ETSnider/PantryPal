/*
 * Calender.cpp
 *
 *  Created on: Oct. 21, 2020
 *      Author: Evan
 */

#include "Calendar.h"
#include "Recipe.h"

Calendar::Calendar(){
	struct tm* date=localtime(&time(0));
	struct day temp;
	for(int i=0;i<7;i++){
		temp.date=localtime(&time(0+i));
		mealplan.push_back(temp);
	}
}


vector<day> Calendar::getMealplan(){
	return mealplan;
}

vector<day> Calendar::updateMealplan(Recipe meal, int mealnum, int day){
	mealplan[day].used=true;
	switch (mealnum){
	case 1:
		mealplan[day].meal1=meal;
		break;
	case 2:
		mealplan[day].meal2=meal;
		break;
	case 3:
		mealplan[day].snack1=meal;
		break;
	case 4:
		mealplan[day].meal3=meal;
		break;
	case 5:
		mealplan[day].snack2=meal;
		break;
	default:
		mealplan[day].used=false;
		throw UnitException("Invalid meal number");
	}
	return mealplan;
}

Recipe Calendar::getMeal(int day, int meal){
	Recipe mealToGet;
switch(meal){
case 1:
	mealToGet=mealplan[day].meal1;
	break;
case 2:
	mealToGet=mealplan[day].meal2;
	break;
case 3:
	mealToGet=mealplan[day].snack1;
	break;
case 4:
	mealToGet=mealplan[day].meal3;
	break;
case 5:
	mealToGet=mealplan[day].snack2;
	break;
default:
	throw CalendarException("Invalid meal number");
}
return mealToGet;
}

float Calendar::updateCalPerDay(){
	float sum=0,count=0;
	for(int i=0;i<7;i++){
		if(mealplan[i].used==true){
			count++;
			sum+=mealplan[i].meal1.getCalories();
			sum+=mealplan[i].meal2.getCalories();
			sum+=mealplan[i].snack1.getCalories();
			sum+=mealplan[i].meal3.getCalories();
			sum+=mealplan[i].snack2.getCalories();
		}
	}
	if(sum!=0){
		sum=sum/count;
	}
	avgCal = sum;
	return avgCal;
}

vector<day> Calendar::newDay(){
	mealplan.erase(mealplan.begin());
	mealplan.push_back(day());
	return mealplan;
}

// Exception code
CalendarException::CalendarException(const string& message) : message(message) {};
string& CalendarException::what() { return message; };