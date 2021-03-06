// SmartGisView.cpp : CSmartGisView 类的实现
//

#include "stdafx.h"
#include "SmartGis.h"

#include "SmartGisDoc.h"
#include "SmartGisView.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CSmartGisView

IMPLEMENT_DYNCREATE(CSmartGisView, CView)

BEGIN_MESSAGE_MAP(CSmartGisView, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)

	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_WM_SIZE()

	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_RBUTTONDOWN()
	ON_WM_SETCURSOR()
	ON_WM_ERASEBKGND()
	ON_WM_MOUSEWHEEL()
	ON_WM_KEYDOWN()
	ON_WM_CONTEXTMENU()

END_MESSAGE_MAP()

// CSmartGisView 构造/析构

CSmartGisView::CSmartGisView()
{
	// TODO: 在此处添加构造代码
}

CSmartGisView::~CSmartGisView()
{

}

BOOL CSmartGisView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CSmartGisView 绘制

void CSmartGisView::OnDraw(CDC* pDC)
{
	CSmartGisDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	// TODO: 在此处为本机数据添加绘制代码
}
// CSmartGisView 打印

BOOL CSmartGisView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CSmartGisView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CSmartGisView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清除过程
}


// CSmartGisView 诊断

#ifdef _DEBUG
void CSmartGisView::AssertValid() const
{
	CView::AssertValid();
}

void CSmartGisView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CSmartGisDoc* CSmartGisView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CSmartGisDoc)));
	return (CSmartGisDoc*)m_pDocument;
}
#endif //_DEBUG


// CSmartGisView 消息处理程序

void CSmartGisView::OnInitialUpdate()
{
	CView::OnInitialUpdate();
}

int CSmartGisView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  在此添加您专用的创建代码
	return 0;
}

void CSmartGisView::OnDestroy()
{
	CView::OnDestroy();

	// TODO: 在此处添加消息处理程序代码
}

void CSmartGisView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);

	// TODO: 在此处添加消息处理程序代码
}

void CSmartGisView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// Pass the message along
	CView::OnLButtonDown(nFlags, point);
} 


void CSmartGisView::OnMouseMove(UINT nFlags, CPoint point)
{
	// Pass the message along
	CView::OnMouseMove(nFlags, point);
} 

void CSmartGisView::OnLButtonUp (UINT nFlags, CPoint point)
{
	// Pass the message along
	CView::OnLButtonUp(nFlags, point);
} 


void CSmartGisView::OnRButtonDown(UINT nFlags, CPoint point)
{
	CView::OnRButtonDown(nFlags, point);
} 

BOOL CSmartGisView::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	return CView::OnMouseWheel(nFlags, zDelta, pt);
}

void CSmartGisView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}
BOOL CSmartGisView::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	return TRUE;
}

void CSmartGisView::OnContextMenu(CWnd*pWnd, CPoint point)
{
	// TODO: 在此处添加消息处理程序代码
}

BOOL CSmartGisView::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message)
{
	return TRUE;
} 

void CSmartGisView::OnPrepareDC(CDC* pDC, CPrintInfo* pInfo)
{
	// TODO: 在此添加专用代码和/或调用基类

	CView::OnPrepareDC(pDC, pInfo);
}