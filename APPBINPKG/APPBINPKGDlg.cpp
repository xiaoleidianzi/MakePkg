
// APPBINPKGDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "APPBINPKG.h"
#include "APPBINPKGDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
#define PKG_SIZE 2048		//�ְ���С
unsigned int Dataint[65536];//256k
unsigned int Dataout[PKG_SIZE/4];//2k
UINT32  CalcCRC32(BYTE *SndBuf, INT32 size);

unsigned int Seek_Count = 0;
unsigned int Seek_End = 0;
unsigned int Int_Count = 0;
int i = 0;
int numread = 0;
CString strfilefath_int;
CFile telfile;
// ����CRC�����ѯ�� 32*8
UINT32 crc32tbl[256]=
{
	0x00000000,0x77073096,0xEE0E612C,0x990951BA,0x076DC419,0x706AF48F,0xE963A535,0x9E6495A3,

	0x0EDB8832,0x79DCB8A4,0xE0D5E91E,0x97D2D988,0x09B64C2B,0x7EB17CBD,0xE7B82D07,0x90BF1D91,

	0x1DB71064,0x6AB020F2,0xF3B97148,0x84BE41DE,0x1ADAD47D,0x6DDDE4EB,0xF4D4B551,0x83D385C7,

	0x136C9856,0x646BA8C0,0xFD62F97A,0x8A65C9EC,0x14015C4F,0x63066CD9,0xFA0F3D63,0x8D080DF5,

	0x3B6E20C8,0x4C69105E,0xD56041E4,0xA2677172,0x3C03E4D1,0x4B04D447,0xD20D85FD,0xA50AB56B,

	0x35B5A8FA,0x42B2986C,0xDBBBC9D6,0xACBCF940,0x32D86CE3,0x45DF5C75,0xDCD60DCF,0xABD13D59,

	0x26D930AC,0x51DE003A,0xC8D75180,0xBFD06116,0x21B4F4B5,0x56B3C423,0xCFBA9599,0xB8BDA50F,

	0x2802B89E,0x5F058808,0xC60CD9B2,0xB10BE924,0x2F6F7C87,0x58684C11,0xC1611DAB,0xB6662D3D,

	0x76DC4190,0x01DB7106,0x98D220BC,0xEFD5102A,0x71B18589,0x06B6B51F,0x9FBFE4A5,0xE8B8D433,

	0x7807C9A2,0x0F00F934,0x9609A88E,0xE10E9818,0x7F6A0DBB,0x086D3D2D,0x91646C97,0xE6635C01,

	0x6B6B51F4,0x1C6C6162,0x856530D8,0xF262004E,0x6C0695ED,0x1B01A57B,0x8208F4C1,0xF50FC457,

	0x65B0D9C6,0x12B7E950,0x8BBEB8EA,0xFCB9887C,0x62DD1DDF,0x15DA2D49,0x8CD37CF3,0xFBD44C65,

	0x4DB26158,0x3AB551CE,0xA3BC0074,0xD4BB30E2,0x4ADFA541,0x3DD895D7,0xA4D1C46D,0xD3D6F4FB,

	0x4369E96A,0x346ED9FC,0xAD678846,0xDA60B8D0,0x44042D73,0x33031DE5,0xAA0A4C5F,0xDD0D7CC9,

	0x5005713C,0x270241AA,0xBE0B1010,0xC90C2086,0x5768B525,0x206F85B3,0xB966D409,0xCE61E49F,

	0x5EDEF90E,0x29D9C998,0xB0D09822,0xC7D7A8B4,0x59B33D17,0x2EB40D81,0xB7BD5C3B,0xC0BA6CAD,

	0xEDB88320,0x9ABFB3B6,0x03B6E20C,0x74B1D29A,0xEAD54739,0x9DD277AF,0x04DB2615,0x73DC1683,

	0xE3630B12,0x94643B84,0x0D6D6A3E,0x7A6A5AA8,0xE40ECF0B,0x9309FF9D,0x0A00AE27,0x7D079EB1,

	0xF00F9344,0x8708A3D2,0x1E01F268,0x6906C2FE,0xF762575D,0x806567CB,0x196C3671,0x6E6B06E7,

	0xFED41B76,0x89D32BE0,0x10DA7A5A,0x67DD4ACC,0xF9B9DF6F,0x8EBEEFF9,0x17B7BE43,0x60B08ED5,

	0xD6D6A3E8,0xA1D1937E,0x38D8C2C4,0x4FDFF252,0xD1BB67F1,0xA6BC5767,0x3FB506DD,0x48B2364B,

	0xD80D2BDA,0xAF0A1B4C,0x36034AF6,0x41047A60,0xDF60EFC3,0xA867DF55,0x316E8EEF,0x4669BE79,

	0xCB61B38C,0xBC66831A,0x256FD2A0,0x5268E236,0xCC0C7795,0xBB0B4703,0x220216B9,0x5505262F,

	0xC5BA3BBE,0xB2BD0B28,0x2BB45A92,0x5CB36A04,0xC2D7FFA7,0xB5D0CF31,0x2CD99E8B,0x5BDEAE1D,

	0x9B64C2B0,0xEC63F226,0x756AA39C,0x026D930A,0x9C0906A9,0xEB0E363F,0x72076785,0x05005713,

	0x95BF4A82,0xE2B87A14,0x7BB12BAE,0x0CB61B38,0x92D28E9B,0xE5D5BE0D,0x7CDCEFB7,0x0BDBDF21,

	0x86D3D2D4,0xF1D4E242,0x68DDB3F8,0x1FDA836E,0x81BE16CD,0xF6B9265B,0x6FB077E1,0x18B74777,

	0x88085AE6,0xFF0F6A70,0x66063BCA,0x11010B5C,0x8F659EFF,0xF862AE69,0x616BFFD3,0x166CCF45,

	0xA00AE278,0xD70DD2EE,0x4E048354,0x3903B3C2,0xA7672661,0xD06016F7,0x4969474D,0x3E6E77DB,

	0xAED16A4A,0xD9D65ADC,0x40DF0B66,0x37D83BF0,0xA9BCAE53,0xDEBB9EC5,0x47B2CF7F,0x30B5FFE9,

	0xBDBDF21C,0xCABAC28A,0x53B39330,0x24B4A3A6,0xBAD03605,0xCDD70693,0x54DE5729,0x23D967BF,

	0xB3667A2E,0xC4614AB8,0x5D681B02,0x2A6F2B94,0xB40BBE37,0xC30C8EA1,0x5A05DF1B,0x2D02EF8D

};


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CAPPBINPKGDlg �Ի���




