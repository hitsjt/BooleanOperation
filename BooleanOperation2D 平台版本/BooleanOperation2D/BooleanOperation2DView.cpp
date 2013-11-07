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

// BooleanOperation2DView.cpp : CBooleanOperation2DView ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
#ifndef SHARED_HANDLERS
#include "BooleanOperation2D.h"
#endif

#include "BooleanOperation2DDoc.h"
#include "BooleanOperation2DView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CBooleanOperation2DView

IMPLEMENT_DYNCREATE(CBooleanOperation2DView, CView)

BEGIN_MESSAGE_MAP(CBooleanOperation2DView, CView)
	// ��׼��ӡ����
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CBooleanOperation2DView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_COMMAND(ID_SPIN_EDGE, &CBooleanOperation2DView::OnSpinEdge)
	ON_COMMAND(ID_BUTTON_OUTLOOP1, &CBooleanOperation2DView::OnButtonOutloop1)
	ON_COMMAND(ID_BUTTON_INNERLOOP1, &CBooleanOperation2DView::OnButtonInnerloop1)
	ON_COMMAND(ID_BUTTON_OUTLOOP2, &CBooleanOperation2DView::OnButtonOutloop2)
	ON_COMMAND(ID_BUTTON_INNERLOOP2, &CBooleanOperation2DView::OnButtonInnerloop2)
	ON_COMMAND(ID_BUTTON_DELETE, &CBooleanOperation2DView::OnButtonDelete)
	ON_COMMAND(ID_BUTTON_EMPTY, &CBooleanOperation2DView::OnButtonEmpty)
	ON_COMMAND(ID_BUTTON_UNION, &CBooleanOperation2DView::OnButtonUnion)
	ON_COMMAND(ID_BUTTON_INTERSET, &CBooleanOperation2DView::OnButtonInterset)
	ON_COMMAND(ID_BUTTON_SUBTRACT, &CBooleanOperation2DView::OnButtonSubtract)
	ON_COMMAND(ID_BUTTON_BACK, &CBooleanOperation2DView::OnButtonBack)
	ON_COMMAND(ID_CHECK_POINT, &CBooleanOperation2DView::OnCheckPoint)
	ON_UPDATE_COMMAND_UI(ID_CHECK_POINT, &CBooleanOperation2DView::OnUpdateCheckPoint)
	ON_COMMAND(ID_CHECK_FILL, &CBooleanOperation2DView::OnCheckFill)
	ON_UPDATE_COMMAND_UI(ID_CHECK_FILL, &CBooleanOperation2DView::OnUpdateCheckFill)
	ON_COMMAND(ID_CHECK_REGION, &CBooleanOperation2DView::OnCheckRegion)
	ON_UPDATE_COMMAND_UI(ID_CHECK_REGION, &CBooleanOperation2DView::OnUpdateCheckRegion)
	ON_COMMAND(ID_CHECK_POLYGON, &CBooleanOperation2DView::OnCheckPolygon)
	ON_UPDATE_COMMAND_UI(ID_CHECK_POLYGON, &CBooleanOperation2DView::OnUpdateCheckPolygon)
	ON_COMMAND(ID_CHECK_A, &CBooleanOperation2DView::OnCheckA)
	ON_UPDATE_COMMAND_UI(ID_CHECK_A, &CBooleanOperation2DView::OnUpdateCheckA)
	ON_COMMAND(ID_CHECK_B, &CBooleanOperation2DView::OnCheckB)
	ON_UPDATE_COMMAND_UI(ID_CHECK_B, &CBooleanOperation2DView::OnUpdateCheckB)
	ON_COMMAND(ID_CHECK_RESULT, &CBooleanOperation2DView::OnCheckResult)
	ON_UPDATE_COMMAND_UI(ID_CHECK_RESULT, &CBooleanOperation2DView::OnUpdateCheckResult)
	ON_WM_SIZE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
//	ON_WM_MOUSEHWHEEL()
    ON_COMMAND(ID_CHECK_INDEX, &CBooleanOperation2DView::OnCheckIndex)
    ON_UPDATE_COMMAND_UI(ID_CHECK_INDEX, &CBooleanOperation2DView::OnUpdateCheckIndex)
    ON_COMMAND(ID_BUTTON_FIT, &CBooleanOperation2DView::OnButtonFit)
    ON_COMMAND(ID_BUTTON_UNIT, &CBooleanOperation2DView::OnButtonUnit)
    ON_WM_ERASEBKGND()
    ON_WM_MOUSEWHEEL()
END_MESSAGE_MAP()

// CBooleanOperation2DView ����/����

CBooleanOperation2DView::CBooleanOperation2DView()
    : m_isButtonDown(false)
	, m_MouseOnLoop(nullptr)
	, m_MousePosition(nullptr)
	, m_BasePoint(0, 0)
	, m_AddOutLoop(false)
	, m_AddInLoop(false)
	, m_MousePolygon(-1)
	, m_TriangluationTime(0.0)
	, m_BoolOperationTime(0.0)
{
	// TODO: �ڴ˴���ӹ������

}

CBooleanOperation2DView::~CBooleanOperation2DView()
{
}

BOOL CBooleanOperation2DView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CView::PreCreateWindow(cs);
}

// CBooleanOperation2DView ����

void CBooleanOperation2DView::OnDraw(CDC* pDC)
{
	CBooleanOperation2DDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: �ڴ˴�Ϊ����������ӻ��ƴ���
	Render(pDC);
}


// CBooleanOperation2DView ��ӡ


void CBooleanOperation2DView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CBooleanOperation2DView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void CBooleanOperation2DView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
}

void CBooleanOperation2DView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӵ�ӡ����е��������
}

void CBooleanOperation2DView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
    CBooleanOperation2DDoc* pDoc = GetDocument();
    ASSERT_VALID(pDoc);
    if (!pDoc)
        return;

    if (!m_AddOutLoop && !m_AddInLoop || m_AddPoint.size() < 3)
        return;

    CEdgeLoop add_loop;
    for (unsigned int i = 0; i < m_AddPoint.size() - 1; i++)
    {
        CEdge edge(m_AddPoint[i], m_AddPoint[i + 1]);
        add_loop.Edges.push_back(edge);
    }
    CEdge edge(m_AddPoint[m_AddPoint.size() - 1], m_AddPoint[0]);
    add_loop.Edges.push_back(edge);
    add_loop.Commit();

    if (m_AddOutLoop) // ��ӵ���һ���⻷
    {
        if (CConfig::ActiveObjectNumber != -1) // ѡ����һ������Σ�Ϊ�˶�������һ��Region
        {
            CRegion region;
            region.OuterLoops = add_loop;
            region.Commit();
            CPolygon polygon = pDoc->allobjects[CConfig::ActiveObjectNumber];
            polygon.Regions.push_back(region);
            polygon.Commit();
            if (!Algorithms::CBooleanOperation::IsValid(polygon))
            {
                m_AddPoint.clear();
                m_AddOutLoop = false;
                MessageBox("����⻷֮�󣬶���β��Ϸ���\r\n��ע���⻷����ʱ��ġ�", "��������");
            }
            else
            {
                pDoc->allobjects[CConfig::ActiveObjectNumber].Regions.push_back(region);
                pDoc->allobjects[CConfig::ActiveObjectNumber].Commit();
                m_AddOutLoop = false;
                m_AddPoint.clear();
                CConfig::is_modified = true;
                CConfig::ActiveRegionNumber = pDoc->allobjects[CConfig::ActiveObjectNumber].Regions.size() -1 ;
                CConfig::ActiveLoopNumber = 0;
                Invalidate();
            }
        }
        else
        {
            CPolygon polygon;
            CRegion region;
            region.OuterLoops = add_loop;
            polygon.Regions.push_back(region);
            if (!Algorithms::CBooleanOperation::IsValid(polygon))
            {
                m_AddPoint.clear();
                m_AddOutLoop = false;
                MessageBox("����⻷֮�󣬶���β��Ϸ���\r\n��ע���⻷����ʱ��ģ�", "��������");
            }
            else
            {
                polygon.Commit();
                pDoc->allobjects.push_back(polygon);
                m_AddOutLoop = false;
                m_AddPoint.clear();
                CConfig::is_modified = true;
                CConfig::ActiveObjectNumber = pDoc->allobjects.size() - 1;
                CConfig::ActiveRegionNumber = 0;
                CConfig::ActiveLoopNumber = 0;
                Invalidate();
            }
        }
    }
    else // ��ӵ���һ���ڻ�
    {
        CPolygon polygon = pDoc->allobjects[CConfig::ActiveObjectNumber];
        polygon.Regions[CConfig::ActiveRegionNumber].InnerLoops.push_back(add_loop);

        if (!Algorithms::CBooleanOperation::IsValid(polygon))
        {
            m_AddPoint.clear();
            m_AddInLoop = false;
            MessageBox("����ڻ�֮�󣬶���β��Ϸ���\r\n��ע���ڻ���˳ʱ��ġ�", "��������");
        }
        else
        {
            pDoc->allobjects[CConfig::ActiveObjectNumber].Regions[CConfig::ActiveRegionNumber].InnerLoops.push_back(add_loop);
            pDoc->allobjects[CConfig::ActiveObjectNumber].Commit();
            m_AddInLoop = false;
            m_AddPoint.clear();
            CConfig::is_modified = true;
            CConfig::ActiveLoopNumber = pDoc->allobjects[CConfig::ActiveObjectNumber].Regions[CConfig::ActiveRegionNumber].InnerLoops.size();
            Invalidate();
        }
    }
    ::SendMessage(AfxGetMainWnd()->m_hWnd, WM_UPDATE_STATUS_BAR, 0, (LPARAM)&pDoc->allobjects);
}

