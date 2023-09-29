#include <iostream>
#include <cmath>
#include "image_menu.h"
#include "Image.h"
#include "PPM.h"
#include "ActionData.h"
#include "NumberGrid.h"
#include "ColorTable.h"
#include "ComplexFractal.h"
#include "JuliaSet.h"

void diagonalQuadPattern(ActionData& ad) {
	int height = getInteger(ad, "Image height? ");
	int width = getInteger(ad, "Image width? ");
	ad.getInputImage1().setWidth(width);
	ad.getInputImage1().setHeight(height);
	ad.getInputImage1().setMaxColorValue(255);

	int column;
	int row;
	int tempValue;

	// Green channel of each pixel is calculated as (2*row + 2*column ) % 256
	for (column = 0; column < width; column++) {
		for (row = 0; row < height; row++) {
			tempValue = (2*row + 2*column ) % 256;
			ad.getInputImage1().setChannel(row, column, 1, tempValue);	// channel value may need altered
		}
	}
	
	// top half of the image has a red channel of 0
	// top half row values calculated by dividing image height by 2
	// bottom half of the image has a red channel of 255
	// bottom half row values calculated similarly
	for (column = 0; column < width; column++) {
		for (row = 0; row < height/2; row++) {
			ad.getInputImage1().setChannel(row, column, 0, 0);		// channel value may need altered
		}
		for (row = height/2; row < height; row++) {
			ad.getInputImage1().setChannel(row, column, 0, 255);
		}
	}

	// left half of the image has a blue channel of 0
	// right half has a blue channel of 255
	// all calculated similarly to red channel, but with regards to columns
	for (row = 0; row < height; row++) {
		for (column = 0; column < width/2; column++) {
			ad.getInputImage1().setChannel(row, column, 2, 0);		// channel value may need altered
		}
		for (column = width/2; column < width; column++) {
			ad.getInputImage1().setChannel(row, column, 2, 255);
		}
	}
}


void stripedDiagonalPattern(ActionData& ad) {
	int height = getInteger(ad, "Image height? ");
	int width = getInteger(ad, "Image width? ");
	ad.getInputImage1().setHeight(height);
	ad.getInputImage1().setWidth(width);
	int max_color_value = (height + width) / 3;
	
	if (max_color_value < 255){
		ad.getInputImage1().setMaxColorValue(max_color_value);
	}else{
		ad.getInputImage1().setMaxColorValue(255);
	}
	max_color_value = ad.getInputImage1().getMaxColorValue();
	// If a pixel is in the top half of the image, set the red channel of the pixel to 0.
	// Set the green channel of a pixel to (row + width - column - 1) % mMaxColorValue+1.
	// Set blue channel of a pixel to 0 if col < row. Else set blue to max.
	int col, row, redValue, greenValue, blueValue;
	for (col = 0; col < width; col++) {
		for (row = 0; row < height; row++) {
			// green value
			greenValue = (row + width - col - 1) % (max_color_value+1);
			// blue value
			if (col < row) {				// sets blue min
				blueValue = 0;
			}else{
				blueValue = max_color_value;		// sets blue max
			}
			// red value
			if ((row < (height/2)) || (row % 3 == 0)) {
				redValue = 0;
			}else{
				redValue = max_color_value;
			}
			
			ad.getInputImage1().setPixel(row, col, redValue, greenValue, blueValue);
		}
	}
}

void setSize(ActionData& ad) {
	int height = getInteger(ad, "Height? ");
	int width = getInteger(ad, "Width? ");
	ad.getInputImage1().setHeight(height);
	ad.getInputImage1().setWidth(width);
}

void setMaxColorValue(ActionData& ad) {
	int val = getInteger(ad, "Max color value? ");
	ad.getInputImage1().setMaxColorValue(val);
}

void setChannel(ActionData& ad) {
	int row = getInteger(ad, "Row? ");
	int col = getInteger(ad, "Column? ");
	int channel = getInteger(ad, "Channel? ");
	int value = getInteger(ad, "Value? ");
	ad.getInputImage1().setChannel(row, col, channel, value);
}

void setPixel(ActionData& ad) {
	int row = getInteger(ad, "Row? ");
	int col = getInteger(ad, "Column? ");
	int r = getInteger(ad, "Red? ");
	int g = getInteger(ad, "Green? ");
	int b = getInteger(ad, "Blue? ");
	ad.getInputImage1().setPixel(row, col, r, g, b);
}

void clearAll(ActionData& ad) {
	int height = ad.getInputImage1().getHeight();
	int width = ad.getInputImage1().getWidth();
	int row, col;
	for (row = 0; row < height; row++) {
		for (col = 0; col < width; col++) {
			ad.getInputImage1().setPixel(row, col, 0, 0, 0);
		}
	}
}