CAPPBINPKGDlg::CAPPBINPKGDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CAPPBINPKGDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CAPPBINPKGDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAPPBINPKGDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//ON_BN_CLICKED(IDC_BUTTON1, &CAPPBINPKGDlg::OnBnClickedButton1)
	ON_BN_CLICKED(ID_WIZFINISH, &CAPPBINPKGDlg::OnBnClickedWizfinish)
	ON_BN_CLICKED(IDC_BUTTON2, &CAPPBINPKGDlg::OnBnClickedButton2)
END_MESSAGE_MAP()


// CAPPBINPKGDlg ��Ϣ�������

BOOL CAPPBINPKGDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CAPPBINPKGDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CAPPBINPKGDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CAPPBINPKGDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CAPPBINPKGDlg::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}


void CAPPBINPKGDlg::OnBnClickedWizfinish()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//TCHAR szFilter[] = _T("�ı��ļ�(*.txt)|�����ļ�(*.*)|");
	//TCHAR szFilter[] = _T("�ı��ļ�(*.txt)");
	//CFileDialog filedlg(TRUE,_T("txt",NULL,0,szFilter,this));
	

	CFileDialog filedlg(TRUE,0,0,0,0,0,0,1);
	//static char BASED_CODE szFilter1[] = "RAW (*.raw)|*.raw|All Files (*.*)|*.*||";
	//CFileDialog fdlg(1,NULL,"HONGWAI_1.raw", OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,szFilter1 , NULL,0,TRUE);
	//CFileDialog filedlg(NULL,  "HONGWAI_1.raw",  OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,szFilter , NULL );
	CStdioFile  X;
	
	CFileDialog m_Read_File (TRUE);
	//��ʾ���ļ��Ի���
	if(IDOK == filedlg.DoModal())
	{
		strfilefath_int = filedlg.GetPathName();
		//SetDlgItemText(IDC_STATIC,strfilefath);
	}
	else
	{
		;
	}

	BOOL filestate;
		
	//BYTE buf[4];
	//unsigned int bufint[1];
	//unsigned short X_BUFF[4];
	//filestate = X.Open(strfilefath,CFile::modeRead);
	filestate=telfile.Open(strfilefath_int,CFile::modeRead,NULL);
	/*tmpimgfile.Open("F:\\XIA\\RealImg14bit-IBM.raw",CFile::modeCreate | CFile::modeWrite,NULL)
	::AfxGetMainWnd()->SetWindowText(strfilefath);*/

	//���ݶ�ȡ
	if(filestate)
	{		
		while(!Seek_End)				//ָ��û�е���β���������ļ�
		{
			telfile.Seek(Seek_Count, CFile::begin );
			numread=telfile.Read(&Dataint[Int_Count],4);

			//Data
			if(numread == 4)
			{
				Seek_Count=Seek_Count+4;//�ļ�ָ��ƫ��
				Int_Count++;			//int����
			}
			else
			{
				Seek_End = 1;			//�Ѿ�������β�����ٶ�ȡ�ļ�
			}

		}
		
	}
	telfile.Close();

	

	MessageBox("��ȡ�ļ����!");
}


