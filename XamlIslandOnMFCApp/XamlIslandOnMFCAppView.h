
// XamlIslandOnMFCAppView.h : interface of the CXamlIslandOnMFCAppView class
//

#pragma once


class CXamlIslandOnMFCAppView : public CView
{
protected: // create from serialization only
	CXamlIslandOnMFCAppView() noexcept;
	DECLARE_DYNCREATE(CXamlIslandOnMFCAppView)

// Attributes
public:
	CXamlIslandOnMFCAppDoc* GetDocument() const;

// Operations
public:

private:
	winrt::Windows::UI::Xaml::Hosting::DesktopWindowXamlSource desktopSource = winrt::Windows::UI::Xaml::Hosting::DesktopWindowXamlSource{ nullptr };


// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Implementation
public:
	virtual ~CXamlIslandOnMFCAppView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnClose();
};

#ifndef _DEBUG  // debug version in XamlIslandOnMFCAppView.cpp
inline CXamlIslandOnMFCAppDoc* CXamlIslandOnMFCAppView::GetDocument() const
   { return reinterpret_cast<CXamlIslandOnMFCAppDoc*>(m_pDocument); }
#endif

