#ifndef VECTOR4D_H
#define VECTOR4D_H

#include <cmath>

class Vector4D {
private:
    float v[4];

    //friend class Matrix4x4;
    //friend Vector4D operator*(const Vector4D& vector, const Matrix4x4& matrix);
    //friend Vector4D operator*(const Matrix4x4& matrix, const Vector4D& vector);

public:
    Vector4D();
    Vector4D(float xpos, float ypos, float zpos, float wpos);

    bool isNull() const;

    float x() const;
    float y() const;
    float z() const;
    float w() const;

    void setX(float x);
    void setY(float y);
    void setZ(float z);
    void setW(float w);

    float& operator[](int i);
    float operator[](int i) const;

    float length() const;
    float lengthSquared() const;

    Vector4D normalized() const;
    void normalize();

    Vector4D& operator+=(Vector4D vector);
    Vector4D& operator-=(Vector4D vector);
    Vector4D& operator*=(float factor);
    Vector4D& operator*=(Vector4D vector);
    Vector4D& operator/=(float divisor);
    Vector4D& operator/=(Vector4D vector);

    static float dotProduct(Vector4D v1, Vector4D v2);

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

    //Point toPoint() const;
};

#endif // VECTOR4D_H