#include "XTransform.h"
#include <math.h>

XTransform2::XTransform2(XP2* pts, int npts)
{
	p = pts;
	n = npts;
}

XTransform2::~XTransform2()
{
}

void XTransform2::Translate(double dx, double dy)
{
	for (int i = 0; i < n; i++)
	{
		p[i].x += dx;
		p[i].y += dy;
	}
}

void XTransform2::Rotate(double deg)
{
	double rad = deg / 180 * 3.1415926;  //½Ç¶È×ª»¡¶È
	for (int i = 0; i < n; i++)
	{
		double _x = p[i].x * cos(rad) - p[i].y * sin(rad);
		double _y = p[i].x * sin(rad) + p[i].y * cos(rad);
		p[i].x = _x;
		p[i].y = _y;
	}
}

void XTransform2::Scale(double scalar)
{
	for (int i = 0; i < n; i++)
	{
		p[i].x *= scalar;
		p[i].y *= scalar;
	}
}

void XTransform2::Scale(double sx, double sy)
{
	for (int i = 0; i < n; i++)
	{
		p[i].x *= sx;
		p[i].y *= sy;
	}
}

void XTransform2::Rotate(double deg, XP2 pCen)
{
	Translate(-pCen.x, -pCen.y);
	Rotate(deg);
	Translate(pCen.x, pCen.y);
}

void XTransform2::Scale(double s, XP2 pCen)
{
	Translate(-pCen.x, -pCen.y);
	Scale(s);
	Translate(pCen.x, pCen.y);
}

void XTransform2::Scale(double sx, double sy, XP2 pCen)
{
	Translate(-pCen.x, -pCen.y);
	Scale(sx, sy);
	Translate(pCen.x, pCen.y);
}

XTransform3::XTransform3(XP3* pts, int npts)
{
	p = pts;
	n = npts;
}

XTransform3::~XTransform3()
{
}

void XTransform3::Translate(double dx, double dy, double dz)
{
	for (int i = 0; i < n; i++)
	{
		p[i].x += dx;
		p[i].y += dy;
		p[i].z += dz;
	}
}

void XTransform3::RotateX(double deg)
{
	double rad = deg / 180 * 3.1415926;
	for (int i = 0; i < n; i++)
	{
		double _y = p[i].y * cos(rad) - p[i].z * sin(rad);
		double _z = p[i].y * sin(rad) + p[i].z * cos(rad);

		p[i].y = _y;
		p[i].z = _z;
	}
}

void XTransform3::RotateY(double deg)
{
	double rad = deg / 180 * 3.1415926;
	for (int i = 0; i < n; i++)
	{
		double _x = p[i].x * cos(rad) - p[i].z * sin(rad);
		double _z = p[i].x * sin(rad) + p[i].z * cos(rad);

		p[i].x = _x;
		p[i].z = _z;
	}
}

void XTransform3::RotateZ(double deg)
{
	double rad = deg / 180 * 3.1415926;
	for (int i = 0; i < n; i++)
	{
		double _x = p[i].x * cos(rad) - p[i].y * sin(rad);
		double _y = p[i].x * sin(rad) + p[i].y * cos(rad);

		p[i].x = _x;
		p[i].y = _y;
	}
}

void XTransform3::Scale(double s)
{
	Scale(s, s, s);
}

void XTransform3::Scale(double sx, double sy, double sz)
{
	for (int i = 0; i < n; i++)
	{
		p[i].x *= sx;
		p[i].y *= sy;
		p[i].z *= sz;
	}
}

void XTransform3::RotateX(double deg, XP3 pCen)
{
	Translate(-pCen.x, -pCen.y, -pCen.z);
	RotateX(deg);
	Translate(pCen.x, pCen.y, pCen.z);
}

void XTransform3::RotateY(double deg, XP3 pCen)
{
	Translate(-pCen.x, -pCen.y, -pCen.z);
	RotateY(deg);
	Translate(pCen.x, pCen.y, pCen.z);
}

void XTransform3::RotateZ(double deg, XP3 pCen)
{
	Translate(-pCen.x, -pCen.y, -pCen.z);
	RotateZ(deg);
	Translate(pCen.x, pCen.y, pCen.z);
}

void XTransform3::Scale(double s, XP3 pCen)
{
	Translate(-pCen.x, -pCen.y, -pCen.z);
	Scale(s);
	Translate(pCen.x, pCen.y, pCen.z);
}

void XTransform3::Scale(double sx, double sy, double sz, XP3 pCen)
{
	Translate(-pCen.x, -pCen.y, -pCen.z);
	Scale(sx, sy, sz);
	Translate(pCen.x, pCen.y, pCen.z);
}
