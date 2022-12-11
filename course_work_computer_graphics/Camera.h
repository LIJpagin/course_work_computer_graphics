#ifndef CAMERA_H
#define CAMERA_H

#include "Vector4D.h"
#include "Matrix4x4.h"

#define _USE_MATH_DEFINES
#include <math.h>

class Camera {
private:
    Vector4D position, forward, up, right;
    int width = 1600, height = 800;
    float v_fov, h_fov = M_PI / 3;
    float near_plane = 0.1f, far_plane = 100;


public:
    Camera(int w, int h, Vector4D pos) {
        if (w > 100 || h > 100)
            width = w, height = h;
        v_fov = h_fov * ((float)height / width);
        position = pos;
        forward = Vector4D(0, 0, 1, 1);
        up = Vector4D(0, 1, 0, 1);
        right = Vector4D(1, 0, 0, 1);
    }
    Vector4D get_position() { return position; }

    Matrix4x4 camera_matrix() {
        Matrix4x4 transfer = Matrix4x4::transfer(
            -position.x(), -position.y(), -position.z());
        transfer(1, 3, 1);
        Matrix4x4 rotation(
            right.x(), up.x(), forward.x(), 0,
            right.y(), up.y(), forward.y(), 0,
            right.z(), up.z(), forward.z(), 0,
            0, 0, 0, 1);
        return (transfer * rotation);
    }
    Matrix4x4 projection_matrix() {
        float m00 = 1 / tan(h_fov / 2);
        float m11 = 1 / tan(v_fov / 2);
        float m22 = (far_plane + near_plane) / (far_plane - near_plane);
        float m32 = (-2 * near_plane * far_plane) / (far_plane - near_plane);
        return Matrix4x4(
            m00, 0, 0, 0,
            0, m11, 0, 0,
            0, 0, m22, 1,
            0, 0, m32, 0);
    }
    Matrix4x4 to_screen_matrix() {
        float HW = (float)(width / 2);
        float HH = (float)(height / 2);
        return Matrix4x4(
            HW,  0, 0, 0,
            0, -HH, 0, 0,
            0,   0, 1, 0,
            HW, HH, 0, 1);
    }

    void translate(float Tx, float Ty, float Tz) {
        position += forward * Tx;
        position += right * Ty;
        position += up * Tz;
    }
    void rotate(float Rx, float Ry, float Rz) {
        forward = forward * Matrix4x4::rotation(Rx, Ry, Rz);
        right = right * Matrix4x4::rotation(Rx, Ry, Rz);
        up = up * Matrix4x4::rotation(Rx, Ry, Rz);
    }

    ~Camera() { }
};

#endif CAMERA_H