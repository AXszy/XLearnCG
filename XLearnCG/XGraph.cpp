#include "XGraph.h"
#include <cmath>

XGraph::XGraph()
{
	m_width = m_height = 0;
	m_img = nullptr;
}

XGraph::~XGraph()
{
}

void XGraph::init(int w, int h)
{
	m_width = w;
	m_height = h;
	m_img = new char[w * h * 3]; //动态创建位图
	memset(m_img, 255, w * h * 3); //初始化为纯白
	m_zbuffer = new double[w * h]; //z轴缓冲
	memset(m_zbuffer, -10000, w * h * sizeof(double));  //初始化低于画布10000像素

	//初始化位图信息
	m_bmi.biSize = sizeof(BITMAPINFOHEADER);
	m_bmi.biBitCount = 24;
	m_bmi.biClrImportant = 0;
	m_bmi.biClrUsed = 0;
	m_bmi.biCompression = 0;
	m_bmi.biPlanes = 1;
	m_bmi.biHeight = m_height;
	m_bmi.biSizeImage = 0;
	m_bmi.biWidth = m_width;
	m_bmi.biXPelsPerMeter = 0;
	m_bmi.biYPelsPerMeter = 0;
}

void XGraph::SetDC(HDC hdc)
{
	m_hdc = hdc;
}

void XGraph::release()
{
	delete[] m_img;
	m_img = nullptr;

	delete[] m_zbuffer;
	m_zbuffer = nullptr;
}

void XGraph::draw()
{
	SetDIBitsToDevice(
		m_hdc, 
		0, 0, m_width, m_height,
		0, 0, 0, m_height, m_img, 
		(BITMAPINFO*)&m_bmi,
		DIB_RGB_COLORS
	);
}

void XGraph::clear()
{
	memset(m_img, 255, m_width * m_height * 3);
	memset(m_zbuffer, -10000, m_width * m_height * sizeof(double));
}

void XGraph::DrawPoint(XP2 p, XColor c)
{
	if (p.x >= 0 && p.x < m_width && p.y >= 0 && p.y < m_height)
	{
		int m = ((m_height - int(p.y) - 1) * m_width + int(p.x)) * 3;
		m_img[m + 0] = c.b;
		m_img[m + 1] = c.g;
		m_img[m + 2] = c.r;
	}
}

void XGraph::DrawRectLine(XRect rc, XColor c)
{
	for (int i = rc.left; i <= rc.right; i++)
	{
		DrawPoint(XP2(i, rc.top), c);
		DrawPoint(XP2(i, rc.bottom), c);
	}
	for (int i = rc.top; i <= rc.bottom; i++)
	{
		DrawPoint(XP2(rc.left, i), c);
		DrawPoint(XP2(rc.right, i), c);
	}
}

void XGraph::FillRect(XRect rc, XColor c)
{
	for (int i = rc.left + 1; i <= rc.right - 1; i++)
		for (int j = rc.top + 1; j <= rc.bottom - 1; j++)
			DrawPoint(XP2(i, j), c);
}

void XGraph::DrawEllipseLine(XEllipse e, XColor c)
{
	//椭圆中心点
	double xCenter = (e.left + e.right) * 0.5;
	double yCenter = (e.bottom + e.top) * 0.5;
	//椭圆长半轴长,短半轴长
	double a = (e.right - e.left) * 0.5;
	double b = (e.bottom - e.top) * 0.5;

	XP2 pLast = {xCenter + a, yCenter};
	for (double rad = 0.01; rad <= 6.28; rad += 0.01)
	{
		XP2 p(xCenter + a * cos(rad), yCenter + b * sin(rad));
		DrawLine(pLast, p, c);
		pLast = p;
	}
}

void XGraph::FillEllipse(XEllipse e, XColor c)
{
	//椭圆中心点
	double xCenter = (e.left + e.right) * 0.5;
	double yCenter = (e.bottom + e.top) * 0.5;
	//椭圆长半轴长,短半轴长
	double a = (e.right - e.left) * 0.5;
	double b = (e.bottom - e.top) * 0.5;

	for (int i = e.left + 1; i <= e.right - 1; i++)
		for (int j = e.top + 1; j <= e.bottom - 1; j++)
		{
			int x_ = i - xCenter;
			int y_ = j - yCenter;
			if ((x_ * x_) / (a * a) + (y_ * y_) / (b * b) - 1 < 0)
				DrawPoint(XP2(i, j), c);
		}
}

void XGraph::DrawLine(XP2 a, XP2 b, XColor c)
{
	double dx = a.x - b.x;
	double dy = a.y - b.y;

	if (dx == 0 && dy == 0) DrawPoint(a, c);
	else
	{
		double(*abs)(double) = [](double d) {return (d > 0) ? d : -d; };
		double dt = 1 / max(abs(dx), abs(dy));
		for (double t = 0; t <= 1; t += dt)
			DrawPoint( a*(1 - t)+ b * t, c);
	}
}

void XGraph::DrawBezier(XBezier2 b, XColor c)
{
	XP2* p = b.GetKnots();
	XP2 pLast = p[0];
	for (int i = 1; i < 20; i++)
	{
		DrawLine(pLast, p[i], c);
		pLast = p[i];
	}
}

void XGraph::DrawBezierPatch(XBezierPatch bp, XColor c)
{
	XP3* p = bp.GetKnots();
	for (int i = 0; i < 20; i++)
	{
		XP3 pLast = p[bp.calc_index(i, 0)];
		for (int j = 1; j < 20; j++)
		{
			DrawLine(pLast, p[bp.calc_index(i, j)], c);
			pLast = p[bp.calc_index(i, j)];
		}
	}
	for (int j = 0; j < 20; j++)
	{
		XP3 pLast = p[bp.calc_index(0, j)];
		for (int i = 1; i < 20; i++)
		{
			DrawLine(pLast, p[bp.calc_index(i, j)], c);
			pLast = p[bp.calc_index(i, j)];
		}
	}
}

void XGraph::DrawPoint(XP3 p, XColor c)
{
	if (p.x >= 0 && p.x < m_width - 2 &&
		p.y >= 0 && p.y < m_height - 2)
	{
		if(p.z >= m_zbuffer[(m_height - int(p.y) - 1) * m_width + int(p.x)])
		{
			int m = ((m_height - int(p.y) - 1) * m_width + int(p.x)) * 3;
			m_img[m + 0] = c.b;
			m_img[m + 1] = c.g;
			m_img[m + 2] = c.r;
			m_zbuffer[(m_height - int(p.y) - 1) * m_width + int(p.x)] = p.z;
		}
	}
		
}

void XGraph::DrawLine(XP3 a, XP3 b, XColor c)
{
	double dx = a.x - b.x;
	double dy = a.y - b.y;

	if (dx == 0 && dy == 0) DrawPoint(a, c);
	else
	{
		double(*abs)(double) = [](double d) {return (d > 0) ? d : -d; };
		double dt = 1 / max(abs(dx), abs(dy));
		for (double t = 0; t <= 1; t += dt)
			DrawPoint(a * (1 - t) + b * t, c);
	}
}




