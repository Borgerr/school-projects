#include "ThreadedGrid.h"
#include "NumberGrid.h"
#include <thread>

ThreadedGrid::ThreadedGrid()
	: NumberGrid(), mTasks() {
}

ThreadedGrid::ThreadedGrid(const int& height, const int& width)
	: NumberGrid(height, width), mTasks() {
}

ThreadedGrid::~ThreadedGrid() {
	// deez nuts
}

void ThreadedGrid::calculateAllNumbers() {
	// accounts for each task needing to be completed
	int row;
	mTasks.resize(mHeight);
	for (row = 0; row < mHeight; row++) {
		mTasks.push_back(row);
	}
	// use try/except statements in a for loop to account for limited resources.
	// count number of cores available for use in threads
	unsigned int max_cores = std::thread::hardware_concurrency();
	std::vector<std::thread> threads;
	unsigned int i;
	for (i = 0; i < max_cores-1; i++) {
		threads.push_back(std::thread(&ThreadedGrid::worker, this));
	}

	for (i = 0; i < threads.size(); i++) {
		threads[i].join();
	}
}

void ThreadedGrid::worker() {
	// As long as tasks are available in the task queue, get one and complete it.
	// Tasks are organized by grid row in the task queue.
	// For each row, calculate the number, and then set the number.
	std::vector<int> this_workers_tasks;
	//std::vector<Row> this_workers_calculated;
	int col, row;	// used to iterate
	unsigned int i;	// used to iterate in worker tasks vector
	while (mTasks.size() > 0) {
		this_workers_tasks.resize(8);
		mTasks.pop_back(this_workers_tasks, 8);
		for (i = 0; i < this_workers_tasks.size(); i++) {
			row = this_workers_tasks[i];
			for (col = 0; col < mWidth; col++) {
				setNumber(row, col, calculateNumber(row, col));
			}
		}
		// calculation complete, reinsert calculated values to grid
		//MAY CHANGE TO BE PROCESSED IN CALCULATEALLNUMBERS
	}
}


// exam
void ThreadedGrid::setPPM(PPM& ppm, const ColorTable& ct) {
	if (ct.getNumberOfColors() >= 2) {
		ppm.setWidth(mWidth);
		ppm.setHeight(mHeight);
		ppm.setMaxColorValue(ct.getMaxChannelValue());

		int row;
		mTasks.resize(mHeight);
		for (row = 0; row < mHeight; row++) {
			mTasks.push_back(row);
		}

		unsigned int max_cores = std::thread::hardware_concurrency();
		std::vector<std::thread> threads;
		unsigned int i;
		for (i = 0; i < max_cores-1; i++) {
			threads.push_back(std::thread( &ThreadedGrid::workerSetPPM, this, std::ref(ppm), std::ref(ct)) );
		}

		for (i = 0; i < threads.size(); i++) {
			threads[i].join();
		}
	}
}

void ThreadedGrid::workerSetPPM(PPM& ppm, const ColorTable& ct) {
	std::vector<int> this_workers_tasks;
	int col, row, r, g, b;
	unsigned int i;
	Color current;
	while (mTasks.size() > 0) {
		this_workers_tasks.resize(8);
		mTasks.pop_back(this_workers_tasks, 8);
		for (i = 0; i < this_workers_tasks.size(); i++) {
			row = this_workers_tasks[i];
			for (col = 0; col < mWidth; col++) {
				if(getNumber(row, col) == mMaxNumber) {
					current = ct[ct.getNumberOfColors()-1];
				}else {
					current = ct[getNumber(row, col) % ct.getNumberOfColors()];
				}
				r = current.getRed();
				g = current.getGreen();
				b = current.getBlue();

				ppm.setPixel(row, col, r, g, b);
			}
		}
	}
}
