#include "commonFunctions.hpp"

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

string encloseInParen(string toEnclose, string enclosingCharacters /*= "()"*/) {

	string assembledString = enclosingCharacters[0] + toEnclose + enclosingCharacters[1];

	return assembledString;
}

/*string encloseInParen(int toEnclose, string enclosingCharacters /*= "()"*/ /*) {

}*/

string encloseInElement(const string& toEnclose, const string& enclosingTag, const string& attributes/*= ""*/) {

	string assembledString = "<" + enclosingTag + " " + attributes + ">";

	assembledString += toEnclose;

	assembledString += "</" + enclosingTag + ">";

	return assembledString;
}

string determineOrdinal(int number) {
	switch (number) {
		case 1: {
			return "st";
		}
		case 2: {
			return "nd";
		}
		case 3: {
			return "rd";
		}
		default: {
			return "th";
		}
	}
}

string determineOrdinal(std::string number) {

	if (_betweeninc(number[number.length() - 1] - '0',0,9)) {
		return determineOrdinal(number);
	} else {
		return "";
	}
}