#include "BasicUnit.h"

XColor operator+(XColor a, XColor b)
{
	XColor c;
	c.r = a.r + b.r;
	c.g = a.g + b.g;
	c.b = a.b + b.b;
	return c;
}

XP2 operator+(XP2 a, XP2 b)
{
	XP2 c;
	c.x = a.x + b.x;
	c.y = a.y + b.y;
	return c;
}

XP3 operator+(XP3 a, XP3 b)
{
	XP3 c;
	c.x = a.x + b.x;
	c.y = a.y + b.y;
	c.z = a.z + b.z;
	return c;
}

XColor operator*(XColor a, double k)
{
	XColor b;
	b.r = a.r * k;
	b.g = a.g * k;
	b.b = a.b * k;
	return b;
}

XP2 operator*(XP2 a, double k)
{
	XP2 b;
	b.x = a.x * k;
	b.y = a.y * k;
	return b;
}

XP3 operator*(XP3 a, double k)
{
	XP3 b;
	b.x = a.x * k;
	b.y = a.y * k;
	b.z = a.z * k;
	return b;
}

XBezier2::XBezier2()
{
}

XBezier2::~XBezier2()
{
}

void XBezier2::SetPts(XP2* p)
{
	for (int i = 0; i < 4; i++)
		pControl[i] = *(p + i);
}

void XBezier2::SetPts(XP2 A, XP2 B, XP2 C, XP2 D)
{
	pControl[0] = A;
	pControl[1] = B;
	pControl[2] = C;
	pControl[3] = D;
}

void XBezier2::Generate()
{
	for (int i = 0; i < 20; i++)
	{
		double t = i * 0.05;
		double _t = 1 - t;

		//四点权重
		double w0 = _t * _t * _t;
		double w1 = 3 * _t * _t * t;
		double w2 = 3 * _t * t * t;
		double w3 = t * t * t;

		knot[i] = pControl[0] * w0 + pControl[1] * w1 + pControl[2] * w2 + pControl[3] * w3;
	}
}

XP2* XBezier2::GetKnots()
{
	return knot;
}

XBezierPatch::XBezierPatch()
{
}

XBezierPatch::~XBezierPatch()
{
}

void XBezierPatch::SetPts(XP3* p)
{
	for (int i = 0; i < 16; i++)
		pControl[i] = *(p + i);
}

void XBezierPatch::Generate()
{
	XBezier3 b[4];
	for (int i = 0; i < 4; i++)
	{
		b[i].SetPts(pControl + 4 * i);
		b[i].Generate();
	}
	XP3* p[4];
	for (int i = 0; i < 4; i++)
		p[i] = b[i].GetKnots();
	for (int i = 0; i < 20; i++)
	{
		XBezier3 bz;
		bz.SetPts(p[0][i], p[1][i], p[2][i], p[3][i]);
		bz.Generate();
		XP3 *pt = bz.GetKnots();
		for (int j = 0; j < 20; j++)
			knot[calc_index(i, j)] = pt[j];
	}
}

XP3* XBezierPatch::GetKnots()
{
	return knot;
}

int XBezierPatch::calc_index(int i, int j)
{
	return i * 20 + j;
}

XBezier3::XBezier3()
{
}

XBezier3::~XBezier3()
{
}

void XBezier3::SetPts(XP3* p)
{
	for (int i = 0; i < 4; i++)
		pControl[i] = *(p + i);
}

void XBezier3::SetPts(XP3 A, XP3 B, XP3 C, XP3 D)
{
	pControl[0] = A;
	pControl[1] = B;
	pControl[2] = C;
	pControl[3] = D;
}

void XBezier3::Generate()
{
	for (int i = 0; i < 20; i++)
	{
		double t = i * 0.05;
		double _t = 1 - t;

		//四点权重
		double w0 = _t * _t * _t;
		double w1 = 3 * _t * _t * t;
		double w2 = 3 * _t * t * t;
		double w3 = t * t * t;

		knot[i] = pControl[0] * w0 + pControl[1] * w1 + pControl[2] * w2 + pControl[3] * w3;
	}
}

XP3* XBezier3::GetKnots()
{
	return knot;
}