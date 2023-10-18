#ifndef LINE_H
#define LINE_H

#include "Point.h"
#include <math.h>
#include <vector>
using namespace std;

class Line {
    Point p1, p2;
public:
    Line(Point _p1 = Point(), Point _p2 = Point());
    Line(const Line &l);
    ~Line();
    Point getP1();
    Point getP2();
    void setP1(Point _p1);
    void setP2(Point _p2);
    vector<Point> drawDDA(int w, int h);
    vector<Point> drawMidPoint(int w, int h);
};

int Round(float n);

#endif