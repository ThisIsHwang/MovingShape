#pragma once
#include "Shape.h"


class CMovingShapeView;
class UserLine : public Shape
{
public:
	UserLine() {
		m_ClientRect = new CRect();
		m_MovingDegree = rand() % 121 - 60;
		m_Pen.CreatePen(PS_SOLID, 10, RGB(255, 255, 0));
		m_ShapeLength = 20;
	}
	/*void DrawShape(int opt) {
		if(opt == 1)
			dc->SetROP2(R2_NOTXORPEN);
		else
			dc->SetROP2(R2_COPYPEN);
		dc->MoveTo(m_StartPoint);
		dc->LineTo(m_EndPoint);
	};*/

	void DrawShape() {
		dc->MoveTo(m_StartPoint);
		dc->LineTo(m_EndPoint);
	};

	 void SetPoint(CView* wnd) {
		 SetDC(new CClientDC(wnd));
		 SetPenBrush();
		 ChangeClientRect(wnd);
		 SetRand();
		m_StartPoint = CPoint(0, (*m_ClientRect).bottom / 2);
		m_EndPoint = CPoint(m_StartPoint.x + m_ShapeLength * cos(m_MovingDegree * (PI / 180)), m_StartPoint.y + m_ShapeLength * sin(m_MovingDegree * (PI / 180)));

	}


	void MoveShape() {
		if (m_EndPoint.y < 0) {
			SetRand();
			m_MovingDegree += 90;
		}
		else if (m_EndPoint.y > (*m_ClientRect).bottom) {

			SetRand();
			m_MovingDegree += 270;
		}
		else if (m_EndPoint.x < 0) {
			SetRand();
		}
		else if (m_EndPoint.x > (*m_ClientRect).right) {
			SetRand();
			m_MovingDegree += 180;
		}
		
		double temp = m_MovingDegree * (PI / 180);
		m_StartPoint = CPoint(m_StartPoint.x + 2*cos(temp), m_StartPoint.y + 2*sin(temp));
		m_EndPoint = CPoint(m_StartPoint.x + (m_ShapeLength * cos(temp)), m_StartPoint.y + (m_ShapeLength * sin(temp)));
	};
};

