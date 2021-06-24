/*
 * User.cpp
 *
 *  Created on: Oct. 20, 2020
 *      Author: Evan
 */
#include <ctime>
#include "User.h"
#include <string>
#include <algorithm>

User::User(int inage, string ingender,string inname,float inweight=-1){
	age=inage;
	gender=ingender;
	name=inname;
	weight=inweight;
	startDate=time(0);
	recipeHistory={};
	ingredientFrequency={};
}

int User::getAge(){
	return age;
}

string User::getGender(){
	return gender;
}

string User::getName(){
	return name;
}

void User::muteAge(int newAge) {
	User.age = newAge;
}

void User::muteGender(string newGender) {
	User.gender = newGender;
}

void User::muteName(string newName) {
	User.name = newName;
}

float User::getWeight(){
	return weight;
}

float User::muteWeight(float newWeight){
	if(newWeight > 0 && newWeight < 5000){
		weight=newWeight;
		return weight;
	}
	else{
		throw UserException("Weight out of bounds");
	}
}

Recipe User::suggestRecipe(vector<Ingredient> pantry){
	Recipe rec, temp;
	float recPercent=0;
	float tempPercent;
	for(int i=0;i<recipeHistory.size();i++){
		temp=recipeHistory[i];
		tempPercent=compareMeal(temp,pantry);
		if(tempPercent>=recPercent){
			rec=temp;
			recPercent=tempPercent;
		}
	}
	return rec;
}


float compareMeal(Recipe meal, vector<Ingredient> pantry){
	vector<Ingredient> food = meal.getIngredients();
	float haveIng = 0;
	for(int i = 0; i < food.size(); i++){
		for(int j = 0; j < pantry.size(); j++){
			if(toupper(strcmp(food[i].getName()), toupper(pantry[j].getName())) == 0){
				haveIng++;
				break;
			}
		}
	}
	float IngPercent=haveIng/float(food.size());
	return IngPercent;
}

// Exception code
UserException::UserException(const string& message) : message(message) {};
string& UserException::what() { return message; };