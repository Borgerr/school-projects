#include <iostream>
#include "image_menu.h"
#include "Image.h"
#include "PPM.h"
#include "ActionData.h"
#include "MenuData.h"
#include "NumberGrid.h"
#include "ComplexFractal.h"
#include "JuliaSet.h"
#include "MandelbrotSet.h"

int assignment1(std::istream& is, std::ostream& os) {
	ActionData ad(is, os);
	int returned = askQuestions3(ad);
	return returned;
}

int assignment2(std::istream& is, std::ostream& os) {
	ActionData ad(is, os);
	diagonalQuadPattern(ad);
	//copy input image 1 to output image between drawing and output.
	copyImage(ad);
	drawAsciiImage(ad);
	return 0;
}

int assignment3(std::istream& is, std::ostream& os) {
	ActionData ad(is, os);
	stripedDiagonalPattern(ad);
	copyImage(ad);
	writeUserImage(ad);
	return 0;
}

void showMenu(MenuData& md, ActionData& ad) {
	std::vector<std::string> commands = md.getNames();
	unsigned int i;				// iterator
	unsigned int len = commands.size();	// iterated
	std::string name;
	for (i=0; i < len; i++) {
		name = commands[i];
		ad.getOS() << name << ") " << md.getDescription(name) << std::endl;
	}
}

void takeAction(const std::string& choice, MenuData& md, ActionData& ad) {
	ActionFunctionType func = md.getFunction(choice);
	if (func != 0) {
		func(ad);
	}else if (choice == "menu") {
		showMenu(md, ad);
	}else {
		ad.getOS() << "Unknown action '" << choice << "'." << std::endl;
	}
}

void configureMenu(MenuData& md) {
	md.addAction("draw-ascii", drawAsciiImage, "Write output image to terminal as ASCII art.");
	md.addAction("write", writeUserImage, "Write output image to file.");
	md.addAction("copy", copyImage, "Copy input image 1 to output image.");
	md.addAction("read1", readUserImage1, "Read file into input image 1.");
	md.addAction("#", commentLine, "Comment to end of line.");
	md.addAction("size", setSize, "Set the size of input image 1.");
	md.addAction("max-color-value", setMaxColorValue, "Set the max color value of input image 1.");
	md.addAction("channel", setChannel, "Set a channel value in input image 1.");
	md.addAction("pixel", setPixel, "Set a pixel's 3 values in input image 1.");
	md.addAction("clear", clearAll, "Set all pixels to 0,0,0 in input image 1.");
	md.addAction("quit", quit, "Quit.");
	md.addAction("read2", readUserImage2, "Read file into input image 2.");
	md.addAction("+", plus, "Set output image from sum of input image 1 and input image 2.");
	md.addAction("+=", plusEquals, "Set input image 1 by adding in input image 2.");
	md.addAction("-", minus, "Set output image from difference of input image 1 and input image 2.");
	md.addAction("-=", minusEquals, "Set input image 1 by subtracting input image 2.");
	md.addAction("*", times, "Set output image from input image 1 multiplied by a number.");
	md.addAction("*=", timesEquals, "Set input image 1 by multiplying by a number.");
	md.addAction("/", divide, "Set output image from input image 1 divided by a number.");
	md.addAction("/=", divideEquals, "Set input image 1 by dividing by a number.");
	md.addAction("red-gray", grayFromRed, "Set output image by grayscale from red on input image 1.");
	md.addAction("green-gray", grayFromGreen, "Set output image by grayscale from green on input image 1.");
	md.addAction("blue-gray", grayFromBlue, "Set output image by grayscale from blue on input image 1.");
	md.addAction("linear-gray", grayFromLinearColorimetric, "Set output image by linear colorimetric grayscale on input image 1.");
	md.addAction("circle", drawCircle, "Draw a circle shape in input image 1.");
	md.addAction("box", drawBox, "Draw a box shape in input image 1.");
	
	md.addAction("grid", configureGrid, "Configure the grid.");
	md.addAction("grid-set", setGrid, "Set a single value in the grid.");
	md.addAction("grid-apply", applyGrid, "Use the grid values to set colors in the output image.");
	md.addAction("grid-apply-color-table", applyGridColorTable, "Use the grid values to set colors in the output image using the color table.");
	md.addAction("set-color-gradient", setColorGradient, "Smoothly set the RGB values for a range of slots in the color table.");
	md.addAction("set-random-color", setRandomColor, "Randomly set the RGB values for one slot in the color table.");
	md.addAction("set-color", setColor, "Set the RGB values for one slot in the color table.");
	md.addAction("set-color-table-size", setColorTableSize, "Change the number of slots in the color table.");
	md.addAction("fractal-plane-size", setFractalPlaneSize, "Set the dimensions of the grid in the complex plane.");
	md.addAction("fractal-calculate", calculateFractal, "Calculate the escape values for the fractal.");
	md.addAction("julia-parameters", setJuliaParameters, "Set the parameters of the Julia Set function.");
	md.addAction("complex-fractal", setComplexFractal, "Choose to make a complex plane.");
	md.addAction("julia", setJuliaFractal, "Choose to make a Julia set.");
	md.addAction("mandelbrot", setMandelbrotFractal, "Choose to make a Mandelbrot set.");
	md.addAction("fractal-calculate-single-thread", calculateFractalSingleThread, "Calculate the escape values for the fractal, single-thread.");

	// NOT IMPLEMENTED IN CLASS, BE CAREFUL
	//md.addAction("write-single-thread", writeSingleThread, "Write output image to file, single-thread.");
	// ------------------------------------

	// exam
	md.addAction("square", drawSquare, "Draw a square shape in input image 1.");
	md.addAction("orange", orangeFilter, "Set output image from orange filter on input image 1.");
	md.addAction("*=-ppm", timesEqualsPPM, "Set input image 1 by multiplying by input image 2.");
	md.addAction("blend", blendImages, "Blend input image 1 and input image 2 into the output image.");
	md.addAction("test-pattern", drawTestColorPattern, "Draw a test pattern in input image 1.");
	md.addAction("diagonal-quad", diagonalQuadPattern, "Draw a diagonal quad pattern in input image 1.");
	md.addAction("striped-diagonal", stripedDiagonalPattern, "Draw a striped diagonal pattern in input image 1.");
	md.addAction("copy12", copyImage1ToImage2, "Copy input image 1 to input image 2.");
	md.addAction("copy21", copyImage2ToImage1, "Copy input image 2 to input image 1.");
	md.addAction("mandelbrot-power", setMandelbrotPowerFractal, "Choose to make a Mandelbrot set with the power function.");
	md.addAction("set-mandelbrot-power", setMandelbrotPower, "Choose a power for the Mandelbrot power function.");
	md.addAction("julia-four", setJuliaFourFractal, "Choose to make a Julia set with the fourth power function.");
	md.addAction("set-inverted-color-gradient", setInvertedColorGradient, "Smoothly set the values for a range of slots in the color table, using a color and its inverse.");
	md.addAction("anti-alias", antiAliasFilter, "Set output image from Anti-alias filter on input image 1.");
	md.addAction("copyo1", copyOutputImageToImage1, "Copy output image to input image 1.");
}

