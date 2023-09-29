#include <vector>
#include <iostream>
#include "ColorTable.h"

// Color methods
Color::Color() 
	: mRed(0), mGreen(0), mBlue(0) {
}

Color::Color(const int& r, const int& g, const int& b)
	: mRed(r), mGreen(g), mBlue(b) {
}

int Color::getRed() const {
	return mRed;
}

int Color::getGreen() const {
	return mGreen;
}

int Color::getBlue() const {
	return mBlue;
}

int Color::getChannel(const int& channel) const {
	if (channel == 0) {
		return mRed;
	}else if (channel == 1) {
		return mGreen;
	}else if (channel == 2) {
		return mBlue;
	}else {
		return -1;
	}
}

void Color::setRed(const int& value) {
	if (value >= 0) {
		mRed = value;
	}
}

void Color::setGreen(const int& value) {
	if (value >= 0) {
		mGreen = value;
	}
}

void Color::setBlue(const int& value) {
	if (value >= 0) {
		mBlue = value;
	}
}

void Color::setChannel(const int& channel, const int& value) {
	if (channel == 0) {
		setRed(value);
	}else if (channel == 1) {
		setGreen(value);
	}else if (channel == 2) {
		setBlue(value);
	}
}

void Color::invert(const int& max_color_value) {
	if ((max_color_value >= mRed) && (max_color_value >= mGreen) && (max_color_value >= mBlue)) {
		mRed = max_color_value - mRed;
		mGreen = max_color_value - mGreen;
		mBlue = max_color_value - mBlue;
	}
}

bool Color::operator==(const Color& rhs) const {
	int i;
	for (i = 0; i < 3; i++) {
		if (getChannel(i) != rhs.getChannel(i)) {
			return false;
		}
	}
	return true;
}

// ColorTable methods
ColorTable::ColorTable(const int& num_color) {
	mColors.resize(num_color);
}

int ColorTable::getNumberOfColors() const {
	return mColors.size();
}

void ColorTable::setNumberOfColors(const int& num_color) {
	mColors.resize(num_color);
}

const Color& ColorTable::operator[](const int& i) const {
	if (i < 0 || i >= getNumberOfColors()) {
		static Color ec(-1, -1, -1);
		static Color c(-1, -1, -1);
		c = ec;
		return c;
	}
	return mColors[i];
}

Color& ColorTable::operator[](const int& i) {	
	if (i < 0 || i >= getNumberOfColors()) {
		static Color ec(-1, -1, -1);
		static Color c(-1, -1, -1);
		c = ec;
		return c;
	}
	return mColors[i];
}

void ColorTable::setRandomColor(const int& max_color_value, const int& position) {
	if ((0 <= position && position < getNumberOfColors()) && max_color_value >= 0) {
		int val = std::rand() % (max_color_value + 1);
		(*this)[position].setRed(val);
		val = std::rand() % (max_color_value + 1);
		(*this)[position].setGreen(val);
		val = std::rand() % (max_color_value + 1);
		(*this)[position].setBlue(val);
	}
}

double ColorTable::gradientSlope(const double y1, const double y2, const double x1, const double x2) const {
	//double rise = y2 - y1;
	//double run = x2 - x1;
	//return rise / run;
	return (y2 - y1) / (x2 - x1);
}

double ColorTable::gradientValue(const double y1, const double x1, const double slope, const double x) const {
	return (slope * (x - x1)) + y1;	// slope formula solved for y
}

void ColorTable::insertGradient(const Color& color1, const Color& color2, const int& position1, const int& position2) {
	int size = mColors.size();
	if ((position1 < position2) && (position1 >= 0 && position1 < size) && (position2 >= 0 && position2 < size)) {
		(*this)[position1] = color1;	// first and last colors already given
		(*this)[position2] = color2;
		/*
		double red_step = (color2.getRed() - color1.getRed()) / (position2 - position1);
		double blue_step = (color2.getBlue() - color1.getBlue()) / (position2 - position1);
		double green_step = (color2.getGreen() - color1.getGreen()) / (position2 - position1);
		*/
		double red_step = gradientSlope(color1.getRed(), color2.getRed(), position1, position2);
		double green_step = gradientSlope(color1.getGreen(), color2.getGreen(), position1, position2);
		double blue_step = gradientSlope(color1.getBlue(), color2.getBlue(), position1, position2);
		int i;
		for (i = position1+1; i < position2; i++) {
			/*
			double red_i = color1.getRed() + (i*red_step);
			double blue_i = color1.getBlue() + (i*blue_step);
			double green_i = color1.getGreen() + (i*green_step);
			*/
			double red_i = gradientValue(color1.getRed(), position1, red_step, i);
			double green_i = gradientValue(color1.getGreen(), position1, green_step, i);
			double blue_i = gradientValue(color1.getBlue(), position1, blue_step, i);
			(*this)[i].setRed(red_i);
			(*this)[i].setGreen(green_i);
			(*this)[i].setBlue(blue_i);
		}
	}
}

int ColorTable::getMaxChannelValue() const {
	int returned = 0;
	unsigned int i;
	int j;
	for (i = 0; i < mColors.size(); i++) {	// iterates through table colors
		for (j = 0; j < 3; j++) {	// iterates through channels
			if (mColors[i].getChannel(j) > returned) {
				returned = mColors[i].getChannel(j);
			}
		}
	}
	return returned;
}

// additional functions
std::ostream& operator<<(std::ostream& os, const Color& color) {
	os << color.getRed() << ":" << color.getGreen() << ":" << color.getBlue();
	return os;
}

// exam

void ColorTable::insertInvertedGradient(const Color& color1, const int& position1, const int& position2) {
	Color color2 = color1;
	color2.invert(255);
	insertGradient(color1, color2, position1, position2);
}
