//main.cpp
//XXS

#include "XWindow.h"

XWindow w; //定义一个窗口

LRESULT CALLBACK WndProc(HWND hwnd, UINT wm, WPARAM wp, LPARAM lp)
{
	
	switch (wm)
	{
	case WM_CREATE:
		SetTimer(hwnd, 1, 50, NULL);
		w.OnCreate((LPCREATESTRUCT)lp);
		break;
	case WM_CLOSE:
		DestroyWindow(hwnd);
		break;
	case WM_PAINT:
		w.OnPaint();
		break;
	case WM_KEYUP:
		w.OnKeyUp(wp);
		break;
	case WM_KEYDOWN:
		w.OnKeyDown(wp);
		break;
	case WM_LBUTTONDOWN:
		w.OnLButtonDown(LOWORD(lp), HIWORD(lp));
		break;
	case WM_LBUTTONUP:
		w.OnLButtonUp(LOWORD(lp), HIWORD(lp));
		break;
	case WM_RBUTTONDOWN:
		w.OnLButtonDown(LOWORD(lp), HIWORD(lp));
		break;
	case WM_RBUTTONUP:
		w.OnRButtonUp(LOWORD(lp), HIWORD(lp));
		break;
	case WM_TIMER:
		if(wp == 1) 
			w.OnTimer();  //默认设置了一个20ms的计时器
		break;
	case WM_DESTROY:
		w.OnDestroy();
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hwnd, wm, wp, lp);
	}
	return 0;
}

int APIENTRY WinMain(HINSTANCE hInst, HINSTANCE, LPSTR, int)
{
	w.Initialize(hInst, WndProc);
	w.Show();
	while (w.Broadcast());
	return 0;
}