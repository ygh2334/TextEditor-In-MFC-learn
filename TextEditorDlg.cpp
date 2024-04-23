// TextEditorDlg.cpp : implementation file
//

#include "stdafx.h"
#include "TextEditor.h"
#include "TextEditorDlg.h"
//#include "CountStringDlg.h"
#include "splash.h"
#include "CountDlg.h"
#include "HelpDlg.h"
#include "atlbase.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

static UINT WM_FINDMESSAGE = RegisterWindowMessage(FINDMSGSTRING);   //���塰����/�滻����Ϣ

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTextEditorDlg dialog

CTextEditorDlg::CTextEditorDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTextEditorDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTextEditorDlg)
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_hAccel=::LoadAccelerators(AfxGetInstanceHandle(),
		MAKEINTRESOURCE(IDR_ACCELERATOR1));//�����������ļ��ټ�����ؼ��ټ�  
}

void CTextEditorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTextEditorDlg)
	DDX_Control(pDX, IDC_EDIT1, m_Edit);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CTextEditorDlg, CDialog)
	//{{AFX_MSG_MAP(CTextEditorDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_COMMAND(ID_MENU_OPEN, OnMenuOpen)
	ON_COMMAND(ID_MENU_SAVE, OnMenuSave)
	ON_COMMAND(ID_MENU_SAVEAS, OnMenuSaveas)
	ON_COMMAND(ID_MENU_FIND_REPLACE, OnMenuFindReplace)
	ON_REGISTERED_MESSAGE(WM_FINDMESSAGE, OnFindReplace)
	ON_COMMAND(ID_MENU_FONT, OnMenuFont)
	ON_COMMAND(ID_MENU_NEW, OnMenuNew)
	ON_COMMAND(ID_MENU_ABOUT, OnMenuAbout)
	ON_WM_CLOSE()
	ON_COMMAND(ID_MENU_COPY, OnMenuCopy)
	ON_COMMAND(ID_MENU_PASTE, OnMenuPaste)
	ON_COMMAND(ID_MENU_CUT, OnMenuCut)
	ON_COMMAND(ID_MENU_DELETE, OnMenuDelete)
	ON_COMMAND(ID_MENU_UNDO, OnMenuUndo)
	ON_COMMAND(ID_MENU_SELECT_ALL, OnMenuSelectAll)
	//ON_COMMAND(ID_MENU_COUNT_STRING, OnMenuCountString)
	ON_COMMAND(ID_MENU_COUNT_ALL, OnMenuCountAll)
	ON_COMMAND(ID_MENU_HELP, OnMenuHelp)
	ON_COMMAND(ID_MENU_REG, OnMenuReg)
	ON_COMMAND(ID_MENU_BACKUP, OnMenuBackUp)
	ON_WM_CREATE()
	ON_WM_DROPFILES()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTextEditorDlg message handlers

