#ifndef _PPM_H_
#define _PPM_H_

#include "Image.h"
//#include "ActionData.h"	DONT INCLUDE THIS, AS CLASS METHODS ARE EXEMPT FROM AD.
//ONLY USE THE CORRECT DEPENDENCIES AND PARAMETERS IN EACH
#include <iostream>

class PPM : public Image {

public:
	PPM();
	PPM(const int& height, const int& width);
	int getMaxColorValue() const;
	bool valueValid(const int& value) const;
	void setMaxColorValue(const int& max_color_value);
	void setChannel(const int& row, const int& column, const int& channel, const int& value);
	void setPixel(const int& row, const int& column, const int& red, const int& green, const int& blue);
	void writeStream(std::ostream& os) const;
	void readStream(std::istream& is);
	
	// operators
	bool operator==(const PPM& rhs) const;
	bool operator!=(const PPM& rhs) const;
	bool operator< (const PPM& rhs) const;
	bool operator<=(const PPM& rhs) const;
	bool operator> (const PPM& rhs) const;
	bool operator>=(const PPM& rhs) const;
	PPM& operator+=(const PPM& rhs);
	PPM& operator-=(const PPM& rhs);
	PPM& operator*=(const double& rhs);
	PPM& operator/=(const double& rhs);
	PPM operator+(const PPM& rhs) const;
	PPM operator-(const PPM& rhs) const;
	PPM operator*(const double& rhs) const;
	PPM operator/(const double& rhs) const;

	// grayscale methods
	void grayFromChannel(PPM& dst, const int& src_channel) const;
	void grayFromRed(PPM& dst) const;
	void grayFromGreen(PPM& dst) const;
	void grayFromBlue(PPM& dst) const;
	double linearColorimetricPixelValue(const int& row, const int& column) const;
	void grayFromLinearColorimetric(PPM& dst) const;
	
	// exam
	void orangeFilter(PPM& dst) const;
	PPM& operator*=(const PPM& rhs);
	int antiAliasPixelValue(int n, int row, int column, int channel) const;
	void antiAlias(const int& n, PPM& dst) const;

protected:
	int mMaxColorValue;
};

#endif // _PPM_H_
