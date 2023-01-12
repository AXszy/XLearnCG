//XWindow.h
//XXS
#pragma once

#include "XGraph.h"  //��ͼ��
#include "XTransform.h" //�任

class XWindow  //������
{
public:
	XWindow();
	~XWindow();
	//��ʼ������
	void Initialize(HINSTANCE hInst, WNDPROC func); 
	//��ʾ����
	void Show(); 
	//�㲥��Ϣ �����Ƿ���յ���Ϣ
	bool Broadcast();
public://��Ϣӳ�亯��
	void OnCreate(LPCREATESTRUCT lpcs);
	void OnDestroy();
	void OnPaint();
	void OnKeyUp(WPARAM key);
	void OnKeyDown(WPARAM key);
	void OnLButtonDown(SHORT x, SHORT y);
	void OnLButtonUp(SHORT x, SHORT y);
	void OnRButtonDown(SHORT x, SHORT y);
	void OnRButtonUp(SHORT x, SHORT y);
	void OnTimer(); //��Ӧһ��50ms��ʱ��
private:
	HWND m_hwnd;
	HINSTANCE m_hInst;
	WNDCLASSEX m_wc;
	XGraph m_g;

	XBezierPatch bp;
};

