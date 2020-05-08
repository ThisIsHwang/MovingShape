#pragma once
#include "Shape.h"

class UserElip : public Shape
{
public:

	UserElip() {
		m_ClientRect = new CRect();
		m_MovingDegree = rand() % 121 - 60 + 270;
		m_Pen.CreatePen(PS_SOLID, 1, RGB(rand() % 256, rand() % 256, rand() % 256));
		m_ShapeLength = 20;
		m_Brush.CreateSolidBrush(RGB(255, 0, 0));
	}
	/*void DrawShape(int opt) {
		if (opt == 1)
			dc->SetROP2(R2_NOTXORPEN);
		else
			dc->SetROP2(R2_COPYPEN);
		dc->Ellipse(m_StartPoint.x, m_StartPoint.y, m_EndPoint.x, m_EndPoint.y);
	}*/

	void DrawShape() {
		dc->Ellipse(m_StartPoint.x, m_StartPoint.y, m_EndPoint.x, m_EndPoint.y);
	}


	void SetPoint(CView* wnd) {
		m_Pen.DeleteObject();
		m_Pen.CreatePen(PS_SOLID, 5, RGB(rand() % 256, rand() % 256, rand() % 256));

		SetRand();
		m_MovingDegree += 180;

		SetDC(new CClientDC(wnd));
		SetPenBrush();
		ChangeClientRect(wnd);

		m_StartPoint = CPoint((*m_ClientRect).right, (*m_ClientRect).bottom/2 - m_ShapeLength/2);
		m_EndPoint = CPoint(m_StartPoint.x - m_ShapeLength, m_StartPoint.y - m_ShapeLength);

	}

	void MoveShape() {
		if (m_EndPoint.y < 0) {
			SetRand();
			m_MovingDegree += 90;
		}
		else if (m_StartPoint.y > (*m_ClientRect).bottom) {
			SetRand();
			m_MovingDegree += 270;
		}
		else if (m_EndPoint.x < 0) {
			SetRand();
		}
		else if (m_StartPoint.x > (*m_ClientRect).right) {
			SetRand();
			m_MovingDegree += 180;
		}

		double temp = m_MovingDegree * (PI / 180);
		m_StartPoint = CPoint(m_StartPoint.x + 2 * cos(temp), m_StartPoint.y + 2 * sin(temp));
		m_EndPoint = CPoint(m_StartPoint.x - m_ShapeLength, m_StartPoint.y - m_ShapeLength);
	};
};

