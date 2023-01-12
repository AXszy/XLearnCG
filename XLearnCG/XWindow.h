//XWindow.h
//XXS
#pragma once

#include "XGraph.h"  //绘图类
#include "XTransform.h" //变换

class XWindow  //窗口类
{
public:
	XWindow();
	~XWindow();
	//初始化窗口
	void Initialize(HINSTANCE hInst, WNDPROC func); 
	//显示窗口
	void Show(); 
	//广播消息 返回是否接收到消息
	bool Broadcast();
public://消息映射函数
	void OnCreate(LPCREATESTRUCT lpcs);
	void OnDestroy();
	void OnPaint();
	void OnKeyUp(WPARAM key);
	void OnKeyDown(WPARAM key);
	void OnLButtonDown(SHORT x, SHORT y);
	void OnLButtonUp(SHORT x, SHORT y);
	void OnRButtonDown(SHORT x, SHORT y);
	void OnRButtonUp(SHORT x, SHORT y);
	void OnTimer(); //响应一个50ms计时器
private:
	HWND m_hwnd;
	HINSTANCE m_hInst;
	WNDCLASSEX m_wc;
	XGraph m_g;

	XBezierPatch bp;
};

