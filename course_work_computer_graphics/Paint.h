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
		HPEN hPen = CreatePen(PS_DASHDOT, 2, 0xBBBBBB);
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
		Face face = root->faces.back();
		root->faces.pop_back();
		fill(hdc, into_screen(camera, face), 0xffffff);
	}
	if (view_sign > EPS) paint(hdc, root->left, camera);
	else paint(hdc, root->right, camera);
}

#endif // PAINT_H