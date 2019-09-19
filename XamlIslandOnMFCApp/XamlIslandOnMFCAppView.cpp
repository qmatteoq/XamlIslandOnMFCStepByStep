
// XamlIslandOnMFCAppView.cpp : implementation of the CXamlIslandOnMFCAppView class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "XamlIslandOnMFCApp.h"
#endif

#include "XamlIslandOnMFCAppDoc.h"
#include "XamlIslandOnMFCAppView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CXamlIslandOnMFCAppView

IMPLEMENT_DYNCREATE(CXamlIslandOnMFCAppView, CView)

BEGIN_MESSAGE_MAP(CXamlIslandOnMFCAppView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CXamlIslandOnMFCAppView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_CREATE()
	ON_WM_CLOSE()
END_MESSAGE_MAP()

// CXamlIslandOnMFCAppView construction/destruction

CXamlIslandOnMFCAppView::CXamlIslandOnMFCAppView() noexcept
{
	// TODO: add construction code here

}

CXamlIslandOnMFCAppView::~CXamlIslandOnMFCAppView()
{
}

BOOL CXamlIslandOnMFCAppView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CXamlIslandOnMFCAppView drawing

void CXamlIslandOnMFCAppView::OnDraw(CDC* /*pDC*/)
{
	CXamlIslandOnMFCAppDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here
}


// CXamlIslandOnMFCAppView printing


void CXamlIslandOnMFCAppView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CXamlIslandOnMFCAppView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CXamlIslandOnMFCAppView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CXamlIslandOnMFCAppView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void CXamlIslandOnMFCAppView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CXamlIslandOnMFCAppView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CXamlIslandOnMFCAppView diagnostics

#ifdef _DEBUG
void CXamlIslandOnMFCAppView::AssertValid() const
{
	CView::AssertValid();
}

void CXamlIslandOnMFCAppView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CXamlIslandOnMFCAppDoc* CXamlIslandOnMFCAppView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CXamlIslandOnMFCAppDoc)));
	return (CXamlIslandOnMFCAppDoc*)m_pDocument;
}
#endif //_DEBUG


// CXamlIslandOnMFCAppView message handlers


int CXamlIslandOnMFCAppView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	desktopSource = winrt::Windows::UI::Xaml::Hosting::DesktopWindowXamlSource{};
	auto interop = desktopSource.as<IDesktopWindowXamlSourceNative>();
	winrt::check_hresult(interop->AttachToWindow(this->GetSafeHwnd()));
	HWND xamlIslandHwnd;
	winrt::check_hresult(interop->get_WindowHandle(&xamlIslandHwnd));
	::SetWindowPos(xamlIslandHwnd, NULL, 10, 10, 510, 510, SWP_SHOWWINDOW); // resize the island to { x:10, y:10, width: 500(510 is cx), height:500(510 is cy) }.

	// Build UI using UWP controls.
	winrt::Windows::UI::Xaml::Controls::Grid root;
	winrt::Windows::UI::Xaml::Controls::TextBlock textBlock;
	textBlock.Text(L"Hello from XAML Island");
	textBlock.HorizontalAlignment(winrt::Windows::UI::Xaml::HorizontalAlignment::Center);
	textBlock.VerticalAlignment(winrt::Windows::UI::Xaml::VerticalAlignment::Center);
	root.Children().Append(textBlock);
	root.Measure(winrt::Windows::Foundation::Size{ 500, 500 });
	root.UpdateLayout();
	// set control to the island
	desktopSource.Content(root);
	return 0;
}

void CXamlIslandOnMFCAppView::OnClose()
{
	// Cleanup desktopSource
	desktopSource.Close();
	desktopSource = winrt::Windows::UI::Xaml::Hosting::DesktopWindowXamlSource{ nullptr };

	CView::OnClose();
}