void drawCircle(ActionData& ad) {
	int row = getInteger(ad, "Center Row? ");
	int col = getInteger(ad, "Center Column? ");
	int radius = getInteger(ad, "Radius? ");
	int r = getInteger(ad, "Red? ");
	int g = getInteger(ad, "Green? ");
	int b = getInteger(ad, "Blue? ");
	double distance, height, width;	// calculate distance from center
	int leftmost = col - radius;
	int rightmost = col + radius;
	int upmost = row - radius;
	int downmost = row + radius;	// later pixels are towards bottom
	int iRow, iCol;			// iterative row and column
	for (iRow = upmost; iRow <= downmost; iRow++) {
		if (iRow <= row) {
			height = row - iRow;
		}else {
			height = iRow - row;
		}
		for (iCol = leftmost; iCol <= rightmost; iCol++) {
			if (iCol <= col) {
				width = col - iCol;
			}else {
				width = iCol - col;
			}
			distance = std::sqrt((width * width) + (height * height));
			if (distance <= radius) {	// swap for hole
				ad.getInputImage1().setPixel(iRow, iCol, r, g, b);
			}
		}
	}
}

void drawBox(ActionData& ad) {
	int top = getInteger(ad, "Top Row? ");
	int left = getInteger(ad, "Left Column? ");
	int bottom = getInteger(ad, "Bottom Row? ");
	int right = getInteger(ad, "Right Column? ");
	int r = getInteger(ad, "Red? ");
	int g = getInteger(ad, "Green? ");
	int b = getInteger(ad, "Blue? ");
	int row, col;
	for (row = top; row <= bottom; row++) {
		for (col = left; col <= right; col++) {
			ad.getInputImage1().setPixel(row, col, r, g, b);
		}
	}
}

void configureGrid(ActionData& ad) {
	int height = getInteger(ad, "Grid Height? ");
	int width = getInteger(ad, "Grid Width? ");
	int max = getInteger(ad, "Grid Max Value? ");
	ad.getGrid().setGridSize(height, width);
	ad.getGrid().setMaxNumber(max);
}

void setGrid(ActionData& ad) {
	int row = getInteger(ad, "Grid Row? ");
	int col = getInteger(ad, "Grid Column? ");
	int value = getInteger(ad, "Grid Value? ");
	ad.getGrid().setNumber(row, col, value);
}

void applyGrid(ActionData& ad) {
	ad.getGrid().setPPM(ad.getOutputImage());
}

void setColorTableSize(ActionData& ad) {
	int size = getInteger(ad, "Size? ");
	ad.getTable().setNumberOfColors(size);
}

void setColor(ActionData& ad) {
	int position = getInteger(ad, "Position? ");
	int r = getInteger(ad, "Red? ");
	int g = getInteger(ad, "Green? ");
	int b = getInteger(ad, "Blue? ");
	ad.getTable()[position].setRed(r);
	ad.getTable()[position].setGreen(g);
	ad.getTable()[position].setBlue(b);
}

void setRandomColor(ActionData& ad) {
	int position = getInteger(ad, "Position? ");
	ad.getTable().setRandomColor(255, position);
}

void setColorGradient(ActionData& ad) {
	int position1 = getInteger(ad, "First position? ");
	int r1 = getInteger(ad, "First red? ");
	int g1 = getInteger(ad, "First green? ");
	int b1 = getInteger(ad, "First blue? ");
	int position2 = getInteger(ad, "Second position? ");
	int r2 = getInteger(ad, "Second red? ");
	int g2 = getInteger(ad, "Second green? ");
	int b2 = getInteger(ad, "Second blue? ");
	Color c1(r1, g1, b1), c2(r2, g2, b2);
	ad.getTable().insertGradient(c1, c2, position1, position2);
}

void applyGridColorTable(ActionData& ad) {
	ad.getGrid().setPPM(ad.getOutputImage(), ad.getTable());
}

void setFractalPlaneSize(ActionData& ad) {
	// DYNAMIC_CAST
	// used to verify type of object pointed to
	ComplexFractal* p = dynamic_cast<ComplexFractal*>(&ad.getGrid());
	if (p == 0) {
		ad.getOS() << "Not a ComplexFractal object. Can't set plane size.\n";
	}else{
		double minx = getDouble(ad, "Min X? ");
		double maxx = getDouble(ad, "Max X? ");
		double miny = getDouble(ad, "Min Y? ");
		double maxy = getDouble(ad, "Max Y? ");
		p->setPlaneSize(minx, maxx, miny, maxy);
	}
}

void calculateFractal(ActionData& ad) {			// utilizes immediate inheritance of threadedgrid
	ad.getGrid().calculateAllNumbers();
}

void calculateFractalSingleThread(ActionData& ad) {	// utilizes single threaded method from NumberGrid class
	ad.getGrid().NumberGrid::calculateAllNumbers();
}

void setJuliaParameters(ActionData& ad) {

	// DYNAMIC_CAST
	// used to verify type of object pointed to
	JuliaSet* p = dynamic_cast<JuliaSet*>(&ad.getGrid());
	if (p == 0) {
		ad.getOS() << "Not a JuliaSet object. Can't set parameters.\n";
	}else{
		double a = getDouble(ad, "Parameter a? ");
		double b = getDouble(ad, "Parameter b? ");
		p->setParameters(a, b);
	}
}

