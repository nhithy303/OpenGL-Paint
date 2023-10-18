#include "Point.h"

Point::Point(int _x, int _y) { x = _x; y = _y; }
Point::Point(const Point &p) { x = p.x; y = p.y; }
Point::~Point() {};
int Point::getX() { return x; }
int Point::getY() { return y; }
void Point::setX(int _x) { x = _x; }
void Point::setY(int _y) { y = _y; }

void validPush(vector<Point> &vp, int x, int y, int w, int h) {
    if (x >= 0 && x < w && y >= 0 && y < h) {
        vp.push_back(Point(x, y));
    }
}