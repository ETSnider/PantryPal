#include <iostream>
#include <fstream>
#include <chrono>
#include "DataBase.h"
using namespace std;

int main() {
	Database database;

	// Initializing nutrient data
	auto start = chrono::high_resolution_clock::now();
	try {
		database.initNutrient();
	}
	catch (exception e) {
		cout << e.what() << endl;
	}
	auto stop = chrono::high_resolution_clock::now();
	auto duration = chrono::duration_cast<chrono::milliseconds>(stop - start);
	cout << "Initialize time (ms): " << duration.count() << endl;
	
	//	Checking for nutritient vector content
	vector<Nutrient> tmpList1;
	tmpList1 = database.nutrients();
	cout << "Nutrient database contains " << tmpList1.size() << " nutrients\n" << endl;
	cout << "The nutrients in the DB are:" << endl;
	for (unsigned int i = 0; i < tmpList1.size(); i++) {
		cout << tmpList1.at(i).name() << endl;
	}

	cout << "\nContents of single Nutrient:" << endl;
	cout << "id: " << tmpList1.at(1).n_id() << endl;
	cout << "name: " << tmpList1.at(1).name() << endl;
	cout << "units: " << tmpList1.at(1).std_unit() << endl;

	//	Initializing food data
	start = chrono::high_resolution_clock::now();
	try {
		database.initFood();
		cout << "\nFood database initialized\n" << endl;
	}
	catch (exception e) {
		cout << e.what() << endl;
	}
	stop = chrono::high_resolution_clock::now();
	duration = chrono::duration_cast<chrono::milliseconds>(stop - start);
	cout << "Initialize time (ms): " << duration.count() << endl;

	//	Check for food vector content
	vector<Food> tmpList2;
	tmpList2 = database.foods();
	cout << "Food database contains " << tmpList2.size() << " foods\n" << endl;
	cout << "The first 250 foods in the DB are:" << endl;
	for (int i = 0; i < 250; i++) {
		cout << tmpList2.at(i).name() << endl;
	}

	cout << "\nContents of single Food:" << endl;
	cout << "id: " << tmpList2.at(1).f_id() << endl;
	cout << "name: " << tmpList2.at(1).name() << endl;
	cout << "dataType: " << tmpList2.at(1).data_type() << endl;
	cout << "category: " << tmpList2.at(1).category() << endl;

	//	Initializing food nutrient data
	start = chrono::high_resolution_clock::now();
	try {
		database.initMacroNutrients();
		database.initFoodNutrient();
		cout << "\nFood nutrition data initialized\n" << endl;
	}
	catch (FileException e) {
		cout << e.what() << endl;
	}
	stop = chrono::high_resolution_clock::now();
	duration = chrono::duration_cast<chrono::milliseconds>(stop - start);
	cout << "Initialize time (ms): " << duration.count() << endl;

	// Check macro nutrient vector content
	for (int i = 0; i < database.macro_nutrients().size(); i++) {
		cout << database.macro_nutrients().at(i).name() << endl;
	}

	//	Check for food nutrient vector content
	vector<Nutrient> tmpList3 = tmpList2.at(2).nutrition();
	cout << "\nFood contains " << tmpList3.size() << " nutrients\n" << endl;
	cout << "The sample food nutrients in the DB are:\n" << endl;
	cout << "name\tamount per 100g of food\n" << endl;
	for (int i = 0; i < tmpList3.size(); i++) {
		cout << tmpList3.at(i).name() << "\t"
			<< tmpList3.at(i).amount_per_100g() << tmpList3.at(i).std_unit() << endl;
	}
}