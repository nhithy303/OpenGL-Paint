#include "Circle.h"

Circle::Circle(Point _center, int _radius) { center = _center; radius = _radius; }
Circle::Circle(const Circle &c) { center = c.center; radius = c.radius; }
Circle::~Circle() {}
Point Circle::getCenter() { return center; }
int Circle::getRadius() { return radius; }
void Circle::setCenter(Point _center) { center = _center; }
void Circle::setRadius(int _radius) { radius = _radius; }

/**************************/
/*** MidPoint Algorithm ***/
/**************************/
vector<Point> Circle::draw(int w, int h) {
    vector<Point> pCircle;

    float p = 5 / 4 - radius;
    // Starting point
    int x = 0;
    int y = radius;
    // Inverse of translation vector
    int tx = center.getX();
    int ty = center.getY();
    // Perform translation to find symmetric points for the remaining parts of circle more easily

    // Apply MidPoint algorithm to get an eighth of circle then get symmetric points
    while (x <= y) {
        validPush(pCircle, x + tx, y + ty, w, h);
        validPush(pCircle, y + tx, x + ty, w, h);
        validPush(pCircle, y + tx, -x + ty, w, h);
        validPush(pCircle, x + tx, -y + ty, w, h);
        validPush(pCircle, -x + tx, -y + ty, w, h);
        validPush(pCircle, -y + tx, -x + ty, w, h);
        validPush(pCircle, -y + tx, x + ty, w, h);
        validPush(pCircle, -x + tx, y + ty, w, h);

        x += 1;
        p = p + 2 * x + 1;
        if (p >= 0) {
            y -= 1;
            p = p - 2 * y;
        }
    }

    return pCircle;
}