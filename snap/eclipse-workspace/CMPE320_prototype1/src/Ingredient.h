#pragma once

#include<iostream>
#include<string>
#include<map>
#include<ctime>

using namespace std;
/// <summary>
/// The Ingredient class is to be the smallest base unit. Recipe class will contain vectors of Ingredients, and Inventory will be tracked as vectors of Ingredients.
/// Attributes:
///		name: The name of the Ingredient, as a string
///		baseAmt: Double that can be interpreted as "ml" or "g". This is the value that will be used in unit conversions,
///			so that there is no loss of precision when converting between units.
///		baseType: A string attribute that is either "weight" or "volume". This attribute can be compared to ensure no incompatible
///			additions/subtractions are made (weight+volume)
///		dispAmt: A double attribute that records what the amount is in units that the user has specified.
///		dispUnit: A string attribute that is the unit that the user has specified that they want the ingredient to measured in.
///		gramToUnit: A map attribute that contains pairs of unit names and conversion values. These conversion values are doubles and 
///			are the "gram to unit" conversions so one must multiply the gram amount by this conversion value to obtain the desired unit.
///			For example converting 500 grams to ounces: 500 * gramToUnit["oz"]
///			20 oz to grams: 20/gramToUnit["oz"]
///		mlToUnit: The exact same as gramToUnit and used the same way as well
/// </summary>
class Ingredient {
public:
	// 3 pararmeter constructor: string name, double amount, string unit
	Ingredient(string, double, string);
	Ingredient(string, double, string, int);
	Ingredient(string, double, string, time_t);
	// Accessors
	string getName() const;
	double getAmt() const;
	string getUnit() const;
	double getBaseAmt() const;
	string getBaseType() const;
	time_t getExpiryDate() const;
	time_t getPurchaseDate() const;

	// Mutators
	void changeName(string);
	void changeAmt(double);
	void convertToUnit(string);
	void changeBaseType(string);
	void changeExpiryDate(time_t);
	void changePurchaseDate(time_t);

	// Should this instead be contained in "User" class?? Depending on if we want to add the ability for users to add their own unit conversions
	map<string, double> gramToUnit;
	map<string, double> mlToUnit;

private:
	string name;
	double baseAmt;
	string baseType;
	double dispAmt;
	string dispUnit;

	time_t purchaseDate;
	time_t expiryDate;

	
};

// Overloaded + and - operators
Ingredient operator+ (const Ingredient&, const Ingredient&);
Ingredient operator- (const Ingredient&, const Ingredient&);

// Exception for Ingredient relating to various erros
class IngredientException {
public:
	IngredientException(const string& message);
	string& what();
private:
	string message;
};
