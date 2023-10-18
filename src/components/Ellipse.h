#ifndef ELLIPSE_H
#define ELLIPSE_H

#include "Point.h"
#include "Circle.h"
#include <vector>
using namespace std;

class Ellipse {
    Point center;
    int a, b;
public:
    Ellipse(Point _center = Point(), int _a = 0, int _b = 0);
    Ellipse(const Ellipse &e);
    ~Ellipse();
    Point getCenter();
    int getA();
    int getB();
    void setCenter(Point _center);
    void setA(int _a);
    void setB(int _b);
    vector<Point> draw(int w, int h);
};

#endif