//exam stuff
void fourSquarePattern(ActionData& ad) {
	int size = getInteger(ad, "Image size? ");
	ad.getInputImage1().setHeight(size);
	ad.getInputImage1().setWidth(size);
	ad.getInputImage1().setMaxColorValue(100);
	int col, row, r, g, b;
	for (col = 0; col < ad.getInputImage1().getWidth(); col++) {
		for (row = 0; row < ad.getInputImage1().getHeight(); row++) {
			if ((col <= ad.getInputImage1().getWidth()/2) && (row <= ad.getInputImage1().getHeight()/2)) {
				r = 100;
				g = 0;
				b = 66;
			}else if ((col >= ad.getInputImage1().getWidth()/2) && (row <= ad.getInputImage1().getHeight()/2)) {
				r = 0;
				g = 100;
				b = 33;
			}else if ((col <= ad.getInputImage1().getWidth()/2) && (row >= ad.getInputImage1().getHeight()/2)) {
				r = 66;
				g = 33;
				b = 100;
			}else {
				r = 33;
				g = 66;
				b = 0;
			}
			ad.getInputImage1().setPixel(row, col, r, g, b);
		}
	}
}

void simpleSquaresPattern(ActionData& ad) {
	int size = getInteger(ad, "Image size? ");
	ad.getInputImage1().setHeight(size);
	ad.getInputImage1().setWidth(size);
	ad.getInputImage1().setMaxColorValue(255);
	int col, row;
	for (col = 0; col < ad.getInputImage1().getWidth(); col++) {
		for (row = 0; row < ad.getInputImage1().getHeight(); row++) {
			if (row < ad.getInputImage1().getHeight()/2) {
				ad.getInputImage1().setChannel(row, col, 0, 127);
			}else {
				ad.getInputImage1().setChannel(row, col, 0, 255);
			}
			if (col < ad.getInputImage1().getWidth()/2) {
				ad.getInputImage1().setChannel(row, col, 1, 0);
			}else {
				ad.getInputImage1().setChannel(row, col, 1, 255);
			}
			ad.getInputImage1().setChannel(row, col, 2, 255);
		}
	}
}

void drawSquare(ActionData& ad) {
	int midRow = getInteger(ad, "Row? ");
	int midCol = getInteger(ad, "Column? ");
	int size = getInteger(ad, "Size? ");
	int r = getInteger(ad, "Red? ");
	int g = getInteger(ad, "Green? ");
	int b = getInteger(ad, "Blue? ");
	int lRow = midRow - (size/2);
	int rRow = midRow + (size/2);
	int tCol = midCol - (size/2);
	int bCol = midCol + (size/2);
	int row, col;
	for (row = lRow; row < rRow; row++) {
	// TODO: make boundaries inclusive (e.g. <= vs <)
		for (col = tCol; col < bCol; col++) {
			ad.getInputImage1().setPixel(row, col, r, g, b);
		}
	}
}

void drawTestColorPattern(ActionData& ad) {
	int height = getInteger(ad, "Height? ");
	int width = getInteger(ad, "Width? ");
	int max = getInteger(ad, "Max color value? ");
	ad.getInputImage1().setHeight(height);
	ad.getInputImage1().setWidth(width);
	ad.getInputImage1().setMaxColorValue(max);
	int col, row;
	for (col = 0; col < width; col++) {
		for (row = 0; row < height; row++) {
			// TODO: reverse inclusions
			if (row <= width/2 && row <= height/2) {
				ad.getInputImage1().setPixel(row, col, max, 0, 0);
			}else if (row > width/2 && row <= height/2) {
				ad.getInputImage1().setPixel(row, col, 0, max, 0);
			}else if (row <= width/2 && row > height/2) {
				ad.getInputImage1().setPixel(row, col, 0, 0, max);
			}else {
				ad.getInputImage1().setPixel(row, col, max/2, max/2, max/2);
			}
		}
	}
}

void setMandelbrotPower(ActionData& ad) {
	MandelbrotPower* p = dynamic_cast<MandelbrotPower*>(&ad.getGrid());
	if (p == 0) {
		ad.getOS() << "Not a MandelbrotPower object. Can't set power.";
	}else {
		double power = getDouble(ad, "Power? ");
		p->setPower(power);
	}
}

void setInvertedColorGradient(ActionData& ad) {
	int position1 = getInteger(ad, "First position? ");
	int r1 = getInteger(ad, "First red? ");
	int g1 = getInteger(ad, "First green? ");
	int b1 = getInteger(ad, "First blue? ");
	int position2 = getInteger(ad, "Second position? ");
	Color c1(r1, g1, b1);
	ad.getTable().insertInvertedGradient(c1, position1, position2);
}
