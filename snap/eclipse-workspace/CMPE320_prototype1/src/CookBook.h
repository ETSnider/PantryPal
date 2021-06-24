#pragma once
#include<string>
using namespace std;
class CookBook {
private:
	//string recipe;
	string ingredients;
	string instructions;
public:
		//searchRecipeByIng();
		//string urlFormat();
		//jsonReceive();
		size_t jsonStore(char* data, size_t size, size_t nmemb, std::string* buffer_in);
		string* recipe;


};