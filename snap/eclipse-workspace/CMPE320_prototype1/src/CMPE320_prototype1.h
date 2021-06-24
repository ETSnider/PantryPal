//============================================================================
// Name        : CMPE320_prototype1.h
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <ctime>
#include <vector>
#pragma once

using namespace std;



class Ingredient{
	private:
		Ingredient();
		string name;
		float amount;
		enum units {g,ml,pieces,head};
		units unit;
		time_t purchaseDate;
		time_t expiryDate;
	public:
		string getName();
		string muteName(string newName);
		float getAmount();
		float muteAmount(float newAmount);
		string getUnits();
		string convertUnits(units newUnit);
		time_t getExpiryDate();
		time_t getPurchaseDate();

};

class Recipe{
private:
	Recipe();
	string name="";
	vector<Ingredient> ingredients={};
	string directions="";
	int portions=1;
	int calories=0;
public:
	vector<Ingredient> getIngredients();

};

class Stock{
private:
	vector<Ingredient> inventory;
	vector<Ingredient> groceries;
public:
	vector<Ingredient> getInventory();
	vector<Ingredient> muteInventory(vector<Ingredient> newInventory);
	vector<Ingredient> expiring(); //for food in Ingredients, if expiryDate-currentDate<3d,expiringList.add(food);
	vector<Ingredient> getGroceries();
	vector<Ingredient> muteGroceries();
	Recipe suggestRecipe(vector<Ingredient> inventory); //implement longest-common-substring for Recipe::ingredients
};

class UnitException{
public:
	UnitException(const string& message);
	string &what();
private:
	string message;
};

class Expiry{
private:
	int tolerance=3;
public:
	Expiry(int tolerance=3);
	int getTolerance();
	int muteTolerance(int newTolerance);
	vector<Ingredient> getExpiring(Stock pantry);
	vector<Ingredient> getExpired(Stock pantry);
};

class User{
private:
	User(int age,string gender,string name,float weight=-1);
	int startDate;
	int age;
	string gender;
	string name;
	float weight;
	vector<Recipe> recipeHistory;
	vector<Ingredient> ingredientFrequency;
public:
	int getAge();
	string getGender();
	string getName();
	float getWeight();
	float muteWeight(float newWeight);
	Recipe suggestRecipe(vector<Ingredient> inventory);
	void makeRecipe(Recipe meal);
};

struct day{
	struct tm* date=localtime(&time(0));
	bool used=false;
	Recipe meal1=Recipe();
	Recipe meal2=Recipe();
	Recipe snack1=Recipe();
	Recipe meal3=Recipe();
	Recipe snack2=Recipe();
};

class Calender{
private:
	vector<day> mealplan;
	float avgCal=0;
public:
	Calender();
	vector<day> getMealplan();
	vector<day> updateMealplan(Recipe meal, int mealnum, int day);
	Recipe getMeal(int day, int meal);
	float getCalPerDay();
	vector<day> newDay();
};