//*****************************//
//�Ի���ĳ�ʼ������           //
//*****************************//
BOOL CTextEditorDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	//�����˵�
	m_Menu.CreateMenu();					//�����˵�����
   
	//���ļ����˵�
	CMenu m_PopMenu1;						//����˵�����	
	m_PopMenu1.CreatePopupMenu();			//���������˵�����
	m_Menu.AppendMenu(MF_POPUP,(UINT)m_PopMenu1.m_hMenu,"�ļ�(&F)");     //����˵�
	m_PopMenu1.AppendMenu(MF_STRING,ID_MENU_NEW,"�½�(&N)   Ctrl+N");    //�����Ӳ˵�
	m_PopMenu1.AppendMenu(MF_STRING,ID_MENU_OPEN,"��(&O)   Ctrl+O");   //�����Ӳ˵�
	m_PopMenu1.AppendMenu(MF_STRING,ID_MENU_SAVE,"����(&S)   Ctrl+S");   //�����Ӳ˵�
    m_PopMenu1.AppendMenu(MF_SEPARATOR);                                 //����ָ���
	m_PopMenu1.AppendMenu(MF_STRING,ID_MENU_SAVEAS,"���Ϊ(&A)");        //�����Ӳ˵�
	
	//���༭���˵�
	CMenu m_PopMenu2;
	m_PopMenu2.CreatePopupMenu();                                  
	m_Menu.AppendMenu(MF_POPUP,(UINT)m_PopMenu2.m_hMenu,"�༭(&E)");     
	m_PopMenu2.AppendMenu(MF_STRING,ID_MENU_UNDO,"����(&U)   Ctrl+Z");
	m_PopMenu2.AppendMenu(MF_STRING, ID_MENU_REDO, "����(&R)   Ctrl+Y");
    m_PopMenu2.AppendMenu(MF_SEPARATOR);
	m_PopMenu2.AppendMenu(MF_STRING,ID_MENU_SELECT_ALL,"ȫѡ(&A)   Ctrl+A");
	m_PopMenu2.AppendMenu(MF_STRING,ID_MENU_CUT,"����(&T)   Ctrl+X");		  
	m_PopMenu2.AppendMenu(MF_STRING,ID_MENU_COPY,"����(&C)   Ctrl+C");         
	m_PopMenu2.AppendMenu(MF_STRING,ID_MENU_PASTE,"ճ��(&V)   Ctrl+V");        
	m_PopMenu2.AppendMenu(MF_STRING, ID_MENU_DELETE, "ɾ��(&D)");
	m_PopMenu2.AppendMenu(MF_SEPARATOR);
	m_PopMenu2.AppendMenu(MF_STRING, ID_MENU_FIND_REPLACE, "�������滻(&F)     Ctrl+F");

	//��Ӧ�á��˵�
	CMenu m_PopMenu3;
	m_PopMenu3.CreatePopupMenu();
	m_Menu.AppendMenu(MF_POPUP,(UINT)m_PopMenu3.m_hMenu,"Ӧ��(&A)");
	//m_PopMenu3.AppendMenu(MF_STRING,ID_MENU_FIND_REPLACE,"����/�滻(&F)     Ctrl+F");
	m_PopMenu3.AppendMenu(MF_STRING,ID_MENU_FONT,"����(&S)          Alt+F");
	m_PopMenu3.AppendMenu(MF_SEPARATOR); 
	m_PopMenu3.AppendMenu(MF_STRING, ID_MENU_REG, "����ע��(&R)");
	m_PopMenu3.AppendMenu(MF_STRING, ID_MENU_BACKUP, "��ԭע��(&B)");
	//m_PopMenu3.AppendMenu(MF_STRING,ID_MENU_COUNT_STRING,"ͳ���ַ���(&C)");
	m_PopMenu3.AppendMenu(MF_SEPARATOR);
	m_PopMenu3.AppendMenu(MF_STRING,ID_MENU_COUNT_ALL,"����ͳ��(&C)");	

	//���������˵�
	CMenu m_PopMenu4;
	m_PopMenu4.CreatePopupMenu();
	m_Menu.AppendMenu(MF_POPUP,(UINT)m_PopMenu4.m_hMenu,"����(&H)");
	m_PopMenu4.AppendMenu(MF_STRING, ID_MENU_HELP, "�鿴����(&H)   Ctrl+H");
	m_PopMenu4.AppendMenu(MF_STRING,ID_MENU_ABOUT,"����TextEditor(&A)");

	//���߼����˵�
	/*
	CMenu m_PopMenu5;
	m_PopMenu5.CreatePopupMenu();
	m_Menu.AppendMenu(MF_POPUP,(UINT)m_PopMenu5.m_hMenu,"�߼�(&H)");
	m_PopMenu5.AppendMenu(MF_STRING,ID_MENU_REG,"����ע��(&R)");
	m_PopMenu5.AppendMenu(MF_STRING,ID_MENU_BACKUP,"��ԭע��(&B)");
    */

	//����˵����
	m_PopMenu1.Detach();
	m_PopMenu2.Detach();
	m_PopMenu3.Detach();
	m_PopMenu4.Detach();
	//m_PopMenu5.Detach();
	SetMenu(&m_Menu); //���˵��ʹ��ڽ��й���
	
	//������������
	/*if (!TextEditor_ToolBar.CreateEx (this,TBSTYLE_FLAT,WS_CHILD|WS_VISIBLE|CBRS_TOP|CBRS_TOOLTIPS|CBRS_FLYBY|CBRS_SIZE_DYNAMIC))
	{
		return FALSE;
	}
	CImageList ImageList;																	//����ͼ���б����
	ImageList.Create(32,32,ILC_COLOR32|ILC_MASK,10,10);										//����ͼ���б�
	ImageList.Add(AfxGetApp()->LoadIcon(IDI_ICON1));										//����ͼ��
	ImageList.Add(AfxGetApp()->LoadIcon(IDI_ICON2));										//����ͼ��
	ImageList.Add(AfxGetApp()->LoadIcon(IDI_ICON3));										//����ͼ��
	ImageList.Add(AfxGetApp()->LoadIcon(IDI_ICON4));										//����ͼ��
	ImageList.Add(AfxGetApp()->LoadIcon(IDI_ICON5));										//����ͼ��
	ImageList.Add(AfxGetApp()->LoadIcon(IDI_ICON6));										//����ͼ��
	ImageList.Add(AfxGetApp()->LoadIcon(IDI_ICON7));										//����ͼ��
	ImageList.Add(AfxGetApp()->LoadIcon(IDI_ICON8));										//����ͼ��
	ImageList.Add(AfxGetApp()->LoadIcon(IDI_ICON9));										//����ͼ��
	TextEditor_ToolBar.GetToolBarCtrl().SetImageList(&ImageList);									//����ͼ���б�
	ImageList.Detach();																		//�ͷ�ͼ���б�
	TextEditor_ToolBar.SetButtons(NULL,9);															//���ù�������ť

	TextEditor_ToolBar.SetButtonInfo(0,ID_MENU_NEW,TBSTYLE_BUTTON,0);								//���ù�������Ϣ
	TextEditor_ToolBar.SetButtonText(0,"�½��ļ�");												//���ù������ı�
	TextEditor_ToolBar.SetButtonInfo(1,ID_MENU_OPEN,TBSTYLE_BUTTON,1);
	TextEditor_ToolBar.SetButtonText(1,"���ļ�");
	TextEditor_ToolBar.SetButtonInfo(2,ID_MENU_SAVE,TBSTYLE_BUTTON,2);
	TextEditor_ToolBar.SetButtonText(2,"�����ļ�");
	TextEditor_ToolBar.SetButtonInfo(3,ID_MENU_SAVEAS,TBSTYLE_BUTTON,3);
	TextEditor_ToolBar.SetButtonText(3,"����ļ�");
	TextEditor_ToolBar.SetButtonInfo(4,ID_MENU_FIND_REPLACE,TBSTYLE_BUTTON,4);
	TextEditor_ToolBar.SetButtonText(4,"�����滻");
	TextEditor_ToolBar.SetButtonInfo(5,ID_MENU_FONT,TBSTYLE_BUTTON,5);
	TextEditor_ToolBar.SetButtonText(5,"��������");
	TextEditor_ToolBar.SetButtonInfo(6,ID_MENU_COUNT_STRING,TBSTYLE_BUTTON,6);
	TextEditor_ToolBar.SetButtonText(6,"ͳ���ִ�");
	TextEditor_ToolBar.SetButtonInfo(7,ID_MENU_COUNT_ALL,TBSTYLE_BUTTON,7);
	TextEditor_ToolBar.SetButtonText(7,"ͳ������");
	TextEditor_ToolBar.SetButtonInfo(8,ID_MENU_HELP,TBSTYLE_BUTTON,8);
	TextEditor_ToolBar.SetButtonText(8,"������ʾ"); 

	TextEditor_ToolBar.SetSizes(CSize(60,60),CSize(32,32));										//���ð�ť��С
	TextEditor_ReBar.Create(this);																	//��������
	TextEditor_ReBar.AddBar(&TextEditor_ToolBar);															//����Ŀ�깤����
    TextEditor_ReBar.RedrawWindow();																//ˢ�´���
	REBARBANDINFO info;																		
	info.cbSize = sizeof(info);																//���ýṹ��С
	info.fMask = RBBIM_BACKGROUND;															//���ñ��
	TextEditor_ToolBar.ModifyStyle(0,TBSTYLE_TRANSPARENT);											//���ù��������
	TextEditor_ReBar.GetReBarCtrl().SetBandInfo(0,&info);											//���ʹ�����
	RepositionBars(AFX_IDW_CONTROLBAR_FIRST,AFX_IDW_CONTROLBAR_LAST,0);						//��ʾ������
	*/
	OpenFile();
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CTextEditorDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CTextEditorDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CTextEditorDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

