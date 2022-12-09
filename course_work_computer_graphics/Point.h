#ifndef POINT_H
#define POINT_H

#define _USE_MATH_DEFINES
#include <math.h>

class Point {
private:
    int xp;
    int yp;

public:
    Point() : xp(0), yp(0) {}
    Point(int xpos, int ypos) : xp(xpos), yp(ypos) {}

    bool is_null() const { return xp == 0 && yp == 0; }

    int x() const { return xp; }
    int y() const { return yp; }
    int& rx() { return xp; }
    int& ry() { return yp; }
    void set_x(int xpos) { xp = xpos; }
    void set_y(int ypos) { yp = ypos; }

    Point& operator+=(const Point& p) {
        xp += p.xp;
        yp += p.yp;
        return *this;
    }
    Point& operator-=(const Point& p) {
        xp -= p.xp;
        yp -= p.yp;
        return *this;
    }
    Point& operator*=(float factor) {
        xp = (int)round(xp * factor);
        yp = (int)round(yp * factor);
        return *this;
    }
    Point& operator*=(double factor) {
        xp = (int)round(xp * factor);
        yp = (int)round(yp * factor);
        return *this;
    }
    Point& operator*=(int factor) {
        xp = xp * factor;
        yp = yp * factor;
        return *this;
    }
    Point& operator/=(double c) {
        xp = (int)round(xp / c);
        yp = (int)round(yp / c);
        return *this;
    }

    static int dot(const Point& p1, const Point& p2) { return p1.xp * p2.xp + p1.yp * p2.yp; }
    friend bool operator==(const Point& p1, const Point& p2) { return p1.xp == p2.xp && p1.yp == p2.yp; }
    friend bool operator!=(const Point& p1, const Point& p2) { return p1.xp != p2.xp || p1.yp != p2.yp; }
    friend Point operator+(const Point& p1, const Point& p2) { return Point(p1.xp + p2.xp, p1.yp + p2.yp); }
    friend Point operator-(const Point& p1, const Point& p2) { return Point(p1.xp - p2.xp, p1.yp - p2.yp); }
    friend Point operator*(const Point& p, float factor) { return Point((int)round(p.xp * factor), (int)round(p.yp * factor)); }
    friend Point operator*(const Point& p, double factor) { return Point((int)round(p.xp * factor), (int)round(p.yp * factor)); }
    friend Point operator*(const Point& p, int factor) { return Point(p.xp * factor, p.yp * factor); }
    friend Point operator*(float factor, const Point& p) { return Point((int)round(p.xp * factor), (int)round(p.yp * factor)); }
    friend Point operator*(double factor, const Point& p) { return Point((int)round(p.xp * factor), (int)round(p.yp * factor)); }
    friend Point operator*(int factor, const Point& p) { return Point(p.xp * factor, p.yp * factor); }
    friend Point operator+(const Point& p) { return p; }
    friend Point operator-(const Point& p) { return Point(-p.xp, -p.yp); }
    friend Point operator/(const Point& p, double c) { return Point((int)round(p.xp / c), (int)round(p.yp / c)); }
};

#endif // POINT_H