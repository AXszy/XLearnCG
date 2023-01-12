//XWindow.cpp
//XXS

#include "XWindow.h"

XWindow::XWindow()
{

}

XWindow::~XWindow()
{
}

void XWindow::Initialize(HINSTANCE hInst, WNDPROC func)
{
	//��ʵ���������Ϊ��Ա
	m_hInst = hInst;

	//��䴰����
	m_wc.cbSize = sizeof(WNDCLASSEX);
	m_wc.hInstance = m_hInst; //ʵ�����
	m_wc.lpszClassName = TEXT("XSZY Window"); //��������
	m_wc.cbClsExtra = 0;
	m_wc.cbWndExtra = 0;
	m_wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1); //���ڱ�����ɫ��ˢ���
	m_wc.hCursor = LoadCursor(m_hInst, IDC_ARROW); //���������
	m_wc.hIcon = LoadIcon(m_hInst, IDI_APPLICATION); //����ͼ��
	m_wc.hIconSm = LoadIcon(m_hInst, IDI_APPLICATION); //����Сͼ��
	m_wc.lpfnWndProc = func;
	m_wc.lpszMenuName = TEXT("");
	m_wc.style = CS_HREDRAW | CS_VREDRAW;

	//ע�ᴰ����
	RegisterClassEx(&m_wc);

	//��ʼ����ͼ��Ļ�����С
	m_g.init(1440, 900);

	//�������ھ��
	m_hwnd = CreateWindowEx(
		WS_EX_APPWINDOW,
		TEXT("XSZY Window"), //��������
		TEXT("�����޵�XXS"), //���ڱ���
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		NULL, NULL, m_hInst, NULL
	);

}

void XWindow::Show()
{
	ShowWindow(m_hwnd, SW_SHOW); //��ʾ����
}

bool XWindow::Broadcast()
{
	MSG msg;
	if (GetMessage(&msg, NULL, 0, 0))  //��Ϣѭ��
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
		return true;
	}
	return false;
}

//��Ϣӳ�亯��

void XWindow::OnCreate(LPCREATESTRUCT lpcs)
{
	double m = 0.5573;
	XP3 p[16];
	p[0] = { 0, 1, 0 };
	p[1] = { 0, 1, m };
	p[2] = { 0, m, 1 };
	p[3] = { 0, 0, 1 };
	p[4] = p[0];
	p[5] = { m * m, 1, m };
	p[6] = { m, m, 1 };
	p[7] = { m, 0, 1 };
	p[8] = p[0];
	p[9] = { m, 1, m * m };
	p[10] = { 1, m, m };
	p[11] = { 1, 0, m };
	p[12] = p[0];
	p[13] = { m, 1, 0 };
	p[14] = { 1, m, 0 };
	p[15] = { 1, 0, 0 };

	XTransform3 t(p, 16);
	t.Scale(200);
	t.Translate(200, 200, 200);

	bp.SetPts(p);
	bp.Generate();
}

void XWindow::OnDestroy()
{
	m_g.release();
}

void XWindow::OnPaint()
{
	PAINTSTRUCT ps;
	HDC hdc = BeginPaint(m_hwnd, &ps);
	m_g.SetDC(hdc);
	m_g.clear();

	
	m_g.DrawBezierPatch(bp, {0, 0, 0});

	m_g.draw();
	EndPaint(m_hwnd, &ps);

}

void XWindow::OnKeyUp(WPARAM key)
{
}

void XWindow::OnKeyDown(WPARAM key)
{
}

void XWindow::OnLButtonDown(SHORT x, SHORT y)
{
}

void XWindow::OnLButtonUp(SHORT x, SHORT y)
{
}

void XWindow::OnRButtonDown(SHORT x, SHORT y)
{
}

void XWindow::OnRButtonUp(SHORT x, SHORT y)
{
}

void XWindow::OnTimer()
{
	XTransform3 t(bp.GetKnots(), 400);
	t.RotateY(5, bp.GetKnots()[0]);
	t.RotateY(2, { 400, 200, 200 });
	InvalidateRect(m_hwnd, NULL, false);
}
