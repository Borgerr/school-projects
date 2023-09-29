#include <iostream>
#include "Image.h"
#include <vector>

Image::Image( ) {
	mWidth = 0;
	mHeight = 0;
}

Image::Image( const int& height, const int& width ) {
	mWidth = width;
	mHeight = height;
	mVector.resize(mWidth * mHeight * 3);
}

int Image::getHeight() const {
	return mHeight;
}

int Image::getWidth() const {
	return mWidth;
}

bool Image::indexValid( const int& row, const int& column, const int& channel ) const {
	bool a = (0 <= row) && (row < mHeight) && (0 <= column) && (column < mWidth) && (0 <= channel); // first half of checks
	bool b = (mHeight > 0) && (mWidth > 0) && (channel <= 2);
	return a && b;
}

int Image::index( const int& row, const int& column, const int& channel ) const {
	// returns the index into the data vector for the location specified by row, column, and channel.
	return (row * mWidth * 3 + column * 3) + channel;
}

int Image::getChannel( const int& row, const int& column, const int& channel ) const {
	// returns an int representation of the value in the data vector at the location specified by row, column, and channel. Uses the index method. Returns -1 if the row, column, or channel is not valid.
	if (!indexValid(row, column, channel)) {
		return -1;
	}
	int currentIndex = index(row, column, channel);
	return mVector[currentIndex];
}

void Image::setHeight( const int& height ) {
	if (height >= 0) {
		mHeight = height;
		mVector.resize(mHeight * mWidth * 3);
	}
}

void Image::setWidth( const int& width ) {
	if (width >= 0) {
		mWidth = width;
		mVector.resize(mHeight * mWidth * 3);
	}
}

void Image::setChannel( const int& row, const int& column, const int& channel, const int& value ) {
	// changes the value of the location specified by row, column, and channel.
	// only store if all values are valid (use indexValid)
	if (indexValid(row, column, channel)) {
		int tempIndex = index(row, column, channel);
		mVector[tempIndex] = value;
	}
}
