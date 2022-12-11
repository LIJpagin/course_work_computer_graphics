#ifndef OBJECT3D_H
#define OBJECT3D_H

#include "Face.h"
#include "Vector4D.h"
#include "Matrix4x4.h"

#include <vector>
#include <sstream>
#include <fstream>
#include <windows.h>

class Object3D {
private:
	std::vector <Face> faces_;

public:
	Object3D() {}
	Object3D(const char* filename) { load_obj(filename); }
	Object3D(std::vector <Face>& faces) : faces_(faces) {}

	void set_faces(std::vector <Face>& faces) { faces_ = faces; }
	std::vector <Face> get_faces() { return faces_; }

	void cube() {
		faces_.clear();
		faces_ = {
			Face(Vector4D(-0.5f, -0.5f,  0.5f),	Vector4D( 0.5f, -0.5f,  0.5f), Vector4D(-0.5f,  0.5f,  0.5f), 0xff0000),
			Face(Vector4D(-0.5f,  0.5f,  0.5f),	Vector4D( 0.5f, -0.5f,  0.5f), Vector4D( 0.5f,  0.5f,  0.5f), 0xff0000),
			Face(Vector4D(-0.5f,  0.5f,  0.5f),	Vector4D( 0.5f,  0.5f,  0.5f), Vector4D(-0.5f,  0.5f, -0.5f), 0x00ff00),
			Face(Vector4D(-0.5f,  0.5f, -0.5f), Vector4D( 0.5f,  0.5f,  0.5f), Vector4D( 0.5f,  0.5f, -0.5f), 0x00ff00),
			Face(Vector4D(-0.5f,  0.5f, -0.5f), Vector4D( 0.5f,  0.5f, -0.5f), Vector4D(-0.5f, -0.5f, -0.5f), 0x0000ff),
			Face(Vector4D(-0.5f, -0.5f, -0.5f), Vector4D( 0.5f,  0.5f, -0.5f), Vector4D( 0.5f, -0.5f, -0.5f), 0x0000ff),
			Face(Vector4D(-0.5f, -0.5f, -0.5f), Vector4D( 0.5f, -0.5f, -0.5f), Vector4D(-0.5f, -0.5f,  0.5f), 0x00ffff),
			Face(Vector4D(-0.5f, -0.5f,  0.5f),	Vector4D( 0.5f, -0.5f, -0.5f), Vector4D( 0.5f, -0.5f,  0.5f), 0x00ffff),
			Face(Vector4D( 0.5f, -0.5f,  0.5f),	Vector4D( 0.5f, -0.5f, -0.5f), Vector4D( 0.5f,  0.5f,  0.5f), 0xffff00),
			Face(Vector4D( 0.5f,  0.5f,  0.5f),	Vector4D( 0.5f, -0.5f, -0.5f), Vector4D( 0.5f,  0.5f, -0.5f), 0xffff00),
			Face(Vector4D(-0.5f, -0.5f, -0.5f), Vector4D(-0.5f, -0.5f,  0.5f), Vector4D(-0.5f,  0.5f, -0.5f), 0xff00ff),
			Face(Vector4D(-0.5f,  0.5f, -0.5f),	Vector4D(-0.5f, -0.5f,  0.5f), Vector4D(-0.5f,  0.5f,  0.5f), 0xff00ff)
		};
	}
	void parallelepiped() {
		faces_.clear();
		faces_ = {
			Face(Vector4D(-1.0f,  0.5f,  0.5f),	Vector4D(-1.0f,  0.5f, -0.5f), Vector4D(-1.0f, -0.5f, -0.5f), 0xff0000),
			Face(Vector4D(-1.0f, -0.5f, -0.5f),	Vector4D(-1.0f, -0.5f,  0.5f), Vector4D(-1.0f,  0.5f,  0.5f), 0xff0000),
			Face(Vector4D(-1.0f, -0.5f,  0.5f),	Vector4D(-1.0f, -0.5f, -0.5f), Vector4D( 1.0f, -0.5f, -0.5f), 0x00ff00),
			Face(Vector4D( 1.0f, -0.5f, -0.5f), Vector4D( 1.0f, -0.5f,  0.5f), Vector4D(-1.0f, -0.5f,  0.5f), 0x00ff00),
			Face(Vector4D( 1.0f, -0.5f,  0.5f), Vector4D( 1.0f, -0.5f, -0.5f), Vector4D( 1.0f,  0.5f, -0.5f), 0x0000ff),
			Face(Vector4D( 1.0f,  0.5f, -0.5f), Vector4D( 1.0f,  0.5f,  0.5f), Vector4D( 1.0f, -0.5f,  0.5f), 0x0000ff),
			Face(Vector4D( 1.0f,  0.5f,  0.5f), Vector4D( 1.0f,  0.5f, -0.5f), Vector4D(-1.0f,  0.5f, -0.5f), 0x00ffff),
			Face(Vector4D(-1.0f,  0.5f, -0.5f),	Vector4D(-1.0f,  0.5f,  0.5f), Vector4D( 1.0f,  0.5f,  0.5f), 0x00ffff),
			Face(Vector4D( 1.0f,  0.5f,  0.5f),	Vector4D(-1.0f,  0.5f,  0.5f), Vector4D(-1.0f, -0.5f,  0.5f), 0xffff00),
			Face(Vector4D(-1.0f, -0.5f,  0.5f), Vector4D( 1.0f, -0.5f,  0.5f), Vector4D( 1.0f,  0.5f,  0.5f), 0xffff00),
			Face(Vector4D( 1.0f, -0.5f, -0.5f),	Vector4D(-1.0f, -0.5f, -0.5f), Vector4D(-1.0f,  0.5f, -0.5f), 0xff00ff),
			Face(Vector4D(-1.0f,  0.5f, -0.5f),	Vector4D( 1.0f,  0.5f, -0.5f), Vector4D( 1.0f, -0.5f, -0.5f), 0xff00ff),
		};
	}
	void pyramid() {
		faces_.clear();
		faces_ = {
			Face(Vector4D( 0.0f,        1.0f, 0.5f), Vector4D(0.0f, 0.0f, -0.8737287f),	Vector4D(-0.8660254f, -0.5f, 0.5f), 0xff0000),
			Face(Vector4D(-0.8660254f, -0.5f, 0.5f), Vector4D(0.0f, 0.0f, -0.8737287f),	Vector4D( 0.8660254f, -0.5f, 0.5f), 0x00ff00),
			Face(Vector4D( 0.8660254f, -0.5f, 0.5f), Vector4D(0.0f, 0.0f, -0.8737287f),	Vector4D( 0.0f,        1.0f, 0.5f), 0x0000ff),
			Face(Vector4D( 0.8660254f, -0.5f, 0.5f), Vector4D(0.0f, 1.0f,  0.5f),       Vector4D(-0.8660254f, -0.5f, 0.5f), 0xffff00),
		};
	}
	void load_obj(const char* filename, COLORREF color = 0xffffff) {
		std::ifstream in(filename, std::ios::in);
		if (!in) exit(1);
		faces_.clear();
		std::vector <Vector4D> vertices;
		std::string line;
		while (getline(in, line)) {
			if (line.substr(0, 2) == "v ") {
				std::istringstream v(line.substr(2));
				float x, y, z;
				v >> x >> y >> z;
				vertices.push_back(Vector4D(x, y, z, 1));
			}
			else if (line.substr(0, 2) == "f ") {
				faces_.resize(faces_.size() + 1);
				std::istringstream v(line.substr(2));
				std::string subline;
				Vector4D* points = faces_.back().get_points();
				faces_.back().set_color(color);
				for (int i = 0; i < 3; i++) {
					v >> subline;
					subline = subline.substr(0, subline.find("/"));
					points[i] = vertices[atoi(subline.c_str()) - 1];
				}
			}
		}
		in.close();
	}

	void translate(float Tx, float Ty, float Tz) {
		for (size_t i = 0; i < faces_.size(); i++) {
			Matrix4x4 mat = Matrix4x4::transfer(Tx, Ty, Tz);
			Vector4D* points = faces_[i].get_points();
			points[0] = points[0] * mat;
			points[1] = points[1] * mat;
			points[2] = points[2] * mat;
		}
	}
	void scale(float Sx, float Sy, float Sz) {
		for (size_t i = 0; i < faces_.size(); i++) {
			Matrix4x4 mat = Matrix4x4::scaling(Sx, Sy, Sz);
			Vector4D* points = faces_[i].get_points();
			points[0] = points[0] * mat;
			points[1] = points[1] * mat;
			points[2] = points[2] * mat;
		}
	}
	void rotate(float Rx, float Ry, float Rz) {
		for (size_t i = 0; i < faces_.size(); i++) {
			Matrix4x4 mat = Matrix4x4::rotation(Rx, Ry, Rz);
			Vector4D* points = faces_[i].get_points();
			points[0] = points[0] * mat;
			points[1] = points[1] * mat;
			points[2] = points[2] * mat;
		}
	}

	~Object3D() { }
};

#endif OBJECT3D_H