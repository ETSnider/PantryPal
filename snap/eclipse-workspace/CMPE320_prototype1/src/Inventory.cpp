#include<vector>
#include<string>
#include<iostream>
#include "Ingredient.h"
#include "Recipe.h"
#include "Inventory.h"
using namespace std;

// Inventory constructor code
Inventory::Inventory() {};
Inventory::Inventory(vector<Ingredient> curInv) : futureInv(), groceryList() {
	currentInv = curInv;
}
Inventory::Inventory(vector<Ingredient> curInv, vector<Ingredient> grocList) : futureInv() {
	currentInv = curInv;
	groceryList = grocList;
}

// Accessor code
vector<Ingredient> Inventory::getCurrentInv() const {
	return currentInv;
}
vector<Ingredient> Inventory::getFutureInv() const {
	return futureInv;
}
vector<Ingredient> Inventory::getGroceryList() const {
	return groceryList;
}

// Mutator code
void Inventory::changeCurrentInv(vector<Ingredient> inv) {
	currentInv = inv;
}
void Inventory::changeFutureInv(vector<Ingredient> inv) {
	futureInv = inv;
}
void Inventory::changeGroceryList(vector<Ingredient> inv) {
	groceryList = inv;
}

// Pseudomutator code
void planFood(Inventory& inv, const vector<Ingredient>& ingList) {
	vector<Ingredient> currentInv = inv.getCurrentInv();
	vector<Ingredient> futureInv;

	int ingListSize = ingList.size();
	int currInvSize = currentInv.size();

	for (int i = 0; i < ingListSize; i++) {
		Ingredient listIng = ingList[i];

		for (int j = 0; j < currInvSize; j++) {
			Ingredient invIng = currentInv[j];

			// Checks for name and base type compatibility between ingredients
			if ((listIng.getName() == invIng.getName()) && (listIng.getBaseType() == invIng.getBaseType())) {
				currentInv[j] = invIng - listIng;
			}			
		}
	}

	// Remove ingredients with negative amounts, add to grocery list
	vector<Ingredient> grocery;
	for (int k = 0; k < currentInv.size(); k++) {
		Ingredient ing = currentInv[k];
		if (ing.getAmt() < 0) {
			ing.changeAmt(-ing.getAmt());
			grocery.push_back(ing);
		}
		else {
			futureInv.push_back(ing);
		}
	}
	inv.changeGroceryList(grocery);
	inv.changeFutureInv(futureInv);
}
void eatFood(Inventory& inv, const vector<Ingredient>& ingList) {
	vector<Ingredient> currInv = inv.getCurrentInv();
	int ingListSize = ingList.size();
	int currInvSize = currInv.size();

	int found;

	for (int i = 0; i < ingListSize; i++) {
		Ingredient listIng = ingList[i];
		found = 0;

		for (int j = 0; j < currInvSize; j++) {
			Ingredient invIng = currInv[j];

			// Checks for name and base type compatibility between ingredients
			if ((listIng.getName() == invIng.getName()) && (listIng.getBaseType() == invIng.getBaseType())) {
				Ingredient newIng = invIng - listIng;
				if (newIng.getAmt() < 0) {
					throw InventoryException("Error: Insufficent amount of \'" + invIng.getName() + "\' in the inventory.");
				}
				currInv[j] = invIng - listIng;
				found = 1;
			}


		}

		if (found == 0) {
			throw InventoryException("Error: Ingredient \'" + listIng.getName() + "\' not found in inventory");
		}
	}

	inv.changeCurrentInv(currInv);
}
void addFood(Inventory& inv, const vector<Ingredient>& ingList) {
	vector<Ingredient> inventory = inv.getCurrentInv();

	int ingListSize = ingList.size();

	int found = 0;
	vector<int> indices;

	for (int i = 0; i < ingListSize; i++) {
		Ingredient listIng = ingList[i];

		int invSize = inventory.size();
		for (int j = 0; j < invSize; j++) {
			Ingredient invIng = inventory[j];

			// Checks for name and base type compatibility between ingredients
			if ((listIng.getName() == invIng.getName()) && (listIng.getBaseType() == invIng.getBaseType())) {
				inventory[j] = invIng + listIng;
				found = 1;
			}			
		}
		if (found == 0) {
			inventory.push_back(listIng);
		}
	}
	inv.changeCurrentInv(inventory);
}

// Inventory exception code
InventoryException::InventoryException(const string& message) : message(message) {};
string& InventoryException::what() { return message; };

/// <summary>
/// consolidate() adds together all duplicate ingredients contained in the provided Ingredients vector.
/// Duplicates are defined as Ingredients with the same "name" and "baseType". Ingredients with the same name
/// but different "baseType" will be treated as unique ingredients.
/// This is done by iterating through each element, and checking the remaining vector for duplicates.
/// If a duplicate is found it is added to the current Ingredient, and after checking the rest of the vector, it
/// is stored in a new vector to be returned at the end of function execution.
/// Since the vector size cannot be changed while iterating through it, a vector of duplicate indicies are stored
/// and skipped.
/// </summary>
/// <param name="list1"> The vector of Ingredients to consolidate </param>
/// <returns> A new Ingredient vector containing consolidated ingredients </returns>
vector<Ingredient> consolidate(const vector<Ingredient>& list1) {
	int endInd = list1.size() - 1;
	string name;
	string base;
	vector<Ingredient> newVec;
	vector<int> skipList;

	for (int i = 0; i <= endInd; i++) {
		if (find(skipList.begin(), skipList.end(), i) != skipList.end()) {
			continue;
		}
		Ingredient ing = list1[i];
		name = ing.getName();
		base = ing.getBaseType();

		int j = i + 1;
		for (j; j <= endInd; j++) {
			if ((name == list1[j].getName()) && (base == list1[j].getBaseType())) {
				ing = ing + list1[j];
				skipList.push_back(j);
			}
		}

		newVec.push_back(ing);
	}
	
	return newVec;
}
/// <summary>
/// Works exactly the same as the 1 parameter consolidate() function, however simply appends list2 to the end of list1,
/// and runs the consolidate() code.
/// </summary>
vector<Ingredient> consolidate(const vector<Ingredient>& list1, const vector<Ingredient>& list2) {
	vector<Ingredient> list12 = list1;
	list12.insert(list12.end(), list2.begin(), list2.end());

	int endInd = list12.size() - 1;
	string name;
	string base;
	vector<Ingredient> newVec;
	vector<int> skipList;

	for (int i = 0; i <= endInd; i++) {
		if (find(skipList.begin(), skipList.end(), i) != skipList.end()) {
			continue;
		}
		Ingredient ing = list12[i];
		name = ing.getName();
		base = ing.getBaseType();

		int j = i + 1;
		for (j; j <= endInd; j++) {
			if ((name == list12[j].getName()) && (base == list12[j].getBaseType())) {
				ing = ing + list12[j];
				skipList.push_back(j);
			}
		}

		newVec.push_back(ing);
	}
	return newVec;
}

vector<Ingredient> consolidateRecipe(const vector<Recipe> recipeList) {
	int numRecipes = recipeList.size();
	vector<Ingredient> allIng;
	vector<Ingredient> ing;
	for (int i = 0; i < numRecipes; i++) {
		ing = recipeList[i].getIngredients();
		allIng.insert(allIng.end(), ing.begin(), ing.end());
	}
	return consolidate(allIng);
};

