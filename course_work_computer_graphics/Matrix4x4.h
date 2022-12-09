#ifndef MATRIX4X4_H
#define MATRIX4X4_H

#include "Vector4D.h"

#define _USE_MATH_DEFINES
#include <math.h>
#include <assert.h>

class Matrix4x4 {
private:
    float m[4][4];

public:
    Matrix4x4() { fill(0); }
    Matrix4x4(float m11, float m12, float m13, float m14,
              float m21, float m22, float m23, float m24,
              float m31, float m32, float m33, float m34,
              float m41, float m42, float m43, float m44) {
        m[0][0] = m11; m[0][1] = m21; m[0][2] = m31; m[0][3] = m41;
        m[1][0] = m12; m[1][1] = m22; m[1][2] = m32; m[1][3] = m42;
        m[2][0] = m13; m[2][1] = m23; m[2][2] = m33; m[2][3] = m43;
        m[3][0] = m14; m[3][1] = m24; m[3][2] = m34; m[3][3] = m44;
    }

    const float& operator()(int aRow, int aColumn) const {
        assert(aRow >= 0 && aRow < 4 && aColumn >= 0 && aColumn < 4);
        return m[aColumn][aRow];
    }
    float& operator()(int aRow, int aColumn) {
        assert(aRow >= 0 && aRow < 4 && aColumn >= 0 && aColumn < 4);
        return m[aColumn][aRow];
    }
    void operator() (int aRow, int aColumn, float value) {
        assert(aRow >= 0 && aRow < 4 && aColumn >= 0 && aColumn < 4);
        m[aColumn][aRow] = value;
    }

    bool is_affine() const {
        return m[0][3] == 0.0f && m[1][3] == 0.0f
            && m[2][3] == 0.0f && m[3][3] == 1.0f;
    }

    bool is_identity() const {
        if (m[0][0] != 1.0f || m[0][1] != 0.0f || m[0][2] != 0.0f) return false;
        if (m[0][3] != 0.0f || m[1][0] != 0.0f || m[1][1] != 1.0f) return false;
        if (m[1][2] != 0.0f || m[1][3] != 0.0f || m[2][0] != 0.0f) return false;
        if (m[2][1] != 0.0f || m[2][2] != 1.0f || m[2][3] != 0.0f) return false;
        if (m[3][0] != 0.0f || m[3][1] != 0.0f || m[3][2] != 0.0f) return false;
        return (m[3][3] == 1.0f);
    }
    void set_to_identity() {
        m[0][0] = 1.0f; m[0][1] = 0.0f; m[0][2] = 0.0f; m[0][3] = 0.0f;
        m[1][0] = 0.0f; m[1][1] = 1.0f; m[1][2] = 0.0f; m[1][3] = 0.0f;
        m[2][0] = 0.0f; m[2][1] = 0.0f; m[2][2] = 1.0f; m[2][3] = 0.0f;
        m[3][0] = 0.0f; m[3][1] = 0.0f; m[3][2] = 0.0f; m[3][3] = 1.0f;
    }

    void fill(float value) {
        m[0][0] = value; m[0][1] = value; m[0][2] = value; m[0][3] = value;
        m[1][0] = value; m[1][1] = value; m[1][2] = value; m[1][3] = value;
        m[2][0] = value; m[2][1] = value; m[2][2] = value; m[2][3] = value;
        m[3][0] = value; m[3][1] = value; m[3][2] = value; m[3][3] = value;
    }

