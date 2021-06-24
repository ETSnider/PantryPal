#include<vector>
#include<string>
#include<iostream>
#include "Recipe.h"

using namespace std;
/// <summary>
/// 1 parameter Recipe constructor. nm is set to the "name" of the Recipe object, while the
/// "ingredients" attribute is instantiated as empty, and "directions" instantiated as 
/// "Put your recipe directions here!"
/// </summary>
/// <param name="nm"> The name of the Recipe </param>
Recipe::Recipe(string nm) : ingredients() {
	name = nm;
	directions = "Put your recipe directions here!";

}
/// <summary>
/// 2 parameter Recipe constructor. nm is set as the name of the Recipe, while ing is set as 
/// the "ingredients" attribute, provided it doesn't contain duplicates. If the vector contains duplicates,\
/// or is empty the constructor will throw a RecipeException.
/// </summary>
/// <param name="nm"> The name of the Recipe </param>
/// <param name="ing"> The "ingredients" attribute of the Recipe. Cannot contain duplicates or be empty</param>
Recipe::Recipe(string nm, vector<Ingredient> ing) {
	if (ing.size() == 0) {
		throw RecipeException("Ingredients list cannot be empty");
	}
	else if (dupIng(ing) != 0) {
		throw RecipeException("Ingredients list cannot contain duplciate ingredients");
	}
	else {
		name = nm;
		ingredients = ing;
		directions = "Put your recipe directions here!";
	}
}
Recipe::Recipe(string nm, vector<Ingredient> ing, string dir) {
	if (ing.size() == 0) {
		throw RecipeException("Ingredients list cannot be empty");
	}
	else if (dupIng(ing) != 0) {
		throw RecipeException("Ingredients list cannot contain duplicate ingredients");
	}
	else {
		name = nm;
		ingredients = ing;
		directions = dir;
	}
}
Recipe::Recipe() {
	Recipe("");
}

// Accessor code
string Recipe::getName() const {
	return name;
}
vector<Ingredient> Recipe::getIngredients() const {
	return ingredients;
}
string Recipe::getDirections() const {
	return directions;
}
int Recipe::getCalories() const {
	return calories;
}

// Mutator code
void Recipe::changeName(string newname) {
	name = newname;
}
void Recipe::changeIngredients(vector<Ingredient> newing) {
	if (newing.size() == 0) {
		throw RecipeException("New ingredients list must not be empty.");
	}
	
	ingredients = newing;
}
void Recipe::changeDirections(string newdir) {
	directions = newdir;
}
void Recipe::changeCalories(int newcals) {
	calories = newcals;
}

// Exception code
RecipeException::RecipeException(const string& message) : message(message) {};
string& RecipeException::what() { return message; };

/// <summary>
/// Checks the provided Ingredient vector for duplicate ingredients by name only.
/// Recipes should not contain duplicate ingredients.
/// </summary>
/// <param name="list"> The Ingredient vector to be checked for duplicate ingredients </param>
/// <returns> Returns 0 if there are no duplicates, 1 if there are any duplicates at all. </returns>
int dupIng(vector<Ingredient> list) {
	int eInd = list.size() - 1;

	// For each vector element, the rest of the list is checked for duplicates
	for (int i = 0; i <= eInd; i++) {
		Ingredient ing = list[i];
		int j = i + 1;
		
		// Returns 1 if a duplicate is found, otherwise iterates through the rest
		for (j ; j <= eInd; j++) {
			if (ing.getName() == list[j].getName()) {
				return 1; 
				
			}
		}
		
	}

	return 0;
}