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

// BooleanOperation2DDoc.cpp : CBooleanOperation2DDoc 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
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


// CBooleanOperation2DDoc 构造/析构

CBooleanOperation2DDoc::CBooleanOperation2DDoc()
{
	// TODO: 在此添加一次性构造代码

}

CBooleanOperation2DDoc::~CBooleanOperation2DDoc()
{
}

BOOL CBooleanOperation2DDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 在此添加重新初始化代码
	// (SDI 文档将重用该文档)
    // 新建窗口，清空所有多边形
    std::vector<CPolygon>::iterator ite = allobjects.begin();
    int num = allobjects.size();
    for (int i = 0; i < num; i++)
        ite = allobjects.erase(ite);

    CConfig::is_modified = true; // 加入三角化之后此处需要更新
    if (AfxGetMainWnd())
        SendMessage(AfxGetMainWnd()->m_hWnd, WM_UPDATE_STATUS_BAR, 0, (LPARAM)&allobjects);

	return TRUE;
}




// CBooleanOperation2DDoc 序列化

void CBooleanOperation2DDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())  // 文件存储
	{
		// TODO: 在此添加存储代码
		if (allobjects.size() == 1)  // 如果只有一个多边形，存储之
			allobjects[0].Serialize(ar);
		else if (allobjects.size() == 3) // 如果有三个，存储第三个，即结果
			allobjects[2].Serialize(ar);
		else // 如果有两个，选定哪个存哪个
		{
			if (CConfig::ActiveObjectNumber != -1) // 存储当前选定的多边形
				allobjects[CConfig::ActiveObjectNumber].Serialize(ar);
			else
				MessageBox(GetActiveWindow(), TEXT("请选择一个模型"), TEXT("操作错误"), MB_ICONQUESTION);
			return;
		}
	}//存储的实现完成
	else // 实现读取
	{
		// TODO: 在此添加加载代码
		if (allobjects.size() == 2) //如果现在有两个多边形，读入时就要删去一个
		{
			int retval = MessageBox(GetActiveWindow(), TEXT("仅支持2个形体的布尔运算，是否替换模型A？"), TEXT("模型过多"), MB_ICONQUESTION | MB_YESNO);
			if (retval != IDYES)
				return;
			allobjects[0].Dispose(); // 删除第一个多边形，第二个移到位置0
			allobjects[0].Serialize(ar);
		}
		else
		{
			if (allobjects.size() == 3) // 做完布尔运算时，将结果保存在第2个位置，如果再读入新的多边形，则擦除前两个，将结果作为A
			{
				std::vector<CPolygon>::iterator ite = allobjects.begin();
				ite = allobjects.erase(ite);
				ite = allobjects.erase(ite);
			}
			CPolygon polygon; 
			polygon.Serialize(ar);
			/*           if (!Algorithms::CBooleanOperation::IsValid(polygon))
			{
				MessageBox(GetActiveWindow(), "文件中的信息不合法！\r\n请核对数据！", "数据非法", MB_YESNO);
				return;
			}
			*/ // 现在多边形的合法性判断还没有做，先注释掉
			allobjects.push_back(polygon);
        }
        CConfig::is_modified = true;
	}
	SendMessage(AfxGetMainWnd()->m_hWnd, WM_UPDATE_STATUS_BAR, 0, (LPARAM)&allobjects);
}

#ifdef SHARED_HANDLERS

// 缩略图的支持
void CBooleanOperation2DDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// 修改此代码以绘制文档数据
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

// 搜索处理程序的支持
void CBooleanOperation2DDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// 从文档数据设置搜索内容。
	// 内容部分应由“;”分隔

	// 例如:  strSearchContent = _T("point;rectangle;circle;ole object;")；
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

// CBooleanOperation2DDoc 诊断

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


// CBooleanOperation2DDoc 命令
