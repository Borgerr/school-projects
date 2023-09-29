#include "ActionData.h"
#include "image_menu.h"

void plusEquals(ActionData& ad) {
	ad.getInputImage1() += ad.getInputImage2();
}

void minusEquals(ActionData& ad) {
	ad.getInputImage1() -= ad.getInputImage2();
}

void timesEquals(ActionData& ad) {
	double factor = getDouble(ad, "Factor? ");
	ad.getInputImage1() *= factor;
}

void divideEquals(ActionData& ad) {
	double factor = getDouble(ad, "Factor? ");
	ad.getInputImage1() /= factor;
}

void plus(ActionData& ad) {
	ad.getOutputImage() = ad.getInputImage1() + ad.getInputImage2();
}

void minus(ActionData& ad) {
	ad.getOutputImage() = ad.getInputImage1() - ad.getInputImage2();
}

void times(ActionData& ad) {
	double factor = getDouble(ad, "Factor? ");
	ad.getOutputImage() = ad.getInputImage1() * factor;
}

void divide(ActionData& ad) {
	double factor = getDouble(ad, "Factor? ");
	ad.getOutputImage() = ad.getInputImage1() / factor;
}

void grayFromRed(ActionData& ad) {
	ad.getInputImage1().grayFromRed(ad.getOutputImage());
}

void grayFromGreen(ActionData& ad) {
	ad.getInputImage1().grayFromGreen(ad.getOutputImage());
}

void grayFromBlue(ActionData& ad) {
	ad.getInputImage1().grayFromBlue(ad.getOutputImage());
}

void grayFromLinearColorimetric(ActionData& ad) {
	ad.getInputImage1().grayFromLinearColorimetric(ad.getOutputImage());
}

// exam

void orangeFilter(ActionData& ad) {
	ad.getInputImage1().orangeFilter(ad.getOutputImage());
}

void timesEqualsPPM(ActionData& ad) {
	ad.getInputImage1() *= ad.getInputImage2();
}

void blendImages(ActionData& ad) {
	double ratio = getInteger(ad, "Ratio? ");
	// TODO: change getInteger to getDouble
	ad.getOutputImage() = (ad.getInputImage1()*ratio) + (ad.getInputImage2()*(1.-ratio));
}

void antiAliasFilter(ActionData& ad) {
	int count = getInteger(ad, "Reduction count? ");
	ad.getInputImage1().antiAlias(count, ad.getOutputImage());
}
