#pragma once
#include "BasicUnit.h"
class XTransform2
{
public:
	XTransform2(XP2 *pts,int npts);  //�õ���������һ���任��
	~XTransform2();

	void Translate(double dx, double dy);
	void Rotate(double deg);
	void Scale(double scalar); //�ȱ�����
	void Scale(double sx, double sy);
	void Rotate(double deg, XP2 pCen);  //���ĳ���ת��
	void Scale(double s, XP2 pCen);
	void Scale(double sx, double sy, XP2 pCen);
private:
	XP2* p; //��
	int n;  //����
};

class XTransform3
{
public:
	XTransform3(XP3* pts, int npts);  //�õ���������һ���任��
	~XTransform3();

	void Translate(double dx, double dy, double dz);
	void RotateX(double deg);
	void RotateY(double deg);
	void RotateZ(double deg);
	void Scale(double s); //�ȱ�������
	void Scale(double sx, double sy, double sz);

	void RotateX(double deg, XP3 pCen);
	void RotateY(double deg, XP3 pCen);
	void RotateZ(double deg, XP3 pCen);
	void Scale(double s, XP3 pCen);
	void Scale(double sx, double sy, double sz, XP3 pCen);
private:
	XP3* p; //��
	int n;  //����
};