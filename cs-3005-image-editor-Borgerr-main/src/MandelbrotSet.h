#ifndef __MANDELBROTSET_H_
#define __MANDELBROTSET_H_

#include "ComplexFractal.h"
#include "NumberGrid.h"

class MandelbrotSet : public ComplexFractal {

public:
	MandelbrotSet();
	MandelbrotSet(const int& height, const int& width, const double& minx, const double& maxx, const double& miny, const double& maxy);
	virtual ~MandelbrotSet();
	virtual void calculateNextPoint(const double x0, const double y0, const double& a, const double& b, double& x1, double& y1) const;
	int calculatePlaneEscapeCount(const double& a, const double& b) const;
	virtual int calculateNumber(const int& row, const int& column) const;

};

class MandelbrotPower : public MandelbrotSet {
public:
	MandelbrotPower();
	virtual ~MandelbrotPower();
	double getPower() const;
	void setPower(const double& power);
	virtual void calculateNextPoint(const double x0, const double y0, const double& a, const double& b, double& x1, double& y1) const;

private:
	double mD;
};

#endif //__MANDELBROTSET_H_