    Matrix4x4& operator+=(const Matrix4x4& other) {
        m[0][0] += other.m[0][0]; m[0][1] += other.m[0][1];
        m[0][2] += other.m[0][2]; m[0][3] += other.m[0][3];
        m[1][0] += other.m[1][0]; m[1][1] += other.m[1][1];
        m[1][2] += other.m[1][2]; m[1][3] += other.m[1][3];
        m[2][0] += other.m[2][0]; m[2][1] += other.m[2][1];
        m[2][2] += other.m[2][2]; m[2][3] += other.m[2][3];
        m[3][0] += other.m[3][0]; m[3][1] += other.m[3][1];
        m[3][2] += other.m[3][2]; m[3][3] += other.m[3][3];
        return *this;
    }
    Matrix4x4& operator-=(const Matrix4x4& other) {
        m[0][0] -= other.m[0][0]; m[0][1] -= other.m[0][1];
        m[0][2] -= other.m[0][2]; m[0][3] -= other.m[0][3];
        m[1][0] -= other.m[1][0]; m[1][1] -= other.m[1][1];
        m[1][2] -= other.m[1][2]; m[1][3] -= other.m[1][3];
        m[2][0] -= other.m[2][0]; m[2][1] -= other.m[2][1];
        m[2][2] -= other.m[2][2]; m[2][3] -= other.m[2][3];
        m[3][0] -= other.m[3][0]; m[3][1] -= other.m[3][1];
        m[3][2] -= other.m[3][2]; m[3][3] -= other.m[3][3];
        return *this;
    }
    Matrix4x4& operator*=(const Matrix4x4& other) {
        float m0, m1, m2;
        m0 = m[0][0] * other.m[0][0] + m[1][0] * other.m[0][1]
            + m[2][0] * other.m[0][2] + m[3][0] * other.m[0][3];
        m1 = m[0][0] * other.m[1][0] + m[1][0] * other.m[1][1]
            + m[2][0] * other.m[1][2] + m[3][0] * other.m[1][3];
        m2 = m[0][0] * other.m[2][0] + m[1][0] * other.m[2][1]
            + m[2][0] * other.m[2][2] + m[3][0] * other.m[2][3];
        m[3][0] = m[0][0] * other.m[3][0] + m[1][0] * other.m[3][1]
            + m[2][0] * other.m[3][2] + m[3][0] * other.m[3][3];
        m[0][0] = m0; m[1][0] = m1; m[2][0] = m2;

        m0 = m[0][1] * other.m[0][0] + m[1][1] * other.m[0][1]
            + m[2][1] * other.m[0][2] + m[3][1] * other.m[0][3];
        m1 = m[0][1] * other.m[1][0] + m[1][1] * other.m[1][1]
            + m[2][1] * other.m[1][2] + m[3][1] * other.m[1][3];
        m2 = m[0][1] * other.m[2][0] + m[1][1] * other.m[2][1]
            + m[2][1] * other.m[2][2] + m[3][1] * other.m[2][3];
        m[3][1] = m[0][1] * other.m[3][0] + m[1][1] * other.m[3][1]
            + m[2][1] * other.m[3][2] + m[3][1] * other.m[3][3];
        m[0][1] = m0;  m[1][1] = m1; m[2][1] = m2;

        m0 = m[0][2] * other.m[0][0] + m[1][2] * other.m[0][1]
            + m[2][2] * other.m[0][2] + m[3][2] * other.m[0][3];
        m1 = m[0][2] * other.m[1][0] + m[1][2] * other.m[1][1]
            + m[2][2] * other.m[1][2] + m[3][2] * other.m[1][3];
        m2 = m[0][2] * other.m[2][0] + m[1][2] * other.m[2][1]
            + m[2][2] * other.m[2][2] + m[3][2] * other.m[2][3];
        m[3][2] = m[0][2] * other.m[3][0] + m[1][2] * other.m[3][1]
            + m[2][2] * other.m[3][2] + m[3][2] * other.m[3][3];
        m[0][2] = m0; m[1][2] = m1; m[2][2] = m2;

        m0 = m[0][3] * other.m[0][0] + m[1][3] * other.m[0][1]
            + m[2][3] * other.m[0][2] + m[3][3] * other.m[0][3];
        m1 = m[0][3] * other.m[1][0] + m[1][3] * other.m[1][1]
            + m[2][3] * other.m[1][2] + m[3][3] * other.m[1][3];
        m2 = m[0][3] * other.m[2][0] + m[1][3] * other.m[2][1]
            + m[2][3] * other.m[2][2] + m[3][3] * other.m[2][3];
        m[3][3] = m[0][3] * other.m[3][0] + m[1][3] * other.m[3][1]
            + m[2][3] * other.m[3][2] + m[3][3] * other.m[3][3];
        m[0][3] = m0; m[1][3] = m1; m[2][3] = m2;
        return *this;
    }
    Matrix4x4& operator*=(float divisor) {
        m[0][0] *= divisor; m[0][1] *= divisor; m[0][2] *= divisor; m[0][3] *= divisor;
        m[1][0] *= divisor; m[1][1] *= divisor; m[1][2] *= divisor; m[1][3] *= divisor;
        m[2][0] *= divisor; m[2][1] *= divisor; m[2][2] *= divisor; m[2][3] *= divisor;
        m[3][0] *= divisor; m[3][1] *= divisor; m[3][2] *= divisor; m[3][3] *= divisor;
        return *this;
    }
    Matrix4x4& operator/=(float divisor) {
        m[0][0] /= divisor; m[0][1] /= divisor; m[0][2] /= divisor; m[0][3] /= divisor;
        m[1][0] /= divisor; m[1][1] /= divisor; m[1][2] /= divisor; m[1][3] /= divisor;
        m[2][0] /= divisor; m[2][1] /= divisor; m[2][2] /= divisor; m[2][3] /= divisor;
        m[3][0] /= divisor; m[3][1] /= divisor; m[3][2] /= divisor; m[3][3] /= divisor;
        return *this;
    }
    bool operator==(const Matrix4x4& other) const {
        return
            m[0][0] == other.m[0][0] && m[0][1] == other.m[0][1] &&
            m[0][2] == other.m[0][2] && m[0][3] == other.m[0][3] &&
            m[1][0] == other.m[1][0] && m[1][1] == other.m[1][1] &&
            m[1][2] == other.m[1][2] && m[1][3] == other.m[1][3] &&
            m[2][0] == other.m[2][0] && m[2][1] == other.m[2][1] &&
            m[2][2] == other.m[2][2] && m[2][3] == other.m[2][3] &&
            m[3][0] == other.m[3][0] && m[3][1] == other.m[3][1] &&
            m[3][2] == other.m[3][2] && m[3][3] == other.m[3][3];
    }
    bool operator!=(const Matrix4x4& other) const {
        return
            m[0][0] != other.m[0][0] || m[0][1] != other.m[0][1] ||
            m[0][2] != other.m[0][2] || m[0][3] != other.m[0][3] ||
            m[1][0] != other.m[1][0] || m[1][1] != other.m[1][1] ||
            m[1][2] != other.m[1][2] || m[1][3] != other.m[1][3] ||
            m[2][0] != other.m[2][0] || m[2][1] != other.m[2][1] ||
            m[2][2] != other.m[2][2] || m[2][3] != other.m[2][3] ||
            m[3][0] != other.m[3][0] || m[3][1] != other.m[3][1] ||
            m[3][2] != other.m[3][2] || m[3][3] != other.m[3][3];
    }
    friend Matrix4x4 operator+(const Matrix4x4& m1, const Matrix4x4& m2) {
        Matrix4x4 m;
        m.m[0][0] = m1.m[0][0] + m2.m[0][0]; m.m[0][1] = m1.m[0][1] + m2.m[0][1];
        m.m[0][2] = m1.m[0][2] + m2.m[0][2]; m.m[0][3] = m1.m[0][3] + m2.m[0][3];
        m.m[1][0] = m1.m[1][0] + m2.m[1][0]; m.m[1][1] = m1.m[1][1] + m2.m[1][1];
        m.m[1][2] = m1.m[1][2] + m2.m[1][2]; m.m[1][3] = m1.m[1][3] + m2.m[1][3];
        m.m[2][0] = m1.m[2][0] + m2.m[2][0]; m.m[2][1] = m1.m[2][1] + m2.m[2][1];
        m.m[2][2] = m1.m[2][2] + m2.m[2][2]; m.m[2][3] = m1.m[2][3] + m2.m[2][3];
        m.m[3][0] = m1.m[3][0] + m2.m[3][0]; m.m[3][1] = m1.m[3][1] + m2.m[3][1];
        m.m[3][2] = m1.m[3][2] + m2.m[3][2]; m.m[3][3] = m1.m[3][3] + m2.m[3][3];
        return m;
    }
    friend Matrix4x4 operator-(const Matrix4x4& m1, const Matrix4x4& m2) {
        Matrix4x4 m;
        m.m[0][0] = m1.m[0][0] - m2.m[0][0]; m.m[0][1] = m1.m[0][1] - m2.m[0][1];
        m.m[0][2] = m1.m[0][2] - m2.m[0][2]; m.m[0][3] = m1.m[0][3] - m2.m[0][3];
        m.m[1][0] = m1.m[1][0] - m2.m[1][0]; m.m[1][1] = m1.m[1][1] - m2.m[1][1];
        m.m[1][2] = m1.m[1][2] - m2.m[1][2]; m.m[1][3] = m1.m[1][3] - m2.m[1][3];
        m.m[2][0] = m1.m[2][0] - m2.m[2][0]; m.m[2][1] = m1.m[2][1] - m2.m[2][1];
        m.m[2][2] = m1.m[2][2] - m2.m[2][2]; m.m[2][3] = m1.m[2][3] - m2.m[2][3];
        m.m[3][0] = m1.m[3][0] - m2.m[3][0]; m.m[3][1] = m1.m[3][1] - m2.m[3][1];
        m.m[3][2] = m1.m[3][2] - m2.m[3][2]; m.m[3][3] = m1.m[3][3] - m2.m[3][3];
        return m;
    }
    friend Matrix4x4 operator*(const Matrix4x4& m1, const Matrix4x4& m2) {
        Matrix4x4 m;
        m.m[0][0] = m1.m[0][0] * m2.m[0][0] + m1.m[1][0] * m2.m[0][1]
            + m1.m[2][0] * m2.m[0][2] + m1.m[3][0] * m2.m[0][3];
        m.m[0][1] = m1.m[0][1] * m2.m[0][0] + m1.m[1][1] * m2.m[0][1]
            + m1.m[2][1] * m2.m[0][2] + m1.m[3][1] * m2.m[0][3];
        m.m[0][2] = m1.m[0][2] * m2.m[0][0] + m1.m[1][2] * m2.m[0][1]
            + m1.m[2][2] * m2.m[0][2] + m1.m[3][2] * m2.m[0][3];
        m.m[0][3] = m1.m[0][3] * m2.m[0][0] + m1.m[1][3] * m2.m[0][1]
            + m1.m[2][3] * m2.m[0][2] + m1.m[3][3] * m2.m[0][3];

        m.m[1][0] = m1.m[0][0] * m2.m[1][0] + m1.m[1][0] * m2.m[1][1]
            + m1.m[2][0] * m2.m[1][2] + m1.m[3][0] * m2.m[1][3];
        m.m[1][1] = m1.m[0][1] * m2.m[1][0] + m1.m[1][1] * m2.m[1][1]
            + m1.m[2][1] * m2.m[1][2] + m1.m[3][1] * m2.m[1][3];
        m.m[1][2] = m1.m[0][2] * m2.m[1][0] + m1.m[1][2] * m2.m[1][1]
            + m1.m[2][2] * m2.m[1][2] + m1.m[3][2] * m2.m[1][3];
        m.m[1][3] = m1.m[0][3] * m2.m[1][0] + m1.m[1][3] * m2.m[1][1]
            + m1.m[2][3] * m2.m[1][2] + m1.m[3][3] * m2.m[1][3];

        m.m[2][0] = m1.m[0][0] * m2.m[2][0] + m1.m[1][0] * m2.m[2][1]
            + m1.m[2][0] * m2.m[2][2] + m1.m[3][0] * m2.m[2][3];
        m.m[2][1] = m1.m[0][1] * m2.m[2][0] + m1.m[1][1] * m2.m[2][1]
            + m1.m[2][1] * m2.m[2][2] + m1.m[3][1] * m2.m[2][3];
        m.m[2][2] = m1.m[0][2] * m2.m[2][0] + m1.m[1][2] * m2.m[2][1]
            + m1.m[2][2] * m2.m[2][2] + m1.m[3][2] * m2.m[2][3];
        m.m[2][3] = m1.m[0][3] * m2.m[2][0] + m1.m[1][3] * m2.m[2][1]
            + m1.m[2][3] * m2.m[2][2] + m1.m[3][3] * m2.m[2][3];

        m.m[3][0] = m1.m[0][0] * m2.m[3][0] + m1.m[1][0] * m2.m[3][1]
            + m1.m[2][0] * m2.m[3][2] + m1.m[3][0] * m2.m[3][3];
        m.m[3][1] = m1.m[0][1] * m2.m[3][0] + m1.m[1][1] * m2.m[3][1]
            + m1.m[2][1] * m2.m[3][2] + m1.m[3][1] * m2.m[3][3];
        m.m[3][2] = m1.m[0][2] * m2.m[3][0] + m1.m[1][2] * m2.m[3][1]
            + m1.m[2][2] * m2.m[3][2] + m1.m[3][2] * m2.m[3][3];
        m.m[3][3] = m1.m[0][3] * m2.m[3][0] + m1.m[1][3] * m2.m[3][1]
            + m1.m[2][3] * m2.m[3][2] + m1.m[3][3] * m2.m[3][3];
        return m;
    }
    friend Vector4D operator*(const Vector4D& vector, const Matrix4x4& matrix) {
        float x, y, z, w;
        x = vector.x() * matrix.m[0][0] + vector.y() * matrix.m[0][1]
            + vector.z() * matrix.m[0][2] + vector.w() * matrix.m[0][3];
        y = vector.x() * matrix.m[1][0] + vector.y() * matrix.m[1][1]
            + vector.z() * matrix.m[1][2] + vector.w() * matrix.m[1][3];
        z = vector.x() * matrix.m[2][0] + vector.y() * matrix.m[2][1]
            + vector.z() * matrix.m[2][2] + vector.w() * matrix.m[2][3];
        w = vector.x() * matrix.m[3][0] + vector.y() * matrix.m[3][1]
            + vector.z() * matrix.m[3][2] + vector.w() * matrix.m[3][3];
        return Vector4D(x, y, z, w);
    }
    friend Vector4D operator*(const Matrix4x4& matrix, const Vector4D& vector) {
        float x, y, z, w;
        x = vector.x() * matrix.m[0][0] + vector.y() * matrix.m[1][0]
            + vector.z() * matrix.m[2][0] + vector.w() * matrix.m[3][0];
        y = vector.x() * matrix.m[0][1] + vector.y() * matrix.m[1][1]
            + vector.z() * matrix.m[2][1] + vector.w() * matrix.m[3][1];
        z = vector.x() * matrix.m[0][2] + vector.y() * matrix.m[1][2]
            + vector.z() * matrix.m[2][2] + vector.w() * matrix.m[3][2];
        w = vector.x() * matrix.m[0][3] + vector.y() * matrix.m[1][3]
            + vector.z() * matrix.m[2][3] + vector.w() * matrix.m[3][3];
        return Vector4D(x, y, z, w);
    }
    Matrix4x4 operator-(const Matrix4x4& matrix) {
        Matrix4x4 m;
        m.m[0][0] = -matrix.m[0][0]; m.m[0][1] = -matrix.m[0][1];
        m.m[0][2] = -matrix.m[0][2]; m.m[0][3] = -matrix.m[0][3];
        m.m[1][0] = -matrix.m[1][0]; m.m[1][1] = -matrix.m[1][1];
        m.m[1][2] = -matrix.m[1][2]; m.m[1][3] = -matrix.m[1][3];
        m.m[2][0] = -matrix.m[2][0]; m.m[2][1] = -matrix.m[2][1];
        m.m[2][2] = -matrix.m[2][2]; m.m[2][3] = -matrix.m[2][3];
        m.m[3][0] = -matrix.m[3][0]; m.m[3][1] = -matrix.m[3][1];
        m.m[3][2] = -matrix.m[3][2]; m.m[3][3] = -matrix.m[3][3];
        return m;
    }
    friend Matrix4x4 operator*(float divisor, const Matrix4x4& matrix) {
        Matrix4x4 m;
        m.m[0][0] = matrix.m[0][0] * divisor; m.m[0][1] = matrix.m[0][1] * divisor;
        m.m[0][2] = matrix.m[0][2] * divisor; m.m[0][3] = matrix.m[0][3] * divisor;
        m.m[1][0] = matrix.m[1][0] * divisor; m.m[1][1] = matrix.m[1][1] * divisor;
        m.m[1][2] = matrix.m[1][2] * divisor; m.m[1][3] = matrix.m[1][3] * divisor;
        m.m[2][0] = matrix.m[2][0] * divisor; m.m[2][1] = matrix.m[2][1] * divisor;
        m.m[2][2] = matrix.m[2][2] * divisor; m.m[2][3] = matrix.m[2][3] * divisor;
        m.m[3][0] = matrix.m[3][0] * divisor; m.m[3][1] = matrix.m[3][1] * divisor;
        m.m[3][2] = matrix.m[3][2] * divisor; m.m[3][3] = matrix.m[3][3] * divisor;
        return m;
    }
    friend Matrix4x4 operator*(const Matrix4x4& matrix, float divisor) {
        Matrix4x4 m;
        m.m[0][0] = matrix.m[0][0] * divisor; m.m[0][1] = matrix.m[0][1] * divisor;
        m.m[0][2] = matrix.m[0][2] * divisor; m.m[0][3] = matrix.m[0][3] * divisor;
        m.m[1][0] = matrix.m[1][0] * divisor; m.m[1][1] = matrix.m[1][1] * divisor;
        m.m[1][2] = matrix.m[1][2] * divisor; m.m[1][3] = matrix.m[1][3] * divisor;
        m.m[2][0] = matrix.m[2][0] * divisor; m.m[2][1] = matrix.m[2][1] * divisor;
        m.m[2][2] = matrix.m[2][2] * divisor; m.m[2][3] = matrix.m[2][3] * divisor;
        m.m[3][0] = matrix.m[3][0] * divisor; m.m[3][1] = matrix.m[3][1] * divisor;
        m.m[3][2] = matrix.m[3][2] * divisor; m.m[3][3] = matrix.m[3][3] * divisor;
        return m;
    }
    friend Matrix4x4 operator/(const Matrix4x4& matrix, float divisor) {
        Matrix4x4 m;
        m.m[0][0] = matrix.m[0][0] / divisor; m.m[0][1] = matrix.m[0][1] / divisor;
        m.m[0][2] = matrix.m[0][2] / divisor; m.m[0][3] = matrix.m[0][3] / divisor;
        m.m[1][0] = matrix.m[1][0] / divisor; m.m[1][1] = matrix.m[1][1] / divisor;
        m.m[1][2] = matrix.m[1][2] / divisor; m.m[1][3] = matrix.m[1][3] / divisor;
        m.m[2][0] = matrix.m[2][0] / divisor; m.m[2][1] = matrix.m[2][1] / divisor;
        m.m[2][2] = matrix.m[2][2] / divisor; m.m[2][3] = matrix.m[2][3] / divisor;
        m.m[3][0] = matrix.m[3][0] / divisor; m.m[3][1] = matrix.m[3][1] / divisor;
        m.m[3][2] = matrix.m[3][2] / divisor; m.m[3][3] = matrix.m[3][3] / divisor;
        return m;
    }
    float* data() { return *m; }
    const float* data() const { return *m; }