UINT32  CalcCRC32(BYTE *SndBuf, INT32 size)
{	
	UINT32 crc32 = 0xffffffff;
	BYTE *ptr;
	ptr=SndBuf;        

	while ( --size>=0 )	
		crc32  = ( crc32 >> 8) ^ crc32tbl[(crc32 ^ (*ptr++)) & 0xFF];

	return crc32^0xffffffff;
}

void CAPPBINPKGDlg::OnBnClickedButton2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int Pkg_Count = ((Seek_Count - 8) / (PKG_SIZE))+1;		//����汾�ź��������ڲ������ܳ���
	int Pkg_END = ((Seek_Count - 8) % (PKG_SIZE));//���һ�����ݳ���
	CString str;
	CString temp;

	CString strfilefath_out;
	//Ӧ�ó��������������ļ�
	strfilefath_out =strfilefath_int.Left(strfilefath_int.GetLength()-4)+".xml";	 //APP.xml
	if(telfile.Open(strfilefath_out,CFile::modeCreate | CFile::modeWrite,NULL))
	{
		
		Dataout[0] = 0x6C6D782E;//֡ͷ��.xml)
		Dataout[1] = Dataint[0];//����汾��
		Dataout[2] = Dataint[1];//�����������
		Dataout[3] = Pkg_Count; //�ܰ���
		Dataout[4] = 0;			//����1
		Dataout[5] = 0;			//����2
		Dataout[6] = 0;			//����3
		Dataout[7] = 0;			//����4
		Dataout[8] = 0;			//����5
		unsigned int uTmp32= CalcCRC32((BYTE *)(&Dataout[1]),8*4);//8��uint
		Dataout[9] = uTmp32;
		Dataout[10] = 0x786D6C2E;//֡β(.lmx)

		telfile.Write(Dataout,44);
		telfile.Close();
	}
	for(i = 0; i<Pkg_Count;i++ )
	{
		//memset(Dataout,0,PKG_SIZE+24);
		str.Format("%d",i+1);
		if(Pkg_Count == 1)
		{
			strfilefath_out =strfilefath_int.Left(strfilefath_int.GetLength()-4)+".pkg";	 //APP.PKG
		}
		else
		{
			strfilefath_out =strfilefath_int.Left(strfilefath_int.GetLength()-4)+str+".pkg"; //APP0.PKG��APP1.PKG
		}

		//����У��+���
		if(telfile.Open(strfilefath_out,CFile::modeCreate | CFile::modeWrite,NULL))
		{

			if(i==(Pkg_Count-1))//���һ��
			{
				//Pkg_END_Len
				unsigned int uTmp32= CalcCRC32(((BYTE *)(&Dataint[i*(PKG_SIZE)/4+2])),Pkg_END);
				Dataout[0] = 0x676B702E;//֡ͷ��.pkg)
				Dataout[1] = Pkg_Count;//�ܰ���
				Dataout[2] = i+1;	  //��ǰ��
				Dataout[3] = Pkg_END;//���ݳ���
				memcpy(&Dataout[4],&Dataint[i*PKG_SIZE/4+2],Pkg_END);
				Dataout[4+(Pkg_END)/4] = uTmp32;
				Dataout[5+(Pkg_END)/4] = 0x6B70672E;//֡β(.gkp)

				telfile.Write(Dataout, Pkg_END + 24 );
				telfile.Close();
			}
			else				//�����һ��
			{
				unsigned int uTmp32= CalcCRC32(((BYTE *)(&Dataint[i*(PKG_SIZE)/4+2])),PKG_SIZE);
				Dataout[0] = 0x676B702E;//֡ͷ��.pkg)
				Dataout[1] = Pkg_Count; //�ܰ���
				Dataout[2] = i+1;	    //��ǰ��
				Dataout[3] = PKG_SIZE;  //���ݳ���
				memcpy(&Dataout[4],&Dataint[i*PKG_SIZE/4+2],PKG_SIZE);
				Dataout[4+(PKG_SIZE)/4] = uTmp32;
				Dataout[5+(PKG_SIZE)/4] = 0x6B70672E;//֡β(.gkp)

				telfile.Write(Dataout, PKG_SIZE + 24 );
				telfile.Close();
			}

		}
		else
		{
			//MessageBox("Open refimg File Error!");
		}
	}

	MessageBox("�������������!");
}
