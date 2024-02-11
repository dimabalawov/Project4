﻿#include "Windows.h"
#include "windowsx.h"
#include "tchar.h"
#include "string"

using namespace std;

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

int lbtnclicks = 0;
int rbtnclicks = 0;
int mbtnclicks = 0;

int WINAPI wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nShowCmd)
{
	WCHAR className[] = L"FirstWindow";

	WNDCLASSEX wndClass;
	wndClass.cbSize = sizeof(WNDCLASSEX);
	wndClass.style = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;
	wndClass.hInstance = hInstance;
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndClass.hIconSm = NULL;
	wndClass.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wndClass.cbClsExtra = 0;
	wndClass.cbWndExtra = 0;
	wndClass.lpszMenuName = NULL;
	wndClass.lpszClassName = className;

	wndClass.lpfnWndProc = WindowProc;

	if (!RegisterClassEx(&wndClass)) {
		return 0;
	}

	HWND hWnd = CreateWindowEx(
		0,
		className,
		L"My first window",
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, //x,y
		CW_USEDEFAULT, CW_USEDEFAULT, //width, height
		NULL,
		NULL,
		hInstance,
		NULL
	);

	ShowWindow(hWnd, nShowCmd);
	UpdateWindow(hWnd);

	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0)) {
		DispatchMessage(&msg);
	}

	return msg.wParam;
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	wstring lbtnstr=L" Left Button Clicks: ";
	wstring rbtnstr=L" Right Button Clicks: ";
	wstring mbtnstr=L" Middle Button Clicks: ";
	lbtnstr += to_wstring(lbtnclicks);
	rbtnstr += to_wstring(rbtnclicks);
	mbtnstr += to_wstring(mbtnclicks);
	switch (uMsg)
	{
	case WM_DESTROY:
		PostQuitMessage(0); //WM_QUIT
		break;

	case WM_LBUTTONUP:
		lbtnclicks++;
		SetWindowText(hwnd, lbtnstr.c_str());
		break;
	case WM_RBUTTONUP:
		rbtnclicks++;
		SetWindowText(hwnd, rbtnstr.c_str());
		break;
	case WM_MBUTTONUP:
		mbtnclicks++;
		SetWindowText(hwnd, mbtnstr.c_str());
		break;
	default:
		return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}

	return 0;
}