void CBooleanOperation2DView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CBooleanOperation2DView ���

#ifdef _DEBUG
void CBooleanOperation2DView::AssertValid() const
{
	CView::AssertValid();
}

void CBooleanOperation2DView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CBooleanOperation2DDoc* CBooleanOperation2DView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CBooleanOperation2DDoc)));
	return (CBooleanOperation2DDoc*)m_pDocument;
}
#endif //_DEBUG


// CBooleanOperation2DView ��Ϣ�������


void CBooleanOperation2DView::OnSpinEdge()
{
    CString string;
    //��ȡRibbon bar ���
    CMFCRibbonBar* robbon_bar = 
        ((CFrameWndEx*)AfxGetMainWnd())->GetRibbonBar();
    if (robbon_bar==NULL)
        return;
    // ��ȡ�༭����
    CMFCRibbonEdit* slider = 
        (CMFCRibbonEdit*)robbon_bar->FindByID(ID_SPIN_EDGE);
    if (slider==NULL)
        return;
    string= slider->GetEditText(); // ��ȡ����
    int i = atoi(string);
    if (i<3)
        i = 3;
    if (i>20)
        i=20;
    CConfig::RegularPolygonEdgesCount = i;
    string.Format("%d", i);
    slider->SetEditText(string);
}

void CBooleanOperation2DView::OnButtonOutloop1()
{
	// TODO: �ڴ���������������
    CBooleanOperation2DDoc* pDoc = GetDocument();
    ASSERT_VALID(pDoc);
    if (!pDoc)
        return;

    if (!m_AddInLoop)
    {
        if (CConfig::ActiveObjectNumber == -1) // û��ѡ��һ�������,���һ���µĻ���Ϊһ���µĶ����
        {
            if (pDoc->allobjects.size() == 2)
            {
                int retval = MessageBox("��֧��2������Ĳ������㣬�Ƿ�ȥ����һ��ģ�ͣ�", "ģ�͹���", MB_YESNO);
                if (retval != IDYES)
                    return;
                std::vector<CPolygon>::iterator ite = pDoc->allobjects.begin();
                ite = pDoc->allobjects.erase(ite);
            }
            else
            {
                if (pDoc->allobjects.size() == 3) // ���겼������ʱ������������ڵ�2��λ�ã�����ٶ����µĶ���Σ������ǰ�������������ΪA
                {
                    int retval = MessageBox("��֧��2������Ĳ������㣡\r\n���ȷ��Ҫ����µĶ���Σ���ɾ���������������ԭʼͼ�Ρ�", "ģ�͹���", MB_YESNO);
                    if (retval != IDYES)
                        return;

                    std::vector<CPolygon>::iterator ite = pDoc->allobjects.begin();
                    ite = pDoc->allobjects.erase(ite);
                    ite = pDoc->allobjects.erase(ite);
                    if (ite->Regions.size() == 0) // �������������Ϊ�գ���Ҳɾȥ
                        ite = pDoc->allobjects.erase(ite);
                    CConfig::ShowResult =  false;
                    CConfig::ShowA = true;
                    CConfig::ShowB = true;
                }
            }
            CRect rect;
            GetClientRect(&rect);
            vec2 center((rect.left + rect.right) / 2, (rect.bottom + rect.top) / 2);
            CEdgeLoop edgeloop;
            double radius = abs(abs(rect.bottom - rect.top) - 200) / 2;
            double angle = DOUBLE_PI / CConfig::RegularPolygonEdgesCount;
            for (int k = 0; k < CConfig::RegularPolygonEdgesCount - 1; k++)
            {
                double point1x = center.x + cos(-angle * k) * radius;
                double point1y = center.y + sin(-angle * k) * radius;
                double point2x = center.x + cos(-angle * k - angle) * radius;
                double point2y = center.y + sin(-angle * k - angle) * radius;
                CEdge edge(vec2(point1x, point1y), vec2(point2x, point2y));
                edgeloop.Edges.push_back(edge);
            }
            double point1x = center.x + cos(angle) * radius;
            double point1y = center.y + sin(angle) * radius;
            double point2x = center.x + cos(0.0) * radius;
            double point2y = center.y + sin(0.0) * radius;
            CEdge edge(vec2(point1x, point1y), vec2(point2x, point2y));
            edgeloop.Edges.push_back(edge);

            CPolygon polygon;
            CRegion region;
            region.OuterLoops = edgeloop;
            polygon.Regions.push_back(region);
            polygon.Commit( );
            if (Algorithms::CBooleanOperation::IsValid(polygon))
            {
                pDoc->allobjects.push_back(polygon);
                CConfig::ActiveObjectNumber = pDoc->allobjects.size() - 1;
                CConfig::ActiveRegionNumber = 0;
                CConfig::ActiveLoopNumber = 0;
                edgeloop.Edges.clear();
            }
        }
        else  // ѡ��һ������Σ�Ϊѡ�еĶ�������һ������ֻ��һ���⻷
        {
            double maxx = pDoc->allobjects[CConfig::ActiveObjectNumber].Box.Max.x;
            double miny = pDoc->allobjects[CConfig::ActiveObjectNumber].Box.Min.y;

            CRect rect;
            GetClientRect(&rect);
            double x1 = rect.right - maxx;
            double y1 = miny - rect.top;

            vec2 center;
            double radius;
            if (x1 > y1)
            {
                center = vec2((maxx + rect.right) / 2, (rect.bottom + rect.top) / 2);
                radius = min(abs(abs(x1) - 50) / 2, abs((rect.bottom - rect.top) / 2 - 100));
            }
            else
            {
                center = vec2((rect.left + rect.right) / 2, (miny - rect.top) / 2);
                radius = min(abs(abs(y1) - 50) / 2, abs((rect.right - rect.left) / 2 - 100));
            }
            CEdgeLoop edgeloop;
            double angle = DOUBLE_PI / CConfig::RegularPolygonEdgesCount;
            for (int k = 0; k < CConfig::RegularPolygonEdgesCount - 1; k++)
            {
                double point1x = center.x + cos(-angle * k) * radius;
                double point1y = center.y + sin(-angle * k) * radius;
                double point2x = center.x + cos(-angle * k - angle) * radius;
                double point2y = center.y + sin(-angle * k - angle) * radius;
                CEdge edge(vec2(point1x, point1y), vec2(point2x, point2y));
                edgeloop.Edges.push_back(edge);
            }
            double point1x = center.x + cos(angle) * radius;
            double point1y = center.y + sin(angle) * radius;
            double point2x = center.x + cos(0.0) * radius;
            double point2y = center.y + sin(0.0) * radius;
            CEdge edge(vec2(point1x, point1y), vec2(point2x, point2y));
            edgeloop.Edges.push_back(edge);

            CPolygon polygon = pDoc->allobjects[CConfig::ActiveObjectNumber];
            CRegion region;
            region.OuterLoops = edgeloop;
            polygon.Regions.push_back(region);
            polygon.Commit( );

            if (Algorithms::CBooleanOperation::IsValid(polygon))
            {
                pDoc->allobjects[CConfig::ActiveObjectNumber].Regions.push_back(region);
                edgeloop.Edges.clear();
                CConfig::ActiveRegionNumber = pDoc->allobjects[CConfig::ActiveObjectNumber].Regions.size() - 1;
                CConfig::ActiveLoopNumber = 1;
            }
        }
        CConfig::is_modified = true;
        ::SendMessage(AfxGetMainWnd()->m_hWnd, WM_UPDATE_STATUS_BAR, 0, (LPARAM)&pDoc->allobjects);
        Invalidate();
    }
}

void CBooleanOperation2DView::OnButtonInnerloop1()
{
	// TODO: �ڴ���������������
    CBooleanOperation2DDoc* pDoc = GetDocument();
    ASSERT_VALID(pDoc);
    if (!pDoc)
        return;

    if (!m_AddOutLoop)
    {
        if (CConfig::ActiveObjectNumber == -1) // û��ѡ��һ�������
        {
            MessageBox("����ѡ��һ������ε�����", "��������");
            return;
        }
        else
        {
            CPolygon polygon = pDoc->allobjects[CConfig::ActiveObjectNumber];
            double minx = polygon.Regions[CConfig::ActiveRegionNumber].Box.Min.x;
            double miny = polygon.Regions[CConfig::ActiveRegionNumber].Box.Min.y;
            double maxx = polygon.Regions[CConfig::ActiveRegionNumber].Box.Max.x;
            double maxy = polygon.Regions[CConfig::ActiveRegionNumber].Box.Max.y;

            bool is_find = false;

            CEdgeLoop edgeloop;
            int radius = min((int)(abs(maxx - minx) / 2), (int)(abs(maxy - miny) / 2)) * 2 / 3;
            for (; radius >= 20; )
            {
                int times_x = (int)((maxx - minx) / 20);
                int times_y = (int)((maxy - miny) / 20);

                for (int i = 2; i < times_x - 1; i++)
                {
                    for (int j = 2; j < times_y - 1; j++)
                    {
                        vec2 center(minx + i * 20, miny + j * 20);
                        double angle = DOUBLE_PI / CConfig::RegularPolygonEdgesCount;
                        for (int k = 0; k < CConfig::RegularPolygonEdgesCount - 1; k++)
                        {
                            double point1x = center.x + cos(angle * k) * radius;
                            double point1y = center.y + sin(angle * k) * radius;
                            double point2x = center.x + cos(angle * k + angle) * radius;
                            double point2y = center.y + sin(angle * k + angle) * radius;
                            CEdge edge(vec2(point1x, point1y), vec2(point2x, point2y));
                            edgeloop.Edges.push_back(edge);
                        }
                        double point1x = center.x + cos(DOUBLE_PI - angle) * radius;
                        double point1y = center.y + sin(DOUBLE_PI - angle) * radius;
                        double point2x = center.x + cos(0.0) * radius;
                        double point2y = center.y + sin(0.0) * radius;
                        CEdge edge(vec2(point1x, point1y), vec2(point2x, point2y));
                        edgeloop.Edges.push_back(edge);

                        polygon.Regions[CConfig::ActiveRegionNumber].InnerLoops.push_back(edgeloop);
                        polygon.Commit( );
                        if (!Algorithms::CBooleanOperation::IsValid(polygon))
                        {
                            polygon = pDoc->allobjects[CConfig::ActiveObjectNumber];
                            edgeloop.Edges.clear();
                        }
                        else
                        {
                            is_find = true;
                            break;
                        }
                    }
                    if (is_find == true)
                        break;
                }
                if (is_find == true)
                    break;
                radius -= 20;
            }
            if (is_find == true)
            {
                pDoc->allobjects[CConfig::ActiveObjectNumber].Regions[CConfig::ActiveRegionNumber].InnerLoops.push_back(edgeloop);
                CConfig::ActiveLoopNumber = pDoc->allobjects[CConfig::ActiveObjectNumber].Regions[CConfig::ActiveRegionNumber].InnerLoops.size();
            }
            else
            {
                MessageBox("��Ǹ���㷨û���ҵ�һ�����ʵ�λ��Ϊ������ڻ���", "��������");
            }
        }
        CConfig::is_modified = true;
        ::SendMessage(AfxGetMainWnd()->m_hWnd, WM_UPDATE_STATUS_BAR, 0, (LPARAM)&pDoc->allobjects);
        Invalidate();
    }
}

