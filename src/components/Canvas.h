#ifndef CANVAS_H
#define CANVAS_H

#include "Point.h"
#include <vector>
using namespace std;

class Canvas {
    int width, height;
    vector<vector<int>> pixels;
public:
    Canvas(int _width = 0, int _height = 0);
    Canvas(const Canvas &cv);
    ~Canvas();
    int getHeight();
    int getWidth();
    int getPixel(int i, int j);
    void setWidth(int _width);
    void setHeight(int _height);
    void setPixel(int i, int j, int value);
    void updatePixels(vector<Point> shape, int colorIndex);
};

#endif