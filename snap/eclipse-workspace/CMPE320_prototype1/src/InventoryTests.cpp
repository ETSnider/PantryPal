
#include<vector>
#include<string>
#include<iostream>
#include "Ingredient.h"
#include "Recipe.h"
#include "Inventory.h"

using namespace std;

int InventoryConsolidateTests() {
	
	Inventory inv;
	vector<Ingredient> test0dup;
	vector<Ingredient> test1dup;
	vector<Ingredient> test2dup;
	vector<Ingredient> testdup;

	vector<Ingredient> mixedWeightTest;
	vector<Ingredient> mixedVolumeTest;
	vector<Ingredient> mixedWVTest;

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

	test0dup.push_back(One);
	test0dup.push_back(Two);
	test0dup.push_back(Three);
	test0dup.push_back(Four);
	test0dup.push_back(Five);
	test0dup.push_back(Six);
	test0dup.push_back(Seven);
	test0dup.push_back(Eight);
	test0dup.push_back(Nine);
	test0dup.push_back(Ten);

	test1dup.push_back(One);	//Duplicate
	test1dup.push_back(One);	//Duplicate
	test1dup.push_back(Two);
	test1dup.push_back(Three);
	test1dup.push_back(Four);
	test1dup.push_back(Five);
	test1dup.push_back(Six);
	test1dup.push_back(Seven);
	test1dup.push_back(Eight);
	test1dup.push_back(Nine);
	test1dup.push_back(Ten);

	test2dup.push_back(One);
	test2dup.push_back(Two);
	test2dup.push_back(Three);	//Duplicate
	test2dup.push_back(Three);	//Duplicate
	test2dup.push_back(Four);
	test2dup.push_back(Five);
	test2dup.push_back(Six);
	test2dup.push_back(Seven);	//Duplicate
	test2dup.push_back(Eight);
	test2dup.push_back(Nine);
	test2dup.push_back(Ten);
	test2dup.push_back(Seven);	//Duplicate

	testdup.push_back(One);
	testdup.push_back(One);
	testdup.push_back(One);
	testdup.push_back(One);
	testdup.push_back(One);
	testdup.push_back(One);
	testdup.push_back(One);
	
	mixedWeightTest.push_back(Ingredient("One", 1, "g"));
	mixedWeightTest.push_back(Ingredient("Two", 1, "g"));
	mixedWeightTest.push_back(Ingredient("One", 1, "oz"));
	mixedWeightTest.push_back(Ingredient("Two", 1, "lbs"));

	mixedVolumeTest.push_back(Ingredient("One", 1, "ml"));
	mixedVolumeTest.push_back(Ingredient("Two", 1, "ml"));
	mixedVolumeTest.push_back(Ingredient("One", 1, "floz"));
	mixedVolumeTest.push_back(Ingredient("Two", 1, "cup"));

	mixedWVTest.push_back(Ingredient("One", 1, "g"));
	mixedWVTest.push_back(Ingredient("Two", 1, "ml"));
	mixedWVTest.push_back(Ingredient("One", 1, "ml"));
	mixedWVTest.push_back(Ingredient("Two", 1, "g"));

	
	vector<Ingredient> consolidatedTest0dup = consolidate(test0dup);

	vector<Ingredient> consolidatedTest1dup = consolidate(test1dup);
	vector<Ingredient> consolidatedTest2dup = consolidate(test2dup);
	vector<Ingredient> consolidatedTestdup = consolidate(testdup);

	vector<Ingredient> consolidatedMixedWeightTest = consolidate(mixedWeightTest);
	vector<Ingredient> consolidatedMixedVolumeTest = consolidate(mixedVolumeTest);

	vector<Ingredient> consolidatedtest2test2 = consolidate(test2dup, test2dup);
	vector<Ingredient> consolidatedtest0test0 = consolidate(test0dup, test0dup);

	// One parameter consolidate() tests
	cout << "One parameter consolidate(vector<Ingredient>) tests: " << endl;
	cout << "   " << "test0 should have 0 duplicates: " << endl;
	for (Ingredient i : consolidatedTest0dup) {
		cout << "\t" << i.getAmt() << " " << i.getUnit() << " of " << i.getName() << endl;
	}

	cout << "   " << "test1 should have 1 duplicate, \"One\" should have 2 g: " << endl;
	for (Ingredient i : consolidatedTest1dup) {
		cout << "\t" << i.getAmt() << " " << i.getUnit() << " of " << i.getName() << endl;
	}

	cout << "   " << "test2 should have 2 duplicates, \"Three\" and \"Seven\" should have 2 g: " << endl;
	for (Ingredient i : consolidatedTest2dup) {
		cout << "\t" << i.getAmt() << " " << i.getUnit() << " of " << i.getName() << endl;
	}

	cout << "   " << "test3 should have all duplicates, \"One\" should have 7 g: " << endl;
	for (Ingredient i : consolidatedTestdup) {
		cout << "\t" << i.getAmt() << " " << i.getUnit() << " of " << i.getName() << endl;
	}

	cout << "   " << "Mixed weight test should have \"One\" with 29.3495 g, and \"Two\" with 454.592 g: " << endl;
	for (Ingredient i : consolidatedMixedWeightTest) {
		cout << "\t" << i.getAmt() << " " << i.getUnit() << " of " << i.getName() << endl;
	}

	cout << "   " << "Mixed volume test should have \"One\" with 30.5735 ml, and \"Two\" with 251 ml: " << endl;
	for (Ingredient i : consolidatedMixedVolumeTest) {
		cout << "\t" << i.getAmt() << " " << i.getUnit() << " of " << i.getName() << endl;
	}

	// Testing duplicates with different unit types
	cout << "\n\n";
	cout << "Attempting to consolidate mixed weights and volumes, shouldn't change values." << endl;
	try {
		vector<Ingredient> consolidatedMixedWVTest = consolidate(mixedWVTest);
		cout << "   " << "Mixed weight/volume test should still contain duplicate \"One\" and \"Two\" entries: " << endl;
		for (Ingredient i : consolidatedMixedWVTest) {
			cout << "\t" << i.getAmt() << " " << i.getUnit() << " of " << i.getName() << endl;
		}
	}
	catch (InventoryException e) {
		cout << "Caught inventory exception with message: " << e.what() << endl;
	}

	// Two parameter consolidate() tests
	cout << "\n\n";
	cout << "Two parameter consolidate() tests: " << endl;
	cout << "   " << "Test 0 twice, should have 2 g of everything " << endl;
	for (Ingredient i : consolidatedtest0test0) {
		cout << "\t" << i.getAmt() << " " << i.getUnit() << " of " << i.getName() << endl;
	}

	cout << "   " << "Test 2 twice, should have 4 g of \"Three\" and \"Seven\", 2 g of everything else: " << endl;
	for (Ingredient i : consolidatedtest2test2) {
		cout << "\t" << i.getAmt() << " " << i.getUnit() << " of " << i.getName() << endl;
	}
	return 0;
}

