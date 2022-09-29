#include "Vector4D.h"

class Matrix4x4 {
private:
    float m[4][4];

    //Matrix4x4 orthonormalInverse() const;

public:
    Matrix4x4() { setToIdentity(); }
    Matrix4x4(float m11, float m12, float m13, float m14,
        float m21, float m22, float m23, float m24,
        float m31, float m32, float m33, float m34,
        float m41, float m42, float m43, float m44);

    const float& operator()(int row, int column) const;
    float& operator()(int row, int column);

    Vector4D column(int index) const;
    void setColumn(int index, const Vector4D& value);

    Vector4D row(int index) const;
    void setRow(int index, const Vector4D& value);

    bool isAffine() const;

    bool isIdentity() const;
    void setToIdentity();

    void fill(float value);

    Matrix4x4& operator+=(const Matrix4x4& other);
    Matrix4x4& operator-=(const Matrix4x4& other);
    Matrix4x4& operator*=(const Matrix4x4& other);
    Matrix4x4& operator*=(float factor);
    Matrix4x4& operator/=(float divisor);
    bool operator==(const Matrix4x4& other) const;
    bool operator!=(const Matrix4x4& other) const;

    friend Matrix4x4 operator+(const Matrix4x4& m1, const Matrix4x4& m2);
    friend Matrix4x4 operator-(const Matrix4x4& m1, const Matrix4x4& m2);
    friend Matrix4x4 operator*(const Matrix4x4& m1, const Matrix4x4& m2);

    friend Vector4D operator*(const Vector4D& vector, const Matrix4x4& matrix);
    friend Vector4D operator*(const Matrix4x4& matrix, const Vector4D& vector);

    friend Matrix4x4 operator-(const Matrix4x4& matrix);

    friend Matrix4x4 operator*(float factor, const Matrix4x4& matrix);
    friend Matrix4x4 operator*(const Matrix4x4& matrix, float factor);
    friend Matrix4x4 operator/(const Matrix4x4& matrix, float divisor);

    float* data() { return *m; }
    const float* data() const { return *m; }

    double determinant() const;
    Matrix4x4 inverted(bool* invertible = nullptr) const;
    Matrix4x4 transposed() const;

    //void scale(float x, float y);
    //void scale(float x, float y, float z);
    //void scale(float factor);
    //void translate(float x, float y);
    //void translate(float x, float y, float z);
    //void rotate(float angle, float x, float y, float z = 0.0f);

    //void ortho(float left, float right, float bottom, float top, float nearPlane, float farPlane);
    //void frustum(float left, float right, float bottom, float top, float nearPlane, float farPlane);
    //void perspective(float verticalAngle, float aspectRatio, float nearPlane, float farPlane);

    //void flipCoordinates();

    //void optimize();

    //void projectedRotate(float angle, float x, float y, float z);
};