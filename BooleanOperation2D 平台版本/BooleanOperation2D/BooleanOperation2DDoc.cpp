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

// BooleanOperation2DDoc.cpp : CBooleanOperation2DDoc ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
#ifndef SHARED_HANDLERS
#include "BooleanOperation2D.h"
#endif

#include "BooleanOperation2DDoc.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CBooleanOperation2DDoc

IMPLEMENT_DYNCREATE(CBooleanOperation2DDoc, CDocument)

BEGIN_MESSAGE_MAP(CBooleanOperation2DDoc, CDocument)
END_MESSAGE_MAP()


// CBooleanOperation2DDoc ����/����

CBooleanOperation2DDoc::CBooleanOperation2DDoc()
{
	// TODO: �ڴ����һ���Թ������

}

CBooleanOperation2DDoc::~CBooleanOperation2DDoc()
{
}

BOOL CBooleanOperation2DDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: �ڴ�������³�ʼ������
	// (SDI �ĵ������ø��ĵ�)
    // �½����ڣ�������ж����
    std::vector<CPolygon>::iterator ite = allobjects.begin();
    int num = allobjects.size();
    for (int i = 0; i < num; i++)
        ite = allobjects.erase(ite);

    CConfig::is_modified = true; // �������ǻ�֮��˴���Ҫ����
    if (AfxGetMainWnd())
        SendMessage(AfxGetMainWnd()->m_hWnd, WM_UPDATE_STATUS_BAR, 0, (LPARAM)&allobjects);

	return TRUE;
}




// CBooleanOperation2DDoc ���л�

void CBooleanOperation2DDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())  // �ļ��洢
	{
		// TODO: �ڴ���Ӵ洢����
		if (allobjects.size() == 1)  // ���ֻ��һ������Σ��洢֮
			allobjects[0].Serialize(ar);
		else if (allobjects.size() == 3) // ������������洢�������������
			allobjects[2].Serialize(ar);
		else // �����������ѡ���ĸ����ĸ�
		{
			if (CConfig::ActiveObjectNumber != -1) // �洢��ǰѡ���Ķ����
				allobjects[CConfig::ActiveObjectNumber].Serialize(ar);
			else
				MessageBox(GetActiveWindow(), TEXT("��ѡ��һ��ģ��"), TEXT("��������"), MB_ICONQUESTION);
			return;
		}
	}//�洢��ʵ�����
	else // ʵ�ֶ�ȡ
	{
		// TODO: �ڴ���Ӽ��ش���
		if (allobjects.size() == 2) //�����������������Σ�����ʱ��Ҫɾȥһ��
		{
			int retval = MessageBox(GetActiveWindow(), TEXT("��֧��2������Ĳ������㣬�Ƿ��滻ģ��A��"), TEXT("ģ�͹���"), MB_ICONQUESTION | MB_YESNO);
			if (retval != IDYES)
				return;
			allobjects[0].Dispose(); // ɾ����һ������Σ��ڶ����Ƶ�λ��0
			allobjects[0].Serialize(ar);
		}
		else
		{
			if (allobjects.size() == 3) // ���겼������ʱ������������ڵ�2��λ�ã�����ٶ����µĶ���Σ������ǰ�������������ΪA
			{
				std::vector<CPolygon>::iterator ite = allobjects.begin();
				ite = allobjects.erase(ite);
				ite = allobjects.erase(ite);
			}
			CPolygon polygon; 
			polygon.Serialize(ar);
			/*           if (!Algorithms::CBooleanOperation::IsValid(polygon))
			{
				MessageBox(GetActiveWindow(), "�ļ��е���Ϣ���Ϸ���\r\n��˶����ݣ�", "���ݷǷ�", MB_YESNO);
				return;
			}
			*/ // ���ڶ���εĺϷ����жϻ�û��������ע�͵�
			allobjects.push_back(polygon);
        }
        CConfig::is_modified = true;
	}
	SendMessage(AfxGetMainWnd()->m_hWnd, WM_UPDATE_STATUS_BAR, 0, (LPARAM)&allobjects);
}

#ifdef SHARED_HANDLERS

// ����ͼ��֧��
void CBooleanOperation2DDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// �޸Ĵ˴����Ի����ĵ�����
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// ������������֧��
void CBooleanOperation2DDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// ���ĵ����������������ݡ�
	// ���ݲ���Ӧ�ɡ�;���ָ�

	// ����:  strSearchContent = _T("point;rectangle;circle;ole object;")��
	SetSearchContent(strSearchContent);
}

void CBooleanOperation2DDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = NULL;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != NULL)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CBooleanOperation2DDoc ���

#ifdef _DEBUG
void CBooleanOperation2DDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CBooleanOperation2DDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CBooleanOperation2DDoc ����
