#include <sstream>
#include <string>
#include "GlutApp.h"
#include "glut_app.h"
#include "image_menu.h"

GlutApp::GlutApp(int height, int width)
  : mHeight(height), mWidth(width), mActionData(mInputStream, mOutputStream), mMinX(-2.0), mMinY(-2.0), mMaxX(2.0), mMaxY(2.0), mInteractionMode(IM_FRACTAL), mFractalMode(M_MANDELBROT), mMaxNumber(200), mColor1(Color(201, 52, 87)),mColor2(Color(4, 129, 136)),mColor3(Color(137, 11, 93)), mNumColor(32), mImageNumber(1), mAntiAliasReductionCount(2), mAntiAlias(false) {
  configureMenu(mMenuData);
  mActionData.setGrid(new ComplexFractal);
  setColorTable();
  createFractal();
}

void GlutApp::setSize(int height, int width) {
  mHeight = height;
  mWidth = width;
}

int GlutApp::getHeight() const {
  return mHeight;
}
int GlutApp::getWidth() const {
  return mWidth;
}

void GlutApp::display() {
  if (mInteractionMode == IM_FRACTAL) {
    PPM& p = mActionData.getOutputImage();
    double max = static_cast<double>(p.getMaxColorValue());
    double r, g, b;
    int row, column;
    glBegin( GL_POINTS );
    for(row = 0; row < p.getHeight(); row++) {
      for(column = 0; column < p.getWidth(); column++) {
        r = p.getChannel(row, column, 0) / max;
        g = p.getChannel(row, column, 1) / max;
        b = p.getChannel(row, column, 2) / max;
        glColor3d(r, g, b);
        glVertex2i(column, p.getHeight()-row-1);
      }
    }
    glEnd( );
  }else if (mInteractionMode == IM_COLORTABLE) {
    displayColorTable();
  }else if (mInteractionMode == IM_COLOR1) {
    displayColorTable();
  }else if (mInteractionMode == IM_COLOR2) {
    displayColorTable();
  }
}


void GlutApp::createJulia() {	// method serves as a reference for other fractal methods

  // julia
  selectJulia();
  // grid
  configureGrid(200);
  // julia-parameters
  juliaParameters(0.45, -0.32);
  // fractal-plane-size
  fractalPlaneSize(-2.0, 2.0, -2.0, 2.0);
  
  // fractal-calculate
  fractalCalculate();

  // grid-apply-color-table
  gridApplyColorTable();

}

void GlutApp::createJulia2() {
  selectJulia();
  configureGrid(200);
  juliaParameters(3.14, 1.21);
  fractalPlaneSize(-10, 10, -10, 10);
  fractalCalculate();
  gridApplyColorTable();
}

void GlutApp::createMandelbrot() {
  selectMandelbrot();
  configureGrid(200);
  fractalPlaneSize(-2.0, 2.0, -2.0, 2.0);
  fractalCalculate();
  gridApplyColorTable();
}

void GlutApp::createMandelbrot2() {
  selectMandelbrot();
  configureGrid(200);
  fractalPlaneSize(-100, 100, -100, 100);
  fractalCalculate();
  gridApplyColorTable();
}

void GlutApp::createComplexFractal() {
  selectComplexFractal();
  configureGrid(200);
  fractalPlaneSize(-2.0, 2.0, -2.0, 2.0);
  gridApplyColorTable();
}

void GlutApp::createComplexFractal2() {
  selectComplexFractal();
  configureGrid(200);
  fractalPlaneSize(-100, 100, -100, 100);
  gridApplyColorTable();
}

void GlutApp::selectJulia() {
  mOutputStream.clear();
  mOutputStream.str("");
  mInputStream.clear();
  mInputStream.str("");
  takeAction("julia", mMenuData, mActionData);
}

void GlutApp::selectMandelbrot() {
  mOutputStream.clear();
  mOutputStream.str("");
  mInputStream.clear();
  mInputStream.str("");
  takeAction("mandelbrot", mMenuData, mActionData);
}

