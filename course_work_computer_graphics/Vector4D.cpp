#include "Vector4D.h"

Vector4D::Vector4D() : v{ 0.0f, 0.0f, 0.0f, 0.0f } {}
Vector4D::Vector4D(float xpos, float ypos, float zpos, float wpos)
    : v{ xpos, ypos, zpos, wpos } {}

bool Vector4D::isNull() const {
    return v[0] && v[1] && v[2] && v[3];
}

float Vector4D::x() const { return v[0]; }
float Vector4D::y() const { return v[1]; }
float Vector4D::z() const { return v[2]; }
float Vector4D::w() const { return v[3]; }

void Vector4D::setX(float aX) { v[0] = aX; }
void Vector4D::setY(float aY) { v[1] = aY; }
void Vector4D::setZ(float aZ) { v[2] = aZ; }
void Vector4D::setW(float aW) { v[3] = aW; }

float& Vector4D::operator[](int i) { return v[i]; }
float  Vector4D::operator[](int i) const { return v[i]; }

float Vector4D::length() const {
    double len =
        double(v[0]) * double(v[0]) + double(v[1]) * double(v[1]) +
        double(v[2]) * double(v[2]) + double(v[3]) * double(v[3]);
    return float(std::sqrt(len));
}

float Vector4D::lengthSquared() const {
    return v[0] * v[0] + v[1] * v[1] + v[2] * v[2] + v[3] * v[3];
}

Vector4D Vector4D::normalized() const {
    double len =
        double(v[0]) * double(v[0]) + double(v[1]) * double(v[1]) +
        double(v[2]) * double(v[2]) + double(v[3]) * double(v[3]);
    double sqrtLen = std::sqrt(len);
    return Vector4D(float(double(v[0]) / sqrtLen),
        float(double(v[1]) / sqrtLen),
        float(double(v[2]) / sqrtLen),
        float(double(v[3]) / sqrtLen));
}

void Vector4D::normalize() {
    double len =
        double(v[0]) * double(v[0]) + double(v[1]) * double(v[1]) +
        double(v[2]) * double(v[2]) + double(v[3]) * double(v[3]);
    len = std::sqrt(len);
    v[0] = float(double(v[0]) / len);
    v[1] = float(double(v[1]) / len);
    v[2] = float(double(v[2]) / len);
    v[3] = float(double(v[3]) / len);
}

Vector4D& Vector4D::operator+=(Vector4D vector) {
    v[0] += vector.v[0]; v[1] += vector.v[1];
    v[2] += vector.v[2]; v[3] += vector.v[3];
    return *this;
}

Vector4D& Vector4D::operator-=(Vector4D vector) {
    v[0] -= vector.v[0]; v[1] -= vector.v[1];
    v[2] -= vector.v[2]; v[3] -= vector.v[3];
    return *this;
}

Vector4D& Vector4D::operator*=(float factor) {
    v[0] *= factor; v[1] *= factor;
    v[2] *= factor; v[3] *= factor;
    return *this;
}

Vector4D& Vector4D::operator*=(Vector4D vector) {
    v[0] *= vector.v[0]; v[1] *= vector.v[1];
    v[2] *= vector.v[2]; v[3] *= vector.v[3];
    return *this;
}

Vector4D& Vector4D::operator/=(float divisor) {
    v[0] /= divisor; v[1] /= divisor;
    v[2] /= divisor; v[3] /= divisor;
    return *this;
}

Vector4D& Vector4D::operator/=(Vector4D vector) {
    v[0] /= vector.v[0]; v[1] /= vector.v[1];
    v[2] /= vector.v[2]; v[3] /= vector.v[3];
    return *this;
}

float Vector4D::dotProduct(Vector4D v1, Vector4D v2) {
    return v1.v[0] * v2.v[0] + v1.v[1] * v2.v[1]
        + v1.v[2] * v2.v[2] + v1.v[3] * v2.v[3];
}

//Point Vector4D::toPoint() const {
//    return Point(v[0], v[1]);
//}