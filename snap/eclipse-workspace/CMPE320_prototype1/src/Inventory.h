#pragma once
#include<vector>
#include<vector>
#include<string>
#include<iostream>
#include "Ingredient.h"
#include "Recipe.h"
#include "Inventory.h"

using namespace std;
/// <summary>
/// The Inventory class keeps track of the user's current food inventory, as well as
/// the "future" inventory after planned meals have been accounted for. Also keeps a grocery
/// list.
/// </summary>
class Inventory {
public:
	// Constructors
	Inventory();
	Inventory(vector<Ingredient>);
	Inventory(vector<Ingredient>, vector<Ingredient>);


	// Accessors
	vector<Ingredient> getCurrentInv() const;
	vector<Ingredient> getGroceryList() const;
	vector<Ingredient> getFutureInv() const;

	// Mutators
	void changeCurrentInv(vector<Ingredient>);
	void changeFutureInv(vector<Ingredient>);
	void changeGroceryList(vector<Ingredient>);

private:
	vector<Ingredient> currentInv;
	vector<Ingredient> futureInv;
	vector<Ingredient> groceryList;;
};

class InventoryException {
public:
	InventoryException(const string&);
	string& what();
private:
	string message;
};

/// <summary>
/// Consolidates duplicate ingredients in either one or two ingredients lists by adding together ingredients with the same name 
/// and compatible units. Returns a new consolidated ingredients vector.
/// </summary>
vector<Ingredient> consolidate(const vector<Ingredient>&);
vector<Ingredient> consolidate(const vector<Ingredient>&, const vector<Ingredient>&);

vector<Ingredient> consolidateRecipe(const vector<Recipe>&);

// PseudoMutators
void planFood(Inventory&, const vector<Ingredient>&);
void eatFood(Inventory&, const vector<Ingredient>&);
void addFood(Inventory&, const vector<Ingredient>&);