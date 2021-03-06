// SmtMapServiceXCatalog.cpp : 实现文件
//

#include "stdafx.h"
#include "SmtXCatalogCore.h"
#include "cata_mapservicexcatalog.h"
#include "sde_datasourcemgr.h"

#include "cata_mapmgr.h"
#include "gis_map.h"
#include "smt_api.h"
#include "sys_sysmanager.h"
#include "sde_datasourcemgr.h"
#include "gis_api.h"
#include "smt_logmanager.h"
#include "cata_mapservicemgr.h"

#include "DlgCreateMapService.h"

using namespace Smt_GIS;
using namespace Smt_Sys;

#define		SMT_MSG_SELCHANGE_MAPSERVIVCE				(WM_USER+100)

// SmtMapServiceXCatalog

namespace Smt_XCatalog
{
	IMPLEMENT_DYNAMIC(SmtMapServiceXCatalog, SmtXCatalog)

	SmtMapServiceXCatalog::SmtMapServiceXCatalog()
	{
		m_hContexMenu = NULL;
	}

	SmtMapServiceXCatalog::~SmtMapServiceXCatalog()
	{

	}


	BEGIN_MESSAGE_MAP(SmtMapServiceXCatalog, SmtXCatalog)
		ON_WM_CREATE()
		ON_WM_RBUTTONDOWN()
		ON_WM_LBUTTONDOWN()
		
		ON_COMMAND(ID_MSERVICE_MGR_ADD, &SmtMapServiceXCatalog::OnMServiceAdd)
		ON_COMMAND(ID_MSERVICE_MGR_DELETE, &SmtMapServiceXCatalog::OnMServiceDelete)

	END_MESSAGE_MAP()

	// SmtMapServiceXCatalog 消息处理程序
	bool SmtMapServiceXCatalog::InitCreate(void) 
	{ 
		//AFX_MANAGE_STATE(AfxGetStaticModuleState());

#ifdef _DEBUG
		HINSTANCE   hInstance  =  ::GetModuleHandle("SmtXCatalogCoreD.dll");
#else
		HINSTANCE   hInstance  =  ::GetModuleHandle("SmtXCatalogCore.dll");
#endif

		m_imgList.Create(16,16,ILC_COLOR16|ILC_MASK,1,0);

		m_imgList.SetBkColor(RGB(255,255,255));

		m_imgList.Add(::LoadIcon(hInstance,MAKEINTRESOURCE(IDI_ICON_HOME)));
		m_imgList.Add(::LoadIcon(hInstance,MAKEINTRESOURCE(IDI_ICON_DS)));
		
		SetImageList(&m_imgList,TVSIL_NORMAL);

		SmtMapServiceMgr *pMServiceMgr = SmtMapServiceMgr::GetSingletonPtr();
		pMServiceMgr->RegisterMServiceCatalog((void*)this);

		return SmtXCatalog::InitCreate();
	}

	bool SmtMapServiceXCatalog::EndDestory(void) 
	{ 
		return SmtXCatalog::EndDestory();
	}

