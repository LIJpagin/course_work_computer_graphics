#ifndef CAMERA_H
#define CAMERA_H

#include "Vector4D.h"
#include "Matrix4x4.h"

#define _USE_MATH_DEFINES
#include <math.h>

class Camera {
private:
    Vector4D position_, forward_, up_, right_;
    int width_ = 1600, height_ = 800;
    float v_fov_, h_fov_ = M_PI / 3;
    float near_plane_ = 0.1f, far_plane_ = 100;


public:
    Camera(int width, int height, Vector4D position) {
        if (width > 100 || height > 100)
            width_ = width, height_ = height;
        v_fov_ = h_fov_ * ((float)height_ / width_);
        position_ = position;
        forward_ = Vector4D(0, 0, 1, 1);
        up_ = Vector4D(0, 1, 0, 1);
        right_ = Vector4D(1, 0, 0, 1);
    }

    int getWidthScreen() { return width_; }
    int getHeightScreen() { return height_; }
    Vector4D get_position() { return position_; }

    Matrix4x4 cameraMatrix() {
        Matrix4x4 transfer = Matrix4x4::transfer(
            -position_.x(), -position_.y(), -position_.z());
        transfer(1, 3, 1);
        Matrix4x4 rotation(
            right_.x(), up_.x(), forward_.x(), 0,
            right_.y(), up_.y(), forward_.y(), 0,
            right_.z(), up_.z(), forward_.z(), 0,
            0, 0, 0, 1);
        return (transfer * rotation);
    }
    Matrix4x4 projectionMatrix() {
        float m00 = 1 / tan(h_fov_ / 2);
        float m11 = 1 / tan(v_fov_ / 2);
        float m22 = (far_plane_ + near_plane_) / (far_plane_ - near_plane_);
        float m32 = (-2 * near_plane_ * far_plane_) / (far_plane_ - near_plane_);
        return Matrix4x4(
            m00, 0, 0, 0,
            0, m11, 0, 0,
            0, 0, m22, 1,
            0, 0, m32, 0);
    }
    Matrix4x4 toScreenMatrix() {
        float HW = (float)(width_ / 2);
        float HH = (float)(height_ / 2);
        return Matrix4x4(
            HW,  0, 0, 0,
            0, -HH, 0, 0,
            0,   0, 1, 0,
            HW, HH, 0, 1);
    }

    void translate(float Tx, float Ty, float Tz) {
        position_ = position_ + forward_ * Tx;
        position_ = position_ + right_ * Ty;
        position_ = position_ + up_ * Tz;
    }
    void rotate(float Rx, float Ry, float Rz) {
        forward_ = forward_ * Matrix4x4::rotation(Rx, Ry, Rz);
        right_ = right_ * Matrix4x4::rotation(Rx, Ry, Rz);
        up_ = up_ * Matrix4x4::rotation(Rx, Ry, Rz);
    }

    ~Camera() { }
};

#endif CAMERA_H