void GlutApp::selectComplexFractal() {
  mOutputStream.clear();
  mOutputStream.str("");
  mInputStream.clear();
  mInputStream.str("");
  takeAction("complex-fractal", mMenuData, mActionData);
}

void GlutApp::configureGrid(int max) {
  mOutputStream.clear();
  mInputStream.clear();
  mOutputStream.str("");
  mInputStream.str("");

  if (mAntiAlias) {
    std::stringstream tmp;
    tmp << mHeight * mAntiAliasReductionCount << " " << mWidth * mAntiAliasReductionCount << " " << max;
    mInputStream.str(tmp.str());
  }

  else {
    std::stringstream tmp;
    tmp << mHeight << " " << mWidth << " " << max;
    mInputStream.str(tmp.str());
  }
  takeAction("grid", mMenuData, mActionData);

}

void GlutApp::juliaParameters(double a, double b) {
  mOutputStream.clear();
  mInputStream.clear();
  mOutputStream.str("");
  mInputStream.str("");
  {
    std::stringstream tmp;
    tmp << a << " " << b;
    mInputStream.str(tmp.str());
  }
  takeAction("julia-parameters", mMenuData, mActionData);
}

void GlutApp::fractalPlaneSize(double minx, double maxx, double miny, double maxy) {
  mOutputStream.clear();
  mInputStream.clear();
  mOutputStream.str("");
  mInputStream.str("");
  {
    std::stringstream tmp;
    tmp << minx << " " << maxx << " " << miny << " " << maxy;
    mInputStream.str(tmp.str());
  }
  takeAction("fractal-plane-size", mMenuData, mActionData);
}

void GlutApp::fractalCalculate() {
  mOutputStream.clear();
  mInputStream.clear();
  mOutputStream.str("");
  mInputStream.str("");
  takeAction("fractal-calculate", mMenuData, mActionData);
}

void GlutApp::gridApplyColorTable() {
  mOutputStream.clear();
  mInputStream.clear();
  mOutputStream.str("");
  mInputStream.str("");
  takeAction("grid-apply-color-table", mMenuData, mActionData);
  applyAntiAlias();
}


// thank you for your help on this, professor!
void GlutApp::displayColorTable() {
  int row, col, i;
  double r, g, b;
  Color current;
  glBegin( GL_POINTS );
  for (row = 0; row < mHeight; row++) {
    for (col = 0; col < mWidth; col++) {
      i = col * mActionData.getTable().getNumberOfColors() / mWidth;
      current = mActionData.getTable()[i];
      r = current.getRed() / 255.0;
      g = current.getGreen() / 255.0;
      b = current.getBlue() / 255.0;
      glColor3d(r,g,b);
      glVertex2i(col, row);
    }
  }
  glEnd();
}

void GlutApp::setInteractionMode(InteractionMode mode) {
  mInteractionMode = mode;
}

void GlutApp::setColorTable() {
  mOutputStream.clear();
  mInputStream.clear();
  mOutputStream.str("");
  mInputStream.str("");
  {
    std::stringstream tmp;
    tmp << mNumColor;
    mInputStream.str(tmp.str());
  }
  takeAction("set-color-table-size", mMenuData, mActionData);

  mOutputStream.clear();
  mInputStream.clear();
  mOutputStream.str("");
  mInputStream.str("");
  {
    std::stringstream tmp;
    tmp << 0 << " " << mColor1.getRed() << " " << mColor1.getGreen() << " " << mColor1.getBlue() << " " <<  mNumColor/2 << " " << mColor2.getRed() << " " << mColor2.getGreen() << " " << mColor2.getBlue();
    mInputStream.str(tmp.str());
  }
  takeAction("set-color-gradient", mMenuData, mActionData);
  

  mOutputStream.clear();
  mInputStream.clear();
  mOutputStream.str("");
  mInputStream.str("");
  {
    std::stringstream tmp;
    tmp << mNumColor/2 << " " << mColor2.getRed() << " " << mColor2.getGreen() << " " << mColor2.getBlue() << " " <<  mNumColor-1 << " " << mColor3.getRed() << " " << mColor3.getGreen() << " " << mColor3.getBlue();
    mInputStream.str(tmp.str());
  }
  takeAction("set-color-gradient", mMenuData, mActionData);
}



