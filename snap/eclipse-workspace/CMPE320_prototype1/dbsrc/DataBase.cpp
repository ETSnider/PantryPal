#define _CRT_SECURE_NO_WARNINGS
#define CSV_IO_NO_THREAD
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <boost/algorithm/string.hpp>
#include "DataBase.h"
#include "csv.h"
using namespace std;

//	Exceptions
FileException::FileException(const string& message) : message(message) {};
string& FileException::what() { return message; };

// Constructors
Nutrient::Nutrient(const int& id, const string& name, const string& unit) {
	this->n_id_ = id;
	this->name_ = name;
	this->std_unit_ = unit;
	this->amount_per_100g_ = 0;
}

Nutrient::Nutrient(const Nutrient& other) {
	this->n_id_ = other.n_id();
	this->name_ = other.name();
	this->std_unit_ = other.std_unit();
	this->amount_per_100g_ = other.amount_per_100g();
}

Food::Food(const int& id, const string& dataType, const string& name, const int& category) {
	this->f_id_ = id;
	this->data_type_ = dataType;
	this->name_ = name;
	this->category_ = category;
}

Database::Database() {
	nutrients_ = {};
	foods_ = {};
	food_file_ = "food.csv";
	nutrient_file_ = "nutrient.csv";
	food_nutrient_file_ = "food_nutrient.csv";
}

//	Initializers
void Database::init() {
	initNutrient();
	initFood();
	initMacroNutrients();
	initFoodNutrient();
}

void Database::initNutrient() {
	try {
		io::CSVReader<3, io::trim_chars<'"'>, io::double_quote_escape<',', '/"'>> in(nutrient_file_);
		in.read_header(io::ignore_extra_column, "id", "name", "unit_name");

		string name, unit_name;
		int id;

		while (in.read_row(id, name, unit_name)) {
			Nutrient new_nutrient = Nutrient(id, name, unit_name);
			nutrients_.push_back(new_nutrient);
		}
	}
	catch (exception e) {
		throw e;
	}
}

void Database::initFood() {
	try {
		io::CSVReader<4, io::trim_chars<'"'>, io::double_quote_escape<',', '/"'>> in(food_file_);
		in.read_header(io::ignore_extra_column, "fdc_id", "data_type", "description", "food_category_id");

		string name, unit_name, data_type, prev_name;
		int id, category_id;

		while (in.read_row(id, data_type, name, category_id)) {
			if (name != prev_name) {
				Food new_food(id, data_type, name, category_id);
				foods_.push_back(new_food);
				prev_name = name;
			}
		}
	}
	catch (exception e) {
		throw e;
	}
}

void Database::initFoodNutrient() {
	try {
		io::CSVReader<3, io::trim_chars<'"'>, io::double_quote_escape<',', '/"'>> in(food_nutrient_file_);
		in.read_header(io::ignore_extra_column, "fdc_id", "nutrient_id", "amount");

		double amount;
		int f_id, n_id;
		unsigned int current_line = in.get_file_line();

		for (Food food : foods_) {
			in.set_file_line(current_line);
			while (in.read_row(f_id, n_id, amount)) {
				if (food.f_id() == f_id) {
					for (Nutrient n : macro_nutrients_) {
						if (n.n_id() == n_id) {
							Nutrient n_copy = Nutrient(n);
							n_copy.amount_per_100g(amount);
							food.addNutrient(n_copy);
						}
					}
				}
			}
			current_line = in.get_file_line();
		}
	}
	catch (exception e) {
		throw e;
	}
}

// Helper functions
void splitLineCSV(string& line, vector<string>& result) {
	line.erase(remove(line.begin(), line.end(), '"'), line.end()); // remove any quotation marks from line
	boost::split(result, line, boost::is_any_of(",")); //	splits line into one element per column
}

bool nameIsDuplicate(const string& str, const vector<Food>& v) {
	auto it = find_if(v.begin(), v.end(), [&str](const Food& food) {
		return food.name() == str;
		});
	if (it != v.end()) {return true;}
	else { return false; }
}

void Database::initMacroNutrients() {
	vector<int> macro_ids = { 1003, 1004, 1005, 1008, 1062 };
	for (Nutrient n : nutrients_) {
		for (int i : macro_ids) {
			if (n.n_id() == i) {
				macro_nutrients_.push_back(n);
			}
		}
	}
}