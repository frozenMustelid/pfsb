#ifndef COMMON_FUNCTIONS_HPP
#define COMMON_FUNCTIONS_HPP

#include <iostream>
#include <limits>

using namespace std;

void clearBuffer() {

	cin.clear();

	cin.ignore(numeric_limits<streamsize>::max(),'\n');

	cin.clear();

	return;
}

string stringToLower(string toLower) {

	int x = 0;

	while(toLower[x] != '\0') {
		toLower[x] = tolower(toLower[x]);
		x++;
	}

	return toLower;

}

//Trivial wrapper for floor. Used because of an enum conflict with cmath and Size::HUGE
/*int intFloor(double value) {

	return static_cast<int>(floor(value));
}*/

#endif