#include<iostream>
#include<string>
#include<map>
#include"Ingredient.h"

using namespace std;

/*
g to oz = 0.035274
to kg = 0.001
to lbs = 0.00220462

ml to cup = 0.004
to floz = 0.033814
to quart = 0.00105669
to gallon = 0.000264172
to pint = 0.00211338
to tsp = 0.202884
to tbsp = 0.067628
*/

/// <summary>
/// Three parameter Ingredient constructor. Depending on what unit is provided,
/// it will initialize the "baseType" as either "weight" or "volume".
/// Throws IngredientException if the supplied unit is not contained in either 
/// "gramToUnit" or "mlToUnit"
/// </summary>
/// <param name="nm"> The name of the ingredient </param>
/// <param name="amnt"> The amount of the ingredient </param>
/// <param name="unit"> The desired measurement unit </param>
Ingredient::Ingredient(string nm, double amnt, string unit)
	: gramToUnit{
		{ "g", 1 },
		{ "kg", 0.001 },
		{ "oz", 0.035274 },
		{ "lbs", 0.00220462 } 
		}
	, mlToUnit{
		{ "ml", 1 },
		{ "cup", 0.004 },
		{ "tsp", 0.202884 },
		{ "tbsp", 0.067628 },
		{ "floz", 0.033814 },
		{ "quart", 0.00105669 },
		{ "gallon", 0.000264172 },
		{ "pint", 0.00211338 } 
		}

{
	name = nm;
	// if statement to determine what type of unit
	if (gramToUnit.count(unit)) {
		baseType = "weight";
		// If provided unit is grams, store that amount. If not, convert to grams and store
		(unit == "g") ? (baseAmt = amnt) : (baseAmt = amnt / gramToUnit[unit]);

		// Change display values to the provided parameters
		dispAmt = amnt;
		dispUnit = unit;
	}
	else if (mlToUnit.count(unit)) {
		baseType = "volume";
		(unit == "ml") ? (baseAmt = amnt) : (baseAmt = amnt / mlToUnit[unit]);
		dispAmt = amnt;
		dispUnit = unit;
	}
	else {
		throw IngredientException("Must supply valid weight or volume unit");
	}
	purchaseDate = time(0);
	expiryDate = purchaseDate + (86400 * 7);// Default expiry of 7 days past purchase
}
// Constructor overload to include expiry date.
Ingredient::Ingredient(string nm, double amnt, string unit, int expiring)
	: gramToUnit{
		{ "g", 1 },
		{ "kg", 0.001 },
		{ "oz", 0.035274 },
		{ "lbs", 0.00220462 }
}
, mlToUnit{
	{ "ml", 1 },
	{ "cup", 0.004 },
	{ "tsp", 0.202884 },
	{ "tbsp", 0.067628 },
	{ "floz", 0.033814 },
	{ "quart", 0.00105669 },
	{ "gallon", 0.000264172 },
	{ "pint", 0.00211338 }
}

{
	name = nm;
	// if statement to determine what type of unit
	if (gramToUnit.count(unit)) {
		baseType = "weight";
		// If provided unit is grams, store that amount. If not, convert to grams and store
		(unit == "g") ? (baseAmt = amnt) : (baseAmt = amnt / gramToUnit[unit]);

		// Change display values to the provided parameters
		dispAmt = amnt;
		dispUnit = unit;
	}
	else if (mlToUnit.count(unit)) {
		baseType = "volume";
		(unit == "ml") ? (baseAmt = amnt) : (baseAmt = amnt / mlToUnit[unit]);
		dispAmt = amnt;
		dispUnit = unit;
	}
	else {
		throw IngredientException("Must supply valid weight or volume unit");
	}
	// Computing purchase and expiry dates
	purchaseDate = time(0);
	expiryDate = purchaseDate + (86400 * expiring);
}
// Constructor overload, provide whole time_t date as expiry
Ingredient::Ingredient(string nm, double amnt, string unit, time_t expiring)
	: gramToUnit{
		{ "g", 1 },
		{ "kg", 0.001 },
		{ "oz", 0.035274 },
		{ "lbs", 0.00220462 }
}
, mlToUnit{
	{ "ml", 1 },
	{ "cup", 0.004 },
	{ "tsp", 0.202884 },
	{ "tbsp", 0.067628 },
	{ "floz", 0.033814 },
	{ "quart", 0.00105669 },
	{ "gallon", 0.000264172 },
	{ "pint", 0.00211338 }
}

