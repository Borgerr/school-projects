#ifndef _IMAGE_MENU_H_
#define _IMAGE_MENU_H_

#include "Image.h"	// needed as Image class is a used parameter
#include "PPM.h"	// needed as PPM class is a used parameter
#include "ActionData.h"
#include "MenuData.h"
#include "ComplexFractal.h"
#include "JuliaSet.h"
#include "MandelbrotSet.h"
#include <string>
#include <iostream>

int getInteger(ActionData& ad, const std::string& prompt);

std::string getString(ActionData& ad, const std::string& prompt);

double getDouble(ActionData& ad, const std::string& prompt);

int askQuestions3(ActionData& ad);

int assignment1(std::istream& is, std::ostream& os);

void drawAsciiImage(ActionData& ad);

void diagonalQuadPattern(ActionData& ad);

int assignment2(std::istream& is, std::ostream& os);

void writeUserImage(ActionData& ad);

void stripedDiagonalPattern(ActionData& ad);

int assignment3(std::istream& is, std::ostream& os);

void fourSquarePattern(ActionData& ad);

int four_square(std::istream& is, std::ostream& os);

void simpleSquaresPattern(ActionData& ad);

std::string getChoice(ActionData& ad);

void commentLine(ActionData& ad);

void quit(ActionData& ad);

void setSize(ActionData& ad);

void setMaxColorValue(ActionData& ad);

void setChannel(ActionData& ad);

void setPixel(ActionData& ad);

void clearAll(ActionData& ad);

void copyImage(ActionData& ad);

void readUserImage1(ActionData& ad);

void showMenu(MenuData& md, ActionData& ad);

void takeAction(const std::string& choice, MenuData& md, ActionData& ad);

void configureMenu(MenuData& md);

int imageMenu(std::istream& is, std::ostream& os);

void plusEquals(ActionData& ad);

void minusEquals(ActionData& ad);

void timesEquals(ActionData& ad);

void divideEquals(ActionData& ad);

void plus(ActionData& ad);

void minus(ActionData& ad);

void times(ActionData& ad);

void divide(ActionData& ad);

void readUserImage2(ActionData& ad);

void grayFromRed(ActionData& ad);

void grayFromGreen(ActionData& ad);

void grayFromBlue(ActionData& ad);

void grayFromLinearColorimetric(ActionData& ad);

void drawCircle(ActionData& ad);

void drawBox(ActionData& ad);

void configureGrid(ActionData& ad);

void setGrid(ActionData& ad);

void applyGrid(ActionData& ad);

void setColorTableSize(ActionData& ad);

void setColor(ActionData& ad);

void setRandomColor(ActionData& ad);

void setColorGradient(ActionData& ad);

void applyGridColorTable(ActionData& ad);

void setFractalPlaneSize(ActionData& ad);

void calculateFractal(ActionData& ad);

void setJuliaParameters(ActionData& ad);

void setComplexFractal(ActionData& ad);

void setJuliaFractal(ActionData& ad);

void setMandelbrotFractal(ActionData& ad);

void calculateFractalSingleThread(ActionData& ad);


// NOT IMPLEMENTED IN CLASS, BE CAREFUL
//void writeSingleThread(ActionData& ad);
// ------------------------------------

// exam stuff
int simple_squares_ascii(std::istream& is, std::ostream& os);

int askHeroQuestions(ActionData& ad);

int hero(std::istream& is, std::ostream& os);

void drawSquare(ActionData& ad);

void orangeFilter(ActionData& ad);

void timesEqualsPPM(ActionData& ad);

void blendImages(ActionData& ad);

void drawTestColorPattern(ActionData& ad);

void copyImage1ToImage2(ActionData& ad);

void copyImage2ToImage1(ActionData& ad);

void setMandelbrotPower(ActionData& ad);

void setMandelbrotPowerFractal(ActionData& ad);

void setJuliaFourFractal(ActionData& ad);

void setInvertedColorGradient(ActionData& ad);

void antiAliasFilter(ActionData& ad);

void copyOutputImageToImage1(ActionData& ad);

#endif //_IMAGE_MENU_H_