int InventoryFoodTests() {
	Inventory myInventory;
	cout << "Initializing variables..." << endl;
	// Beef stew ingredients
	Ingredient broccoli("Broccoli", 200, "g");
	Ingredient carrots("Carrots", 10, "oz");
	Ingredient beefbroth("Beef Broth", 50, "floz");
	Ingredient beef("Beef", 2, "lbs");
	Ingredient worcestersauce("Worcestershire sauce", 2, "tbsp");
	Ingredient tomatopaste("Tomato Paste", 2, "tbsp");

	// Inventory ingredients
	Ingredient broccoli2("Broccoli", 5, "lbs");
	Ingredient carrots2("Carrots", 5, "lbs");
	Ingredient beefbroth2("Beef Broth", 4000, "ml");
	Ingredient beef2("Beef", 5, "lbs");
	Ingredient tomatopaste2("Tomato Paste", 500, "ml");
	Ingredient chicken("Chicken Breast", 3, "lbs");
	Ingredient parsley("Parsley", 200, "g");
	Ingredient milk("Milk", 2000, "ml");

	vector<Ingredient> beefstew;
	beefstew.push_back(broccoli);
	beefstew.push_back(carrots);
	beefstew.push_back(beefbroth);
	beefstew.push_back(beef);
	beefstew.push_back(tomatopaste);

	vector<Ingredient>fancybeefstew;
	fancybeefstew.push_back(broccoli);
	fancybeefstew.push_back(carrots);
	fancybeefstew.push_back(beefbroth);
	fancybeefstew.push_back(beef);
	fancybeefstew.push_back(worcestersauce);
	fancybeefstew.push_back(tomatopaste);

	vector<Ingredient> inv;
	inv.push_back(broccoli2);
	inv.push_back(carrots2);
	inv.push_back(beefbroth2);
	inv.push_back(beef2);
	inv.push_back(tomatopaste2);
	inv.push_back(chicken);
	inv.push_back(parsley);
	inv.push_back(milk);

	myInventory.changeCurrentInv(inv);

	cout << "Current inventory contains: " << endl;
	for (int i = 0; i < inv.size(); i++) {
		cout << "\t " << myInventory.getCurrentInv()[i].getAmt() << " " <<
			myInventory.getCurrentInv()[i].getUnit() << " of " << myInventory.getCurrentInv()[i].getName() << endl;
	}
	cout << endl;

	cout << "Beef stew recipe contains: " << endl;
	for (int i = 0; i < beefstew.size(); i++) {
		cout << "\t " << beefstew[i].getAmt() << " " <<
			beefstew[i].getUnit() << " of " << beefstew[i].getName() << endl;
	}
	cout << endl;

	cout << "Fancy beef stew recipe contains: " << endl;
	for (int i = 0; i < fancybeefstew.size(); i++) {
		cout << "\t " << fancybeefstew[i].getAmt() << " " <<
			fancybeefstew[i].getUnit() << " of " << fancybeefstew[i].getName() << endl;
	}
	cout << endl;

	cout << "Attempting to \'Eat\' the beef stew" << endl;
	try { 
		eatFood(myInventory, beefstew);
		cout << "Success!" << endl;
	}
	catch (InventoryException e) {
		cout << e.what() << endl;
	}
	cout << endl;	

	inv = myInventory.getCurrentInv();
	cout << "Inventory after subtracting/eating beef stew: " << endl;
	for (int i = 0; i < inv.size(); i++) {
		cout << "\t " << inv[i].getAmt() << " " << inv[i].getUnit() << " of " << inv[i].getName() << endl;
	}
	cout << endl;

	cout << "Attempting to \'Eat\' the fancy beef stew (Should throw error)" << endl;
	try {
		eatFood(myInventory, fancybeefstew);
		cout << "Success!" << endl;
	}
	catch (InventoryException e) {
		cout << e.what() << endl;
	}
	cout << endl;

	cout << "Inventory after subtracting/eating FANCY beef stew (Should be unchanged): " << endl;
	for (int i = 0; i < inv.size(); i++) {
		cout << "\t " << myInventory.getCurrentInv()[i].getAmt() << " " <<
			myInventory.getCurrentInv()[i].getUnit() << " of " << myInventory.getCurrentInv()[i].getName() << endl;
	}
	cout << endl;



	return 0;
}