#ifndef FACE_H
#define FACE_H

#include "Vector4D.h"

#include <vector>

#define EPS 0.00001
enum class Location { FRONT, INSIDE, BACK, SPLIT };

struct Plane {
    float a, b, c, d;

    Plane(float aparam, float bparam, float cparam, float dparam = 0) :
        a(aparam), b(bparam), c(cparam), d(dparam) {}
    Vector4D isect(Vector4D start, Vector4D end) {
        Vector4D vector = end - start, normal = Vector4D(a, b, c, 0);
        float t = -(d + start.dot(normal)) / normal.dot(vector);
        return Vector4D(start.x() + t * vector.x(),
            start.y() + t * vector.y(),
            start.z() + t * vector.z(), 1);
    }
    bool is_isect(Vector4D start, Vector4D end) {
        return Vector4D(a, b, c, 0).dot(end - start);
    }
    float distance(Vector4D pt) {
        return a * pt.x() + b * pt.y() + c * pt.z() + d;
    }
};

class Face {
private:
    Vector4D pt[3];

public:
    Face() {}
    Face(Vector4D pt1, Vector4D pt2, Vector4D pt3) : pt{ pt1, pt2, pt3 } {}

    Vector4D a() { return pt[0]; };
    Vector4D b() { return pt[1]; };
    Vector4D c() { return pt[2]; };
    Vector4D* get_points() { return pt; }

    Plane to_plane() {
        Vector4D n = Vector4D::cross(pt[1] - pt[0], pt[2] - pt[0]);
        return Plane(n.x(), n.y(), n.z(), -pt[0].dot(n));
    }
    Vector4D normal() {
        return Vector4D::cross(pt[1] - pt[0], pt[2] - pt[0]);
    }
    Location located_relative(Face face) {
        bool front = false, back = false;
        Plane plane = face.to_plane();
        for (int i = 0; i < 3; i++) {
            float sign = plane.distance(pt[i]);
            if (sign > EPS) front = true;
            if (sign < -EPS) back = true;
        }
        if (front && back) return Location::SPLIT;
        if (front) return Location::FRONT;
        if (back) return Location::BACK;
        return Location::INSIDE;
    }
    std::vector <Face> split(Face face) {
        Plane plane = face.to_plane();
        std::vector <Face> faces;
        std::vector <Vector4D> points = { pt[0], pt[1], pt[2] };
        for (int i = 0; i < 3; i++)
            if (plane.is_isect(pt[i], pt[(i + 1) % 3]))
                points.insert(points.begin() + (i + 1) % 3,
                    plane.isect(pt[i], pt[(i + 1) % 3]));
        for (int i = 1; i < points.size() - 2; i++)
            faces.push_back(Face(points[i - 1], points[i], points[i + 1]));
        return faces;
    }
};

#endif // FACE_H