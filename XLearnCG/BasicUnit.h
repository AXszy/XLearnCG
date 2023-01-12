#pragma once
//定义一些基本的单元

#include <Windows.h>

//颜色
struct XColor
{
	XColor() {}
	XColor(double _r, double _g, double _b) : r(_r), g(_g), b(_b) {}
	double r;
	double g;
	double b;
};
XColor operator+(XColor a, XColor b);
XColor operator*(XColor a, double k);

//二维点
struct XP2
{
	XP2() {}
	XP2(double _x, double _y) : x(_x), y(_y) {}
	double x;
	double y;
};
XP2 operator+(XP2 a, XP2 b);
XP2 operator*(XP2 a, double k);

//三维点 
struct XP3
{
	XP3() {}
	XP3(double _x, double _y, double _z) :x(_x), y(_y), z(_z) {}
	double x;
	double y;
	double z;
};
XP3 operator+(XP3 a, XP3 b);
XP3 operator*(XP3 a, double k);

//矩形
typedef struct XRect
{
	XRect() {}
	XRect(int l, int t, int r, int b) :left(l), top(t), right(r), bottom(b) {}
	int left, top, right, bottom;
}XEllipse;

class XBezier2
{
public:
	XBezier2();
	~XBezier2();
	void SetPts(XP2* p);
	void SetPts(XP2 A, XP2 B, XP2 C, XP2 D);
	void Generate();

	XP2* GetKnots();
private:
	XP2 pControl[4];
	XP2 knot[20];
};

class XBezier3
{
public:
	XBezier3();
	~XBezier3();
	void SetPts(XP3* p);
	void SetPts(XP3 A, XP3 B, XP3 C, XP3 D);
	void Generate();

	XP3* GetKnots();
private:
	XP3 pControl[4];
	XP3 knot[20];
};

class XBezierPatch
{
public:
	XBezierPatch();
	~XBezierPatch();
	void SetPts(XP3* p);
	void Generate();

	XP3* GetKnots();
	int calc_index(int i, int j);  //计算数组下标
private:
	XP3 pControl[16];
	XP3 knot[400];
};