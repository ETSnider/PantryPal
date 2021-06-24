#pragma once
#include <vector>
#include "Ingredient.h"
#include "Recipe.h"

class User {
private:
	User(int age, string gender, string name, float weight = -1);
	// User statistics
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
	void muteAge(int newAge);
	void muteGender(string newGender);
	void muteName(string newName);
	float muteWeight(float newWeight);
	Recipe suggestRecipe(vector<Ingredient> inventory);
};

class UserException {
public:
	UserException(const string& message);
	string& what();
private:
	string message;
};