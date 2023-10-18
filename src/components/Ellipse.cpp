#include "Ellipse.h"

Ellipse::Ellipse(Point _center, int _a, int _b) { center = _center; a = _a; b = _b; }
Ellipse::Ellipse(const Ellipse &e) { center = e.center; a = e.a; b = e.b; }
Ellipse::~Ellipse() {}
Point Ellipse::getCenter() { return center; }
int Ellipse::getA() { return a; }
int Ellipse::getB() { return b; }
void Ellipse::setCenter(Point _center) { center = _center; }
void Ellipse::setA(int _a) { a = _a; }
void Ellipse::setB(int _b) { b = _b; }

/**************************/
/*** MidPoint Algorithm ***/
/**************************/
vector<Point> Ellipse::draw(int w, int h) {
    vector<Point> pEllipse;

    // If a = b then ellipse becomes a circle
    if (a == b) {
        return Circle(center, a).draw(w, h);
    }

    int x = 0;
    int y = b;
    int tx = center.getX();
    int ty = center.getY();

    // High region
    float p1 = b * b + a * a * 0.25 - a * a * b;
    int dx = 2 * b * b * x;
    int dy = 2 * a * a * y;
    while (dx <= dy) {
        validPush(pEllipse, x + tx, y + ty, w, h);
        validPush(pEllipse, x + tx, -y + ty, w, h);
        validPush(pEllipse, -x + tx, -y + ty, w, h);
        validPush(pEllipse, -x + tx, y + ty, w, h);

        x += 1;
        dx = dx + 2 * b * b;
        p1 = p1 + dx + b * b;
        if (p1 >= 0) {
            y -= 1;
            dy = dy - 2 * a * a;
            p1 = p1 - dy;
        }
    }
    
    // Low region
    float p2 = b * b * (x + 0.5) * (x + 0.5) + a * a * (y - 1) * (y - 1) - a * a * b * b;
    while (y >= 0) {
        validPush(pEllipse, x + tx, y + ty, w, h);
        validPush(pEllipse, x + tx, -y + ty, w, h);
        validPush(pEllipse, -x + tx, -y + ty, w, h);
        validPush(pEllipse, -x + tx, y + ty, w, h);
        
        y -= 1;
        dy = dy - 2 * a * a;
        p2 = p2 - dy + a * a;
        if (p2 <= 0) {
            x += 1;
            dx = dx + 2 * b * b;
            p2 = p2 + dx;
        }
    }

    return pEllipse;
}