//*****************************//
//���򿪡��Ĵ�����           //
//*****************************//
void CTextEditorDlg::OnMenuOpen()
{
    // TODO: Add your control notification handler code here
	//��ǰ�������ı��ĵĴ���
	isModified = m_Edit.GetModify();									//��ȡ�ı��޸ı��
	//MessageBox("���ڴ��ļ����Եȣ�");
    CString string;
	m_Edit.GetWindowText(string);
	if (isNew && string.IsEmpty())										//�����½��ı����ı�������
	{
		;
	}

	else if(isModified)													//����ı��ѱ��޸ģ����������
	{
	    int Choice = MessageBox("��ǰ�ı��ѱ��޸ģ��뱣����","ϵͳ��ʾ",
			MB_YESNO|MB_ICONQUESTION);									//������Ϣ�Ի���ѯ��
	    if(Choice==IDYES)												//ѡ���ǡ�
		{
			OnMenuSave();												//���ñ��溯�������ļ�
		}
	}
    
	//��
	CFileDialog dlg(TRUE,NULL,NULL,OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,
		"All Files(*.TXT)|*.TXT||",AfxGetMainWnd());					//���조�ļ��򿪡��Ի���
	CString strPath,strText="";
	if(dlg.DoModal() == IDOK)											//�жϰ��¡��򿪡�
	{
		strPath = SavePath = dlg.GetPathName();							//��ȡ�ļ���·��
		CFile file(strPath,CFile::modeReadWrite);						//�Զ���д��ʽ���ļ�
		char read[50000];
		file.Read(read,50000);											//��ȡ�ļ�����
		for(unsigned i=0;i<file.GetLength();i++)
		{
			strText += read[i];											//���ļ����ݸ�ֵ��CString����
		}		
		file.Close();													//�ر��ļ�
		m_Edit.SetWindowText(strText);									//�ڱ༭������ʾ�ļ�����
		m_Edit.SetModify(FALSE);										//�ı��޸ı����Ϊδ�޸�
		isNew = FALSE;													//�����½����ı�
	}
}

//*****************************//
//���½����Ĵ�����           //
//*****************************//
void CTextEditorDlg::OnMenuNew()
{
	//�½�ǰ�������ı��ĵĴ���
	isModified = m_Edit.GetModify();									//��ȡ�ı��޸ı��
	
	CString string;
	m_Edit.GetWindowText(string);
	if (isNew && string.IsEmpty())										//�����½��ı����ı�����������
	{
		;
	}

	else if(isModified)													//����ı��ѱ��޸ģ����������
	{
	    int Choice = MessageBox("��ǰ�ı��ѱ��޸ģ��뱣����","ϵͳ��ʾ",
			MB_YESNO|MB_ICONQUESTION);									//������Ϣ�Ի���ѯ��
	    if(Choice==IDYES)												//ѡ���ǡ�
		{
			OnMenuSave();												//���ñ��溯�������ļ�
		}
	}
    
	//�½�
	m_Edit.SetSel(0, -1);												//ȫ��ѡ���ı�����
	m_Edit.Clear();														//�������ı�ɾ��
	isNew = TRUE;														//���Ϊ�½��ı�
	m_Edit.SetModify(FALSE);											//�ı��޸ı����Ϊδ�޸�
}