	bool SmtMapServiceXCatalog::CreateContexMenu()
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());

		CMenu menuDSMgr;
		menuDSMgr.LoadMenu(IDR_MENU_MSERVICEMGR);
		m_hContexMenu = menuDSMgr.GetSafeHmenu();

		return SmtXCatalog::CreateContexMenu();
	}

	//////////////////////////////////////////////////////////////////////////
	BOOL SmtMapServiceXCatalog::Create(DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID)
	{
		// TODO: 在此添加专用代码和/或调用基类

		return SmtXCatalog::Create(dwStyle, rect, pParentWnd, nID);
	}

	int SmtMapServiceXCatalog::OnCreate(LPCREATESTRUCT lpCreateStruct)
	{
		if (SmtXCatalog::OnCreate(lpCreateStruct) == -1)
			return -1;

		// TODO:  在此添加您专用的创建代码

		return 0;
	}

	void SmtMapServiceXCatalog::OnRButtonDown(UINT nFlags, CPoint point)
	{
		// TODO: 在此添加消息处理程序代码和/或调用默认值

		AFX_MANAGE_STATE(AfxGetStaticModuleState());

		HTREEITEM hItem = HitTest(point,&m_nFlags); 
		if((hItem != NULL)&&(TVHT_ONITEM&nFlags)) 
		{ 
			SelectItem(hItem); 
		}
		else 
			return;

		HTREEITEM hParentItem=GetParentItem(hItem);
		if (hParentItem == m_hRoot || hItem == m_hRoot)
		{
			m_strSelMServiceName = GetItemText(hItem);
		}

		CMenu menuMapMgr;
		menuMapMgr.LoadMenu(IDR_MENU_MSERVICEMGR);

		CMenu* pMenu = NULL;
		pMenu = menuMapMgr.GetSubMenu(0);

		if (pMenu)
		{
			CPoint      menuPos;   
			GetCursorPos(&menuPos);  

			pMenu->TrackPopupMenu(TPM_LEFTALIGN|TPM_LEFTBUTTON|TPM_RIGHTBUTTON,menuPos.x,menuPos.y,this);
			pMenu->Detach();
		}		

		SmtXCatalog::OnRButtonDown(nFlags, point);
	}

	void SmtMapServiceXCatalog::OnLButtonDown(UINT nFlags, CPoint point)
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());

		SmtXCatalog::OnLButtonDown(nFlags, point);

		HTREEITEM hItem = GetSelectedItem();
		HTREEITEM hParentItem=GetParentItem(hItem);
		if (hParentItem == m_hRoot)
		{
			m_strSelMServiceName = GetItemText(hItem);
			CWnd *pParentWnd = GetParent();
			if (NULL != pParentWnd)
				pParentWnd->PostMessage(WM_COMMAND,SMT_MSG_SELCHANGE_MAPSERVIVCE,NULL);
		}
	}

	void SmtMapServiceXCatalog::UpdateMServiceCatalogTree(void)
	{
		SmtMapServiceMgr *pMServiceMgr = SmtMapServiceMgr::GetSingletonPtr();

		SetRedraw(FALSE);
		DeleteAllItems();
		SetTextColor(RGB(0,0,255));
		m_hRoot =InsertItem("地图服务",0,0,TVI_ROOT);
	
		pMServiceMgr->MoveFirst();
		while (!pMServiceMgr->IsEnd())
		{
			AppendMServiceNode(pMServiceMgr->GetMapService());
			pMServiceMgr->MoveNext();
		}

		Expand(m_hRoot,TVE_EXPAND);

		SetRedraw(TRUE);

		RedrawWindow();		
	}

	void SmtMapServiceXCatalog::AppendMServiceNode(SmtMapService *pMService)
	{
		if (pMService)
		{
			HTREEITEM hMService = InsertItem(pMService->GetName().c_str(),1,1,m_hRoot);
		}	
	}

	void SmtMapServiceXCatalog::OnMServiceAdd()
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());

		::SetCapture(AfxGetMainWnd()->m_hWnd);

		CDlgCreateMapService dlg(this);
		if (dlg.DoModal() == IDOK)
		{
			SmtMapServiceMgr *pMServiceMgr = SmtMapServiceMgr::GetSingletonPtr();

			SmtMapService *pMapService = new SmtMapService();
			pMapService->SetName((LPCTSTR)(dlg.m_strMapServiceName));
			pMServiceMgr->AppendMapService(pMapService);
		}

		ReleaseCapture();
	}

	void SmtMapServiceXCatalog::OnMServiceDelete()
	{
		SmtMapServiceMgr *pMServiceMgr = SmtMapServiceMgr::GetSingletonPtr();
		pMServiceMgr->RemoveMapService(m_strSelMServiceName);
	}
}