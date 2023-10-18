#ifndef POINT_H
#define POINT_H

#include <vector>
using namespace std;

class Point {
    int x, y;
public:
    Point(int _x = 0, int _y = 0);
    Point(const Point &p);
    ~Point();
    int getX();
    int getY();
    void setX(int _x);
    void setY(int _y);
};

void validPush(vector<Point> &vp, int x, int y, int w, int h);

#endif