//*****************************//
//�����桱�Ĵ�����           //
//*****************************//
void CTextEditorDlg::OnMenuSave()
{
    if (isNew)											//���½���δ������ı����á����Ϊ�����б���
	{
		OnMenuSaveas();									//�½��ı��ѱ���
	}
	else												//�Դ򿪵��ļ��޸ĺ���б���
	{            
		CString strText="";
		char write[50000];		
		CFile file(_T(SavePath),CFile::modeCreate|CFile::modeReadWrite);//�Զ���д��ʽ�����ļ�
		m_Edit.GetWindowText(strText);                  //��ȡ�༭���е�����
		strcpy(write,strText);                          //���༭���е����ݸ�ֵ���ַ�������
		file.Write(write,strText.GetLength());          //�ѱ༭���е�����д���ļ�
		file.Close();									//�ر��ļ�
		m_Edit.SetModify(FALSE);						//�����޸ı��Ϊδ�޸�
	}
	m_Edit.SetSel(0,0);
}

//*****************************//
//�����Ϊ���Ĵ�����         //
//*****************************//
void CTextEditorDlg::OnMenuSaveas()
{
	CFileStatus fs;										//�ļ�����״̬ 

	CFileDialog dlg(FALSE,NULL,NULL,OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,
		"All Files(*.txt)|*.txt||",AfxGetMainWnd());    //���조�ļ����Ϊ���Ի���
	CString strPath,strText="";
	char write[50000];
	if(dlg.DoModal() == IDOK)                           //�жϰ��¡����Ϊ��
	{
		strPath = dlg.GetPathName();                    //��ȡ�ļ����Ϊ·��
		if(strPath.Right(4) != ".txt")
		{
			strPath += ".txt";                          //�����ļ���չ��Ϊtxt
		}

		if(CFile::GetStatus(_T(strPath),fs))			//����ļ�����
		{   
			CString info = strPath;
			info += " �Ѵ��ڡ�\r\nҪ�滻����";
			int nChoice = MessageBox (info,"���Ϊ",MB_ICONWARNING|MB_YESNO);	//����ȷ���滻��Ϣ
			if (nChoice == IDYES)												//���ȷ���滻
			{
				
				SavePath = strPath;												//��ȡ�����½��ı���·��
		
				CFile file(_T(strPath),CFile::modeCreate|CFile::modeWrite);		//��ֻд��ʽ�����ļ�
				m_Edit.GetWindowText(strText);									//��ȡ�༭���е�����
				strcpy(write,strText);											//���༭���е����ݸ�ֵ���ַ�������
				file.Write(write,strText.GetLength());							//�ѱ༭���е�����д���ļ�
				file.Close();													//�ر��ļ�
				isNew = FALSE;
				m_Edit.SetModify(FALSE);
			}
			else																//���滻
			{
				OnMenuSaveas();													//�������Ի���
			}
		}
		else																	//����ļ�������
		{
			SavePath = strPath;													//��ȡ�����½��ı���·��

			CFile file(_T(strPath),CFile::modeCreate|CFile::modeWrite);			//��ֻд��ʽ�����ļ�
			m_Edit.GetWindowText(strText);										//��ȡ�༭���е�����
			strcpy(write,strText);												//���༭���е����ݸ�ֵ���ַ�������
			file.Write(write,strText.GetLength());								//�ѱ༭���е�����д���ļ�
			file.Close();
			isNew = FALSE;
			m_Edit.SetModify(FALSE);
		}									
	}
	m_Edit.SetSel(0,0);
	
	CRect rect (15,80,586,686);
	InvalidateRect(rect);														//ˢ���û�����
}

//*****************************//
//������/�滻���Ĳ˵���Ӧ����  //
//*****************************//
void CTextEditorDlg::OnMenuFindReplace()
{
	// TODO: Add your control notification handler code here
	nindex = 0;
	degree = FALSE;
	index = 0;
	dlg = new CFindReplaceDialog;									//����������/�滻���Ի���ָ��
	dlg->Create(FALSE,NULL);										//�������滻���Ի���
	dlg->ShowWindow(SW_SHOW);										//��ʾ���滻���Ի���
}

