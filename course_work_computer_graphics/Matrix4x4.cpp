#include "Matrix4x4.h"

Matrix4x4::Matrix4x4(float m11, float m12, float m13, float m14,
    float m21, float m22, float m23, float m24,
    float m31, float m32, float m33, float m34,
    float m41, float m42, float m43, float m44) {
    m[0][0] = m11; m[0][1] = m21; m[0][2] = m31; m[0][3] = m41;
    m[1][0] = m12; m[1][1] = m22; m[1][2] = m32; m[1][3] = m42;
    m[2][0] = m13; m[2][1] = m23; m[2][2] = m33; m[2][3] = m43;
    m[3][0] = m14; m[3][1] = m24; m[3][2] = m34; m[3][3] = m44;
}

const float& Matrix4x4::operator()(int aRow, int aColumn) const {
    _ASSERT(aRow >= 0 && aRow < 4 && aColumn >= 0 && aColumn < 4);
    return m[aColumn][aRow];
}
float& Matrix4x4::operator()(int aRow, int aColumn) {
    _ASSERT(aRow >= 0 && aRow < 4 && aColumn >= 0 && aColumn < 4);
    return m[aColumn][aRow];
}

Vector4D Matrix4x4::column(int index) const {
    _ASSERT(index >= 0 && index < 4);
    return Vector4D(m[index][0], m[index][1], m[index][2], m[index][3]);
}
void Matrix4x4::setColumn(int index, const Vector4D& value) {
    _ASSERT(index >= 0 && index < 4);
    m[index][0] = value.x();
    m[index][1] = value.y();
    m[index][2] = value.z();
    m[index][3] = value.w();
}

Vector4D Matrix4x4::row(int index) const {
    _ASSERT(index >= 0 && index < 4);
    return Vector4D(m[0][index], m[1][index], m[2][index], m[3][index]);
}
void Matrix4x4::setRow(int index, const Vector4D& value) {
    _ASSERT(index >= 0 && index < 4);
    m[0][index] = value.x();
    m[1][index] = value.y();
    m[2][index] = value.z();
    m[3][index] = value.w();
}

bool Matrix4x4::isAffine() const {
    return m[0][3] == 0.0f && m[1][3] == 0.0f
        && m[2][3] == 0.0f && m[3][3] == 1.0f;
}

bool Matrix4x4::isIdentity() const {
    if (m[0][0] != 1.0f || m[0][1] != 0.0f || m[0][2] != 0.0f) return false;
    if (m[0][3] != 0.0f || m[1][0] != 0.0f || m[1][1] != 1.0f) return false;
    if (m[1][2] != 0.0f || m[1][3] != 0.0f || m[2][0] != 0.0f) return false;
    if (m[2][1] != 0.0f || m[2][2] != 1.0f || m[2][3] != 0.0f) return false;
    if (m[3][0] != 0.0f || m[3][1] != 0.0f || m[3][2] != 0.0f) return false;
    return (m[3][3] == 1.0f);
}
void Matrix4x4::setToIdentity() {
    m[0][0] = 1.0f; m[0][1] = 0.0f; m[0][2] = 0.0f; m[0][3] = 0.0f;
    m[1][0] = 0.0f; m[1][1] = 1.0f; m[1][2] = 0.0f; m[1][3] = 0.0f;
    m[2][0] = 0.0f; m[2][1] = 0.0f; m[2][2] = 1.0f; m[2][3] = 0.0f;
    m[3][0] = 0.0f; m[3][1] = 0.0f; m[3][2] = 0.0f; m[3][3] = 1.0f;
}

void Matrix4x4::fill(float value) {
    m[0][0] = value; m[0][1] = value; m[0][2] = value; m[0][3] = value;
    m[1][0] = value; m[1][1] = value; m[1][2] = value; m[1][3] = value;
    m[2][0] = value; m[2][1] = value; m[2][2] = value; m[2][3] = value;
    m[3][0] = value; m[3][1] = value; m[3][2] = value; m[3][3] = value;
}

Matrix4x4& Matrix4x4::operator+=(const Matrix4x4& other) {
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
Matrix4x4& Matrix4x4::operator-=(const Matrix4x4& other) {
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
Matrix4x4& Matrix4x4::operator*=(const Matrix4x4& other) {
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
Matrix4x4& Matrix4x4::operator*=(float divisor) {
    m[0][0] *= divisor; m[0][1] *= divisor; m[0][2] *= divisor; m[0][3] *= divisor;
    m[1][0] *= divisor; m[1][1] *= divisor; m[1][2] *= divisor; m[1][3] *= divisor;
    m[2][0] *= divisor; m[2][1] *= divisor; m[2][2] *= divisor; m[2][3] *= divisor;
    m[3][0] *= divisor; m[3][1] *= divisor; m[3][2] *= divisor; m[3][3] *= divisor; 
    return *this;
}
Matrix4x4& Matrix4x4::operator/=(float divisor) {
    m[0][0] /= divisor; m[0][1] /= divisor; m[0][2] /= divisor; m[0][3] /= divisor;
    m[1][0] /= divisor; m[1][1] /= divisor; m[1][2] /= divisor; m[1][3] /= divisor;
    m[2][0] /= divisor; m[2][1] /= divisor; m[2][2] /= divisor; m[2][3] /= divisor;
    m[3][0] /= divisor; m[3][1] /= divisor; m[3][2] /= divisor; m[3][3] /= divisor;
    return *this;
}
bool Matrix4x4::operator==(const Matrix4x4& other) const {
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
bool Matrix4x4::operator!=(const Matrix4x4& other) const {
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

Matrix4x4 operator+(const Matrix4x4& m1, const Matrix4x4& m2) {
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
Matrix4x4 operator-(const Matrix4x4& m1, const Matrix4x4& m2) {
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
Matrix4x4 operator*(const Matrix4x4& m1, const Matrix4x4& m2) {
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
              + m1.m[2][3] * m2.m[2][2]  + m1.m[3][3] * m2.m[2][3];

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

Vector4D operator*(const Vector4D& vector, const Matrix4x4& matrix) {
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
Vector4D operator*(const Matrix4x4& matrix, const Vector4D& vector) {
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

Matrix4x4 operator*(float divisor, const Matrix4x4& matrix) {
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
Matrix4x4 operator*(const Matrix4x4& matrix, float divisor) {
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
Matrix4x4 operator/(const Matrix4x4& matrix, float divisor) {
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