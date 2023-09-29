#ifndef _IMAGE_H_
#define _IMAGE_H_
// if this class is already defined, don't define it again.
#include <vector>

class Image {

public:
	// constructors
	Image();
	Image(const int& height, const int& width);

	// const methods promise to not change the value of any data members.
	int getHeight() const;
	int getWidth() const;
	bool indexValid( const int& row, const int& column, const int& channel ) const;
	int index( const int& row, const int& column, const int& channel ) const;
	int getChannel( const int& row, const int& column, const int& channel ) const;

	void setHeight( const int& height );
	void setWidth( const int& width );
	void setChannel( const int& row, const int& column, const int& channel, const int& value );

protected:
	int mHeight;
	int mWidth;
	std::vector<int> mVector;
};
#endif // end of if block