//*****************************//
//������/�滻���Ĵ�����      //
//*****************************//
long CTextEditorDlg::OnFindReplace(WPARAM wParam, LPARAM lParam)
{
	CString strText,repText;										//�����ַ�������
	strText = dlg->GetFindString();									//��ò����ַ���
	CString str;													//�����ַ�������
	m_Edit.GetWindowText(str);										//��ñ༭�������ı�

	int len;

	if(dlg->ReplaceAll())											//�ж��Ƿ�ȫ���滻
	{
		strText = dlg->GetFindString();								//��ò����ַ���
		repText = dlg->GetReplaceString();							//����滻�ַ���
		len = repText.GetLength();									//����滻�ַ�������
		str.Replace(strText,repText);								//ʹ���滻�ַ����滻�����ַ���
		m_Edit.SetWindowText(str);									//���滻����ַ�����ʾ�ڱ༭����
		nindex =0;													//���ò���λ��Ϊ��ʼ
		m_Edit.SetModify(TRUE);		             					//�ı��޸ı����Ϊ�޸�
		m_Edit.SetSel(0,-1);

		CRect rect (15,80,586,686);
		InvalidateRect(rect);										//ˢ�½���
	}
	
	if(dlg->ReplaceCurrent())										//�滻
		find = FALSE;												//�����滻
	else
	{
		find = TRUE;												//���в���
	}
    																//�������ͱ���
	
	if(find)														//�ж��ǲ��һ����滻
	{
		len = strText.GetLength();									//���Ҫ�����ַ����ĳ���
	}
	else
	{
		CString left,right;											//�����ַ�������
		int num   = strText.GetLength();							//��ò����ַ����ĳ���
		int strnum = str.GetLength();								//��ñ༭�����ı�����	
		
		if(!degree)													//�ж�Ϊ��һ���滻
			index = str.Find(strText,nindex);						//��ò����ַ����ڱ༭���ı��е�λ��

		if(index < 0)
		{
			nindex = 0;
			degree = FALSE;
			return 1;
		}		

		left = str.Left(index);										//����滻�ַ��������ַ���
		right = str.Right(strnum-index-num);						//����滻�ַ����Ҳ���ַ���
		repText = dlg->GetReplaceString();							//����滻�ַ���
		len = repText.GetLength();									//����滻�ַ�������
		str = left + repText + right;								//��ϳ��µ��ַ���
		m_Edit.SetWindowText(str);									//�ڱ༭������ʾ�µ��ַ���
		m_Edit.SetModify(TRUE);		             					//�ı��޸ı����Ϊ�޸�
	}
	
	strText = dlg->GetFindString();									//��ò����ַ���
	m_Edit.GetWindowText(str);										//��ñ༭�������ı�

	index = str.Find (strText,nindex);								//��ò����ַ����ڱ༭���ı��е�λ��
	
	m_Edit.SetSel(index,index+strText.GetLength());					//ѡ�в��һ��滻���ַ���
	nindex = index+len;												//������ʼ����λ��
	if (index >= 0)
	{
		degree = TRUE;
	}
	else
	{
		degree = FALSE;
		nindex = 0;
	}
	m_Edit.SetFocus();												//�༭���ý���

	CRect rect1 (15,80,586,686);
	InvalidateRect(rect1);											//ˢ�½���

	return 0;
}

//*****************************//
//�����塱�Ĵ�����           //
//*****************************//
void CTextEditorDlg::OnMenuFont()
{
	// TODO: Add your control notification handler code here
	CFont* TempFont = m_Edit.GetFont();             //��ȡ�༭��ǰ����
	LOGFONT LogFont;
	TempFont->GetLogFont(&LogFont);					//��ȡ������Ϣ
	CFontDialog dlg(&LogFont);						//��ʼ��������Ϣ
	if(dlg.DoModal()==IDOK)
	{
		m_Font.Detach();                            //��������
		LOGFONT temp;
		dlg.GetCurrentFont(&temp);					//��ȡ��ǰ������Ϣ
		m_Font.CreateFontIndirect(&temp);			//ֱ�Ӵ�������
		m_Edit.SetFont(&m_Font);					//��������
	}
}

//*****************************//
//������TextEditor���Ĵ�����        //
//*****************************//
void CTextEditorDlg::OnMenuAbout()
{
	CAboutDlg dlg;       //����ϵͳ���ڶԻ��������
	dlg.DoModal();		 //��ʾ�Ի���
}

//*****************************//
//�����ơ��Ĵ�����           //
//*****************************//
void CTextEditorDlg::OnMenuCopy()
{
	m_Edit.Copy();       //���༭���еĵ�ǰѡ���ı���������������
}

//*****************************//
//��ճ�����Ĵ�����           //
//*****************************//
void CTextEditorDlg::OnMenuPaste()
{
	m_Edit.Paste();      //�ڵ�ǰ���λ�ò���������ڵ��ı�
}

//*****************************//
//�����С��Ĵ�����           //
//*****************************//
void CTextEditorDlg::OnMenuCut()
{
	m_Edit.Cut();        //ɾ���༭�ؼ��е�ǰѡ�е��ı�������ɾ�����ı���������������
}

//*****************************//
//��ɾ�����Ĵ�����           //
//*****************************//
void CTextEditorDlg::OnMenuDelete()
{
	m_Edit.Clear();      //ɾ���༭���е�ǰѡ�е��ı�
}

//*****************************//
//��ȫѡ���Ĵ�����           //
//*****************************//
void CTextEditorDlg::OnMenuSelectAll()
{
	m_Edit.SetSel(0, -1);//ȫ��ѡ���ı�����
}

//*****************************//
//���������Ĵ�����           //
//*****************************//
void CTextEditorDlg::OnMenuUndo()
{
	m_Edit.Undo();       //������һ�εı༭���еĲ���������������
}

