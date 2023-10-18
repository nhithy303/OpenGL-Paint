#include "Line.h"

Line::Line(Point _p1, Point _p2) { p1 = _p1; p2 = _p2; }
Line::Line(const Line &l) { p1 = l.p1; p2 = l.p2; }
Line::~Line() {}
Point Line::getP1() { return p1; }
Point Line::getP2() { return p2; }
void Line::setP1(Point _p1) { p1 = _p1; }
void Line::setP2(Point _p2) { p2 = _p2; }

/*********************/
/*** DDA Algorithm ***/
/*********************/
vector<Point> Line::drawDDA(int w, int h) {
    // Initialize an empty pLine vector to store all the points of line
    vector<Point> pLine;
    
    // p1 and p2 coincide
    if (p1.getX() == p2.getX() && p1.getY() == p2.getY()) {
        validPush(pLine, p1.getX(), p1.getY(), w, h);
        return pLine;
    }
    
    // Calculate Dx and Dy from p1 to p2
    float dx = p2.getX() - p1.getX();
    float dy = p2.getY() - p1.getY();

    // stepX and stepY refer to the direction of movement from p1 to p2
    // So it can be positive (moving forwards) or negative (moving backwards)
    int stepX = 0, stepY = 0;
    if (dx != 0) {
        stepX = dx / abs(dx);
    }
    if (dy != 0) {
        stepY = dy / abs(dy);
    }

    // Starting point
    float x = p1.getX();
    float y = p1.getY();
    // Destination - target point
    int dest; // only need either x or y to determine when to stop drawing

    // Line is parallel with Oy
    if (dx == 0) {
        dest = p2.getY() * stepY;
        while (y * stepY <= dest) {
            validPush(pLine, x, y, w, h);
            y += stepY;
        }
    }
    // Line is parallel with Ox
    else if (dy == 0) {
        dest = p2.getX() * stepX;
        while (x * stepX <= dest) {
            validPush(pLine, x, y, w, h);
            x += stepX;
        }
    }
    // Diagonal line
    else {
        float m;
        dx = abs(dx); dy = abs(dy); // the sign of movement is already stored in stepX and stepY
                                    // so we only have to care about the ratio of dx and dy
        // Shallow slope
        if (dx > dy) {
            dest = p2.getX() * stepX;
            m = stepY * dy / dx;
            while (x * stepX <= dest) {
                validPush(pLine, x, round(y), w, h);
                x += stepX; y += m;
            }
        }
        // Steep slope
        else if (dx < dy) {
            dest = p2.getY() * stepY;
            m = stepX * dx / dy;
            while (y * stepY <= dest) {
                validPush(pLine, round(x), y, w, h);
                x += m; y += stepY;
            }
        }
        // Line of equality
        else {
            dest = p2.getX() * stepX;
            while (x * stepX <= dest) {
                validPush(pLine, x, y, w, h);
                x += stepX; y += stepY;
            }
        }
    }
    return pLine;
}

/**************************/
/*** MidPoint Algorithm ***/
/**************************/
vector<Point> Line::drawMidPoint(int w, int h) {
    vector<Point> pLine;
    
    if (p1.getX() == p2.getX() && p1.getY() == p2.getY()) {
        validPush(pLine, p1.getX(), p1.getY(), w, h);
        return pLine;
    }

    float dx = p2.getX() - p1.getX();
    float dy = p2.getY() - p1.getY();

    int stepX = 0, stepY = 0;
    if (dx != 0) {
        stepX = dx / abs(dx);
    }
    if (dy != 0) {
        stepY = dy / abs(dy);
    }

    float x = p1.getX();
    float y = p1.getY();
    int dest;

    if (dx == 0) {
        dest = p2.getY() * stepY;
        while (y * stepY <= dest) {
            validPush(pLine, x, y, w, h);
            y += stepY;
        }
    }
    else if (dy == 0) {
        dest = p2.getX() * stepX;
        while (x * stepX <= dest) {
            validPush(pLine, x, y, w, h);
            x += stepX;
        }
    }
    else {
        int p, const1, const2;
        dx = abs(dx); dy = abs(dy);
        if (dx > dy) {
            dest = p2.getX() * stepX;
            p = 2 * dy - dx;
            const1 = 2 * dy;
            const2 = 2 * (dy - dx);
            while (x * stepX <= dest) {
                validPush(pLine, x, y, w, h);
                x += stepX;
                if (p < 0) {
                    p += const1;
                }
                else {
                    p += const2; y += stepY;
                }
            }
        }
        else if (dx < dy) {
            dest = p2.getY() * stepY;
            p = 2 * dx - dy;
            const1 = 2 * dx;
            const2 = 2 * (dx - dy);
            while (y * stepY <= dest) {
                validPush(pLine, x, y, w, h);
                if (p < 0) {
                    p += const1;
                }
                else {
                    p += const2; x += stepX;
                }
                y += stepY;
            }
        }
        else {
            dest = p2.getX() * stepX;
            while (x * stepX <= dest) {
                validPush(pLine, x, y, w, h);
                x += stepX; y += stepY;
            }
        }
    }
    return pLine;
}

// Utils
int Round(float n) {
    return int(n + 0.5);
}