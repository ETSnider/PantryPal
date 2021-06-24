#include<vector>
#include<string>
#include<iostream>
#include "Recipe.h"

using namespace std;

int RecipeTests() {
	vector<Ingredient> ingList;
	ingList.push_back(Ingredient("Beef", 2, "lbs"));
	ingList.push_back(Ingredient("Beef stock", 2, "cup"));
	ingList.push_back(Ingredient("Celery", 500, "g"));
	ingList.push_back(Ingredient("Carrot", 500, "g"));
	ingList.push_back(Ingredient("Worcestershire sauce", 2, "tbsp"));
	ingList.push_back(Ingredient("Tomato sauce", 0.5, "cup"));
	ingList.push_back(Ingredient("Cornstarch", 2, "tsp"));
	ingList.push_back(Ingredient("Water", 2, "tbsp"));

	Recipe beefstew("Beef Stew", ingList);

	// Check for proper recipe construction
	cout << "The recipe \"" << beefstew.getName() << "\" contains: " << endl;
	vector<Ingredient> ingList2 = beefstew.getIngredients();
	for (unsigned int i = 0; i < ingList2.size(); i++) {
		double amt = ingList2[i].getAmt();
		string unt = ingList2[i].getUnit();
		string nm = ingList2[i].getName();
		cout << "\t" << amt << " " << unt << " of " << nm << endl;
	}
	cout << "The directions are: " << beefstew.getDirections() << endl;

	cout << "Test mutators: " << endl;
	cout << "\t" << "Change name from \"Beef Stew\" --> \"Stewed Beef \"" << endl;
	cout << "\t" << "Added directions" << endl;
	cout << "\t" << "Removed Tomato sauce and replaced with 2 tbsp of Tomato Paste" << endl;
	cout << "\t" << "Added 1 lbs of beef" << endl;
	cout << "\t" << "Removed Cornstarch and Water" << endl;

	beefstew.changeName("Stewed Beef");
	beefstew.changeDirections("1. Throw everything in a pressure cooker.\n2. Cook on high for 40 minutes\n3. ????\n4. Profit!");
	ingList2 = beefstew.getIngredients();
	Ingredient tp("Tomato Paste", 2, "tbsp");
	swap(ingList2[5], tp);
	ingList2[0].changeAmt(3);
	ingList2.pop_back();
	ingList2.pop_back();
	beefstew.changeIngredients(ingList2);

	cout << endl << "NEW RECIPE:" << endl;
	cout << "The recipe \"" << beefstew.getName() << "\" contains: " << endl;
	vector<Ingredient> ingList3 = beefstew.getIngredients();
	for (unsigned int i = 0; i < ingList2.size(); i++) {
		double amt = ingList3[i].getAmt();
		string unt = ingList3[i].getUnit();
		string nm = ingList3[i].getName();
		cout << "\t" << amt << " " << unt << " of " << nm << endl;
	}
	cout << "The directions are: " << endl << beefstew.getDirections() << endl;

	vector<Ingredient> duplicateTests1;
	vector<Ingredient> duplicateTests2;
	vector<Ingredient> duplicateTests3;
	vector<Ingredient> duplicateTests4;

	Ingredient One("One", 1, "g");
	Ingredient Two("Two", 1, "g");
	Ingredient Three("Three", 1, "g");
	Ingredient Four("Four", 1, "g");
	Ingredient Five("Five", 1, "g");
	Ingredient Six("Six", 1, "g");
	Ingredient Seven("Seven", 1, "g");
	Ingredient Eight("Eight", 1, "g");
	Ingredient Nine("Nine", 1, "g");
	Ingredient Ten("Ten", 1, "g");

	// Unique ingredients vector
	duplicateTests1.push_back(One);
	duplicateTests1.push_back(Two);
	duplicateTests1.push_back(Three);
	duplicateTests1.push_back(Four);
	duplicateTests1.push_back(Five);
	duplicateTests1.push_back(Six);
	duplicateTests1.push_back(Seven);
	duplicateTests1.push_back(Eight);
	duplicateTests1.push_back(Nine);
	duplicateTests1.push_back(Ten);

	// Vector with 1 duplicates
	duplicateTests2.push_back(One);
	duplicateTests2.push_back(One);
	duplicateTests2.push_back(Three);
	duplicateTests2.push_back(Four);
	duplicateTests2.push_back(Five);
	duplicateTests2.push_back(Six);
	duplicateTests2.push_back(Seven);
	duplicateTests2.push_back(Eight);
	duplicateTests2.push_back(Nine);
	duplicateTests2.push_back(Ten);

	// Vector with 2 duplicates
	duplicateTests3.push_back(One);
	duplicateTests3.push_back(Two);
	duplicateTests3.push_back(Three);
	duplicateTests3.push_back(Ten);
	duplicateTests3.push_back(Five);
	duplicateTests3.push_back(Six);
	duplicateTests3.push_back(Seven);
	duplicateTests3.push_back(Eight);
	duplicateTests3.push_back(Ten);
	duplicateTests3.push_back(Ten);

	// Vector with 3 duplicates
	duplicateTests4.push_back(Six);
	duplicateTests4.push_back(One);
	duplicateTests4.push_back(Nine);
	duplicateTests4.push_back(Three);
	duplicateTests4.push_back(Two);
	duplicateTests4.push_back(Four);
	duplicateTests4.push_back(Five);
	duplicateTests4.push_back(Eight);
	duplicateTests4.push_back(Ten);
	duplicateTests4.push_back(Seven);


	cout << endl;
	// Testing dupIng()
	cout << "Testing dupIng(): " << endl;
	cout << "DuplicateTest1: " << dupIng(duplicateTests1) << endl;
	cout << "DuplicateTest2: " << dupIng(duplicateTests2) << endl;
	cout << "DuplicateTest3: " << dupIng(duplicateTests3) << endl;
	cout << "DuplicateTest4: " << dupIng(duplicateTests4) << endl;

	cout << endl;

	cout << "Testing 2 and 3 parameter constructors for duplicate ingredients rejection: " << endl;
	cout << "Expecting success: ";
	try {
		Recipe rTest1("Test", duplicateTests1);
		cout << "Recipe successfully created" << endl;
	}
	catch (RecipeException) {
		cout << "Duplicate ingredient list caught" << endl;
	}
	cout << "Expecting failure: ";
	try {
		Recipe rTest2("Test", duplicateTests2);
		cout << "Recipe successfully created" << endl;
	}
	catch (RecipeException) {
		cout << "Duplicate ingredient list caught" << endl;
	}

	cout << "Expecting success: ";
	try {
		Recipe rTest3("Test", duplicateTests1, "Second constructor test");
		cout << "Recipe successfully created" << endl;
	}
	catch (RecipeException) {
		cout << "Duplicate ingredient list caught" << endl;
	}
	cout << "Expecting Failure: ";
	try {
		Recipe rTest4("Test", duplicateTests2, "Second constructor test");
		cout << "Recipe successfully created" << endl;
	}
	catch (RecipeException) {
		cout << "Duplicate ingredient list caught" << endl;
	}


	return 0;
}