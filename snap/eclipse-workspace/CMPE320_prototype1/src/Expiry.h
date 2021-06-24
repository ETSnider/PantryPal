#pragma once
#include <iostream>
#include <ctime>
#include <vector>
#include "Ingredient.h"
#include "Inventory.h"

class Expiry {
private:
	int tolerance = 3;
public:
	Expiry(int tolerance = 3);
	int getTolerance();
	int muteTolerance(int newTolerance);
	vector<Ingredient> getExpiring(Inventory pantry);
	vector<Ingredient> getExpired(Inventory pantry);
};

class ExpiryException {
public:
	ExpiryException(const string& message);
	string& what();
private:
	string message;
};