// DlgCreateMapService.cpp : 实现文件
//

#include "stdafx.h"
#include "SmtXCatalogCore.h"
#include "DlgCreateMapService.h"


// CDlgCreateMapService 对话框

IMPLEMENT_DYNAMIC(CDlgCreateMapService, CDialog)

CDlgCreateMapService::CDlgCreateMapService(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgCreateMapService::IDD, pParent)
{

}

CDlgCreateMapService::~CDlgCreateMapService()
{
}

void CDlgCreateMapService::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX,IDC_EDIT_MAPSERVICE_NAME,m_strMapServiceName);
}


BEGIN_MESSAGE_MAP(CDlgCreateMapService, CDialog)
	ON_BN_CLICKED(IDOK, &CDlgCreateMapService::OnBnClickedOk)
END_MESSAGE_MAP()


// CDlgCreateMapService 消息处理程序
void CDlgCreateMapService::OnBnClickedOk()
{
	// TODO: ÔÚ´ËÌí¼Ó¿Ø¼þÍ¨Öª´¦Àí³ÌÐò´úÂë
	UpdateData(TRUE);
	OnOK();
}