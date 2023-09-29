#include "MandelbrotSet.h"
#include "ComplexFractal.h"
#include "NumberGrid.h"
#include <cmath>

MandelbrotSet::MandelbrotSet()
	: ComplexFractal() {

}

MandelbrotSet::MandelbrotSet(const int& height, const int& width, const double& minx, const double& maxx, const double& miny, const double& maxy)
	: ComplexFractal(height, width, minx, maxx, miny, maxy) {

}

MandelbrotSet::~MandelbrotSet() {
	// deez nuts
}

void MandelbrotSet::calculateNextPoint(const double x0, const double y0, const double& a, const double& b, double& x1, double& y1) const {
	x1 = (x0*x0) - (y0*y0) + a;
	y1 = (2*x0*y0) + b;
}

int MandelbrotSet::calculatePlaneEscapeCount(const double& a, const double& b) const {
	double x, y;
	x = a;
	y = b;
	double distance = std::sqrt((x*x) + (y*y));
	int i = 0;
	while ((i < mMaxNumber) && (distance <= 2)) {
		// increasing distance radius shifts color values to be larger
		// decreasing distance radius shifts color values to be smaller
		i++;
		calculateNextPoint(x, y, a, b, x, y);
		distance = std::sqrt((x*x) + (y*y));
	}
	return i;
}

int MandelbrotSet::calculateNumber(const int& row, const int& column) const {
	if (!indexValid(row, column)) {
		return -1;
	}
	double x = calculatePlaneXFromPixelColumn(column);
	double y = calculatePlaneYFromPixelRow(row);
	return calculatePlaneEscapeCount(x, y);
}

// exam

MandelbrotPower::MandelbrotPower()
	: MandelbrotSet(), mD(2.0) {
}

MandelbrotPower::~MandelbrotPower() {
}

double MandelbrotPower::getPower() const {
	return mD;
}

void MandelbrotPower::setPower(const double& power) {
	mD = power;
}

void MandelbrotPower::calculateNextPoint(const double x0, const double y0, const double& a, const double& b, double& x1, double& y1) const {
	double r = std::sqrt(x0*x0 + y0*y0);
	double theta = std::atan2(y0, x0);
	x1 = std::pow(r, mD) * std::cos(mD * theta) + a;
	y1 = std::pow(r, mD) * std::sin(mD * theta) + b;
}
