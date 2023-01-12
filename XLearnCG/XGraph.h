#pragma once
#include <Windows.h>
#include "BasicUnit.h"
class XGraph  //��ͼ��
{
public:
	XGraph();
	~XGraph();
	void init(int w, int h);
	void SetDC(HDC hdc);
	void release();
	void draw();//��λͼ����DC��
	void clear(); //���λͼ��zbuffer
public://����Ĳ������ǰѶ�������λͼ��
	void DrawPoint(XP2 p, XColor c);
	void DrawRectLine(XRect rc, XColor c);
	void FillRect(XRect rc, XColor c);
	void DrawEllipseLine(XEllipse e, XColor c);
	void FillEllipse(XEllipse e, XColor c);
	void DrawLine(XP2 a, XP2 b, XColor c);
	void DrawBezier(XBezier2 b, XColor c);
	void DrawBezierPatch(XBezierPatch bp, XColor c);

	void DrawPoint(XP3 p, XColor c);
	void DrawLine(XP3 a, XP3 b, XColor c);
private:
	int m_width;
	int m_height;
	HDC m_hdc;
	char* m_img;
	BITMAPINFOHEADER m_bmi;

	double* m_zbuffer;
};