void CBooleanOperation2DView::OnButtonOutloop2()
{
	// TODO: �ڴ���������������
    CBooleanOperation2DDoc* pDoc = GetDocument();
    ASSERT_VALID(pDoc);
    if (!pDoc)
        return;

    if (!m_AddInLoop)
    {
        if (CConfig::ActiveObjectNumber == -1) // û��ѡ��һ�������
        {
            if (pDoc->allobjects.size() == 2)
            {
                int retval = MessageBox("��֧��2������Ĳ������㣬�Ƿ�ȥ����һ��ģ�ͣ�", "ģ�͹���", MB_YESNO);
                if (retval != IDYES)
                    return;
                std::vector<CPolygon>::iterator ite = pDoc->allobjects.begin();
                ite = pDoc->allobjects.erase(ite);
            }
            else
            {
                if (pDoc->allobjects.size() == 3) // ���겼������ʱ������������ڵ�2��λ�ã�����ٶ����µĶ���Σ������ǰ�������������ΪA
                {
                    int retval = MessageBox("��֧��2������Ĳ������㣡\r\n���ȷ��Ҫ����µĶ���Σ���ɾ���������������ԭʼͼ�Ρ�", "ģ�͹���", MB_YESNO);
                    if (retval != IDYES)
                        return;

                    std::vector<CPolygon>::iterator ite = pDoc->allobjects.begin();
                    ite = pDoc->allobjects.erase(ite);
                    ite = pDoc->allobjects.erase(ite);
                    if (ite->Regions.size() == 0) // �������������Ϊ�գ���Ҳɾȥ
                        ite = pDoc->allobjects.erase(ite);
                    CConfig::ShowResult =  false;
                    CConfig::ShowA = true;
                    CConfig::ShowB = true;
                }
            }
        }
        else
        {
            CConfig::ActivePointNumber = -1;
            CConfig::ActiveLoopNumber = -1;
        }
        ::SendMessage(AfxGetMainWnd()->m_hWnd, WM_UPDATE_STATUS_BAR, 0, (LPARAM)&pDoc->allobjects);
        CConfig::is_modified = true;
        m_AddOutLoop = true;
    }
}

void CBooleanOperation2DView::OnButtonInnerloop2()
{
	// TODO: �ڴ���������������
    CBooleanOperation2DDoc* pDoc = GetDocument();
    ASSERT_VALID(pDoc);
    if (!pDoc)
        return;

    if (!m_AddOutLoop)
    {
        if (CConfig::ActiveObjectNumber == -1) // û��ѡ��һ�������
        {
            MessageBox("����ѡ��һ������ε�����", "��������");
            return;
        }
        else
        {
            CConfig::ActivePointNumber = -1;
            CConfig::ActiveEdgeNumber = -1;
            CConfig::ActiveLoopNumber = -1;
        }
        ::SendMessage(AfxGetMainWnd()->m_hWnd, WM_UPDATE_STATUS_BAR, 0, (LPARAM)&pDoc->allobjects);
        m_AddInLoop = true;
        CConfig::is_modified = true;
    }
}

void CBooleanOperation2DView::OnButtonDelete()
{
	// TODO: �ڴ���������������
    CBooleanOperation2DDoc* pDoc = GetDocument();
    ASSERT_VALID(pDoc);
    if (!pDoc)
        return;

    if (pDoc->allobjects.size() == 0)
        return;
    if (CConfig::ActiveLoopNumber != -1)
    {
        if (CConfig::SeletePolygon) // ɾ��һ�������
        {
            std::vector<CPolygon>::iterator ite = pDoc->allobjects.begin();
            for (int i = 0; i < CConfig::ActiveObjectNumber; i++)
                ite++;
            ite = pDoc->allobjects.erase(ite);
            CConfig::ActiveObjectNumber = CConfig::ActiveRegionNumber = CConfig::ActiveLoopNumber = CConfig::ActiveEdgeNumber = CConfig::ActivePointNumber = -1;
        }
        else if (CConfig::SeleteRegion) //��ɾ��һ������
        {
            if (pDoc->allobjects[CConfig::ActiveObjectNumber].Regions.size() == 1) // ɾ�����������
            {
                std::vector<CPolygon>::iterator ite = pDoc->allobjects.begin();
                for (int i = 0; i < CConfig::ActiveObjectNumber; i++)
                    ite++;
                ite = pDoc->allobjects.erase(ite);
                CConfig::ActiveObjectNumber = CConfig::ActiveRegionNumber = CConfig::ActiveLoopNumber = CConfig::ActiveEdgeNumber = CConfig::ActivePointNumber = -1;
            }
            else
            {
                std::vector<CRegion>::iterator ite = pDoc->allobjects[CConfig::ActiveObjectNumber].Regions.begin();
                for (int i = 0; i < CConfig::ActiveRegionNumber; i++)
                    ite++;
                ite = pDoc->allobjects[CConfig::ActiveObjectNumber].Regions.erase(ite);
                CConfig::ActiveRegionNumber = CConfig::ActiveLoopNumber = CConfig::ActiveEdgeNumber = CConfig::ActivePointNumber = -1;
            }
        }
        else // ɾ��һ����
        {
            if (CConfig::ActiveLoopNumber == 0) // �⻷���൱��ɾ���������
            {
                if (pDoc->allobjects[CConfig::ActiveObjectNumber].Regions.size() == 1) // ɾ�����������
                {
                    std::vector<CPolygon>::iterator ite = pDoc->allobjects.begin();
                    for (int i = 0; i < CConfig::ActiveObjectNumber; i++)
                        ite++;
                    ite = pDoc->allobjects.erase(ite);
                    CConfig::ActiveObjectNumber = CConfig::ActiveRegionNumber = CConfig::ActiveLoopNumber = CConfig::ActiveEdgeNumber = CConfig::ActivePointNumber = -1;
                }
                else // ɾ��������
                {
                    std::vector<CRegion>::iterator ite = pDoc->allobjects[CConfig::ActiveObjectNumber].Regions.begin();
                    for (int i = 0; i < CConfig::ActiveRegionNumber; i++)
                        ite++;
                    ite = pDoc->allobjects[CConfig::ActiveObjectNumber].Regions.erase(ite);
                    CConfig::ActiveRegionNumber = CConfig::ActiveLoopNumber = CConfig::ActiveEdgeNumber = CConfig::ActivePointNumber = -1;
                }
            }
            else // ɾ���ڻ�
            {
                std::vector<CEdgeLoop>::iterator ite = pDoc->allobjects[CConfig::ActiveObjectNumber].Regions[CConfig::ActiveRegionNumber].InnerLoops.begin();
                for (int i = 0; i < CConfig::ActiveLoopNumber - 1; i++)
                    ite++;
                ite = pDoc->allobjects[CConfig::ActiveObjectNumber].Regions[CConfig::ActiveRegionNumber].InnerLoops.erase(ite);
                CConfig::ActiveLoopNumber = CConfig::ActiveEdgeNumber = CConfig::ActivePointNumber = -1;
            }
        }
        CConfig::is_modified = true;
        ::SendMessage(AfxGetMainWnd()->m_hWnd, WM_UPDATE_STATUS_BAR, 0, (LPARAM)&pDoc->allobjects);

        Invalidate();
    }
    else
    {
        MessageBox("����ѡ��һ������ε�����", "��������");
    }
}

void CBooleanOperation2DView::OnButtonEmpty()
{
	// TODO: �ڴ���������������
    CBooleanOperation2DDoc* pDoc = GetDocument();
    ASSERT_VALID(pDoc);
    if (!pDoc)
        return;

    CConfig::ActiveObjectNumber = CConfig::ActiveRegionNumber = CConfig::ActiveLoopNumber = CConfig::ActiveEdgeNumber = CConfig::ActivePointNumber = -1;
    pDoc->OnNewDocument();
}