{
	name = nm;
	// if statement to determine what type of unit
	if (gramToUnit.count(unit)) {
		baseType = "weight";
		// If provided unit is grams, store that amount. If not, convert to grams and store
		(unit == "g") ? (baseAmt = amnt) : (baseAmt = amnt / gramToUnit[unit]);

		// Change display values to the provided parameters
		dispAmt = amnt;
		dispUnit = unit;
	}
	else if (mlToUnit.count(unit)) {
		baseType = "volume";
		(unit == "ml") ? (baseAmt = amnt) : (baseAmt = amnt / mlToUnit[unit]);
		dispAmt = amnt;
		dispUnit = unit;
	}
	else {
		throw IngredientException("Must supply valid weight or volume unit");
	}
	// Computing purchase and expiry dates
	purchaseDate = time(0);
	expiryDate = expiring;
}


// Exception code
IngredientException::IngredientException(const string& message) : message(message) {};
string& IngredientException::what() { return message; };

// Accessor code
string Ingredient::getName() const {
	return name;
}
double Ingredient::getAmt() const {
	return dispAmt;
}
string Ingredient::getUnit() const {
	return dispUnit;
}
double Ingredient::getBaseAmt() const {
	return baseAmt;
}
string Ingredient::getBaseType() const {
	return baseType;
}
time_t Ingredient::getExpiryDate() const {
	return expiryDate;
}
time_t Ingredient::getPurchaseDate() const {
	return purchaseDate;
}

// Mutator code
void Ingredient::changeName(string newname) {
	name = newname;
}
/// <summary>
/// The changeAmt() mutator will also change the baseAmt by converting to either grams or ml,
/// depending on the type of Ingredient unit.
/// </summary>
/// <param name="newamt"> The new amount of the Ingredient </param>
void Ingredient::changeAmt(double newamt) {
	// Sets the display amount to the new amount, converts new amount to grams and stores
	// that as the base amount.
	if (newamt < 0) {
		throw IngredientException("The new amount cannot be negative.");
	}
	else if (baseType == "weight"){
		dispAmt = newamt;
		baseAmt = newamt / gramToUnit[dispUnit];
	}
	else {
		dispAmt = newamt;
		baseAmt = newamt / mlToUnit[dispUnit];
	}
	
}
/// <summary>
/// Converts the current amount stored "displayAmt" using the value of "baseAmt" to the desired unit.
/// Changes the Ingredient's "dispUnit" to the new unit.
/// Will throw an IngredientException if a unit that is incompatible with the Ingredient's "baseType" is supplied.
/// </summary>
/// <param name="newunit"> The unit that the ingredient measurement will be converted to </param>
void Ingredient::convertToUnit(string newunit) {
	// Checks to see if the new unit and base unit of the ingredient are compatible. If they are
	// then the conversion is carried out.
	if (baseType == "volume" && mlToUnit.count(newunit)) {
		dispUnit = newunit;
		dispAmt = baseAmt * mlToUnit[newunit];
	}
	else if (baseType == "weight" && gramToUnit.count(newunit)) {
		dispUnit = newunit;
		dispAmt = baseAmt * gramToUnit[newunit];
	}
	else {
		throw IngredientException("Incompatible unit provided");
	}
}
void Ingredient::changeBaseType(string newtype) {
	if (newtype == "weight" || newtype == "volume") {
		baseType = newtype;
	}
	else {
		throw IngredientException("Base type must be either the string \"weight\" or \"volume\"");
	}
}
void Ingredient::changeExpiryDate(time_t newexpiry) {
	expiryDate = newexpiry;
}
void Ingredient::changePurchaseDate(time_t newpurchase) {
	purchaseDate = newpurchase;
}

