#include "Face.h"
#include "Paint.h"
#include "Camera.h"
#include "BSPtree.h"
#include "Object3D.h"

#include <vector>
#include <chrono>
#include <tchar.h>

class Scene {
private:
	bool show_help_ = false;

public:
	std::vector <Camera> cameras;
	std::vector <Object3D> objects;

	int action_object = 0, action_camera = 0;
	int WidthWndClass = 1600, HeightWndClass = 900;
	long delta_time = 0, delta_wheel = 0;
	bool left_button_pressed = false;

	void createObjects() {
		Camera camera1(WidthWndClass, HeightWndClass, Vector4D(0, 0, 5, 1));
		cameras.push_back(camera1);
		Object3D object1;
		object1.parallelepiped();
		objects.push_back(object1);
		object1.pyramid();
		objects.push_back(object1);
		objects[0].rotate(45, 15, 0);
		objects[0].translate(1, 0, 0);
		objects[1].rotate(0, 180, 0);
		objects[1].translate(-1, 0, 0);
	}
	void show(HDC hdc) {
		std::vector <Face> all_faces;
		for (int i = 0; i < objects.size(); i++) {
			std::vector <Face> object_faces = objects[i].get_faces();
			all_faces.insert(all_faces.end(), std::make_move_iterator(object_faces.begin()),
				std::make_move_iterator(object_faces.end()));
		}
		shadow(hdc, cameras[0], all_faces, Vector4D(0, -3, 10), -5, 0xaabdbb);
		BSPnode* root = new BSPnode;
		build_bsp_tree(root, all_faces);
		paint(hdc, root, cameras[0]);
		clear_tree(root);

		SetBkColor(hdc, 0xddf1ff);
		if (show_help_) {
			TextOut(hdc, 10, 10, L"���������� ��������", 19);
			TextOut(hdc, 10, 26, L"������� numpad - �����������", 28);
			TextOut(hdc, 10, 42, L"������� - ��������", 18);
			TextOut(hdc, 10, 58, L"C - ����� ������", 16);
			TextOut(hdc, 10, 90, L"���������� ���������", 20);
			TextOut(hdc, 10, 106, L"W,A,S,D,Q,E - �����������", 25);
			TextOut(hdc, 10, 122, L"SHIFT + W,A,S,D,Q,E - ��������", 30);
			TextOut(hdc, 10, 138, L"CTRL + W,A,S,D,Q,E - ���������������", 36);
			TextOut(hdc, 10, 154, L"O - ����� �������", 17);
		}
		else {
			TCHAR buffer[20];
			_stprintf_s(buffer, _T("%d ms"), delta_time);
			TextOut(hdc, 10, 10, buffer, (int)_tcslen(buffer));
		}
		if (left_button_pressed) {
			HPEN hPen;
			hPen = CreatePen(PS_DASHDOT, 2, 0x000000);
			SelectObject(hdc, hPen);
			MoveToEx(hdc, WidthWndClass / 2 - 10, HeightWndClass / 2, NULL);
			LineTo(hdc, WidthWndClass / 2 + 10, HeightWndClass / 2);
			MoveToEx(hdc, WidthWndClass / 2, HeightWndClass / 2 - 10, NULL);
			LineTo(hdc, WidthWndClass / 2, HeightWndClass / 2 + 10);
			DeleteObject(hPen);
		}
	}
	void control(WPARAM key) {
		float translate_speed = 0.05f;
		float rotate_speed = 1.5f;
		float scale_speed = 0.05f;
		if (GetKeyState(VK_SHIFT) & 0x8000) {
			if (key == int('E')) objects[action_object].rotate(0, 0, rotate_speed);
			if (key == int('Q')) objects[action_object].rotate(0, 0, -rotate_speed);
			if (key == int('W')) objects[action_object].rotate(rotate_speed, 0, 0);
			if (key == int('S')) objects[action_object].rotate(-rotate_speed, 0, 0);
			if (key == int('D')) objects[action_object].rotate(0, rotate_speed, 0);
			if (key == int('A')) objects[action_object].rotate(0, -rotate_speed, 0);
		}
		else if (GetKeyState(VK_CONTROL) & 0x8000) {
			if (key == int('E')) objects[action_object].scale(1, 1, 1 + scale_speed);
			if (key == int('Q')) objects[action_object].scale(1, 1, 1 - scale_speed);
			if (key == int('W')) objects[action_object].scale(1 + scale_speed, 1, 1);
			if (key == int('S')) objects[action_object].scale(1 - scale_speed, 1, 1);
			if (key == int('D')) objects[action_object].scale(1, 1 + scale_speed, 1);
			if (key == int('A')) objects[action_object].scale(1, 1 - scale_speed, 1);
		}
		else {
			if (key == int('E')) objects[action_object].translate(0, 0, translate_speed);
			if (key == int('Q')) objects[action_object].translate(0, 0, -translate_speed);
			if (key == int('W')) objects[action_object].translate(translate_speed, 0, 0);
			if (key == int('S')) objects[action_object].translate(-translate_speed, 0, 0);
			if (key == int('D')) objects[action_object].translate(0, translate_speed, 0);
			if (key == int('A')) objects[action_object].translate(0, -translate_speed, 0);
		}
		if (key == 105) cameras[action_camera].translate(0, 0, translate_speed);
		if (key == 103) cameras[action_camera].translate(0, 0, -translate_speed);
		if (key == 101) cameras[action_camera].translate(translate_speed, 0, 0);
		if (key == 104) cameras[action_camera].translate(-translate_speed, 0, 0);
		if (key == 100) cameras[action_camera].translate(0, translate_speed, 0);
		if (key == 102) cameras[action_camera].translate(0, -translate_speed, 0);

		if (key == int('O')) action_object == objects.size() - 1 ? action_object = 0 : action_object++;
		if (key == int('C')) action_camera == cameras.size() - 1 ? action_camera = 0 : action_camera++;
		if (key == 112) show_help_ = !show_help_;
	}
	void movement() {

	}
} scene;


