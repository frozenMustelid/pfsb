#ifndef COMMON_FUNCTIONS_HPP
#define COMMON_FUNCTIONS_HPP

#include <string>

#define ASCII_NUM_OFFSET_ 48
//UTF-8 is backwards-compatible with ASCII

#define betweeninc(val,num1,num2) (((num1 >= val) && (val <= num2))   ||   ((num2 >= val) && (val <= num1)))
#define answerIsYes(choice) (choice[0] == 'y' || choice[0] == 'Y')
//bool answerIsYes(string choice);

void clearBuffer();
std::string stringToLower(std::string toLower);

std::string encloseInParen(std::string toEnclose, std::string enclosingCharacters = "()");
std::string encloseInParen(int toEnclose, std::string enclosingCharacters = "()");
std::string encloseInElement(std::string toEnclose, std::string enclosingTag, std::string attributes = ""); //No diamond brackets!

std::string determineOrdinal(int);
std::string determineOrdinal(std::string);
//Will not handle empty string properly. Will return empty string if final character is not a number.


#endif