#include "Canvas.h"

Canvas::Canvas(int _width, int _height) {
    width = _width; height = _height;
    pixels = vector<vector<int>>(width);
    for (int i = 0; i < width; i++) {
        pixels[i] = vector<int>(height, 0);
    }
}
Canvas::Canvas(const Canvas &cv) { width = cv.width; height = cv.height; pixels = cv.pixels; }
Canvas::~Canvas() {}
int Canvas::getWidth() { return width; }
int Canvas::getHeight() { return height; }
int Canvas::getPixel(int i, int j) { return pixels[i][j]; }
void Canvas::setWidth(int _width) { width = _width; }
void Canvas::setHeight(int _height) { height = _height; }
void Canvas::setPixel(int i, int j, int value) { pixels[i][j] = value; }
void Canvas::updatePixels(vector<Point> shape, int colorIndex) {
    for (auto& p : shape) {
        pixels[p.getX()][p.getY()] = colorIndex;
    }
}