void CBooleanOperation2DView::OnButtonUnion()
{
	// TODO: �ڴ���������������
    CBooleanOperation2DDoc* pDoc = GetDocument();
    ASSERT_VALID(pDoc);
    if (!pDoc)
        return;

    if (pDoc->allobjects.size() < 2)
        return;
    CConfig::ActiveObjectNumber = CConfig::ActiveRegionNumber = CConfig::ActiveLoopNumber = CConfig::ActiveEdgeNumber = CConfig::ActivePointNumber = -1;

    clock_t clockBegin, clockEnd;
    clockBegin = clock();
    CPolygon polygon;
    Algorithms::CBooleanOperation::BooleanOperate(pDoc->allobjects[0], pDoc->allobjects[1], Algorithms::BooleanOperationType::BooleanUnion, polygon);
    clockEnd = clock();
    m_BoolOperationTime = clockEnd - clockBegin;

    if (pDoc->allobjects.size() == 3)
    {
        std::vector<CPolygon>::iterator ite = pDoc->allobjects.end();
        ite--;
        ite = pDoc->allobjects.erase(ite);
    }
    polygon.Commit( );

    pDoc->allobjects.push_back(polygon);
    CConfig::is_modified = true;
    CConfig::ShowResult =  true;
    CConfig::ShowA = false;
    CConfig::ShowB = false;
    ::SendMessage(AfxGetMainWnd()->m_hWnd, WM_UPDATE_STATUS_BAR, 0, (LPARAM)&pDoc->allobjects);
}

void CBooleanOperation2DView::OnButtonInterset()
{
	// TODO: �ڴ���������������
    CBooleanOperation2DDoc* pDoc = GetDocument();
    ASSERT_VALID(pDoc);
    if (!pDoc)
        return;
    if (pDoc->allobjects.size() < 2)
        return;

    CConfig::ActiveObjectNumber = CConfig::ActiveRegionNumber = CConfig::ActiveLoopNumber = CConfig::ActiveEdgeNumber = CConfig::ActivePointNumber = -1;

    clock_t clockBegin, clockEnd;
    clockBegin = clock();
    CPolygon polygon;
    Algorithms::CBooleanOperation::BooleanOperate(pDoc->allobjects[0], pDoc->allobjects[1], Algorithms::BooleanOperationType::BooleanIntersection, polygon);
    clockEnd = clock();
    m_BoolOperationTime = clockEnd - clockBegin;

    if (pDoc->allobjects.size() == 3)
    {
        std::vector<CPolygon>::iterator ite = pDoc->allobjects.end();
        ite--;
        ite = pDoc->allobjects.erase(ite);
    }
    polygon.Commit( );
    pDoc->allobjects.push_back(polygon);
    CConfig::is_modified = true;
    CConfig::ShowResult =  true;
    CConfig::ShowA = false;
    CConfig::ShowB = false;
    ::SendMessage(AfxGetMainWnd()->m_hWnd, WM_UPDATE_STATUS_BAR, 0, (LPARAM)&pDoc->allobjects);
}

void CBooleanOperation2DView::OnButtonSubtract()
{
	// TODO: �ڴ���������������
    CBooleanOperation2DDoc* pDoc = GetDocument();
    ASSERT_VALID(pDoc);
    if (!pDoc)
        return;
    if (pDoc->allobjects.size() < 2)
        return;

    CConfig::ActiveObjectNumber = CConfig::ActiveRegionNumber = CConfig::ActiveLoopNumber = CConfig::ActiveEdgeNumber = CConfig::ActivePointNumber = -1;

    clock_t clockBegin, clockEnd;
    clockBegin = clock();
    CPolygon polygon;
    Algorithms::CBooleanOperation::BooleanOperate(pDoc->allobjects[0], pDoc->allobjects[1], Algorithms::BooleanOperationType::BooleanDifference, polygon);
    clockEnd = clock();
    m_BoolOperationTime = clockEnd - clockBegin;

    if (pDoc->allobjects.size() == 3)
    {
        std::vector<CPolygon>::iterator ite = pDoc->allobjects.end();
        ite--;
        ite = pDoc->allobjects.erase(ite);
    }
    polygon.Commit( );
    pDoc->allobjects.push_back(polygon);
    CConfig::is_modified = true;
    CConfig::ShowResult =  true;
    CConfig::ShowA = false;
    CConfig::ShowB = false;
    ::SendMessage(AfxGetMainWnd()->m_hWnd, WM_UPDATE_STATUS_BAR, 0, (LPARAM)&pDoc->allobjects);
}

void CBooleanOperation2DView::OnButtonBack()
{
	// TODO: �ڴ���������������
    CBooleanOperation2DDoc* pDoc = GetDocument();
    ASSERT_VALID(pDoc);
    if (!pDoc)
        return;

    if (pDoc->allobjects.size() == 3)
    {
        std::vector<CPolygon>::iterator ite = pDoc->allobjects.end();
        ite --;
        ite = pDoc->allobjects.erase(ite);
        CConfig::is_modified = true;
        CConfig::ShowResult =  false;
        CConfig::ShowA = true;
        CConfig::ShowB = true;
        ::SendMessage(AfxGetMainWnd()->m_hWnd, WM_UPDATE_STATUS_BAR, 0, (LPARAM)&pDoc->allobjects);
    }
}

void CBooleanOperation2DView::OnCheckPoint()
{
    CConfig::RenderPoint ^= true; // ���֮��ֵ��ת
    if (!CConfig::RenderPoint)
        CConfig::ShowIndex = false;
    Invalidate(); // ˢ��
}

void CBooleanOperation2DView::OnUpdateCheckPoint(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
    pCmdUI->SetCheck(CConfig::RenderPoint); // ���ݹ���������ֵˢ�½���
}

void CBooleanOperation2DView::OnCheckFill()
{
	// TODO: �ڴ���������������
    CConfig::RenderFull ^= true;
    Invalidate(); // ˢ��
}

void CBooleanOperation2DView::OnUpdateCheckFill(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
    pCmdUI->SetCheck(CConfig::RenderFull);
}

void CBooleanOperation2DView::OnCheckRegion()
{
	// TODO: �ڴ���������������
    CConfig::SeleteRegion ^= true;
    if (CConfig::SeleteRegion)
        CConfig::SeletePolygon = false;
    Invalidate();
}

void CBooleanOperation2DView::OnUpdateCheckRegion(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
    pCmdUI->SetCheck(CConfig::SeleteRegion);
}

void CBooleanOperation2DView::OnCheckPolygon()
{
	// TODO: �ڴ���������������
    CConfig::SeletePolygon ^= true;
    if (CConfig::SeletePolygon)
        CConfig::SeleteRegion = false;
    Invalidate();
}

void CBooleanOperation2DView::OnUpdateCheckPolygon(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
    pCmdUI->SetCheck(CConfig::SeletePolygon);
}

void CBooleanOperation2DView::OnCheckA()
{
	// TODO: �ڴ���������������
    CConfig::ShowA ^= true;
    if (CConfig::RenderFull) // �����ʾ��Ƭ����Ҫ������ʾ
        CConfig::is_modified = true;
    Invalidate(); // ˢ��
}

void CBooleanOperation2DView::OnUpdateCheckA(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
    pCmdUI->SetCheck(CConfig::ShowA);
}

void CBooleanOperation2DView::OnCheckB()
{
	// TODO: �ڴ���������������
    CConfig::ShowB ^= true;
    if (CConfig::RenderFull) // �����ʾ��Ƭ����Ҫ������ʾ
        CConfig::is_modified = true;
    Invalidate(); // ˢ��
}

void CBooleanOperation2DView::OnUpdateCheckB(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
    pCmdUI->SetCheck(CConfig::ShowB);
}

void CBooleanOperation2DView::OnCheckResult()
{
	// TODO: �ڴ���������������
    CConfig::ShowResult ^= true;
    if (CConfig::RenderFull) // �����ʾ��Ƭ����Ҫ������ʾ
        CConfig::is_modified = true;
    Invalidate(); // ˢ��
}

void CBooleanOperation2DView::OnUpdateCheckResult(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
    pCmdUI->SetCheck(CConfig::ShowResult);
}

void CBooleanOperation2DView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);

	// TODO: �ڴ˴������Ϣ����������
    if (m_dcBuffer.m_hDC != NULL)
        m_dcBuffer.DeleteDC();
    CDC* pDC = GetDC();
    m_dcBuffer.CreateCompatibleDC(pDC);
    HBITMAP hBMP = CreateCompatibleBitmap(pDC->GetSafeHdc(), cx, cy);
    m_dcBuffer.SelectObject(hBMP);
    ReleaseDC(pDC);
}

void CBooleanOperation2DView::OnLButtonDown(UINT nFlags, CPoint point)
{
    CBooleanOperation2DDoc* pDoc = GetDocument();
    ASSERT_VALID(pDoc);
    if (!pDoc)
        return;

    if (m_AddInLoop || m_AddOutLoop)
        return;

    vec2 point1((point.x - m_BasePoint.x) / CConfig::EnlargementFactor,
                (point.y - m_BasePoint.y) / CConfig::EnlargementFactor);
    m_MouseMoveStartPoint = point1;
    m_MousuMovePoint = point1;
    // �жϵ�ǰ�����λ���Ƿ���ĳһ��������ϣ�����¼����Ρ����򡢱ߵ���ţ��Ա����
    bool is_point_find = false;
    if (pDoc->allobjects.size() == 3 && CConfig::ShowResult)  // ��������������������겼�����㣬������׽ǰ����
    {
        if (pDoc->allobjects[2].IsPointOn(point1, CConfig::ActiveRegionNumber, CConfig::ActiveLoopNumber, CConfig::ActiveEdgeNumber, CConfig::ActivePointNumber, Tolerance2))
        {
            CConfig::ActiveObjectNumber = 2;
            is_point_find = true;
        }
    }
    else
    {
        for (unsigned int i = 0; i < pDoc->allobjects.size(); i++)
        {
            if (i == 0 && CConfig::ShowA && pDoc->allobjects[i].IsPointOn(point1, CConfig::ActiveRegionNumber, CConfig::ActiveLoopNumber, CConfig::ActiveEdgeNumber, CConfig::ActivePointNumber, Tolerance2) ||
                i == 1 && CConfig::ShowB && pDoc->allobjects[i].IsPointOn(point1, CConfig::ActiveRegionNumber, CConfig::ActiveLoopNumber, CConfig::ActiveEdgeNumber, CConfig::ActivePointNumber, Tolerance2))
            {
                CConfig::ActiveObjectNumber = i;
                is_point_find = true;
                break;
            }
        }
    }
    if (is_point_find == false)
        CConfig::ActiveObjectNumber = -1;
    m_isButtonDown = true;

    Invalidate();
	CView::OnLButtonDown(nFlags, point);
}

