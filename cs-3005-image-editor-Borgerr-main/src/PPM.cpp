#include <iostream>
#include <fstream>
#include "PPM.h"
#include <vector>
//#include "ActionData.h"

PPM::PPM()
	: Image(), mMaxColorValue(1) {
}

PPM::PPM(const int& height, const int& width)
	: Image(height, width), mMaxColorValue(1) {
}

int PPM::getMaxColorValue() const {
	return mMaxColorValue;
}

bool PPM::valueValid(const int& value) const {
	return ((0 <= value) && (value <= mMaxColorValue));
}

void PPM::setMaxColorValue(const int& max_color_value) {
	if ((1 <= max_color_value) && (max_color_value <= 255)) {
		mMaxColorValue = max_color_value;
	}
}

void PPM::setChannel(const int& row, const int& column, const int& channel, const int& value) {
	if (valueValid(value)) {
		Image::setChannel(row, column, channel, value);
		// since this method overrides the inherited method of the same name,
		// the parent class is necessary as a namespace.
	}
}

void PPM::setPixel(const int& row, const int& column, const int& red, const int& green, const int& blue){
	setChannel(row, column, 0, red);
	setChannel(row, column, 1, green);
	setChannel(row, column, 2, blue);
}

void PPM::writeStream(std::ostream& os) const {
	// Writes PPM data to the output stream "os". Use format described in assignment.
	os << "P6" << " " << mWidth << " " << mHeight << " " << mMaxColorValue << "\n";
	unsigned char c;
	unsigned int i;
	for (i = 0; i < mVector.size(); i++) {
		c = mVector[i];
		os.write((char *) &c, sizeof(c));
	}
}

void PPM::readStream(std::istream& is) {
	int w, h, maxColor;
	std::string p6;
	unsigned char c;
	//unsigned int value;
	is >> p6 >> w >> h >> maxColor;
	is.read((char *)&c, sizeof(c));
	
	//std::cout << "Width: " << w << " Height: " << h << " colorVal: " << maxColor << std::endl;

	setMaxColorValue(maxColor);
	setWidth(w);
	setHeight(h);


	//std::cout << "Actual: " << "Width: " << getWidth() << " Height: " << getHeight() << " colorVal: " << getMaxColorValue() << std::endl;

	int i, j, k;
	for (i=0; i<getHeight(); i++) {
		for (j=0; j<getWidth(); j++) {
			for (k=0; k<3; k++) {
				is.read((char *)&c, sizeof(c));
				setChannel(i, j, k, c);
			}
		}
	}
}


// operators
bool PPM::operator==(const PPM& rhs) const {
	return this->mVector.size() == rhs.mVector.size();
}

bool PPM::operator!=(const PPM& rhs) const {
	return this->mVector.size() != rhs.mVector.size();
}

bool PPM::operator<(const PPM& rhs) const {
	return this->mVector.size() < rhs.mVector.size();
}

bool PPM::operator<=(const PPM& rhs) const {
	return ((*this)<rhs) || ((*this)==rhs);
}

bool PPM::operator>(const PPM& rhs) const {
	return this->mVector.size() > rhs.mVector.size();
}

bool PPM::operator>=(const PPM& rhs) const {
	return ((*this)>rhs) || ((*this)==rhs);
}

PPM& PPM::operator+=(const PPM& rhs) {
	// assumes *this and rhs have same width and height
	int row, col;
	int height = getHeight();
	int width = getWidth();
	int r1, g1, b1, r2, g2, b2, r, g, b;	// rgb1 values -> this, rgb2 values -> rhs, rgb -> added values

	for (row = 0; row < height; row++) {
		for (col = 0; col < width; col++) {
			r1 = getChannel(row, col, 0);
			r2 = rhs.getChannel(row, col, 0);
			r = r1 + r2;
			if (r > mMaxColorValue) {
				r = mMaxColorValue;
			}

			g1 = getChannel(row, col, 1);
			g2 = rhs.getChannel(row, col, 1);
			g = g1 + g2;
			if (g > mMaxColorValue) {
				g = mMaxColorValue;
			}

			b1 = getChannel(row, col, 2);
			b2 = rhs.getChannel(row, col, 2);
			b = b1 + b2;
			if (b > mMaxColorValue) {
				b = mMaxColorValue;
			}

			setPixel(row, col, r, g, b);
		}
	}
	return (*this);
}

