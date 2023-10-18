#ifndef CIRCLE_H
#define CIRCLE_H

#include "Point.h"
#include <vector>
using namespace std;

class Circle {
    Point center;
    int radius;
public:
    Circle(Point _center = Point(), int _radius = 0);
    Circle(const Circle &c);
    ~Circle();
    Point getCenter();
    int getRadius();
    void setCenter(Point _center);
    void setRadius(int _radius);
    vector<Point> draw(int w, int h);
};

#endif