void CBooleanOperation2DView::OnLButtonUp(UINT nFlags, CPoint point)
{
    m_isButtonDown = false;
    CBooleanOperation2DDoc* pDoc = GetDocument();
    ASSERT_VALID(pDoc);
    if (!pDoc)
        return;

    vec2 mouse_point((point.x - m_BasePoint.x) / CConfig::EnlargementFactor, 
                     (point.y - m_BasePoint.y) / CConfig::EnlargementFactor);
    if (m_AddInLoop || m_AddOutLoop)
    {
        m_AddPoint.push_back(mouse_point);
        Invalidate();
        return;
    }
    if (CConfig:: ActivePointNumber != -1 && CConfig::ActiveObjectNumber != -1) // ˵���ղ���ѡ���˵㲢�ƶ�
    {
        if (!Algorithms::CBooleanOperation::IsValid(pDoc->allobjects[CConfig::ActiveObjectNumber])) // �ƶ����Ϸ�������
        {
            MessageBox("�ƶ�����ǷǷ��ģ�", "��������");
            if (CConfig::ActiveLoopNumber == 0) // �����⻷��
            {
                if (CConfig:: ActivePointNumber == 0) // ���
                {
                    pDoc->allobjects[CConfig::ActiveObjectNumber].Regions[CConfig::ActiveRegionNumber].OuterLoops.Edges[CConfig::ActiveEdgeNumber].Start = m_MouseMoveStartPoint;
                    if (CConfig::ActiveEdgeNumber == 0)
                        pDoc->allobjects[CConfig::ActiveObjectNumber].Regions[CConfig::ActiveRegionNumber].OuterLoops.Edges[pDoc->allobjects[CConfig::ActiveObjectNumber].Regions[CConfig::ActiveRegionNumber].OuterLoops.Edges.size() - 1].End = m_MouseMoveStartPoint;
                    else
                        pDoc->allobjects[CConfig::ActiveObjectNumber].Regions[CConfig::ActiveRegionNumber].OuterLoops.Edges[CConfig::ActiveEdgeNumber - 1].End = m_MouseMoveStartPoint;
                }
                else if (CConfig:: ActivePointNumber == 1)
                {
                    pDoc->allobjects[CConfig::ActiveObjectNumber].Regions[CConfig::ActiveRegionNumber].OuterLoops.Edges[CConfig::ActiveEdgeNumber].End = m_MouseMoveStartPoint;
                    if (CConfig::ActiveEdgeNumber == (pDoc->allobjects[CConfig::ActiveObjectNumber].Regions[CConfig::ActiveRegionNumber].OuterLoops.Edges.size() - 1))
                        pDoc->allobjects[CConfig::ActiveObjectNumber].Regions[CConfig::ActiveRegionNumber].OuterLoops.Edges[0].Start = m_MouseMoveStartPoint;
                    else
                        pDoc->allobjects[CConfig::ActiveObjectNumber].Regions[CConfig::ActiveRegionNumber].OuterLoops.Edges[CConfig::ActiveEdgeNumber + 1].Start = m_MouseMoveStartPoint;
                }
            }
            else
            {
                if (CConfig:: ActivePointNumber == 0) // ���
                {
                    pDoc->allobjects[CConfig::ActiveObjectNumber].Regions[CConfig::ActiveRegionNumber].InnerLoops[CConfig::ActiveLoopNumber - 1].Edges[CConfig::ActiveEdgeNumber].Start = m_MouseMoveStartPoint;
                    if (CConfig::ActiveEdgeNumber == 0)
                        pDoc->allobjects[CConfig::ActiveObjectNumber].Regions[CConfig::ActiveRegionNumber].InnerLoops[CConfig::ActiveLoopNumber - 1].Edges[pDoc->allobjects[CConfig::ActiveObjectNumber].Regions[CConfig::ActiveRegionNumber].InnerLoops[CConfig::ActiveLoopNumber - 1].Edges.size() - 1].End = m_MouseMoveStartPoint;
                    else
                        pDoc->allobjects[CConfig::ActiveObjectNumber].Regions[CConfig::ActiveRegionNumber].InnerLoops[CConfig::ActiveLoopNumber - 1].Edges[CConfig::ActiveEdgeNumber - 1].End = m_MouseMoveStartPoint;
                }
                else if (CConfig:: ActivePointNumber == 1)
                {
                    pDoc->allobjects[CConfig::ActiveObjectNumber].Regions[CConfig::ActiveRegionNumber].InnerLoops[CConfig::ActiveLoopNumber - 1].Edges[CConfig::ActiveEdgeNumber].End = m_MouseMoveStartPoint;
                    if (CConfig::ActiveEdgeNumber == (pDoc->allobjects[CConfig::ActiveObjectNumber].Regions[CConfig::ActiveRegionNumber].InnerLoops[CConfig::ActiveLoopNumber - 1].Edges.size() - 1))
                        pDoc->allobjects[CConfig::ActiveObjectNumber].Regions[CConfig::ActiveRegionNumber].InnerLoops[CConfig::ActiveLoopNumber - 1].Edges[0].Start = m_MouseMoveStartPoint;
                    else
                        pDoc->allobjects[CConfig::ActiveObjectNumber].Regions[CConfig::ActiveRegionNumber].InnerLoops[CConfig::ActiveLoopNumber - 1].Edges[CConfig::ActiveEdgeNumber + 1].Start = m_MouseMoveStartPoint;
                }
            }
            CConfig::is_modified = true;
            pDoc->allobjects[CConfig::ActiveObjectNumber].Commit(); // ����Box
        }
    }
    else if (CConfig::ActiveLoopNumber != -1 && CConfig::ActiveObjectNumber != -1) // �ƶ�����������
    {
        if (!Algorithms::CBooleanOperation::IsValid(pDoc->allobjects[CConfig::ActiveObjectNumber])) // �ƶ����Ϸ�
        {
            MessageBox("�ƶ�����ǷǷ��ģ�", "��������");
            vec2 direction = (m_MouseMoveStartPoint - mouse_point);
            if (CConfig::SeletePolygon)
                pDoc->allobjects[CConfig::ActiveObjectNumber].Move(direction);
            else if (CConfig::SeleteRegion)
                pDoc->allobjects[CConfig::ActiveObjectNumber].Regions[CConfig::ActiveRegionNumber].Move(direction);
            else
            {
                if (CConfig::ActiveLoopNumber == 0)
                    pDoc->allobjects[CConfig::ActiveObjectNumber].Regions[CConfig::ActiveRegionNumber].OuterLoops.Move(direction);
                else
                    pDoc->allobjects[CConfig::ActiveObjectNumber].Regions[CConfig::ActiveRegionNumber].InnerLoops[CConfig::ActiveLoopNumber - 1].Move(direction);
            }
            CConfig::is_modified = true;
            pDoc->allobjects[CConfig::ActiveObjectNumber].Commit(); // ����Box
        }
    }
    Invalidate();
 
	CView::OnLButtonUp(nFlags, point);
}

