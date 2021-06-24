#include <vector>
#pragma once
using namespace std;

class Nutrient {
public:
	// Constructors
	Nutrient(const int& n_id, const string& name, const string& std_unit);
	Nutrient(const Nutrient& other);

	//	Accessors
	int n_id() const { return n_id_; };
	double amount_per_100g() const { return amount_per_100g_; };
	string name() const { return name_; };
	string std_unit() const { return std_unit_; };

	//	Mutators
	void amount_per_100g(double new_amount) { amount_per_100g_ = new_amount; };

private:
	//	Attributes
	int n_id_;					// unique nutrient id
	double amount_per_100g_;	// amount of standard unit per 100g of specific food
	string name_;
	string std_unit_;			// standard unit of measure in g, mg, kJ, ...
};

class Food {
public:
	//	Constructors
	Food(const int& f_id, const string& data_type, const string& name, const int& category);

	//	Accessors
	int f_id() const { return f_id_; };
	string data_type() const { return data_type_; };
	string name() const { return name_; };
	int category() const { return category_; };
	vector<Nutrient> nutrition() const { return nutrition_; };

	// Mutators
	void nutrition(vector<Nutrient> new_vector) { nutrition_ = new_vector; };
	void addNutrient(Nutrient n) { nutrition_.push_back(n); };

private:
	//	Attributes
	int f_id_;						//	unique food id
	string data_type_;				//	type of data gathered by USDA. Ie. market_aquisition, foundation_food, ...
	string name_;
	int category_;					//	category integer value to be searched for in "food_category.csv"
	vector<Nutrient> nutrition_;	//	vector of nutrients containing amounts/100g
};

class Database {
public:
	Database();

	//	Initializers
	void init();				// initializes all data
	void initFood();			// loads data from "food.csv"
	void initNutrient();		// loads data from "nutrient.csv"
	void initFoodNutrient();	// loads data from "food_nutrient.csv"
	void initMacroNutrients();	// generates macro list from the nutrient list

	//	Accessors
	vector<Nutrient> nutrients() const { return nutrients_; };
	vector<Food> foods() const { return foods_; };
	vector<Nutrient> macro_nutrients() const { return macro_nutrients_; };

private:
	//	Attributes
	vector<Nutrient> nutrients_;		// nutrient data excluding food-specific information
	vector<Nutrient> macro_nutrients_;
	vector<Food> foods_;				// food data selected from USDA files
	string nutrient_file_;
	string food_file_;
	string food_nutrient_file_;
};

//	Thrown when a file cannot be opened during init
class FileException {
public:
	FileException(const string& message);
	string& what();
private:
	string message;
};

// Helper functions
void splitLineCSV(string& line, vector<string>& result); // takes comma delimited line and splits it into result
bool compareCsvStrings(const string& str1, const string& str2, const unsigned int& delim_count);
bool nameIsDuplicate(const string& str, const vector<Food>& v);