//*****************************//
//�˳�����Ĵ�����           //
//*****************************//
void CTextEditorDlg::OnClose() 
{
	isModified = m_Edit.GetModify();				//��ȡ�ı��޸ı��
	CString string;
	m_Edit.GetWindowText(string);
	if (isNew && string.IsEmpty())					//�����½��ı����ı�����������
	{
		CDialog::OnClose();							//�˳�����
	}
	else if(isModified)								//����ı��ѱ��޸ģ����������
	{
	    int QuitChoice = MessageBox("��ǰ�ı��ѱ��޸ģ��뱣����","ϵͳ��ʾ",
			MB_YESNOCANCEL|MB_ICONQUESTION);		//������Ϣ�Ի���ѯ��
	    if(QuitChoice==IDYES)						//ѡ���ǡ�
		{
			OnMenuSave();							//���ñ��溯�������ļ�
			if (isModified = FALSE)
				CDialog::OnClose();					//�˳�����
		}
		else if(QuitChoice==IDNO)					//ѡ�񡰷�
		{
			CDialog::OnClose();						//�˳�����
		}
		else
		{
		    return;									//ѡ��ȡ����ʱ���˳�
		}
	}
	else
	{
	    CDialog::OnClose();							//����ı�δ���޸���ֱ���˳�����
	}
}

//*****************************//
//ͳ���ַ����Ĵ�����         //
//*****************************//
/*
void CTextEditorDlg::OnMenuCountString()
{
	CString str;
	m_Edit.GetWindowText(str);						//��ȡ�༭���ı�
	//CCountStringDlg dlg;							//����ͳ���ַ����Ի��������
    //dlg.SetText(str);
	//dlg.DoModal();									//��ʾ�Ի���

}
*/

//*****************************//
//ͳ���ַ��Ĵ�����           //
//*****************************//
void CTextEditorDlg::OnMenuCountAll()
{
	
	int nTotalLenth = 0;					//�ܹ����� 
	int nCLenth = 0;						//����   
	int nELenth = 0;						//Ӣ��  
	int nNLenth = 0;						//����
	int nBLenth = 0;						//�ո�
	int nEnLenth = 0;						//����ַ�
	int nEnterLenth = 0;					//�س�
	
	CString strText;
	m_Edit.GetWindowText(strText);
	int Lenth = strText.GetLength();

	for(int i=0;i<Lenth;i++)    
	{    
       
		char c = strText.GetAt(i);			//��ȡ��ǰ�ַ�   
       
		//�����ַ�     
		if(c<0||c>255)    
			continue;
		
		//Ӣ���ַ�   
		else    
		{
			if(c == '\r')					//�س���
			{
				i ++;						//����"\n"
				nEnterLenth ++;				//�س���������1
			}
			else
			{
				nEnLenth ++;
				if (c == ' ')				//�ո�����1
					nBLenth ++;
				else if (c>='0' && c<='9')	//�����ַ���1
					nNLenth ++;
				else if ((c>='a'&&c<='z')||(c>='A' && c <= 'Z'))
					nELenth ++;				//Ӣ���ַ�����1
			}
		}
  
	}    
	//���������ַ���   
	nCLenth = (Lenth-nEnLenth)/2-nEnterLenth;
	nTotalLenth = nCLenth + nEnLenth; 

	CCountDlg dlg;	   //����ͳ�������Ի��������
	dlg.SetText(nTotalLenth,nCLenth,nELenth,nNLenth,nBLenth);
	dlg.DoModal();		   //��ʾ�Ի���  
}

//*****************************//
//�����Ĵ�����   			   //
//*****************************//
void CTextEditorDlg::OnMenuHelp()
{
    CHelpDlg dlg;          //���������Ի��������
	dlg.DoModal();		   //��ʾ�Ի���
}

//*****************************//
//�������ܣ����ؼ��ټ�         //
//*****************************//
BOOL CTextEditorDlg::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: Add your specialized code here and/or call the base class
	if(m_hAccel!=NULL)   
	if(::TranslateAccelerator(m_hWnd,m_hAccel,pMsg))   //������ټ���
	return TRUE;  
	
	return CDialog::PreTranslateMessage(pMsg);
}

BOOL CTextEditorDlg::Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	return CDialog::Create(IDD, pParentWnd);
}

//*****************************//
//��������Ĵ�����           //
//*****************************//
int CTextEditorDlg::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	CSplashWnd::ShowSplashScreen(this);							//��ʾ��������
	Sleep(2000);												//��������������ʾʱ��

	

	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here
	DragAcceptFiles(TRUE);

	return 0;
}


