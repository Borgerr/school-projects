#ifndef __ACTIONDATA_
#define __ACTIONDATA_

#include <iostream>
#include "PPM.h"
#include "NumberGrid.h"
#include "ColorTable.h"

class ActionData {
public:
	ActionData(std::istream& is, std::ostream& os);
	std::istream& getIS();
	std::ostream& getOS();
	PPM& getInputImage1();
	PPM& getInputImage2();
	PPM& getOutputImage();
	bool getDone() const;
	void setDone();
	~ActionData();
	NumberGrid& getGrid();
	void setGrid(NumberGrid *grid);
	ColorTable& getTable();
protected:
	std::istream& mIs;
	std::ostream& mOs;
	PPM p1;
	PPM p2;
	PPM pout;
	bool done;
	NumberGrid *mGrid;
	ColorTable mColors;
};

#endif //__ACTIONDATA_