    static Matrix4x4 transfer(float Tx, float Ty, float Tz) {
        return Matrix4x4(
            1, 0, 0, 0,
            0, 1, 0, 0,
            0, 0, 1, 0,
            Tx, Ty, Tz, 1);
    }
    static Matrix4x4 scaling(float Sx, float Sy, float Sz) {
        return Matrix4x4(
            Sx, 0, 0, 0,
            0, Sy, 0, 0,
            0, 0, Sz, 0,
            0, 0, 0, 1);
    }
    static Matrix4x4 rotation(float Rx, float Ry, float Rz) {
        Rx = Rx * (float)M_PI / 180;
        Ry = Ry * (float)M_PI / 180;
        Rz = Rz * (float)M_PI / 180;
        Matrix4x4 rotateX(
            1, 0, 0, 0,
            0, cos(Rx), sin(Rx), 0,
            0, -sin(Rx), cos(Rx), 0,
            0, 0, 0, 1);
        Matrix4x4 rotateY(
            cos(Ry), 0, -sin(Ry), 0,
            0, 1, 0, 0,
            sin(Ry), 0, cos(Ry), 0,
            0, 0, 0, 1 );
        Matrix4x4 rotateZ(
            cos(Rz), sin(Rz), 0, 0,
            -sin(Rz), cos(Rz), 0, 0,
            0, 0, 1, 0,
            0, 0, 0, 1);
        return (rotateX * rotateY * rotateZ);
    }
};

#endif // MATRIX4X4_H