//*****************************//
//�����ļ��Ĵ�����(�Ի���)   //
//*****************************//
void CTextEditorDlg::OnDropFiles(HDROP hDropInfo)     
{ 
	
	char *lpszFileName=new char[512]; 
	int nFileCount,i; nFileCount=::DragQueryFile (hDropInfo,0xFFFFFFFF,NULL,512); 

	for (i=0;i<nFileCount;i++)
	{ 
		UINT nChars=::DragQueryFile (hDropInfo,i,&lpszFileName[0],512); 
		CString str(&lpszFileName[0],nChars);								//����ļ�·��


		//��ǰ�������ı��ĵĴ���
		isModified = m_Edit.GetModify();									//��ȡ�ı��޸ı��
	
		CString string;
		m_Edit.GetWindowText(string);
		if (isNew && string.IsEmpty())										//�����½��ı����ı�����������
		{
			;
		}

		else if(isModified)													//����ı��ѱ��޸ģ����������
		{
			int Choice = MessageBox("��ǰ�ı��ѱ��޸ģ��뱣����","ϵͳ��ʾ",
			MB_YESNO|MB_ICONQUESTION);										//������Ϣ�Ի���ѯ��
			if(Choice==IDYES)												//ѡ���ǡ�
			{
				OnMenuSave();												//���ñ��溯�������ļ�
			}
		}

		CString strText="";
		SavePath = str;

		int n = SavePath.ReverseFind('.');   
		CString stl = SavePath.Right(SavePath.GetLength() - n - 1);
		if (stl == "txt" || stl == "TXT" || stl == "c" || stl == "C" || stl == "cpp" || stl == "CPP"
			|| stl == "h" || stl == "H" || stl == "xml" || stl == "XML" || stl == "html" || stl == "HTML")
		{
			CFile file(str,CFile::modeReadWrite);								//�Զ���д��ʽ���ļ�		
		
			//�����
			m_Edit.SetSel(0, -1);												//ȫ��ѡ���ı�����
			m_Edit.Clear();														//�������ı�ɾ��

			char read[50000];
			file.Read(read,50000);												//��ȡ�ļ�����
			for(unsigned i=0;i<file.GetLength();i++)
			{
				strText += read[i];												//���ļ����ݸ�ֵ��CString����
			}		
			file.Close();														//�ر��ļ�
			m_Edit.SetWindowText(strText);
			isNew = FALSE;														//���Ϊ���ı�
			m_Edit.SetModify(FALSE);											//�ı��޸ı����Ϊ�޸�
		}
		else
		{
			MessageBox ("��֧�ֵ��ļ����ͣ�","�򿪴���");
		}
	} 
	::DragFinish (hDropInfo); //�ͷ��ڴ� 
	i=0;
	delete []lpszFileName; 
}

//**********************************//
//���ڳ���ͼ���ϴ��ļ��Ĵ�����  //
//**********************************//
void CTextEditorDlg::OpenFile()
{
	CString strCmdLine = GetCommandLine();
	int totalLen = strCmdLine.GetLength();
	int i = 0;
	int index = 0;
	//ѭ��ͳ���ַ�����
	for (i = 0,index = 0; i < 3; i++,index ++)
	{
		index = strCmdLine.Find("\"", index);											//�����ַ���
	}
	if (index != 0)
	{
		for (i = index;i < totalLen - 1;i ++)
			SavePath += strCmdLine.GetAt(i);
		
		int n = SavePath.ReverseFind('.');   
		CString stl = SavePath.Right(SavePath.GetLength() - n - 1);
		if (stl == "txt" || stl == "TXT" || stl == "c" || stl == "C" || stl == "cpp" || stl == "CPP"
			|| stl == "h" || stl == "H" || stl == "xml" || stl == "XML" || stl == "html" || stl == "HTML")
		{
			CString strText;
			CFile file(SavePath,CFile::modeReadWrite);									//�Զ���д��ʽ���ļ�
			char read[50000];
			file.Read(read,50000);														//��ȡ�ļ�����
			for(unsigned i=0;i<file.GetLength();i++)
			{
				strText += read[i];														//���ļ����ݸ�ֵ��CString����
			}		
			file.Close();																//�ر��ļ�
			m_Edit.SetWindowText(strText);												//�ڱ༭������ʾ�ļ�����
			m_Edit.SetModify(FALSE);													//�ı��޸ı����Ϊδ�޸�
			isNew = FALSE;
			Invalidate();
		}
		else
		{
			MessageBox ("��֧�ֵ��ļ����ͣ�","�򿪴���");
			m_Edit.SetModify(FALSE);													//�ı��޸ı����Ϊδ�޸�
			isNew = TRUE;
		}
	}
	else
	{
		m_Edit.SetModify(FALSE);														//�ı��޸ı����Ϊδ�޸�
		isNew = TRUE;
	}
	m_Edit.SetSel(0,0);
}

//*****************************//
//дע���Ĵ�����           //
//*****************************//
void CTextEditorDlg::OnMenuReg()
{
	int nChoice = MessageBox ("�������˳������Ϣд��ϵͳע���\r\nȷ��Ҫд����","����ע��",MB_ICONWARNING|MB_YESNO);
	if(nChoice == IDYES)
	{
		HKEY hresult;   
		CString str1,str2;   
		long value;   
    
		LPCTSTR dataset1 = "txtfile\\shell\\OPEN";									//�򿪷�ʽ�Ӽ�
		LPCTSTR dataset2 = "txtfile\\shell\\OPEN\\command";							//���ó���·���Ӽ�   
		LPCTSTR dataset3Icon = "txtfile\\DefaultIcon";								//����ͼ���Ӽ�   
    
		//��������Ӽ�Ҫ���õ�����
		str1="��TextEditor miniword��";  
		
		char buffModulPath[MAX_PATH];   
		GetModuleFileName(GetModuleHandle(NULL),buffModulPath,MAX_PATH);   
    
		str2.Format("%s",(LPCTSTR)buffModulPath);
		str2 = "\"" + str2 + "\" ";
		CString str3 = str2;   
		str2 += "\"%1\"";
		CString CTextName = "TextEditor.exe,10";											//��������ʾ���ͼ��  
		

		for (int nPathEnd = strlen(buffModulPath) - 1; nPathEnd >= 0; nPathEnd --)	//��ó���·��
		{   
			if (buffModulPath[nPathEnd]=='\\')   
			{     
				buffModulPath[nPathEnd+1]='\0';   
  				strcat(buffModulPath,CTextName);   
    
  				break;   
			}   
		}   
		str3.Format("%s",(LPCTSTR)buffModulPath);   
    
		DWORD dwPos;   
    
		//������TextEditorminiwordӦ�ó����Ӽ�   
		value=RegCreateKeyEx(HKEY_CLASSES_ROOT,dataset1,0,NULL,REG_OPTION_NON_VOLATILE,KEY_CREATE_SUB_KEY|KEY_ALL_ACCESS,NULL,&hresult,&dwPos);   
		//�����Ӽ��ġ�Ĭ�ϡ����������������Ϊ����TextEditorminiword�򿪡�   
		value=RegSetValueEx(hresult,NULL,0,REG_SZ,(const BYTE*)(LPCTSTR)str1,str1.GetLength());   
		//������command���Ӽ�   
		value=RegCreateKeyEx(HKEY_CLASSES_ROOT,dataset2,0,NULL,REG_OPTION_NON_VOLATILE,KEY_CREATE_SUB_KEY|KEY_ALL_ACCESS,NULL,&hresult,&dwPos);   
		//�����Ӽ��ġ�Ĭ�ϡ����������������ΪTextEditorӦ�ó����·��   
		value=RegSetValueEx(hresult,NULL,0,REG_SZ,(const BYTE*)(LPCTSTR)str2,str2.GetLength());   
    
		//����Default�   
		value=RegCreateKeyEx(HKEY_CLASSES_ROOT,dataset3Icon,0,NULL,REG_OPTION_NON_VOLATILE,KEY_CREATE_SUB_KEY|KEY_ALL_ACCESS,NULL,&hresult,&dwPos);   
		//�����Ӽ��ġ�Ĭ�ϡ����������������Ϊ��TextEditorͼ�ꡱ   
		value=RegSetValueEx(hresult,NULL,0,REG_SZ,(const BYTE*)(LPCTSTR)str3,str3.GetLength());   
    
		::RegCloseKey(hresult);  

		MessageBox ("�ѽ���Ϣд��ע���ϵͳ��������Ч��","ϵͳ��ʾ");
	}
}

//*****************************//
//��ԭע���Ĵ�����         //
//*****************************//
void CTextEditorDlg::OnMenuBackUp()
{
	int nChoice = MessageBox ("������ԭϵͳע���\r\nȷ��Ҫ��ԭ��","��ԭ��Ϣ",MB_ICONWARNING|MB_YESNO);
	CString str1,str2,str3;

	if(nChoice == IDYES)
	{
		HKEY hresult;  
		long value;   
    
		LPCTSTR dataset1 = "txtfile\\shell\\OPEN";									//�򿪷�ʽ�Ӽ�
		LPCTSTR dataset2 = "txtfile\\shell\\OPEN\\command";							//���ó���·���Ӽ�   
		LPCTSTR dataset3Icon = "txtfile\\DefaultIcon";								//����ͼ���Ӽ�   
		
		//��������Ӽ�Ĭ�ϵ�����
		str1="�ü��±���"; 
		str2 = "%SystemRoot%\\NotePad.exe\" \"%1\"";
		str3 = "%SystemRoot%\\system32\\shell32.dll,-152";

		DWORD dwPos;   
    
		//�������ҵ�Ӧ�ó����Ӽ�   
		value=RegCreateKeyEx(HKEY_CLASSES_ROOT,dataset1,0,NULL,REG_OPTION_NON_VOLATILE,KEY_CREATE_SUB_KEY|KEY_ALL_ACCESS,NULL,&hresult,&dwPos);   
		//�����Ӽ��ġ�Ĭ�ϡ����������������Ϊ���ü��±��򿪡�   
		value=RegSetValueEx(hresult,NULL,0,REG_SZ,(const BYTE*)(LPCTSTR)str1,str1.GetLength());   
		//������command���Ӽ�   
		value=RegCreateKeyEx(HKEY_CLASSES_ROOT,dataset2,0,NULL,REG_OPTION_NON_VOLATILE,KEY_CREATE_SUB_KEY|KEY_ALL_ACCESS,NULL,&hresult,&dwPos);   
		//�����Ӽ��ġ�Ĭ�ϡ����������������Ϊ���±������·��   
		value=RegSetValueEx(hresult,NULL,0,REG_SZ,(const BYTE*)(LPCTSTR)str2,str2.GetLength());   
    
		//����Default�   
		value=RegCreateKeyEx(HKEY_CLASSES_ROOT,dataset3Icon,0,NULL,REG_OPTION_NON_VOLATILE,KEY_CREATE_SUB_KEY|KEY_ALL_ACCESS,NULL,&hresult,&dwPos);   
		//�����Ӽ��ġ�Ĭ�ϡ����������������Ϊ�����±�����ͼ�ꡱ   
		value=RegSetValueEx(hresult,NULL,0,REG_SZ,(const BYTE*)(LPCTSTR)str3,str3.GetLength());   
    
		::RegCloseKey(hresult);  

		MessageBox ("�ѻ�ԭע�����Ϣ��ϵͳ��������Ч��","ϵͳ��ʾ");
	}
}