#ifndef _GLUTAPP_H_
#define _GLUTAPP_H_

#include "ActionData.h"
#include "MenuData.h"
#include <sstream>

// enums
enum InteractionMode { IM_FRACTAL, IM_COLORTABLE, IM_COLOR1, IM_COLOR2 };
enum FractalMode { M_MANDELBROT, M_JULIA, M_COMPLEX };



class GlutApp {
public:
  GlutApp(int height, int width);
  void setSize(int height, int width);
  int getHeight() const;
  int getWidth() const;
  void display();

  //assignment 14
  void createJulia();
  void selectJulia();
  void selectMandelbrot();
  void selectComplexFractal();
  void configureGrid(int max);
  void juliaParameters(double a, double b);
  void fractalPlaneSize(double minx, double maxx, double miny, double maxy);
  void fractalCalculate();
  void gridApplyColorTable();
  void createJulia2();
  void createMandelbrot();
  void createMandelbrot2();
  void createComplexFractal();
  void createComplexFractal2();

  //assignment 15
  void displayColorTable();
  void setInteractionMode(InteractionMode mode);
  void setColorTable();
  void decreaseColorTableSize();
  void increaseColorTableSize();
  void zoomIn();
  void zoomOut();
  void moveLeft();
  void moveRight();
  void moveDown();
  void moveUp();
  void setFractalMode(FractalMode mode);
  void increaseMaxNumber();
  void decreaseMaxNumber();
  void setAB(int x, int y);
  void resetPlane();
  void createFractal();

  // exam
  void increaseChannel(Color& color, int channel);
  void decreaseChannel(Color& color, int channel);
  Color& fetchColor();
  void increaseRed();
  void decreaseRed();
  void increaseGreen();
  void decreaseGreen();
  void increaseBlue();
  void decreaseBlue();
  void zoomInAndMove(int x, int y);
  void writeImage();
  void copyOutputToInput1();
  void antiAlias(int reduction_count);
  void applyAntiAlias();
  void toggleAntiAlias();
  void increaseAntiAliasReductionCount();
  void decreaseAntiAliasReductionCount();


protected:
  int mHeight, mWidth;
  std::stringstream mInputStream;
  std::stringstream mOutputStream;
  ActionData mActionData;
  MenuData mMenuData;
  double mMinX, mMinY, mMaxX, mMaxY;
  double mA, mB;
  InteractionMode mInteractionMode;
  FractalMode mFractalMode;
  int mMaxNumber;
  Color mColor1, mColor2, mColor3;	// mColor3 added during exam
  int mNumColor;
  int mImageNumber;
  int mAntiAliasReductionCount;
  bool mAntiAlias;
};

#endif /* _GLUTAPP_H_ */
/* Local Variables: */
/* mode:c++         */
/* End:             */