/// <summary>
/// Overloaded + and - operator. Work in essentially the same way except for the operator itself.
/// If two ingredients of the same units are provided, they are simply added/subtracted.
/// If two ingredients of compatible units are provided, operator will return an ingredient with
///		the units of the LEFT supplied ingredient.
/// If two ingredients of incompatible units are provided, an IngredientException is thrown.
/// </summary>
/// <param name="lhs"> Left ingredient to be added/subtracted </param>
/// <param name="rhs"> Right ingredient to be added/subtracted </param>
/// <returns> A new Ingredient object with summed amounts. The unit type is the same as the Ingredient supplied as the left parameter </returns>
Ingredient operator+ (const Ingredient& lhs, const Ingredient& rhs) {
	string nm;
	double amt;
	string unit;
	time_t newExpiry;

	// Expiry date comparisons, default to the LATER expiry date
	if (difftime(lhs.getExpiryDate(), rhs.getExpiryDate() > 0)) {
		newExpiry = lhs.getExpiryDate();
	}
	else {
		newExpiry = rhs.getExpiryDate();
	}

	// Ensure they're the same ingredient being added
	if (lhs.getName() != rhs.getName()) {
		throw IngredientException("Cannot add two different ingredients, names do not match");
	}
	// Ensure compatible unit types
	else if (lhs.getBaseType() != rhs.getBaseType()) {
		throw IngredientException("Cannot add incompatible unit types (Weight and Volume)");
	}
	// If units are the same just add amounts
	else if (lhs.getUnit() == rhs.getUnit()) {
		nm = lhs.getName();
		amt = lhs.getAmt() + rhs.getAmt();
		unit = lhs.getUnit();
		return Ingredient(nm, amt, unit, newExpiry);
	}
	// If units aren't the same, add base amounts and convert back to supplied unit
	else if (lhs.getUnit() != rhs.getUnit()) {
		unit = lhs.getUnit();
		nm = lhs.getName();
		amt = lhs.getBaseAmt() + rhs.getBaseAmt(); // Add both "baseAmt" values
		
		if (lhs.getBaseType() == "weight") {
			Ingredient ing(nm, amt, "g", newExpiry);
			ing.convertToUnit(unit);
			return ing;
		}
		else {
			Ingredient ing(nm, amt, "ml", newExpiry);
			ing.convertToUnit(unit);
			return ing;
		}
	}
}
Ingredient operator- (const Ingredient& lhs, const Ingredient& rhs) {
	string nm;
	double amt;
	string unit;
	time_t newExpiry;

	// Expiry date comparisons, default to the LATER expiry date
	if (difftime(lhs.getExpiryDate(), rhs.getExpiryDate() > 0)) {
		newExpiry = lhs.getExpiryDate();
	}
	else {
		newExpiry = rhs.getExpiryDate();
	}
	// Ensure they're the same ingredient being added
	if (lhs.getName() != rhs.getName()) {
		throw IngredientException("Cannot subtract two different ingredients, names do not match");
	}
	// Ensure compatible unit types
	else if (lhs.getBaseType() != rhs.getBaseType()) {
		throw IngredientException("Cannot subtract incompatible unit types (Weight and Volume)");
	}
	// If units are the same just add
	else if (lhs.getUnit() == rhs.getUnit()) {
		nm = lhs.getName();
		amt = lhs.getAmt() - rhs.getAmt();
		unit = lhs.getUnit();
		return Ingredient(nm, amt, unit, newExpiry);
	}
	// If units aren't the same, add base amounts and convert back to supplied unit
	else if (lhs.getUnit() != rhs.getUnit()) {
		unit = lhs.getUnit();
		nm = lhs.getName();
		amt = lhs.getBaseAmt() - rhs.getBaseAmt();

		if (lhs.getBaseType() == "weight") {
			Ingredient ing(nm, amt, "g", newExpiry);
			ing.convertToUnit(unit);
			return ing;
		}
		else {
			Ingredient ing(nm, amt, "ml", newExpiry);
			ing.convertToUnit(unit);
			return ing;
		}
	}

}