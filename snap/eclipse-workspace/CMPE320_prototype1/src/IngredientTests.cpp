#include<iostream>
#include<string>
#include<vector>
#include "Ingredient.h"

using namespace std;

int IngredientTests() {

	vector<Ingredient> weightRecipe;
	vector<Ingredient> volumeRecipe;

	vector<string> vecWeightUnits{ "g", "kg", "oz", "lbs" };
	vector<string> vecVolumeUnits{ "ml", "tsp", "tbsp", "cup", "floz", "pint", "quart", "gallon" };

	Ingredient wTest1("Broccoli", 100, "g");
	Ingredient wTest2("Carrots", 20, "oz");
	Ingredient wTest3("Chicken", 0.5, "kg");
	Ingredient wTest4("Flour", 1, "lbs");

	Ingredient vTest1("Chicken Stock", 0.25, "quart");
	Ingredient vTest2("Milk", 1, "cup");
	Ingredient vTest3("Red Wine", 1, "gallon");
	Ingredient vTest4("Vinegar", 200, "floz");
	Ingredient vTest5("Flour", 1, "cup");
	Ingredient vTest6("Water", 3, "tbsp");
	Ingredient vTest7("Vegetable Oil", 2, "tsp");
	Ingredient vTest8("Beer", 2, "pint");

	weightRecipe.push_back(wTest1);
	weightRecipe.push_back(wTest2);
	weightRecipe.push_back(wTest3);
	weightRecipe.push_back(wTest4);

	volumeRecipe.push_back(vTest1);
	volumeRecipe.push_back(vTest2);
	volumeRecipe.push_back(vTest3);
	volumeRecipe.push_back(vTest4);
	volumeRecipe.push_back(vTest5);
	volumeRecipe.push_back(vTest6);
	volumeRecipe.push_back(vTest7);
	volumeRecipe.push_back(vTest8);

	// Test constructor functionality
	cout << "Testing proper ingredient creation: " << endl;
	int k = 1;
	for (Ingredient i : weightRecipe) {
		cout << "Test " << k << ": ";
		cout << i.getAmt() << " " << i.getUnit() << " of " << i.getName() << "." << endl;
		k++;
	};
	k = 1;
	for (Ingredient i : volumeRecipe) {
		cout << "Test " << k << ": ";
		cout << i.getAmt() << " " << i.getUnit() << " of " << i.getName() << "." << endl;
		k++;
	};

	// Test conversion functionality
	cout << endl << "Testing proper unit conversions: " << endl;
	for (unsigned int i = 0; i < weightRecipe.size(); i++) {
		string u = vecWeightUnits[i];
		cout << "Converting " << weightRecipe[i].getAmt() << " " << weightRecipe[i].getUnit() << " of " << weightRecipe[i].getName()
			<< " to " << u << ":";

		weightRecipe[i].convertToUnit(u);
		
		cout << " " << weightRecipe[i].getAmt() << " " << weightRecipe[i].getUnit() << endl;
	}
	for (unsigned int i = 0; i < volumeRecipe.size(); i++) {
		string u = vecVolumeUnits[i];
		cout << "Converting " << volumeRecipe[i].getAmt() << " " << volumeRecipe[i].getUnit() << " of " << volumeRecipe[i].getName()
			<< " to " << u << ":";

		volumeRecipe[i].convertToUnit(u);

		cout << " " << volumeRecipe[i].getAmt() << " " << volumeRecipe[i].getUnit() << endl;
	}

	cout << endl << "Testing for persistent changes to Ingredients" << endl;
	for (Ingredient i : weightRecipe) {
		string nm = i.getName();
		double amt = i.getAmt();
		string unt = i.getUnit();
		cout << "     " << nm << ": " << amt << " " << unt << endl;
	}
	for (Ingredient i : volumeRecipe) {
		string nm = i.getName();
		double amt = i.getAmt();
		string unt = i.getUnit();
		cout << "     " << nm << ": " << amt << " " << unt << endl;
	}

	// Overloaded Operator tests
	Ingredient opTest1("Broccoli", 200, "g");
	Ingredient opTest2("Broccoli", 100, "g");
	Ingredient opTest3("Broccoli", 10, "oz");

	Ingredient opTest4("Chicken Stock", 100, "ml");
	Ingredient opTest5("Chicken Stock", 2, "ml");
	Ingredient opTest6("Chicken Stock", 10, "floz");

	Ingredient opTest7("Broccoli", 10, "tsp");
	Ingredient opTest8("Chicken Stock", 1, "lbs");

	Ingredient add12 = opTest1 + opTest2;
	Ingredient add13 = opTest1 + opTest3;
	Ingredient sub31 = opTest3 - opTest1;
	Ingredient sub21 = opTest2 - opTest1;

	Ingredient add45 = opTest4 + opTest5;
	Ingredient add46 = opTest4 + opTest6;
	Ingredient sub46 = opTest4 - opTest6;

	cout << "Operator tests: " << endl;
	cout << "\t" << "Should be 300 g of Broccoli:     " << add12.getAmt()
		<< " " << add12.getUnit() << " of " << add12.getName() << endl;

	cout << "\t" << "Should be 483.495 g of Broccoli: " << add13.getAmt()
		<< " " << add13.getUnit() << " of " << add13.getName() << endl;

	cout << "\t" << "Should be -2.9452 g of Broccoli: " << sub31.getAmt()
		<< " " << sub31.getUnit() << " of " << sub31.getName() << endl;

	cout << "\t" << "Should be -100 g of Broccoli:    " << sub21.getAmt()
		<< " " << sub21.getUnit() << " of " << sub21.getName() << endl;

	cout << "\t" << "Should be 102 ml of Chicken Stock: " << add45.getAmt()
		<< " " << add45.getUnit() << " of " << add45.getName() << endl;

	cout << "\t" << "Should be 395.735 g of Broccoli: " << add46.getAmt()
		<< " " << add46.getUnit() << " of " << add46.getName() << endl;

	cout << "\t" << "Should be -195.735 ml of Chicken Stock: " << sub46.getAmt()
		<< " " << sub46.getUnit() << " of " << sub46.getName() << endl;
	cout << endl;
	// Testing exceptions for + and -
	cout << "Testing exceptions for + and - operators: " << endl;
	try {
		Ingredient add16 = opTest1 + opTest6;
	}
	catch (IngredientException ie) {
		cout << "Ingredient exception caught with message: " << ie.what() << endl;
	}
	cout << endl;
	try {
		Ingredient sub16 = opTest1 - opTest6;
	}
	catch (IngredientException ie) {
		cout << "Ingredient exception caught with message: " << ie.what() << endl;
	}
	cout << endl;
	try {
		Ingredient add17 = opTest1 + opTest7;
	}
	catch (IngredientException ie) {
		cout << "Ingredient exception caught with message: " << ie.what() << endl;
	}
	cout << endl;
	try {
		Ingredient sub48 = opTest4 - opTest8;
	}
	catch (IngredientException ie) {
		cout << "Ingredient exception caught with message: " << ie.what() << endl;
	}
	cout << endl;
	return 0;
}