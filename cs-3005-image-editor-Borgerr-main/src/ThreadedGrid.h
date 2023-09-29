#ifndef __THREADEDGRID_H_
#define __THREADEDGRID_H_

#include "NumberGrid.h"
#include "ThreadedVector.h"
#include <vector>

/*
class Row {
public:
	int rowNum;
	std::vector<int> numbers;
};
*/

class ThreadedGrid : public NumberGrid {

public:
	ThreadedGrid();
	ThreadedGrid(const int& height, const int& width);
	virtual ~ThreadedGrid();
	virtual void calculateAllNumbers();
	virtual void worker();
	virtual void setPPM(PPM& ppm, const ColorTable& ct);
	virtual void workerSetPPM(PPM& ppm, const ColorTable& ct);

protected:
	ThreadedVector<int> mTasks;
};

#endif //__THREADEDGRID_H_
