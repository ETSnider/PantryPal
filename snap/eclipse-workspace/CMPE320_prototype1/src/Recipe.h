#pragma once
#include<string>
#include<vector>
#include "Ingredient.h"
using namespace std;

/// <summary>
/// Recipe class is fairly simple, designed to essentially be an Ingredients list holder.
/// Attributes:
///		name: String value for the name of the recipe
///		ingredients: A vector of Ingredients that are the components of the recipe. Cannot 
///			contain duplicates.
///		directions: An optional string value, for the user to store recipe directions.
/// </summary>
class Recipe {
public:
	// Constructors for Recipe
	Recipe();
	Recipe(string);
	Recipe(string, vector<Ingredient>);
	Recipe(string, vector<Ingredient>, string);
	
	// Accessors
	string getName() const;
	vector<Ingredient> getIngredients() const;
	string getDirections() const;
	int getCalories() const;

	// Mutators
	void changeName(string);
	void changeIngredients(vector<Ingredient>);
	void changeDirections(string);
	void changeCalories(int);

private:
	string name;
	vector<Ingredient> ingredients;
	string directions;
	int calories;
};

class RecipeException {
public:
	RecipeException(const string& message);
	string& what();
private:
	string message;
};

// Checks if there are duplicate ingredients in the supplied ingredients vector, since recipes should not contain duplicates
int dupIng(vector<Ingredient>);