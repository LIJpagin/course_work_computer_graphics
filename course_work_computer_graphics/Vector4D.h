#ifndef VECTOR4D_H
#define VECTOR4D_H

#include "Point.h"

#define _USE_MATH_DEFINES
#include <math.h>

class Vector4D {
private:
    float v[4];

public:
    Vector4D() : v{ 0.0f, 0.0f, 0.0f, 1.0f } {}
    Vector4D(float xpos, float ypos, float zpos, float wpos = 1.0f)
        : v{ xpos, ypos, zpos, wpos } {}

    bool isNull() const { return v[0] && v[1] && v[2] && v[3]; }

    float x() const { return v[0]; }
    float y() const { return v[1]; }
    float z() const { return v[2]; }
    float w() const { return v[3]; }

    void set_x(float aX) { v[0] = aX; }
    void set_y(float aY) { v[1] = aY; }
    void set_z(float aZ) { v[2] = aZ; }
    void set_w(float aW) { v[3] = aW; }

    float& operator[](int i) { return v[i]; }
    float  operator[](int i) const { return v[i]; }

    float length() const {
        double len =
            double(v[0]) * double(v[0]) + double(v[1]) * double(v[1]) +
            double(v[2]) * double(v[2]) + double(v[3]) * double(v[3]);
        return float(sqrt(len));
    }
    float length_squared() const {
        return v[0] * v[0] + v[1] * v[1] + v[2] * v[2] + v[3] * v[3];
    }
    Vector4D normalized() const {
        double len =
            double(v[0]) * double(v[0]) + double(v[1]) * double(v[1]) +
            double(v[2]) * double(v[2]) + double(v[3]) * double(v[3]);
        double sqrtLen = sqrt(len);
        return Vector4D(float(double(v[0]) / sqrtLen),
            float(double(v[1]) / sqrtLen),
            float(double(v[2]) / sqrtLen),
            float(double(v[3]) / sqrtLen));
    }
    void normalize() {
        double len =
            double(v[0]) * double(v[0]) + double(v[1]) * double(v[1]) +
            double(v[2]) * double(v[2]) + double(v[3]) * double(v[3]);
        len = sqrt(len);
        v[0] = float(double(v[0]) / len);
        v[1] = float(double(v[1]) / len);
        v[2] = float(double(v[2]) / len);
        v[3] = float(double(v[3]) / len);
    }
    void normalization() {
        v[0] = float(double(v[0]) / v[3]);
        v[1] = float(double(v[1]) / v[3]);
        v[2] = float(double(v[2]) / v[3]);
        v[3] = float(double(v[3]) / v[3]);
    }

    Vector4D& operator+=(Vector4D vector) {
        v[0] += vector.v[0]; v[1] += vector.v[1];
        v[2] += vector.v[2]; v[3] += vector.v[3];
        return *this;
    }
    Vector4D& operator-=(Vector4D vector) {
        v[0] -= vector.v[0]; v[1] -= vector.v[1];
        v[2] -= vector.v[2]; v[3] -= vector.v[3];
        return *this;
    }
    Vector4D& operator*=(float factor) {
        v[0] *= factor; v[1] *= factor;
        v[2] *= factor; v[3] *= factor;
        return *this;
    }
    Vector4D& operator*=(Vector4D vector) {
        v[0] *= vector.v[0]; v[1] *= vector.v[1];
        v[2] *= vector.v[2]; v[3] *= vector.v[3];
        return *this;
    }
    Vector4D& operator/=(float divisor) {
        v[0] /= divisor; v[1] /= divisor;
        v[2] /= divisor; v[3] /= divisor;
        return *this;
    }
    Vector4D& operator/=(Vector4D vector) {
        v[0] /= vector.v[0]; v[1] /= vector.v[1];
        v[2] /= vector.v[2]; v[3] /= vector.v[3];
        return *this;
    }
    float dot(Vector4D v2) {
        return v[0] * v2.v[0] + v[1] * v2.v[1]
            +v[2] * v2.v[2] +v[3] * v2.v[3];
    }
    static Vector4D cross(Vector4D v1, Vector4D v2) {
        return Vector4D(v1.v[1] * v2.v[2] - v1.v[2] * v2.v[1],
            v1.v[2] * v2.v[0] - v1.v[0] * v2.v[2],
            v1.v[0] * v2.v[1] - v1.v[1] * v2.v[0], 0);
    }

    Point to_point() const {
        return Point((int)v[0], (int)v[1]);
    }

    friend bool operator==(Vector4D v1, Vector4D v2) {
        return v1.v[0] == v2.v[0] && v1.v[1] == v2.v[1]
            && v1.v[2] == v2.v[2] && v1.v[3] == v2.v[3];
    }
    friend bool operator!=(Vector4D v1, Vector4D v2) {
        return v1.v[0] != v2.v[0] || v1.v[1] != v2.v[1]
            || v1.v[2] != v2.v[2] || v1.v[3] != v2.v[3];
    }
    friend Vector4D operator+(Vector4D v1, Vector4D v2) {
        return Vector4D(v1.v[0] + v2.v[0], v1.v[1] + v2.v[1],
            v1.v[2] + v2.v[2], v1.v[3] + v2.v[3]);
    }
    friend Vector4D operator-(Vector4D v1, Vector4D v2) {
        return Vector4D(v1.v[0] - v2.v[0], v1.v[1] - v2.v[1],
            v1.v[2] - v2.v[2], v1.v[3] - v2.v[3]);
    }
    friend Vector4D operator*(float factor, Vector4D vector) {
        return Vector4D(vector.v[0] * factor, vector.v[1] * factor,
            vector.v[2] * factor, vector.v[3] * factor);
    }
    friend Vector4D operator*(Vector4D vector, float factor) {
        return Vector4D(vector.v[0] * factor, vector.v[1] * factor,
            vector.v[2] * factor, vector.v[3] * factor);
    }
    friend Vector4D operator*(Vector4D v1, Vector4D v2) {
        return Vector4D(v1.v[0] * v2.v[0], v1.v[1] * v2.v[1],
            v1.v[2] * v2.v[2], v1.v[3] * v2.v[3]);
    }
    friend Vector4D operator-(Vector4D vector) {
        return Vector4D(-vector.v[0], -vector.v[1], -vector.v[2], -vector.v[3]);
    }
    friend Vector4D operator/(Vector4D vector, float divisor) {
        return Vector4D(vector.v[0] / divisor, vector.v[1] / divisor,
            vector.v[2] / divisor, vector.v[3] / divisor);
    }
    friend Vector4D operator/(Vector4D vector, Vector4D divisor) {
        return Vector4D(vector.v[0] / divisor.v[0], vector.v[1] / divisor.v[1],
            vector.v[2] / divisor.v[2], vector.v[3] / divisor.v[3]);
    }

    float* data() { return v; }
    const float* data() const { return v; }
};

#endif // VECTOR4D_H