#include "NumberGrid.h"
#include "PPM.h"
#include "ColorTable.h"
#include <vector>

NumberGrid::NumberGrid()
	: mHeight(300), mWidth(400), mMaxNumber(255) {
	// fill grid with zeroes
	int size = mHeight * mWidth;
	int i;
	mVector.resize(size);
	for (i = 0; i < size; i++) {
		mVector[i] = 0;
	}
}

NumberGrid::NumberGrid(const int& height, const int& width)
	: mHeight(height), mWidth(width), mMaxNumber(255) {
	// fill grid with zeroes
	int size = height * width;
	int i;
	mVector.resize(size);
	for (i = 0; i < size; i++) {
		mVector[i] = 0;
	}
}

NumberGrid::~NumberGrid() {

}

int NumberGrid::getHeight() const {
	return mHeight;
}

int NumberGrid::getWidth() const {
	return mWidth;
}

int NumberGrid::getMaxNumber() const {
	return mMaxNumber;
}

void NumberGrid::setGridSize(const int& height, const int& width) {
	if (height >= 2 && width >= 2) {
		mHeight = height;
		mWidth = width;
		mVector.resize(height * width);
	}
}

void NumberGrid::setMaxNumber(const int& number) {
	if (number >= 0) {
		mMaxNumber = number;
	}
}

const std::vector<int>& NumberGrid::getNumbers() const {
	return mVector;
}

int NumberGrid::index(const int& row, const int& column) const {
	// returns an integer representation of the vector index
	// when given the grid row and column parameters.
	if (!indexValid(row, column)) {
		return -1;
	}
	return (row*mWidth) + column;
}

bool NumberGrid::indexValid(const int& row, const int& column) const {
	return ((row < mHeight) && (column < mWidth) && (row >= 0) && (column >= 0));
}

bool NumberGrid::numberValid(const int& number) const {
	return (number >= 0 && number <= mMaxNumber);
}

int NumberGrid::getNumber(const int& row, const int& column) const {
	// returns the number in the position of parameters row, column in the grid
	if (!indexValid(row, column)) {
		return -1;
	}
	return mVector[index(row, column)];
}

void NumberGrid::setNumber(const int& row, const int& column, const int& number) {
	if (indexValid(row, column) && numberValid(number)) {
		mVector[index(row, column)] = number;
	}
}

void NumberGrid::setPPM(PPM& ppm) const {
	ppm.setHeight(mHeight);
	ppm.setWidth(mWidth);
	ppm.setMaxColorValue(63);
	int row, col, value;
	for (row = 0; row < mHeight; row++) {
		for (col = 0; col < mWidth; col++) {
			value = getNumber(row, col);
			if (value == 0) {
				ppm.setPixel(row, col, 0, 0, 0);
			}else if (value == mMaxNumber) {
				ppm.setPixel(row, col, 63, 31, 31);
			}else if (value % 8 == 0) {
				ppm.setPixel(row, col, 63, 63, 63);
			}else if (value % 8 == 1) {
				ppm.setPixel(row, col, 63, 31, 31);
			}else if (value % 8 == 2) {
				ppm.setPixel(row, col, 63, 63, 31);
			}else if (value % 8 == 3) {
				ppm.setPixel(row, col, 31, 63, 31);
			}else if (value % 8 == 4) {
				ppm.setPixel(row, col, 0, 0, 0);
			}else if (value % 8 == 5) {
				ppm.setPixel(row, col, 31, 63, 63);
			}else if (value % 8 == 6) {
				ppm.setPixel(row, col, 31, 31, 63);
			}else if (value % 8 == 7) {
				ppm.setPixel(row, col, 63, 31, 63);
			}
		}
	}
}

void NumberGrid::setPPM(PPM& ppm, const ColorTable& colors) {
	if (colors.getNumberOfColors() >= 2) {
		ppm.setWidth(mWidth);
		ppm.setHeight(mHeight);
		ppm.setMaxColorValue(colors.getMaxChannelValue());	// possibly remove
		int row, col, r, g, b;
		Color current;
		//int height = ppm.getHeight();
		//int width = ppm.getWidth();
		for (row = 0; row < mHeight; row++) {
			for (col = 0; col < mWidth; col++) {
				if(getNumber(row, col) == mMaxNumber) {
					current = colors[colors.getNumberOfColors()-1];
				}else {
					current = colors[getNumber(row, col) % colors.getNumberOfColors()];
				}
				r = current.getRed();
				g = current.getGreen();
				b = current.getBlue();
				// DEBUGGING VALUES
				//std::cout << "red: " << r << ", " << "green: " << g << ", " << "blue: " << b;
				ppm.setPixel(row, col, r, g, b);
			}
		}
	}
}


//complex fractal assignment
void NumberGrid::calculateAllNumbers() {
	int row, col;
	for (row = 0; row < mHeight; row++) {
		for (col = 0; col < mWidth; col++) {
			setNumber(row, col, calculateNumber(row, col));
		}
	}
}