void CBooleanOperation2DView::OnMouseMove(UINT nFlags, CPoint point)
{
    CBooleanOperation2DDoc* pDoc = GetDocument();
    ASSERT_VALID(pDoc);
    if (!pDoc)
        return;

    if (m_AddInLoop || m_AddOutLoop)
        return;
    vec2 mouse_point((point.x - m_BasePoint.x) / CConfig::EnlargementFactor, (point.y - m_BasePoint.y) / CConfig::EnlargementFactor);
    if (m_isButtonDown) // ����ǰ�������϶�
    {
        // ����֮ǰѡ�����ǵ㣬�ƶ��㣬�޸���������
        if (CConfig::ActivePointNumber != -1 && ((CConfig::ActiveObjectNumber == 0 && CConfig::ShowA) || (CConfig::ActiveObjectNumber == 1 && CConfig::ShowB) || (CConfig::ActiveObjectNumber == 2 && CConfig::ShowResult)))
        {
            if (CConfig::ActiveLoopNumber == 0) // �����⻷��
            {
                if (CConfig:: ActivePointNumber== 0) // ���
                {
                    pDoc->allobjects[CConfig::ActiveObjectNumber].Regions[CConfig::ActiveRegionNumber].OuterLoops.Edges[CConfig::ActiveEdgeNumber].Start = mouse_point;
                    if (CConfig::ActiveEdgeNumber == 0)
                        pDoc->allobjects[CConfig::ActiveObjectNumber].Regions[CConfig::ActiveRegionNumber].OuterLoops.Edges[pDoc->allobjects[CConfig::ActiveObjectNumber].Regions[CConfig::ActiveRegionNumber].OuterLoops.Edges.size() - 1].End = mouse_point;
                    else
                        pDoc->allobjects[CConfig::ActiveObjectNumber].Regions[CConfig::ActiveRegionNumber].OuterLoops.Edges[CConfig::ActiveEdgeNumber - 1].End = mouse_point;
                }
                else if (CConfig:: ActivePointNumber== 1)// �յ�
                {
                    pDoc->allobjects[CConfig::ActiveObjectNumber].Regions[CConfig::ActiveRegionNumber].OuterLoops.Edges[CConfig::ActiveEdgeNumber].End = mouse_point;
                    if (CConfig::ActiveEdgeNumber == (pDoc->allobjects[CConfig::ActiveObjectNumber].Regions[CConfig::ActiveRegionNumber].OuterLoops.Edges.size() - 1))
                        pDoc->allobjects[CConfig::ActiveObjectNumber].Regions[CConfig::ActiveRegionNumber].OuterLoops.Edges[0].Start = mouse_point;
                    else
                        pDoc->allobjects[CConfig::ActiveObjectNumber].Regions[CConfig::ActiveRegionNumber].OuterLoops.Edges[CConfig::ActiveEdgeNumber + 1].Start = mouse_point;
                }
            }
            else // �����ڻ���
            {
                if (CConfig:: ActivePointNumber== 0) // ���
                {
                    pDoc->allobjects[CConfig::ActiveObjectNumber].Regions[CConfig::ActiveRegionNumber].InnerLoops[CConfig::ActiveLoopNumber - 1].Edges[CConfig::ActiveEdgeNumber].Start = mouse_point;
                    if (CConfig::ActiveEdgeNumber == 0)
                        pDoc->allobjects[CConfig::ActiveObjectNumber].Regions[CConfig::ActiveRegionNumber].InnerLoops[CConfig::ActiveLoopNumber - 1].Edges[pDoc->allobjects[CConfig::ActiveObjectNumber].Regions[CConfig::ActiveRegionNumber].InnerLoops[CConfig::ActiveLoopNumber - 1].Edges.size() - 1].End = mouse_point;
                    else
                        pDoc->allobjects[CConfig::ActiveObjectNumber].Regions[CConfig::ActiveRegionNumber].InnerLoops[CConfig::ActiveLoopNumber - 1].Edges[CConfig::ActiveEdgeNumber - 1].End = mouse_point;
                }
                else if (CConfig:: ActivePointNumber== 1)// �յ�
                {
                    pDoc->allobjects[CConfig::ActiveObjectNumber].Regions[CConfig::ActiveRegionNumber].InnerLoops[CConfig::ActiveLoopNumber - 1].Edges[CConfig::ActiveEdgeNumber].End = mouse_point;
                    if (CConfig::ActiveEdgeNumber == (pDoc->allobjects[CConfig::ActiveObjectNumber].Regions[CConfig::ActiveRegionNumber].InnerLoops[CConfig::ActiveLoopNumber - 1].Edges.size() - 1))
                        pDoc->allobjects[CConfig::ActiveObjectNumber].Regions[CConfig::ActiveRegionNumber].InnerLoops[CConfig::ActiveLoopNumber - 1].Edges[0].Start = mouse_point;
                    else
                        pDoc->allobjects[CConfig::ActiveObjectNumber].Regions[CConfig::ActiveRegionNumber].InnerLoops[CConfig::ActiveLoopNumber - 1].Edges[CConfig::ActiveEdgeNumber + 1].Start = mouse_point;
                }
            }
            CConfig::is_modified = true;
            pDoc->allobjects[CConfig::ActiveObjectNumber].Commit(); // ����Box
        }
        else if (CConfig::ActiveLoopNumber != -1 && ((CConfig::ActiveObjectNumber == 0 && CConfig::ShowA) || (CConfig::ActiveObjectNumber == 1 && CConfig::ShowB) || (CConfig::ActiveObjectNumber == 2 && CConfig::ShowResult)))
        { // ����һ��ѡ����ĳ������ε�ĳ�������ƶ�
            vec2 direction = (mouse_point - m_MousuMovePoint);
            if (CConfig::SeletePolygon)
                pDoc->allobjects[CConfig::ActiveObjectNumber].Move(direction);
            else if (CConfig::SeleteRegion)
                pDoc->allobjects[CConfig::ActiveObjectNumber].Regions[CConfig::ActiveRegionNumber].Move(direction);
            else
            {
                if (CConfig::ActiveLoopNumber == 0)
                    pDoc->allobjects[CConfig::ActiveObjectNumber].Regions[CConfig::ActiveRegionNumber].OuterLoops.Move(direction);
                else
                    pDoc->allobjects[CConfig::ActiveObjectNumber].Regions[CConfig::ActiveRegionNumber].InnerLoops[CConfig::ActiveLoopNumber - 1].Move(direction);
            }
            m_MousuMovePoint = mouse_point;
            CConfig::is_modified = true;
            pDoc->allobjects[CConfig::ActiveObjectNumber].Commit(); // ����Box
        }
        else// ʲôҲû��ѡ�У������ƶ�
        {
            vec2 direction = mouse_point - m_MouseMoveStartPoint;
            m_BasePoint.x += (int)(direction.x * CConfig::EnlargementFactor);
            m_BasePoint.y += (int)(direction.y * CConfig::EnlargementFactor);
        }
        m_MousePolygon = -1;
        m_MouseOnLoop = nullptr;
        m_MousePosition = nullptr;
        Invalidate();
    }
    else // û��Ŀ�걻ѡ�У����ƶ������м������Ƿ�ָ��ĳ�������ǵĻ�����Ӵ�
    {
        int a = -1, b = -1, c = -1, d = -1, e = -1;
        for (unsigned int i = 0; i < pDoc->allobjects.size(); i++)
        {
            if ((i == 0 && CConfig::ShowA) || (i == 1 && CConfig::ShowB) || (i == 2 && CConfig::ShowResult))
            {
                if (pDoc->allobjects[i].IsPointOn(mouse_point, a, b, c, d, Tolerance2))
                {
                    e = i;
                    break;
                }
            }
        }
        if ((e == 0 && CConfig::ShowA) || (e == 1 && CConfig::ShowB) || (e == 2 && CConfig::ShowResult))
        {
            m_MousePolygon = e;
            m_MouseOnLoop = b == 0 ? &(pDoc->allobjects[e].Regions[a].OuterLoops) : &(pDoc->allobjects[e].Regions[a].InnerLoops[b - 1]);
            if (d != -1)
            {
                m_MousePosition = b==0 ? (d == 0 ? &(pDoc->allobjects[e].Regions[a].OuterLoops.Edges[c].Start) : &(pDoc->allobjects[e].Regions[a].OuterLoops.Edges[c].End)) :
                    (d == 0 ? &(pDoc->allobjects[e].Regions[a].InnerLoops[b - 1].Edges[c].Start) : &(pDoc->allobjects[e].Regions[a].InnerLoops[b - 1].Edges[c].End));
            }
            else
                m_MousePosition = nullptr;
            Invalidate();
        }
        else
        {
            if (m_MouseOnLoop != nullptr) // ���֮ǰ��Ϊ�գ�˵������ƶ���û��ָ��ĳ������Σ�ʲôҲ���������֮ǰ��Ϊ�գ����ڽ����գ���ȡ���Ӵ֣�����Ҫˢ��
            {
                m_MousePolygon = -1;
                m_MouseOnLoop = nullptr;
                m_MousePosition = nullptr;
                Invalidate();
            }
        }
    }

	CView::OnMouseMove(nFlags, point);
}


BOOL CBooleanOperation2DView::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
    // TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
    CConfig::EnlargementFactor += (zDelta * 0.001f);
    Invalidate();

    return CView::OnMouseWheel(nFlags, zDelta, pt);
}

