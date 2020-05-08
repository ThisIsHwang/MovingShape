
// MovingShapeView.cpp: CMovingShapeView 클래스의 구현
//

#include "pch.h"
#include "framework.h"


// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "MovingShape.h"
#endif

#include "MovingShapeDoc.h"
#include "MovingShapeView.h"

#ifdef _DEBUG
#define new DEBUG_NEW

#endif
#define USERLINE 101
#define USERRECT 102
#define USERELIP 103

// CMovingShapeView

IMPLEMENT_DYNCREATE(CMovingShapeView, CView)

BEGIN_MESSAGE_MAP(CMovingShapeView, CView)
	ON_WM_LBUTTONDOWN()
	ON_WM_TIMER()
END_MESSAGE_MAP()

// CMovingShapeView 생성/소멸

CMovingShapeView::CMovingShapeView() noexcept
{
}

CMovingShapeView::~CMovingShapeView()
{
}

BOOL CMovingShapeView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CMovingShapeView 그리기

void CMovingShapeView::OnDraw(CDC* pDC)
{
	CMovingShapeDoc* pDoc = GetDocument();
	CClientDC dc(this);
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	
	pDoc->m_UserLine.ChangeClientRect(this);
	pDoc->m_UserRect.ChangeClientRect(this);
	pDoc->m_UserElip.ChangeClientRect(this);

	pDoc->m_UserLine.SetDC(&dc);
	pDoc->m_UserRect.SetDC(&dc);
	pDoc->m_UserElip.SetDC(&dc);

	dc.SelectObject(pDoc->m_UserLine.m_Pen);
	pDoc->m_UserLine.DrawShape();


	dc.SelectObject(pDoc->m_UserElip.m_Pen);
	dc.SelectObject(pDoc->m_UserElip.m_Brush);
	pDoc->m_UserElip.DrawShape();

	dc.SelectObject(pDoc->m_UserRect.m_Pen);
	dc.SelectObject(pDoc->m_UserRect.m_Brush);
	pDoc->m_UserRect.DrawShape();
	
	

}


// CMovingShapeView 진단

#ifdef _DEBUG
void CMovingShapeView::AssertValid() const
{
	CView::AssertValid();
}

void CMovingShapeView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMovingShapeDoc* CMovingShapeView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMovingShapeDoc)));
	return (CMovingShapeDoc*)m_pDocument;
}
#endif //_DEBUG


// CMovingShapeView 메시지 처리기


void CMovingShapeView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	Invalidate();
	CMovingShapeDoc* pDoc = GetDocument();
	pDoc->m_UserLine.SetPoint(this);
	pDoc->m_UserLine.DrawShape();

	pDoc->m_UserRect.SetPoint(this);
	pDoc->m_UserRect.DrawShape();

	pDoc->m_UserElip.SetPoint(this);
	pDoc->m_UserElip.DrawShape();

	SetTimer(USERLINE, 100, NULL);
	SetTimer(USERRECT, 50, NULL);
	SetTimer(USERELIP, 200, NULL);
	CView::OnLButtonDown(nFlags, point);	
}


void CMovingShapeView::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	CMovingShapeDoc* pDoc = GetDocument();
	switch (nIDEvent) {
	case USERLINE:
		pDoc->m_UserLine.MoveShape();
		Invalidate();
		break;
	case USERRECT:
		
		pDoc->m_UserRect.MoveShape();
		Invalidate();
		break;
	case USERELIP:
		
		pDoc->m_UserElip.MoveShape();
		Invalidate();
		break;
	}
	CView::OnTimer(nIDEvent);
}