void GlutApp::decreaseColorTableSize() {
  if (mNumColor > 10) {
    mNumColor /= 1.1;
    setColorTable();
    gridApplyColorTable();
  }
}

void GlutApp::increaseColorTableSize() {
  if (mNumColor < 1024) {
    mNumColor *= 1.1;
    setColorTable();
    gridApplyColorTable();
  }
}

void GlutApp::zoomIn() {
  double dx, dy;
  dx = (1.0 - 0.9)*(mMaxX - mMinX) / 2.0;
  dy = (1.0 - 0.9)*(mMaxY - mMinY) / 2.0;
  mMinX += dx;
  mMaxX -= dx;
  mMinY += dy;
  mMaxY -= dy;
}

void GlutApp::zoomOut() {
  double dx, dy;
  dx = (1.0 - 0.9)*(mMaxX - mMinX) / 2.0;
  dy = (1.0 - 0.9)*(mMaxY - mMinY) / 2.0;
  bool a = mMinX - dx >= -2.0;
  bool b = mMaxX + dx <= 2.0;
  bool c = mMinY - dy >= -2.0;
  bool d = mMaxY + dy <= 2.0;
  if(a && b && c && d) {
    mMinX -= dx;
    mMaxX += dx;
    mMinY -= dy;
    mMaxY += dy;
  }
}

void GlutApp::moveLeft() {
  double dx = (1.0 - 0.9)*(mMaxX-mMinX) / 2.0;
  if (mMinX - dx >= -2.0) {
    mMinX -= dx;
    mMaxX -= dx;
  }
}

void GlutApp::moveRight() {
  double dx = (1.0 - 0.9)*(mMaxX-mMinX) / 2.0;
  if (mMaxX + dx <= 2.0) {
    mMinX += dx;
    mMaxX += dx;
  }
}

void GlutApp::moveDown() {
  double dy = (1.0 - 0.9)*(mMaxY-mMinY) / 2.0;
  if (mMinY - dy >= -2.0) {
    mMinY -= dy;
    mMaxY -= dy;
  }
}

void GlutApp::moveUp() {
  double dy = (1.0 - 0.9)*(mMaxY-mMinY) / 2.0;
  if (mMaxY + dy <= 2.0) {
    mMinY += dy;
    mMaxY += dy;
  }
}

void GlutApp::setFractalMode(FractalMode mode) {
  mFractalMode = mode;
}

void GlutApp::increaseMaxNumber() {
  if (mMaxNumber < 2048) {
    mMaxNumber *= 1.1;
  }
}

void GlutApp::decreaseMaxNumber() {
  if (mMaxNumber > 11) {
    mMaxNumber /= 1.1;
  }
}

void GlutApp::setAB(int x, int y) {
  ComplexFractal* p = dynamic_cast<ComplexFractal*>(&mActionData.getGrid());
  if (mFractalMode == M_MANDELBROT && p != 0) {
    double delta_x = p->getDeltaX();
    double delta_y = p->getDeltaY();
    mA = mMinX + x * delta_x;
    mB = mMinY + y * delta_y;
  }
}

void GlutApp::resetPlane() {
  mMinX = -2.0;
  mMinY = -2.0;
  mMaxX = 2.0;
  mMaxY = 2.0;
}

void GlutApp::createFractal() {
  switch (mFractalMode) {
    case M_MANDELBROT:
      selectMandelbrot();
      break;
    case M_JULIA:
      selectJulia();
      juliaParameters(mA, mB);
      break;
    case M_COMPLEX:
      selectComplexFractal();
      break;
  }
  configureGrid(mMaxNumber);
  fractalPlaneSize(mMinX, mMaxX, mMinY, mMaxY);
  fractalCalculate();
  gridApplyColorTable();
}