int imageMenu(std::istream& is, std::ostream& os) {
	ActionData ad(is, os);
	NumberGrid *ptr;
	ptr = new ComplexFractal;
	ad.setGrid(ptr);
	MenuData md;
	configureMenu(md);
	std::string choice;

	while ((!ad.getDone()) && (ad.getIS().good())) {
		choice = getChoice(ad);
		takeAction(choice, md, ad);
	}
	return 0;
}

void setComplexFractal(ActionData& ad) {
	ComplexFractal *ptr = new ComplexFractal;
	ad.setGrid(ptr);
}

void setJuliaFractal(ActionData& ad) {
	JuliaSet *ptr = new JuliaSet;
	ad.setGrid(ptr);
}

void setMandelbrotFractal(ActionData& ad) {
	MandelbrotSet *ptr = new MandelbrotSet;
	ad.setGrid(ptr);
}

// exam problems
int four_square(std::istream& is, std::ostream& os) {
	ActionData ad(is, os);
	fourSquarePattern(ad);
	copyImage(ad);
	writeUserImage(ad);
	return 0;
}

int simple_squares_ascii(std::istream& is, std::ostream& os) {
	ActionData ad(is, os);
	simpleSquaresPattern(ad);
	copyImage(ad);
	drawAsciiImage(ad);
	return 0;
}

int hero(std::istream& is, std::ostream& os) {
	ActionData ad(is, os);
	return askHeroQuestions(ad);
}

void setMandelbrotPowerFractal(ActionData& ad) {
	MandelbrotPower* ptr = new MandelbrotPower;
	ad.setGrid(ptr);
}

void setJuliaFourFractal(ActionData& ad) {
	JuliaSetFour* ptr = new JuliaSetFour;
	ad.setGrid(ptr);
}