PPM& PPM::operator-=(const PPM& rhs) {
	int row, col;
	int height = getHeight();
	int width = getWidth();
	int r1, g1, b1, r2, g2, b2, r, g, b;

	for (row = 0; row < height; row++) {
		for (col = 0; col < width; col++) {
			r1 = getChannel(row, col, 0);
			r2 = rhs.getChannel(row, col, 0);
			r = r1 - r2;
			if (r < 0) {
				r = 0;
			}

			g1 = getChannel(row, col, 1);
			g2 = rhs.getChannel(row, col, 1);
			g = g1 - g2;
			if (g < 0) {
				g = 0;
			}

			b1 = getChannel(row, col, 2);
			b2 = rhs.getChannel(row, col, 2);
			b = b1 - b2;
			if (b < 0) {
				b = 0;
			}

			setPixel(row, col, r, g, b);
		}
	}
	return (*this);
}

PPM& PPM::operator*=(const double& rhs) {
	int row, col;
	int height = getHeight();
	int width = getWidth();
	int r, g, b;

	for (row = 0; row < height; row++) {
		for (col = 0; col < width; col++) {
			r = getChannel(row, col, 0)*rhs;
			if (r > mMaxColorValue) {
				r = mMaxColorValue;
			}else if (r < 0){
				r = 0;
			}

			g = getChannel(row, col, 1)*rhs;
			if (g > mMaxColorValue) {
				g = mMaxColorValue;
			}else if (g < 0) {
				g = 0;
			}

			b = getChannel(row, col, 2)*rhs;
			if (b > mMaxColorValue) {
				b = mMaxColorValue;
			}else if (b < 0) {
				b = 0;
			}

			setPixel(row, col, r, g, b);
		}
	}
	return (*this);
}

PPM& PPM::operator/=(const double& rhs) {
	int row, col;
	int height = getHeight();
	int width = getWidth();
	int r, g, b;

	for (row = 0; row < height; row++) {
		for (col = 0; col < width; col++) {
			r = getChannel(row, col, 0)/rhs;
			if (r > mMaxColorValue) {
				r = mMaxColorValue;
			}else if (r < 0) {
				r = 0;
			}

			g = getChannel(row, col, 1)/rhs;
			if (g > mMaxColorValue) {
				g = mMaxColorValue;
			}else if (g < 0) {
				g = 0;
			}

			b = getChannel(row, col, 2)/rhs;
			if (b > mMaxColorValue) {
				b = mMaxColorValue;
			}else if (b < 0) {
				b = 0;
			}

			setPixel(row, col, r, g, b);
		}
	}
	return (*this);
}

PPM PPM::operator+(const PPM& rhs) const {
	PPM returned = (*this);
	return returned += rhs;
}

PPM PPM::operator-(const PPM& rhs) const {
	PPM returned = (*this);
	return returned -= rhs;
}

PPM PPM::operator*(const double& rhs) const {
	PPM returned = (*this);
	return returned *= rhs;
}

PPM PPM::operator/(const double& rhs) const {
	PPM returned = (*this);
	return returned /= rhs;
}

// grayscale methods
void PPM::grayFromChannel(PPM& dst, const int& src_channel) const {
	int height = getHeight();
	int width = getWidth();
	int row, col, tempVal;

	dst.setHeight(height);
	dst.setWidth(width);
	dst.setMaxColorValue(getMaxColorValue());

	for (row = 0; row < height; row++) {
		for (col = 0; col < width; col++) {
			tempVal = getChannel(row, col, src_channel);
			dst.setPixel(row, col, tempVal, tempVal, tempVal);
		}
	}
}

