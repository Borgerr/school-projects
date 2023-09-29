#include "JuliaSet.h"
#include "ComplexFractal.h"
#include "NumberGrid.h"
#include <cmath>

JuliaSet::JuliaSet() 
	: ComplexFractal(), mA(-0.650492), mB(-0.478235) {
		setMaxNumber(255);
}

JuliaSet::JuliaSet(const int& height, const int& width, const double& minx, const double& maxx, const double& miny, const double& maxy, const double& a, const double& b)
	: ComplexFractal(height, width, minx, maxx, miny, maxy), mA(a), mB(b) {
		setMaxNumber(255);
}

JuliaSet::~JuliaSet() {

}

double JuliaSet::getA() const {
	return mA;
}

double JuliaSet::getB() const {
	return mB;
}

void JuliaSet::setParameters(const double& a, const double& b) {
	if (-2.0 <= a && a <= 2.0 && -2.0 <= b && b <= 2.0) {
		mA = a;
		mB = b;
	}
}

void JuliaSet::calculateNextPoint(const double x0, const double y0, double& x1, double& y1) const {
	x1 = (x0*x0) - (y0*y0) + mA;
	y1 = (2*x0*y0) + mB;
}

int JuliaSet::calculatePlaneEscapeCount(const double& x0, const double& y0) const {
	double x, y;
	x = x0;
	y = y0;
	int i = 0;
	double distance = std::sqrt((x*x) + (y*y));
	while ((i < mMaxNumber) && (distance <= 2)) {
		i++;
		calculateNextPoint(x, y, x, y);
		distance = std::sqrt((x*x) + (y*y));
	}
	return i;
}

int JuliaSet::calculateNumber(const int& row, const int& column) const {
	if (!indexValid(row, column)) {
		return -1;
	}
	double x = calculatePlaneXFromPixelColumn(column);
	double y = calculatePlaneYFromPixelRow(row);
	return calculatePlaneEscapeCount(x, y);
}

// exam

JuliaSetFour::JuliaSetFour()
	: JuliaSet() {
}

JuliaSetFour::~JuliaSetFour() {
}

void JuliaSetFour::calculateNextPoint(const double x0, const double y0, double& x1, double& y1) const {
	x1 = (x0*x0*x0*x0) - (6*x0*x0*y0*y0) + (y0*y0*y0*y0) + mA;
	y1 = (4*x0*x0*x0*y0) - (4*x0*y0*y0*y0) + mB;
}