// �ú����Ĺ����ǻ��ƴ���Ķ����
void CBooleanOperation2DView::RenderSingleObject(const CPolygon& polygon, int t)
{
    COLORREF inloopColor[3] = {RGB(0, 255, 0), RGB(0, 255, 255), RGB(255, 255, 50)};
    COLORREF outloopColor[3] ={RGB(255, 0, 0), RGB(255, 0, 255), RGB(0, 0, 0)};
    COLORREF pointColor(RGB(0, 0, 0));

    for (unsigned int i = 0; i < polygon.Regions.size(); i++)
    {
        for (unsigned int j = 0; j < polygon.Regions[i].InnerLoops.size() + 1; j++)
        {
            if (j == 0) // ���⻷
            {
                // ���⻷��
                CPen line_pen;
                CPen* penOld;
                if (CConfig::ActiveObjectNumber == t && ((CConfig::ActiveRegionNumber == i && (CConfig::ActiveLoopNumber == j || CConfig::SeleteRegion)) || CConfig::SeletePolygon))
                    line_pen.CreatePen(PS_SOLID, 6, outloopColor[t]);
                else
                    line_pen.CreatePen(PS_SOLID, 3, outloopColor[t]);
                penOld=(CPen*)m_dcBuffer.SelectObject(&line_pen);

                for (unsigned int k = 0; k < polygon.Regions[i].OuterLoops.Edges.size(); k++)
                {
                    int point_x = m_BasePoint.x + (int)(polygon.Regions[i].OuterLoops.Edges[k].Start.x * CConfig::EnlargementFactor);
                    int point_y = m_BasePoint.y + (int)(polygon.Regions[i].OuterLoops.Edges[k].Start.y * CConfig::EnlargementFactor);
                    m_dcBuffer.MoveTo(point_x, point_y);
                    point_x = m_BasePoint.x + (int)(polygon.Regions[i].OuterLoops.Edges[k].End.x * CConfig::EnlargementFactor);
                    point_y = m_BasePoint.y + (int)(polygon.Regions[i].OuterLoops.Edges[k].End.y * CConfig::EnlargementFactor);
                    m_dcBuffer.LineTo(point_x, point_y);
                }

                m_dcBuffer.SelectObject(penOld);
                // ���⻷��
                if (CConfig::RenderPoint == true)
                {
                    CPen point_pen(PS_SOLID, 3, pointColor);
                    CPen* penOld;
                    CBrush brush;
                    CBrush* brushOld;
                    brush.CreateSolidBrush(pointColor);
                    penOld=(CPen*)m_dcBuffer.SelectObject(&point_pen);
                    brushOld=(CBrush*)m_dcBuffer.SelectObject(&brush);
 	                for (unsigned int k = 0; k < polygon.Regions[i].OuterLoops.Edges.size(); k++)
                    {
                        int point_x = m_BasePoint.x + (int)(polygon.Regions[i].OuterLoops.Edges[k].Start.x * CConfig::EnlargementFactor);
                        int point_y = m_BasePoint.y + (int)(polygon.Regions[i].OuterLoops.Edges[k].Start.y * CConfig::EnlargementFactor);
                        CRect rect(point_x - 3, point_y + 3, point_x + 3, point_y - 3);
                        m_dcBuffer.Ellipse(&rect);
                        if (CConfig::ShowIndex)
                        {
                            CString textout;
                            textout.Format("R%dL0V%d", i, k);
                            m_dcBuffer.TextOutA(point_x, point_y, textout.GetString());
                        }
                    }
                    m_dcBuffer.SelectObject(brushOld);
                    m_dcBuffer.SelectObject(penOld);
                    brush.DeleteObject();
                }
                m_dcBuffer.SelectObject(penOld);
            }
            else
            {
                CPen line_pen;
                CPen* penOld;
                if (CConfig::ActiveObjectNumber == t && ((CConfig::ActiveRegionNumber == i && (CConfig::ActiveLoopNumber == j || CConfig::SeleteRegion)) || CConfig::SeletePolygon))
                    line_pen.CreatePen(PS_SOLID, 6, inloopColor[t]);
                else
                    line_pen.CreatePen(PS_SOLID, 3, inloopColor[t]);
                penOld=(CPen*)m_dcBuffer.SelectObject(&line_pen);
 	            // ���ڻ���
                for (unsigned int k = 0; k < polygon.Regions[i].InnerLoops[j - 1].Edges.size(); k++)
                {
                    int point_x = m_BasePoint.x + (int)(polygon.Regions[i].InnerLoops[j - 1].Edges[k].Start.x * CConfig::EnlargementFactor);
                    int point_y = m_BasePoint.y + (int)(polygon.Regions[i].InnerLoops[j - 1].Edges[k].Start.y * CConfig::EnlargementFactor);
                    m_dcBuffer.MoveTo(point_x, point_y);
                    point_x = m_BasePoint.x + (int)(polygon.Regions[i].InnerLoops[j - 1].Edges[k].End.x * CConfig::EnlargementFactor);
                    point_y = m_BasePoint.y + (int)(polygon.Regions[i].InnerLoops[j - 1].Edges[k].End.y * CConfig::EnlargementFactor);
                    m_dcBuffer.LineTo(point_x, point_y);
                }
                m_dcBuffer.SelectObject(penOld);
                // ���ڻ���
                if (CConfig::RenderPoint == true)
                {
                    CPen point_pen(PS_SOLID, 3, pointColor);
                    CPen* penOld;
                    CBrush brush;
                    CBrush * brushOld;
                    brush.CreateSolidBrush(pointColor);
                    penOld=(CPen*)m_dcBuffer.SelectObject(&point_pen);
                    brushOld=(CBrush *)m_dcBuffer.SelectObject(&brush);
                    for (unsigned int k = 0; k < polygon.Regions[i].InnerLoops[j - 1].Edges.size(); k++)
                    {
                        int point_x = m_BasePoint.x + (int)(polygon.Regions[i].InnerLoops[j - 1].Edges[k].Start.x * CConfig::EnlargementFactor);
                        int point_y = m_BasePoint.y + (int)(polygon.Regions[i].InnerLoops[j - 1].Edges[k].Start.y * CConfig::EnlargementFactor);
                        CRect rect(point_x - 3, point_y + 3, point_x + 3, point_y - 3);
                        m_dcBuffer.Ellipse(&rect);
                        if (CConfig::ShowIndex)
                        {
                            CString textout;
                            textout.Format("R%dI%dV%d", i, j, k);
                            m_dcBuffer.TextOutA(point_x, point_y, textout.GetString());
                        }
                    }
                    m_dcBuffer.SelectObject(brushOld);
                    m_dcBuffer.SelectObject(penOld);
                    brush.DeleteObject();
                }
            }
        }
    }
}


// �ú��������ǽ���Ļ��ƹ��ܣ�����OnDraw()����������
void CBooleanOperation2DView::Render(CDC* pDC)
{
    CBooleanOperation2DDoc* pDoc = GetDocument();
    ASSERT_VALID(pDoc);
    if (!pDoc)
        return;

    // ������
    CRect rc;
    m_dcBuffer.GetClipBox(&rc);
    CBrush br;
    br.CreateSolidBrush(RGB(255, 255, 255));
    CBrush* oldbr = (CBrush*)(m_dcBuffer.SelectObject(&br));
    m_dcBuffer.FillRect(&rc, &br);
    m_dcBuffer.SelectObject(oldbr);
    DeleteObject(br);

    // ���ǻ�����ʾ��Ƭ������������ڲ�
    TriangulateAndPaint(pDoc);

    int n = pDoc->allobjects.size( );
    if (n >= 1)
    {
        if (CConfig::ShowA)
            RenderSingleObject(pDoc->allobjects[0], 0);
        if (n >= 2)
        {
            if (CConfig::ShowB)
                RenderSingleObject(pDoc->allobjects[1], 1);
            if (n == 3)
            {
                if (CConfig::ShowResult)
                    RenderSingleObject(pDoc->allobjects[2], 2);
            }
        }
    }

    // �е㱻ѡ�У���ѡ������㲢�϶��޸ĵĹ��̣�
    if (CConfig::ActivePointNumber != -1)
        PaintModifyingPoint(pDoc);

    // ����ƶ������зŵ��˵���ĳһ������,����Ӵ���ʾ
    if (m_MouseOnLoop != nullptr)
        OverStriking(pDoc);

    // �ֶ���ӻ���ʱ����ʾ�ѻ����ı�
    if (m_AddInLoop || m_AddOutLoop)
        ShowAddingLoop(pDoc);

    // ��ʾ���ǻ���ʱ��
    CRect rect;
    GetClientRect(&rect);
    CString textout;
    textout.Format("���ǻ���ʱ��Ϊ��%.2lf ms.", m_TriangluationTime);
    m_dcBuffer.TextOutA(rect.right - 250, rect.top + 30, textout.GetString());
    textout.Format("��������ʱ��Ϊ��%.2lf ms.", m_BoolOperationTime);
    m_dcBuffer.TextOutA(rect.right - 250, rect.top + 50, textout.GetString());

	if(n >=1)
	{
		cf_drawBezier(m_dcBuffer,pDoc->allobjects[0],100,m_BasePoint,CConfig::EnlargementFactor);
	}

    // ��������Ԫ�ض����ú󣬽������е����ݻ�����
    pDC->BitBlt(0, 0, rect.right - rect.left, rect.bottom - rect.top, &m_dcBuffer, 0, 0, SRCCOPY);
}

void CBooleanOperation2DView::AutoFit(CBooleanOperation2DDoc *pDoc)
{
    CRect rect;
    GetClientRect(&rect);

    int left = rect.left;
    int right = rect.right;
    int top = rect.top;
    int bottom = rect.bottom;
    int n = pDoc->allobjects.size();
    if (n < 1)
        return;
    for (int i=0; i<n; i++)
        pDoc->allobjects[i].Commit( );
    CBoundingBox box;
    box = pDoc->allobjects[0].Box;
    if (pDoc->allobjects.size() >= 2)
        box.Union(pDoc->allobjects[1].Box);

    // ������������������û�п���0�����
    double factor_x = (right - left) / (box.Max.x - box.Min.x) * 3 / 4;
    double factor_y = (bottom - top) / (box.Max.y - box.Min.y) * 3 / 4;

    CConfig::EnlargementFactor = (float)min(factor_x, factor_y);
    m_BasePoint.x = (LONG)((right + left) / 2 - (box.Max.x + box.Min.x) / 2 * CConfig::EnlargementFactor);
    m_BasePoint.y = (LONG)((bottom + top) / 2 - (box.Max.y + box.Min.y) / 2 * CConfig::EnlargementFactor);
}

// ��objects�еĶ���ν��������ʷֲ�����
void CBooleanOperation2DView::TriangulateAndPaint(CBooleanOperation2DDoc *pDoc)
{
    COLORREF regionColor(RGB(255, 200, 200));

    // �ж��Ƿ��б��Ķ�������У���Ҫ�������ǻ�
    if (CConfig::RenderFull && CConfig::is_modified)
    {
        triangles.clear();
        clock_t clockBegin, clockEnd;
        clockBegin = clock();
        unsigned int t = 0;
        for (; t < pDoc->allobjects.size() && Algorithms::CBooleanOperation::IsValid(pDoc->allobjects[t]); t++)
        {
            if ((t == 0 && CConfig::ShowA) || (t == 1 && CConfig::ShowB) || (t == 2 && CConfig::ShowResult))
            {
                try
                {
                    for (unsigned int i = 0; i < pDoc->allobjects[t].Regions.size(); i++)
                        Algorithms::CTriangulation::Triangulate(triangles, pDoc->allobjects[t].Regions[i]);
                }
                catch (CException* e)
                {
                    delete e;
                    MessageBox("�ܱ�Ǹ��\r\n����������ǻ�ʱ�������⣡\r\n�����ĵ��ԣ�лл!", "�������");
                }
            }
        }
        clockEnd = clock();
        m_TriangluationTime = clockEnd - clockBegin;
        CConfig::is_modified = false;
    }
    // ���ǻ�֮����ʾ
    if (CConfig::RenderFull)
    {
        CPoint p[3];
        for (unsigned int i = 0; i < triangles.size(); i++)
        {
            p[0].x = m_BasePoint.x + (int)(triangles[i].Edges[0].Start.x * CConfig::EnlargementFactor);
            p[0].y = m_BasePoint.y + (int)(triangles[i].Edges[0].Start.y * CConfig::EnlargementFactor);
            p[1].x = m_BasePoint.x + (int)(triangles[i].Edges[1].Start.x * CConfig::EnlargementFactor);
            p[1].y = m_BasePoint.y + (int)(triangles[i].Edges[1].Start.y * CConfig::EnlargementFactor);
            p[2].x = m_BasePoint.x + (int)(triangles[i].Edges[2].Start.x * CConfig::EnlargementFactor);
            p[2].y = m_BasePoint.y + (int)(triangles[i].Edges[2].Start.y * CConfig::EnlargementFactor);

            CRgn rgn;
            CBrush brush(regionColor);
            rgn.CreatePolygonRgn(p, 3, ALTERNATE); 
            m_dcBuffer.FillRgn(&rgn, &brush); 
        }
    }
}

