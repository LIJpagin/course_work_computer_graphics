#ifndef PAINT_H
#define PAINT_H

#include "Face.h"
#include "Camera.h"
#include "BSPtree.h"
#include "Matrix4x4.h"
#include "Object3D.h"

#include <windows.h>

POINT* into_screen(Camera& camera, Face& face) {
	POINT* screen_points = new POINT[3];
	Vector4D* points = face.get_points();
	for (size_t i = 0; i < 3; i++) {
		points[i] = points[i] * camera.cameraMatrix() * camera.projectionMatrix();
		points[i].normalization();
		points[i] = points[i] * camera.toScreenMatrix();
		screen_points[i] = { (long)points[i].x(), (long)points[i].y() };
	}
	return screen_points;
}

void fill(HDC& hdc, POINT* face, COLORREF color) {
		HBRUSH hBrush = CreateSolidBrush(color);
		HPEN hPen = CreatePen(PS_DASHDOT, 1, color);
		SetBkColor(hdc, color);
		SelectObject(hdc, hBrush);
		SelectObject(hdc, hPen);
		Polygon(hdc, face, 3);
		DeleteObject(hBrush);
		DeleteObject(hPen);
}

void paint(HDC& hdc, BSPnode* root, Camera& camera) {
    if (!root) return;
    float view_sign = root->faces.front().to_plane().distance(camera.get_position());
	if (view_sign > EPS) paint(hdc, root->right, camera);
	else paint(hdc, root->left, camera);
	while (root->faces.size()) {
		Face face = root->faces.front();
		root->faces.erase(root->faces.begin());
		fill(hdc, into_screen(camera, face), face.get_color());
	}
	if (view_sign > EPS) paint(hdc, root->left, camera);
	else paint(hdc, root->right, camera);
}

void shadow(HDC& hdc, Camera& camera, std::vector <Face>& faces, Vector4D light, float ground, COLORREF color_shadow) {
	for (int i = 0; i < faces.size(); i++) {
		Face shadow;
		Vector4D* shadow_points = shadow.get_points();
		Vector4D* face_points = faces[i].get_points();
		for (int j = 0; j < 3; j++) {
			float t = (ground - face_points[j].z()) / light.z();
			shadow_points[j].set_x(face_points[j].x() + t * light.x());
			shadow_points[j].set_y(face_points[j].y() + t * light.y());
			shadow_points[j].set_z(ground);
		}
		fill(hdc, into_screen(camera, shadow), color_shadow);
	}
}

#endif // PAINT_H