LRESULT CALLBACK WndProc(HWND hWnd, UINT messg, WPARAM wParam, LPARAM lParam) {
	PAINTSTRUCT ps; RECT Rect; HDC hdc, hCmpDC; HBITMAP hBmp;

	switch (messg) {

	case WM_PAINT: {
		auto begin = std::chrono::high_resolution_clock::now();

		GetClientRect(hWnd, &Rect);
		hdc = BeginPaint(hWnd, &ps);

		// �������� �������� ��������� ��� ������� �����������
		hCmpDC = CreateCompatibleDC(hdc);
		hBmp = CreateCompatibleBitmap(hdc, Rect.right - Rect.left, Rect.bottom - Rect.top);
		SelectObject(hCmpDC, hBmp);

		// �������� ������� ������
		LOGBRUSH br;
		br.lbStyle = BS_SOLID;
		br.lbColor = 0xddf1ff;
		HBRUSH brush;
		brush = CreateBrushIndirect(&br);
		FillRect(hCmpDC, &Rect, brush);
		DeleteObject(brush);

		SetTextColor(hCmpDC, 0x000000);
		// ���������
		scene.show(hCmpDC);

		// �������� ����������� �� �������� ��������� �� �����
		SetStretchBltMode(hdc, COLORONCOLOR);
		BitBlt(hdc, 0, 0, Rect.right - Rect.left, Rect.bottom - Rect.top, hCmpDC, 0, 0, SRCCOPY);

		// ������� �������� ��������� �������
		DeleteDC(hCmpDC);
		DeleteObject(hBmp);
		hCmpDC = NULL;

		EndPaint(hWnd, &ps);

		auto end = std::chrono::high_resolution_clock::now();
		auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
		scene.delta_time = (long)elapsed.count();
	} break;

	case WM_ERASEBKGND:
		return 1;
		break;

	case WM_LBUTTONDOWN:
		scene.left_button_pressed = !scene.left_button_pressed;
		scene.left_button_pressed ? ShowCursor(false) : ShowCursor(true);
		SetCursorPos(scene.WidthWndClass / 2, scene.HeightWndClass / 2);
		break;
	case WM_MOUSEWHEEL:
		if (!scene.left_button_pressed)
			break;
		scene.delta_wheel += GET_WHEEL_DELTA_WPARAM(wParam);
		for (; scene.delta_wheel > WHEEL_DELTA; scene.delta_wheel -= WHEEL_DELTA)
			scene.cameras[scene.action_camera].translate(-0.5, 0, 0);
		for (; scene.delta_wheel < 0; scene.delta_wheel += WHEEL_DELTA)
			scene.cameras[scene.action_camera].translate(0.5, 0, 0);
		break;
	case WM_MOUSEMOVE:
		if (!scene.left_button_pressed)
			break;
		POINT position;
		GetCursorPos(&position);
		scene.cameras[scene.action_camera].rotate(
			(position.y - scene.HeightWndClass / 2) * 0.02f,
			(position.x - scene.WidthWndClass / 2) * 0.02f, 0);
		SetCursorPos(scene.WidthWndClass / 2, scene.HeightWndClass / 2);
		break;

	case WM_KEYDOWN:
		scene.control(wParam);
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	default:
		return (DefWindowProc(hWnd, messg, wParam, lParam));
	}
	scene.movement();
	InvalidateRect(hWnd, NULL, TRUE);
	return (0);
}
int WINAPI wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nCmdShow) {
	HWND hWnd;
	MSG lpMsg;
	WNDCLASS WndClass;

	scene.createObjects();

	// ��������� ��������� ������ ����
	WndClass.style = CS_HREDRAW | CS_VREDRAW;
	WndClass.lpfnWndProc = WndProc;
	WndClass.cbClsExtra = 0;
	WndClass.cbWndExtra = 0;
	WndClass.hInstance = hInstance;
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	WndClass.lpszMenuName = NULL;
	WndClass.lpszClassName = L"CG_WAPI_Template";

	// ������������ ����� ����
	if (!RegisterClass(&WndClass)) {
		MessageBox(NULL, L"�� ���� ���������������� ����� ����!", L"������", MB_OK);
		return 0;
	}

	// ������� �������� ���� ����������
	hWnd = CreateWindow(
		L"CG_WAPI_Template", // ��� ������ 
		L"������������ ������� ������������ ������ �1", // ����� ���������
		WS_VISIBLE | WS_POPUP | WS_MAXIMIZE, // ����� ���� 
		CW_USEDEFAULT, CW_USEDEFAULT, // ������� ������ �������� ���� 
		scene.WidthWndClass, scene.HeightWndClass, // ������ � ������ ���� 
		(HWND)NULL, // ��������� �� ������������ ���� NULL 
		(HMENU)NULL, // ������������ ���� ������ ���� 
		(HINSTANCE)hInstance, // ��������� �� ������� ����������
		NULL); // ���������� � �������� lParam � ������� WM_CREATE


	// ���� ���� �� ������� �������
	if (!hWnd) {
		MessageBox(NULL, L"�� ������� ������� ������� ����!", L"������", MB_OK);
		return 0;
	}

	// ���������� ����
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	// ��������� ���� ��������� ��������� �� �������� ����������
	while (GetMessage(&lpMsg, NULL, 0, 0)) {
		TranslateMessage(&lpMsg);
		DispatchMessage(&lpMsg);
	}
	return (int)lpMsg.wParam;
}