// exam
void GlutApp::increaseChannel(Color& color, int channel) {
  if (channel == 0) {
    int r = color.getRed();
    if (r + 10 > 255) {
      r = 255;
    }else {
      r += 10;
    }
  }else if(channel == 1) {
    int g = color.getGreen();
    if (g + 10 > 255) {
      g = 255;
    }else {
      g += 10;
    }
  }else if(channel == 2) {
    int b = color.getBlue();
    if (b + 10 > 255) {
      b = 255;
    }else {
      b += 10;
    }
  }
  setColorTable();
  gridApplyColorTable();
}

void GlutApp::decreaseChannel(Color& color, int channel) {
  if (channel == 0) {
    int r = color.getRed();
    if (r - 10 < 0) {
      r = 0;
    }else {
      r -= 10;
    }
  }else if(channel == 1) {
    int g = color.getGreen();
    if (g - 10 < 0) {
      g = 0;
    }else {
      g -= 10;
    }
  }else if(channel == 2) {
    int b = color.getBlue();
    if (b - 10 < 0) {
      b = 0;
    }else {
      b -= 10;
    }
  }
  setColorTable();
  gridApplyColorTable();
}

Color& GlutApp::fetchColor() {
  if (mInteractionMode == IM_COLOR1) {
    return mColor1;
  }else if(mInteractionMode == IM_COLOR2) {
    return mColor2;
  }else {
    static Color ec(-1, -1, -1);
    static Color c(-1, -1, -1);
    c = ec;
    return c;
  }
}

void GlutApp::increaseRed() {
  increaseChannel(fetchColor(), 0);
}

void GlutApp::decreaseRed() {
  decreaseChannel(fetchColor(), 0);
}

void GlutApp::increaseGreen() {
  increaseChannel(fetchColor(), 1);
}

void GlutApp::decreaseGreen() {
  decreaseChannel(fetchColor(), 1);
}

void GlutApp::increaseBlue() {
  increaseChannel(fetchColor(), 2);
}

void GlutApp::decreaseBlue() {
  decreaseChannel(fetchColor(), 2);
}

void GlutApp::zoomInAndMove(int x, int y) {
  zoomIn();
  int dx = x - (mWidth/2);
  int dy = y - (mHeight/2);
  if (dx < 0) {
    dx *= -1;
  }
  if (dy < 0) {
    dy *= -1;
  }
  if (dx > dy) {
    if (x < (mWidth/2)) {
      moveLeft();
    }else {
      moveRight();
    }
  }else {
    if (y < (mHeight/2)) {
      moveDown();
    }else {
      moveUp();
    }
  }
}

void GlutApp::writeImage() {
  mOutputStream.clear();
  mInputStream.clear();
  mOutputStream.str("");
  mInputStream.str("");
  {
    std::stringstream tmp;
    tmp << mImageNumber << ".ppm";
    mInputStream.str(tmp.str());
  }
  mImageNumber++;
  takeAction("write", mMenuData, mActionData);
}

void GlutApp::copyOutputToInput1() {
  mOutputStream.clear();
  mInputStream.clear();
  mOutputStream.str("");
  mInputStream.str("");
  takeAction("copyo1", mMenuData, mActionData);
}

void GlutApp::antiAlias(int reduction_count) {
  mOutputStream.clear();
  mInputStream.clear();
  mOutputStream.str("");
  mInputStream.str("");
  {
    std::stringstream tmp;
    tmp << reduction_count << std::endl;
    mInputStream.str(tmp.str());
  }
  takeAction("anti-alias", mMenuData, mActionData);
}

void GlutApp::applyAntiAlias() {
  if (mAntiAlias) {
    copyOutputToInput1();
    antiAlias(mAntiAliasReductionCount);
  }
}

void GlutApp::toggleAntiAlias() {
  mAntiAlias = !mAntiAlias;
}

void GlutApp::increaseAntiAliasReductionCount() {
  mAntiAliasReductionCount += 1;
}

void GlutApp::decreaseAntiAliasReductionCount() {
  mAntiAliasReductionCount -= 1;
  if (mAntiAliasReductionCount < 2) {
    mAntiAliasReductionCount = 2;
  }
}
