#include <iostream>
#include <string>
#include <fstream>
#include "image_menu.h"
#include "Image.h"
#include "PPM.h"
#include "ActionData.h"

void drawAsciiImage(ActionData& ad){
	// float R + G + B / 765.0 = strength
	int r, g, b, row, column;
	double strength;
	int height = ad.getOutputImage().getHeight();
	int width = ad.getOutputImage().getWidth();

	for (row = 0; row < height; row++) {
		for (column = 0; column < width; column++) {
			r = ad.getOutputImage().getChannel(row, column, 0);
			g = ad.getOutputImage().getChannel(row, column, 1);
			b = ad.getOutputImage().getChannel(row, column, 2);
			strength = (r + g + b) / 765.0;
			// if strength in value range, assign this character
			if (strength >= 1.0) {
			// the order of if/else if statements matters here.
				ad.getOS() << "@";
			}else if (strength >= 0.9) {
				ad.getOS() << "#";
			}else if (strength >= 0.8) {
				ad.getOS() << "%";
			}else if (strength >= 0.7) {
				ad.getOS() << "*";
			}else if (strength >= 0.6) {
				ad.getOS() << "|";
			}else if (strength >= 0.5) {
				ad.getOS() << "+";
			}else if (strength >= 0.4) {
				ad.getOS() << ";";
			}else if (strength >= 0.3) {
				ad.getOS() << "~";
			}else if (strength >= 0.2) {
				ad.getOS() << "-";
			}else if (strength >= 0.1) {
				ad.getOS() << ".";
			}else if (strength >= 0.0) {
				ad.getOS() << " ";
			}
		}
		ad.getOS() << std::endl;
	}
}

void writeUserImage(ActionData& ad) {
	std::string str;
	str = getString(ad, "Output filename? ");
	std::ofstream fout(str);
	// fout.open();
	ad.getOutputImage().writeStream(fout);
	fout.close();
}



// NOT IMPLEMENTED IN CLASS, MAY NEED TO BE REMOVED
/*
void writeSingleThread(ActionData& ad) {
	std::string str;
	str = getString(ad, "Output filename? ");
	std::ofstream fout(str);
	ad.getOutputImage().writeStream(fout);
	fout.close();
}
*/
// ------------------------------------------------


void copyImage(ActionData& ad) {
	ad.getOutputImage() = ad.getInputImage1();
}

void readUserImage1(ActionData & ad) {
	std::string filename = getString(ad, "Input filename? ");
	std::ifstream fout(filename);
	if (fout.good()) {
		ad.getInputImage1().readStream(fout);
	}else {
		ad.getOS() << "'" << filename << "' could not be opened." << std::endl;
	}
	fout.close();
}

void readUserImage2(ActionData& ad) {
	std::string filename = getString(ad, "Input filename? ");
	std::ifstream fout(filename);
	if (fout.good()) {
		ad.getInputImage2().readStream(fout);
	}else {
		ad.getOS() << "'" << filename << "' could not be opened." << std::endl;
	}
	fout.close();
}


//exam
void copyImage1ToImage2(ActionData& ad) {
	ad.getInputImage2() = ad.getInputImage1();
}

void copyImage2ToImage1(ActionData& ad) {
	ad.getInputImage1() = ad.getInputImage2();
}

void copyOutputImageToImage1(ActionData& ad) {
	ad.getInputImage1() = ad.getOutputImage();
}
