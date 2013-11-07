// ��� MFC ʾ��Դ������ʾ���ʹ�� MFC Microsoft Office Fluent �û����� 
// (��Fluent UI��)����ʾ�������ο���
// ���Բ��䡶Microsoft ������ο����� 
// MFC C++ ������渽����ص����ĵ���
// ���ơ�ʹ�û�ַ� Fluent UI ����������ǵ����ṩ�ġ�
// ��Ҫ�˽��й� Fluent UI ��ɼƻ�����ϸ��Ϣ�������  
// http://go.microsoft.com/fwlink/?LinkId=238214��
//
// ��Ȩ����(C) Microsoft Corporation
// ��������Ȩ����

// BooleanOperation2DView.h : CBooleanOperation2DView ��Ľӿ�
//

#pragma once

#include "Polygon.h" 
#include "Config.h"
#include <time.h>
#include "Triangulation.h"
#include "BooleanOperation.h"
#include "CF_Draw.h"


class CBooleanOperation2DView : public CView
{
protected: // �������л�����
	CBooleanOperation2DView();
	DECLARE_DYNCREATE(CBooleanOperation2DView)

// ����
public:
	CBooleanOperation2DDoc* GetDocument() const;

public:
    vec2 m_MouseMoveStartPoint; // �������ʱ���ƶ������
    vec2 m_MousuMovePoint; // �������ʱ�ƶ������еĵ�
    bool m_isButtonDown; // ����Ƿ����������
    bool m_AddOutLoop;
    bool m_AddInLoop;
    int m_MousePolygon;  // �������ƶ�������ָ��Ķ�����±�
    vec2 *m_MousePosition;  // �������ƶ�������ָ��ĵ�
    CEdgeLoop *m_MouseOnLoop; // �������ƶ�������ָ��Ļ�
    std::vector<vec2> m_AddPoint;
    double m_TriangluationTime, m_BoolOperationTime;
	
	CDC m_dcBuffer; // ˫����
    CPoint m_BasePoint; // ����ϵ����㣬��������¿հ״��϶�ʱ�ı�
    std::vector<CEdgeLoop> triangles; // ���ǻ�֮���������,����β����������CEdge���
    void Render(CDC* pDC); // ���ƺ���
    void RenderSingleObject(const CPolygon& polygon, int num); // ����һ�������
    void TriangulateAndPaint(CBooleanOperation2DDoc *pDoc); // �����ʷֲ�����������
    void PaintModifyingPoint(CBooleanOperation2DDoc *pDoc); // ѡ�к�Ӵ���ʾ
    void OverStriking(CBooleanOperation2DDoc *pDoc); // ����ƶ��мӴ���ʾ
    void ShowAddingLoop(CBooleanOperation2DDoc *pDoc); // ���Ӵ���ʾ
    void AutoFit(CBooleanOperation2DDoc *pDoc);

// ����
public:

// ��д
public:
	virtual void OnDraw(CDC* pDC);  // ��д�Ի��Ƹ���ͼ
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// ʵ��
public:
	virtual ~CBooleanOperation2DView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnSpinEdge();
	afx_msg void OnButtonOutloop1();
	afx_msg void OnButtonInnerloop1();
	afx_msg void OnButtonOutloop2();
	afx_msg void OnButtonInnerloop2();
	afx_msg void OnButtonDelete();
	afx_msg void OnButtonEmpty();
	afx_msg void OnButtonUnion();
	afx_msg void OnButtonInterset();
	afx_msg void OnButtonSubtract();
	afx_msg void OnButtonBack();
	afx_msg void OnCheckPoint();
	afx_msg void OnUpdateCheckPoint(CCmdUI *pCmdUI);
	afx_msg void OnCheckFill();
	afx_msg void OnUpdateCheckFill(CCmdUI *pCmdUI);
	afx_msg void OnCheckRegion();
	afx_msg void OnUpdateCheckRegion(CCmdUI *pCmdUI);
	afx_msg void OnCheckPolygon();
	afx_msg void OnUpdateCheckPolygon(CCmdUI *pCmdUI);
	afx_msg void OnCheckA();
	afx_msg void OnUpdateCheckA(CCmdUI *pCmdUI);
	afx_msg void OnCheckB();
	afx_msg void OnUpdateCheckB(CCmdUI *pCmdUI);
	afx_msg void OnCheckResult();
	afx_msg void OnUpdateCheckResult(CCmdUI *pCmdUI);
//	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
//	afx_msg void OnDestroy();
	afx_msg void OnSize(UINT nType, int cx, int cy);
//	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
//	afx_msg void OnMouseHWheel(UINT nFlags, short zDelta, CPoint pt);
//	afx_msg void OnTimer(UINT_PTR nIDEvent);
    afx_msg void OnCheckIndex();
    afx_msg void OnUpdateCheckIndex(CCmdUI *pCmdUI);
    afx_msg void OnButtonFit();
    afx_msg void OnButtonUnit();
    afx_msg BOOL OnEraseBkgnd(CDC* pDC);
    afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
};

#ifndef _DEBUG  // BooleanOperation2DView.cpp �еĵ��԰汾
inline CBooleanOperation2DDoc* CBooleanOperation2DView::GetDocument() const
   { return reinterpret_cast<CBooleanOperation2DDoc*>(m_pDocument); }
#endif