void PPM::grayFromRed(PPM& dst) const {
	grayFromChannel(dst, 0);
}

void PPM::grayFromGreen(PPM& dst) const {
	grayFromChannel(dst, 1);
}

void PPM::grayFromBlue(PPM& dst) const {
	grayFromChannel(dst, 2);
}

double PPM::linearColorimetricPixelValue(const int& row, const int& column) const {
	int r, g, b;
	r = getChannel(row, column, 0);
	g = getChannel(row, column, 1);
	b = getChannel(row, column, 2);
	return 0.2126*r + 0.7152*g + 0.0722*b;
}

void PPM::grayFromLinearColorimetric(PPM& dst) const {
	int height = getHeight();
	int width = getWidth();
	int row, col, tempVal;

	dst.setHeight(height);
	dst.setWidth(width);
	dst.setMaxColorValue(getMaxColorValue());

	for (row = 0; row < height; row++) {
		for (col = 0; col < width; col++) {
			tempVal = linearColorimetricPixelValue(row, col);
			dst.setPixel(row, col, tempVal, tempVal, tempVal);
		}
	}
}

// exam

void PPM::orangeFilter(PPM& dst) const {
	// TODO: check for overflow in new values
	dst.setWidth(getWidth());
	dst.setHeight(getHeight());
	dst.setMaxColorValue(getMaxColorValue());
	int r, g, b, newR, newG, newB, row, col;
	for (row = 0; row < dst.getHeight(); row++) {
		for (col = 0; col < dst.getWidth(); col++) {
			r = getChannel(row, col, 0);
			g = getChannel(row, col, 1);
			b = getChannel(row, col, 2);
			newR = 2*(2*r+g)/3;
			newG = 2*(2*r+g)/6;
			newB = b/2;
			dst.setPixel(row, col, newR, newG, newB);
		}
	}
}

PPM& PPM::operator*=(const PPM& rhs) {
	unsigned int i;
	int newVal;
	for (i = 0; i < this->mVector.size(); i++) {
		newVal = (this->mVector[i] * rhs.mVector[i])/rhs.getMaxColorValue();
		mVector[i] = newVal;
	}
	return (*this);
}

int PPM::antiAliasPixelValue(int n, int row, int column, int channel) const {
	int big_row1 = row*n;
	int big_row2 = (row+1)*n;
	
	int big_col1 = column*n;
	int big_col2 = (column+1)*n;

	int big_row, big_col; // iterators
	int total = 0;
	for (big_row = big_row1; big_row < big_row2; big_row++) {
		for (big_col = big_col1; big_col < big_col2; big_col++) {
			total += getChannel(big_row, big_col, channel);
		}
	}
	return (total/(n*n));
}

void PPM::antiAlias(const int& n, PPM& dst) const {
	dst.setMaxColorValue(getMaxColorValue());
	dst.setHeight(getHeight()/n);
	dst.setWidth(getWidth()/n);
	int row, col, channel;
	for (row = 0; row < getHeight()/n; row++) {
		for (col = 0; col < getWidth()/n; col++) {
			for (channel = 0; channel < 3; channel++) {
				dst.setChannel(row, col, channel, 
				antiAliasPixelValue(n, row, col, channel));
			}
		}
	}
}

/*
 * HOMESTUCK DISCORD SOLUTION FOR writeStream() METHOD
 * unsigned char r,g,b;
 * unsigned int rgb = mVector[i];
 * r = rgb & 0xff000000 >> 24;
 * g = rgb & 0x00ff0000 >> 16;
 * b = rgb & 0x0000ff00 >> 8;
 * os << r << g << b;
 * suffice it to say, I was desperate, and didn't really know what to do.
 * this was more as a conversational piece between friends. I don't plan on using it.
*/
