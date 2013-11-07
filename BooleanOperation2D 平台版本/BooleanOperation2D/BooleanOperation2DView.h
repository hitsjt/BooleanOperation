// 这段 MFC 示例源代码演示如何使用 MFC Microsoft Office Fluent 用户界面 
// (“Fluent UI”)。该示例仅供参考，
// 用以补充《Microsoft 基础类参考》和 
// MFC C++ 库软件随附的相关电子文档。
// 复制、使用或分发 Fluent UI 的许可条款是单独提供的。
// 若要了解有关 Fluent UI 许可计划的详细信息，请访问  
// http://go.microsoft.com/fwlink/?LinkId=238214。
//
// 版权所有(C) Microsoft Corporation
// 保留所有权利。

// BooleanOperation2DView.h : CBooleanOperation2DView 类的接口
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
protected: // 仅从序列化创建
	CBooleanOperation2DView();
	DECLARE_DYNCREATE(CBooleanOperation2DView)

// 特性
public:
	CBooleanOperation2DDoc* GetDocument() const;

public:
    vec2 m_MouseMoveStartPoint; // 左键按下时，移动的起点
    vec2 m_MousuMovePoint; // 左键按下时移动过程中的点
    bool m_isButtonDown; // 标记是否是左键按下
    bool m_AddOutLoop;
    bool m_AddInLoop;
    int m_MousePolygon;  // 标记鼠标移动过程中指向的多边形下标
    vec2 *m_MousePosition;  // 标记鼠标移动过程中指向的点
    CEdgeLoop *m_MouseOnLoop; // 标记鼠标移动过程中指向的环
    std::vector<vec2> m_AddPoint;
    double m_TriangluationTime, m_BoolOperationTime;
	
	CDC m_dcBuffer; // 双缓冲
    CPoint m_BasePoint; // 坐标系的起点，当左键按下空白处拖动时改变
    std::vector<CEdgeLoop> triangles; // 三角化之后的三角形,由首尾相连的三条CEdge组成
    void Render(CDC* pDC); // 绘制函数
    void RenderSingleObject(const CPolygon& polygon, int num); // 绘制一个多边形
    void TriangulateAndPaint(CBooleanOperation2DDoc *pDoc); // 三角剖分并绘制三角形
    void PaintModifyingPoint(CBooleanOperation2DDoc *pDoc); // 选中后加粗显示
    void OverStriking(CBooleanOperation2DDoc *pDoc); // 鼠标移动中加粗显示
    void ShowAddingLoop(CBooleanOperation2DDoc *pDoc); // 环加粗显示
    void AutoFit(CBooleanOperation2DDoc *pDoc);

// 操作
public:

// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 实现
public:
	virtual ~CBooleanOperation2DView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
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

#ifndef _DEBUG  // BooleanOperation2DView.cpp 中的调试版本
inline CBooleanOperation2DDoc* CBooleanOperation2DView::GetDocument() const
   { return reinterpret_cast<CBooleanOperation2DDoc*>(m_pDocument); }
#endif

