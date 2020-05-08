#pragma once
#include <atltypes.h>
#include <afxwin.h>

#define PI 3.1415
class Shape
{
public:
	CPoint m_StartPoint, m_EndPoint;
	CPen m_Pen;
	CBrush m_Brush;
	CClientDC* dc;
	CRect* m_ClientRect;
	int m_ShapeLength;
	int m_MovingDegree;
public:
	void SetRand() {
		m_MovingDegree = rand() % 121 - 60;
	}
	void ChangeClientRect(CView* wnd) {
		wnd->GetClientRect(m_ClientRect);
	}
	void SetDC(CClientDC* dc) {
		this->dc = dc;
	}
	void SetPenBrush() {
		dc->SelectObject(m_Pen);
		dc->SelectObject(m_Brush);
	}
	virtual void SetPoint(CView* wnd) = 0;
	virtual void DrawShape() = 0;
	virtual void MoveShape() = 0;
};

