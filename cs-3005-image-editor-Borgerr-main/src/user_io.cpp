// Use these functions to get better user input output.
// Refer to questions3 assignment or lecture.
#include <iostream>	// std::cout, std::cin
#include <string>	// std::string
#include "image_menu.h"	// allows for export
#include "ActionData.h"

int getInteger(ActionData& ad, const std::string& prompt) {	// parameter types must be clarified.
	int i;
	ad.getOS() << prompt;
	ad.getIS() >> i;
	return i;
}

std::string getString(ActionData& ad, const std::string& prompt) {
	std::string i;
	ad.getOS() << prompt;
	ad.getIS() >> i;
	return i;
}

double getDouble(ActionData& ad, const std::string& prompt) {
	double i;
	ad.getOS() << prompt;
	ad.getIS() >> i;
	return i;
}

int askQuestions3(ActionData& ad) {
	std::string color = getString(ad, "What is your favorite color? ");
	int x = getInteger(ad, "What is your favorite integer? ");
	double number = getDouble(ad, "What is your favorite number? ");
	for(int i=1; i<x+1; i++) {
		ad.getOS() << i << " " << color << " " << number << std::endl;
	}
	return x;
}

int askHeroQuestions(ActionData& ad) {
	std::string hero = getString(ad, "Who is your hero? ");
	int birth = getInteger(ad, "What year were they born? ");
	ad.getOS() << hero << " was born in " << birth << "." << std::endl;
	return birth;
}

//	NEXT ASSIGNMENT
std::string getChoice(ActionData& ad) {
	return getString(ad, "Choice? ");
}

void commentLine(ActionData& ad) {
	char current;
	while ((current != '\n') && (ad.getIS().good())) {
		ad.getIS().read((char *) &current, sizeof(current));
	}
}

void quit(ActionData& ad) {
	ad.setDone();
}