// ��������ѡ����ĳһ���㲢�ƶ�����ʱ����˵����ڵĶ���Ρ����򡢻��ı�ţ���Ҫ�ҵ�����㣬������Ŵ���ʾ��
void CBooleanOperation2DView::PaintModifyingPoint(CBooleanOperation2DDoc *pDoc)
{
    COLORREF pointColor(RGB(0, 0, 0));
    CPen point_pen(PS_SOLID, 3, pointColor);
    CBrush brush;
    brush.CreateSolidBrush(pointColor);
    m_dcBuffer.SelectObject(&point_pen);
    m_dcBuffer.SelectObject(&brush);

    vec2 point;

    // ������ڱ�ʰȡ���Ǹ�����β�����ʾ������ʾ��
    if (!((CConfig::ActiveObjectNumber == 0 && CConfig::ShowA) || (CConfig::ActiveObjectNumber == 1 && CConfig::ShowB) || (CConfig::ActiveObjectNumber == 2 && CConfig::ShowResult)))
        return;

    if (CConfig::ActiveLoopNumber == 0) // �����⻷��
    {
        if (CConfig:: ActivePointNumber == 0) // ���
            point = pDoc->allobjects[CConfig::ActiveObjectNumber].Regions[CConfig::ActiveRegionNumber].OuterLoops.Edges[CConfig::ActiveEdgeNumber].Start;
        else if (CConfig:: ActivePointNumber == 1)
            point = pDoc->allobjects[CConfig::ActiveObjectNumber].Regions[CConfig::ActiveRegionNumber].OuterLoops.Edges[CConfig::ActiveEdgeNumber].End;
    }
    else
    {
        if (CConfig:: ActivePointNumber == 0) // ���
            point = pDoc->allobjects[CConfig::ActiveObjectNumber].Regions[CConfig::ActiveRegionNumber].InnerLoops[CConfig::ActiveLoopNumber - 1].Edges[CConfig::ActiveEdgeNumber].Start;
        else if (CConfig:: ActivePointNumber== 1)
            point = pDoc->allobjects[CConfig::ActiveObjectNumber].Regions[CConfig::ActiveRegionNumber].InnerLoops[CConfig::ActiveLoopNumber - 1].Edges[CConfig::ActiveEdgeNumber].End;
    }

    int point_x = m_BasePoint.x + (int)(point.x * CConfig::EnlargementFactor);
    int point_y = m_BasePoint.y + (int)(point.y * CConfig::EnlargementFactor);
    CRect rect(point_x - 6, point_y + 6, point_x + 6, point_y - 6);
    m_dcBuffer.Ellipse(&rect);
}

// ����ƶ������зŵ��˵���ĳһ������,����Ӵ���ʾ
void CBooleanOperation2DView::OverStriking(CBooleanOperation2DDoc *pDoc)
{
    COLORREF inloopColor[3] = {RGB(0, 255, 0), RGB(0, 255, 255), RGB(255, 255, 50)};
    COLORREF outloopColor[3] ={RGB(255, 0, 0), RGB(255, 0, 255), RGB(0, 0, 0)};
    COLORREF pointColor(RGB(0, 0, 0));
    CPen line_pen;
    if (m_MouseOnLoop->Type == ELoopType::OuterLoop)
        line_pen.CreatePen(PS_SOLID, 6, outloopColor[m_MousePolygon]);
    else
        line_pen.CreatePen(PS_SOLID, 6, inloopColor[m_MousePolygon]);
    m_dcBuffer.SelectObject(&line_pen);
    for (unsigned int i = 0; i < m_MouseOnLoop->Edges.size(); i++)
    {
        int point_x = m_BasePoint.x + (int)(m_MouseOnLoop->Edges[i].Start.x * CConfig::EnlargementFactor);
        int point_y = m_BasePoint.y + (int)(m_MouseOnLoop->Edges[i].Start.y * CConfig::EnlargementFactor);
        m_dcBuffer.MoveTo(point_x, point_y);
        point_x = m_BasePoint.x + (int)(m_MouseOnLoop->Edges[i].End.x * CConfig::EnlargementFactor);
        point_y = m_BasePoint.y + (int)(m_MouseOnLoop->Edges[i].End.y * CConfig::EnlargementFactor);
        m_dcBuffer.LineTo(point_x, point_y);
    }

    if (m_MousePosition != nullptr) // ����ƶ������зŵ��˵���
    {
        CPen point_pen(PS_SOLID, 3, pointColor);
        CBrush brush;
        brush.CreateSolidBrush(pointColor);
        m_dcBuffer.SelectObject(&point_pen);
        m_dcBuffer.SelectObject(&brush);

        int point_x = m_BasePoint.x + (int)(m_MousePosition->x * CConfig::EnlargementFactor);
        int point_y = m_BasePoint.y + (int)(m_MousePosition->y * CConfig::EnlargementFactor);
        CRect rect(point_x - 6, point_y + 6, point_x + 6, point_y - 6);
        m_dcBuffer.Ellipse(&rect);
    }
}

// �ֶ���Ӷ����ʱ��ʾһ��δ����Ļ�
void CBooleanOperation2DView::ShowAddingLoop(CBooleanOperation2DDoc *pDoc)
{
    COLORREF inloopColor[3] = {RGB(0, 255, 0), RGB(0, 255, 255), RGB(0, 0, 0)};
    COLORREF outloopColor[3] ={RGB(255, 0, 0), RGB(255, 0, 255), RGB(0, 0, 0)};
    COLORREF pointColor(RGB(0, 0, 0));

    CPen line_pen;
    if (m_AddOutLoop)
    {
        if (CConfig::ActiveObjectNumber != -1)
            line_pen.CreatePen(PS_SOLID, 6, outloopColor[CConfig::ActiveObjectNumber]);
        else
            line_pen.CreatePen(PS_SOLID, 6, outloopColor[pDoc->allobjects.size()]);
    }
    else
        line_pen.CreatePen(PS_SOLID, 6, inloopColor[CConfig::ActiveObjectNumber]);
    m_dcBuffer.SelectObject(&line_pen);

    for (unsigned int i = 0; m_AddPoint.size() > 1 && i < m_AddPoint.size() - 1; i++)
    {
        int point_x = m_BasePoint.x + (int)(m_AddPoint[i].x * CConfig::EnlargementFactor);
        int point_y = m_BasePoint.y + (int)(m_AddPoint[i].y * CConfig::EnlargementFactor);
        m_dcBuffer.MoveTo(point_x, point_y);
        point_x = m_BasePoint.x + (int)(m_AddPoint[i + 1].x * CConfig::EnlargementFactor);
        point_y = m_BasePoint.y + (int)(m_AddPoint[i + 1].y * CConfig::EnlargementFactor);
        m_dcBuffer.LineTo(point_x, point_y);
    }

    CPen point_pen(PS_SOLID, 3, pointColor);
    CBrush brush;
    brush.CreateSolidBrush(pointColor);
    m_dcBuffer.SelectObject(&point_pen);
    m_dcBuffer.SelectObject(&brush);
    for (unsigned int i = 0; i < m_AddPoint.size(); i++)
    {
        int point_x = m_BasePoint.x + (int)(m_AddPoint[i].x * CConfig::EnlargementFactor);
        int point_y = m_BasePoint.y + (int)(m_AddPoint[i].y * CConfig::EnlargementFactor);
        CRect rect(point_x - 3, point_y + 3, point_x + 3, point_y - 3);
        m_dcBuffer.Ellipse(&rect);
    }
}


void CBooleanOperation2DView::OnCheckIndex()
{
    // TODO: �ڴ���������������
    CConfig::ShowIndex ^= true;
    Invalidate(); // ˢ��
}


void CBooleanOperation2DView::OnUpdateCheckIndex(CCmdUI *pCmdUI)
{
    // TODO: �ڴ������������û����洦��������
    pCmdUI->SetCheck(CConfig::ShowIndex);
}


void CBooleanOperation2DView::OnButtonFit()
{
    // TODO: �ڴ���������������
    CBooleanOperation2DDoc* pDoc = GetDocument();
    ASSERT_VALID(pDoc);
    if (!pDoc)
        return;
    AutoFit(pDoc);
    Invalidate();
}


void CBooleanOperation2DView::OnButtonUnit()
{
    // TODO: �ڴ���������������
    CConfig::EnlargementFactor = 1.0f;
    m_BasePoint.x = 0;
    m_BasePoint.y = 0;
    Invalidate();
}


BOOL CBooleanOperation2DView::OnEraseBkgnd(CDC* pDC)
{
    // TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

//     return CView::OnEraseBkgnd(pDC);
    return true;
}
