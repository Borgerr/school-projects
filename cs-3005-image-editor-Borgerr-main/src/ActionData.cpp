#include <iostream>
#include "ActionData.h"
#include "PPM.h"
#include "NumberGrid.h"
#include "ColorTable.h"

ActionData::ActionData(std::istream& is, std::ostream& os) 
	: mIs(is), mOs(os), p1(), p2(), pout(), done(false), mGrid(0), mColors(16) {
		Color start(0, 255, 0);
		Color end(255, 0, 255);
		mColors.insertGradient(start, end, 0, 15);
}

std::istream& ActionData::getIS() {
	return mIs;
}

std::ostream& ActionData::getOS() {
	return mOs;
}

PPM& ActionData::getInputImage1() {
	return p1;
}

PPM& ActionData::getInputImage2() {
	return p2;
}

PPM& ActionData::getOutputImage() {
	return pout;
}

bool ActionData::getDone() const {
	return done;
}

void ActionData::setDone() {
	done = true;
}

ActionData::~ActionData() {
	if (mGrid != 0) {
		delete mGrid;
	}
}

NumberGrid& ActionData::getGrid() {
	return (*mGrid);
}

void ActionData::setGrid(NumberGrid *grid) {
	if (mGrid != 0) {
		delete mGrid;
	}
	mGrid = grid;
}

ColorTable& ActionData::getTable() {
	return mColors;
}
