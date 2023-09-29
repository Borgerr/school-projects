#include <cmath>
#include "ComplexFractal.h"
#include "ThreadedGrid.h"

ComplexFractal::ComplexFractal() 
	: ThreadedGrid(200, 300), mMinX(-1.5), mMaxX(1.5), mMinY(-1), mMaxY(1), mDy(0.01), mDx(0.01) {

}

ComplexFractal::ComplexFractal(const int& height, const int& width, const double& minx, const double& maxx, const double& miny, const double& maxy) 
	: ThreadedGrid(height, width), mMinX(minx), mMaxX(maxx), mMinY(miny), mMaxY(maxy), mDy(0.01), mDx(0.01) {

}

ComplexFractal::~ComplexFractal() {
}

double ComplexFractal::getMinX() const {
	return mMinX;
}

double ComplexFractal::getMaxX() const {
	return mMaxX;
}

double ComplexFractal::getMinY() const {
	return mMinY;
}

double ComplexFractal::getMaxY() const {
	return mMaxY;
}

void ComplexFractal::setGridSize(const int& height, const int& width) {
	if (getHeight() >= 2 && getWidth() >= 2) {
		NumberGrid::setGridSize(height, width);
		setDeltas(calculateDeltaX(), calculateDeltaY());
	}
}

void ComplexFractal::setPlaneSize(const double& minx, const double& maxx, const double& miny, const double& maxy) {
	// there's probably a much easier way to do this.
	bool a = (-2 <= minx && minx <= 2);	// min x value index
	bool b = (-2 <= maxx && maxx <= 2);	// max x value index
	bool c = (-2 <= miny && miny <= 2);	// min y value index
	bool d = (-2 <= maxy && maxy <= 2);	// max y value index
	bool e = (minx != maxx);		// ensures dimensions
	bool f = (miny != maxy);		// ^
	if (a && b && c && d && e && f) {
		double tempMinX, tempMaxX, tempMinY, tempMaxY;
		if (minx > maxx) {		// swap if min is greater than max
			tempMinX = maxx;
			tempMaxX = minx;
		}else {
			tempMinX = minx;
			tempMaxX = maxx;
		}
		if (miny > maxy) {		// swap if min is greater than max
			tempMinY = maxy;
			tempMaxY = miny;
		}else {
			tempMinY = miny;
			tempMaxY = maxy;
		}
		mMinX = tempMinX;
		mMaxX = tempMaxX;
		mMinY = tempMinY;
		mMaxY = tempMaxY;
		setDeltas(calculateDeltaX(), calculateDeltaY());
	}
}

double ComplexFractal::getDeltaX() const {
	return mDx;
}

double ComplexFractal::getDeltaY() const {
	return mDy;
}

void ComplexFractal::setDeltas(const double& dx, const double& dy) {
	if (dx >= 0 && dy >= 0) {	// may change depending on if 0 is a valid dx/dy
		mDx = dx;
		mDy = dy;
	}
}

double ComplexFractal::calculateDeltaY() const {
	return (mMaxY - mMinY) / (mHeight - 1);
}

double ComplexFractal::calculateDeltaX() const {
	return (mMaxX - mMinX) / (mWidth - 1);
}

double ComplexFractal::calculatePlaneXFromPixelColumn(const int& column) const {
	if (column < 0 || column >= mWidth) {
		 return 0;
	}
	return mMinX + (column * mDx);
}

double ComplexFractal::calculatePlaneYFromPixelRow(const int& row) const {
	if (row < 0 || row >= mHeight) {
		return 0;
	}
	return mMaxY - (row * mDy);
}

void ComplexFractal::calculatePlaneCoordinatesFromPixelCoordinates(const int& row, const int& column, double& x, double& y) const {
	if (row < 0 || column < 0 || row >= mHeight || column >= mWidth) {
		x = 0;
		y = 0;
	}else {
		x = calculatePlaneXFromPixelColumn(column);
		y = calculatePlaneYFromPixelRow(row);
	}
}

int ComplexFractal::calculateNumber(const int& row, const int& column) const {
	if (row < 0 || column < 0 || row >= mHeight || column >= mWidth) {
		return -1;
	}else {
		double x = calculatePlaneXFromPixelColumn(column);
		double y = calculatePlaneYFromPixelRow(row);
		return std::abs(getMaxNumber() * std::sin(10*x) * std::cos(10*y));
	}
}
