#ifndef __JULIASET_H_
#define __JULIASET_H_

#include "ComplexFractal.h"

class JuliaSet : public ComplexFractal {

public:
	JuliaSet();
	JuliaSet(const int& height, const int& width, const double& minx, const double& maxx, const double& miny, const double& maxy, const double& a, const double& b);
	virtual ~JuliaSet();
	double getA() const;
	double getB() const;
	void setParameters(const double& a, const double& b);
	virtual void calculateNextPoint(const double x0, const double y0, double& x1, double& y1) const;
	virtual int calculatePlaneEscapeCount(const double& x0, const double& y0) const;
	virtual int calculateNumber(const int& row, const int& column) const;

protected:
	double mA, mB;
};


// exam


class JuliaSetFour : public JuliaSet {

public:
	JuliaSetFour();
	virtual ~JuliaSetFour();
	virtual void calculateNextPoint(const double x0, const double y0, double& x1, double& y1) const;
};

#endif //__JULIASET_H_
