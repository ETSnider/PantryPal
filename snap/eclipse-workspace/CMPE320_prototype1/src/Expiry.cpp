/*
 * Expiry.cpp
 *
 *  Created on: Oct. 20, 2020
 *      Author: Evan
 */
#include "Expiry.h"
#include "Inventory.h"

//Constructor for Expiry class, default expiration tolerance of 3 days
Expiry::Expiry(int tol=3){
 tolerance=tol;
}
//Accessor for expiration tolerance
int Expiry::getTolerance(){
	return tolerance;
}
//Mutator for expiration tolerance, takes a positive integer
int Expiry::muteTolerance(int newTolerance){
	if (newTolerance<0){
		throw ExpiryException("Invalid tolerance");
	}
	else{
		tolerance=newTolerance;
		return newTolerance;
	}
}
//retrieves a vector of all expired ingredients
vector<Ingredient> Expiry::getExpired(Inventory pantry){
	vector<Ingredient> inventory=pantry.getCurrentInv();
	vector<Ingredient> expired;
	time_t now=time(0);

	for (int i=0;i<inventory.size();i++){
		time_t endDate=inventory[i].getExpiryDate();
		time_t buyDate=inventory[i].getPurchaseDate();
		if (endDate==buyDate){
			struct tm* tmbuyDate=localtime(&buyDate);
			tmbuyDate->tm_mday+=14;
			buyDate=mktime(tmbuyDate);
			if(difftime(buyDate,now)<=0){
				expired.push_back(inventory[i]);
			}
		}
		else{
			if (difftime(endDate,now)<=0){
				expired.push_back(inventory[i]);
			}
		}
	}
	return expired;
}
//retrieves a vector of all ingredients that expire in the next tolerance days
vector<Ingredient> Expiry::getExpiring(Inventory pantry){
	vector<Ingredient> inventory=pantry.getCurrentInv();
	vector<Ingredient> expiring;
	time_t now=time(0);
	int tol=getTolerance();

	for (int i=0;i<inventory.size();i++){
		time_t endDate=inventory[i].getExpiryDate();
		time_t buyDate=inventory[i].getPurchaseDate();
		struct tm* tmbuyDate=localtime(&buyDate);
		if (endDate==buyDate){
			tmbuyDate->tm_mday+=14-tol;
			buyDate=mktime(tmbuyDate);
			if(difftime(buyDate,now)<=0){
				expiring.push_back(inventory[i]);
			}
		}
		else{
			struct tm* tmExpiry=localtime(&endDate);
			tmExpiry->tm_mday-=tol;
			endDate=mktime(tmExpiry);
			if (difftime(endDate,now)<=0){
				expiring.push_back(inventory[i]);
			}
		}
	}
	return expiring;
}

// Exception code
ExpiryException::ExpiryException(const string& message) : message(message) {};
string& ExpiryException::what() { return message; };