#ifndef __COMPLEXFRACTAL_H_
#define __COMPLEXFRACTAL_H_
#include "ThreadedGrid.h"

class ComplexFractal : public ThreadedGrid {

public:
	ComplexFractal();
	ComplexFractal(const int& height, const int& width, const double& minx, const double& maxx, const double& miny, const double& maxy);
	virtual ~ComplexFractal();
	double getMinX() const;
	double getMaxX() const;
	double getMinY() const;
	double getMaxY() const;
	virtual void setGridSize(const int& height, const int& width);
	void setPlaneSize(const double& minx, const double& maxx, const double& miny, const double& maxy);
	double getDeltaX() const;
	double getDeltaY() const;
	void setDeltas(const double& dx, const double& dy);
	double calculateDeltaY() const;
	double calculateDeltaX() const;
	double calculatePlaneXFromPixelColumn(const int& column) const;
	double calculatePlaneYFromPixelRow(const int& row) const;
	void calculatePlaneCoordinatesFromPixelCoordinates(const int& row, const int& column, double& x, double& y) const;
	virtual int calculateNumber(const int& row, const int& column) const;

protected:
	double mMinX, mMaxX, mMinY, mMaxY;
	double mDy, mDx;

};

#endif	//__COMPLEXFRACTAL_H_
