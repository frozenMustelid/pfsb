#ifndef COMMON_FUNCTIONS_HPP
#define COMMON_FUNCTIONS_HPP

#include <string>

#define _betweeninc(val,num1,num2) (((num1 <= val) && (val <= num2))   ||   ((num2 <= val) && (val <= num1)))
//bool betweeninc(int val, int num1, int num2);
#define _answerIsYes(choice) (choice[0] == 'y' || choice[0] == 'Y')
//bool answerIsYes(string choice);

void clearBuffer();
std::string stringToLower(std::string toLower);

       std::string encloseInParen(std::string toEnclose, std::string enclosingCharacters = "()");
inline std::string encloseInParen(const int& toEnclose, const std::string& enclosingCharacters = "()") {return encloseInParen(std::to_string(toEnclose),enclosingCharacters);}
std::string encloseInElement(const std::string& toEnclose, const std::string& enclosingTag, const std::string& attributes = ""); 
//No diamond brackets!

std::string determineOrdinal(int);
std::string determineOrdinal(std::string);
//Will not handle empty string properly. Will return empty string if final character is not a number.


#endif