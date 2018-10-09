#define  WIN32_LEAN_AND_MEAN
#pragma comment ( linker,"/ALIGN:4096" )
#include <windows.h>
#include <commdlg.h>
#include <commctrl.h>

#include "resource.h"
#include "test.h"

char szFile[MAX_PATH];
char str[32767];	// ��ʾ������
char colorvalue[12]="000000FF";
void WINAPI test(int * OutBytes);
char * WINAPI ToHex(int nLength,unsigned char *buf);
char text[]=
"------------- EncryptPE SDK V++ Sample ------------------\r\n"
"---------------------------------------------------------";


COLORREF cl = RGB(0,0,0);
HWND combo;		// ���Ͽ�ؼ����
HWND hDlg;
HINSTANCE g_hInst;
BOOL CALLBACK DialogProc(HWND HwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam);

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	g_hInst = hInstance;

	INITCOMMONCONTROLSEX icc;
	icc.dwSize = sizeof(INITCOMMONCONTROLSEX);
	icc.dwICC = ICC_USEREX_CLASSES|ICC_BAR_CLASSES;
	InitCommonControlsEx(&icc);

	CreateDialog(NULL, MAKEINTRESOURCE(IDD_APP), NULL, (DLGPROC)DialogProc);
	MSG msg;

	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	} 
	return 0;
}

BOOL CALLBACK DialogProc(HWND HwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch(uMsg)
	{
	case WM_COMMAND:

		switch (LOWORD(wParam)) 
		{ 
		case IDC_COMBOBOXEX1: 
			if (HIWORD(wParam) == CBN_SELCHANGE) 
			{
				// �û�ѡ���Ҫ��ȡ����
				SetWindowText(GetDlgItem(HwndDlg, IDC_EDIT9), " ");
				int index = SendMessage(combo, CB_GETCURSEL, (WPARAM)0, 0L);
				char * ret = GetRegisterInfo(index);
				SetWindowText(GetDlgItem(HwndDlg, IDC_EDIT9), ret);
				return TRUE; 
			}
		} 
		//break; 

		switch(wParam)
		{
		case IDC_BUTTON8: // ����/���ܲ���
			{
				unsigned char InBuf[32767];
				unsigned char OutBuf[10240];
				memset(OutBuf,0,10240);
				GetWindowText(GetDlgItem(hDlg, IDC_EDIT_MSG),(char *)InBuf,32767);
				if(InBuf[0]==0)
				{
					MessageBox(NULL,"pls type some word in edit control","note",0);
					return 0;
				}
				int ol = strlen((const char *)InBuf);
				int InBytes = strlen((const char *)InBuf);
				int OutBytes=0;

				// �ڴ�/������
				Encrypt((int)InBuf,InBytes,(int)OutBuf,&OutBytes,"abcdefg");
				char * hx = ToHex(OutBytes,OutBuf);
				strcat((char *)InBuf,"\r\n");
				strcat((char *)InBuf,"\r\n\r\n���ܺ�Ĵ�:\r\n");
				strcat((char *)InBuf,hx);
				SetWindowText(GetDlgItem(hDlg, IDC_EDIT_MSG), (const char *)InBuf);

				char msg[260];
				wsprintf(msg,"ԭ����:%d ���ܺ󴮳�:%d",ol,OutBytes);
				SetWindowText(GetDlgItem(hDlg, IDC_EDITINFO), msg);
				//return 0;

				// �ڴ�/������
				memset(InBuf,0,32767);
				Decrypt((int)OutBuf,OutBytes,(int)InBuf,&InBytes,"abcdefg");
				char * hx2 = ToHex(InBytes,InBuf);
				GetWindowText(GetDlgItem(hDlg, IDC_EDIT_MSG),(char *)OutBuf,10240);
				strcat((char *)OutBuf,"\r\n");
				strcat((char *)OutBuf,"\r\n\r\n���ܺ�Ĵ�:\r\n");
				strcat((char *)OutBuf,hx2);
				SetWindowText(GetDlgItem(hDlg, IDC_EDIT_MSG), (const char *)OutBuf);

			}
			break;
		case IDC_BUTTON13: // ����ע����ʾ������Ϣ
			{
				unsigned char RegHint[4096];
				memset(RegHint,0,4096);
				char Info[1024];
				GetWindowText(GetDlgItem(HwndDlg, IDC_EDIT3),Info,1024);
				strcpy((char *)RegHint,colorvalue);
				strcat((char *)RegHint,"~");
				strcat((char *)RegHint,Info);
				GetWindowText(GetDlgItem(HwndDlg, IDC_EDIT4),Info,1024);
				strcat((char *)RegHint,"~");
				strcat((char *)RegHint,Info);
				GetWindowText(GetDlgItem(HwndDlg, IDC_EDIT5),Info,1024);
				strcat((char *)RegHint,"~");
				strcat((char *)RegHint,Info);

				int l=strlen((const char *)RegHint);
				for(int i=0;i<l;i++)
				{
					if(RegHint[i]==126) 
						RegHint[i]=0;
				}

				if ( SetRegisterHint((DWORD)RegHint))
					MessageBox(NULL, "����ע����ʾ������Ϣ�ɹ���", "",0);
				//Call ShowRegisterForm
				else
					MessageBox(NULL, "����ע����ʾ������Ϣʧ�ܣ�", "",0);
    
    
			}
			break;
		case IDC_BUTTON18: // ����ע����Ϣ
			{
				//GetRegisterInfo();
				char TxtUserName[1024];
				char TxtRegInfo[1024];
				GetWindowText(GetDlgItem(HwndDlg, IDC_EDIT6),TxtUserName,1024);
				GetWindowText(GetDlgItem(HwndDlg, IDC_EDIT7),TxtRegInfo,1024);
				if (SetRegisterInfo(TxtUserName, TxtRegInfo))
				{
					MessageBox(NULL,"����ע����Ϣ�ɹ���", "",0);
					//GetRegisterHandle(g_hInst);
					//ShowRegisterForm();
				}
				else
					MessageBox(NULL,"����ע����Ϣʧ�ܣ�", "",0);
			}
			break;
		case IDC_BUTTON19: // ������ɫ
			{
				CHOOSECOLOR cc;                 // common dialog box structure 
				static COLORREF acrCustClr[16]; // array of custom colors 
				//HWND hwnd;                      // owner window
				HBRUSH hbrush;                  // brush handle
				static DWORD rgbCurrent;        // initial color selection
				
				// Initialize CHOOSECOLOR 
				ZeroMemory(&cc, sizeof(CHOOSECOLOR));
				cc.lStructSize = sizeof(CHOOSECOLOR);
				cc.hwndOwner = HwndDlg;
				cc.lpCustColors = (LPDWORD) acrCustClr;
				cc.rgbResult = rgbCurrent;
				cc.Flags = CC_FULLOPEN | CC_RGBINIT;
				
				if (ChooseColor(&cc)==TRUE) 
				{
					hbrush = CreateSolidBrush(cc.rgbResult);
					rgbCurrent = cc.rgbResult; 
					cl = cc.rgbResult;
					char msg[1024];
					wsprintf(msg,"%d",cl);
					wsprintf(colorvalue,"%08X",cl);
					//colorvalue = cl;
					SetWindowText(GetDlgItem(HwndDlg, IDC_EDIT8), msg);
					RedrawWindow(HwndDlg, NULL, NULL, RDW_INVALIDATE);
				}
			}
			break;
		//case IDC_BUTTON8: // �ļ���/���ܡ�ѹ��/��ѹ��
		//	{
		//		OPENFILENAME ofn;
		//		ZeroMemory(&ofn,sizeof(OPENFILENAME));
		//		ofn.lStructSize = sizeof(OPENFILENAME) ;
		//		char szFilter[MAX_PATH];
		//		memset(szFilter,0,MAX_PATH);
		//		wsprintf(szFilter,"%s","*.exe");
		//		ofn.lpstrFilter = szFilter ;
		//		ofn.nMaxFile = MAX_PATH;
		//		char szFileA[MAX_PATH];
		//		memset(szFileA,0,MAX_PATH);
		//		wsprintf(szFileA,"%s","*.exe");
		//		ofn.lpstrFile=szFileA;
		//		ofn.Flags = 0;
		//		
		//		if(GetOpenFileName(&ofn))
		//		{
		//			SetWindowText(GetDlgItem(HwndDlg, IDC_EXEFILE), ofn.lpstrFile);
		//			SendDlgItemMessage(HwndDlg, IDC_EXEFILE, WM_GETTEXT, MAX_PATH, (LPARAM) szFile);
		//		}
		//		// �е����������̫���Ҫ,��ʱ���Բ���
		//	}
		//	break;
		case IDC_BUTTON1: // ��ʾע�ᴰ��
			{
				BOOL retValue = ShowRegisterForm();
			}
			break;
		case IDC_BUTTON2: // ע��״̬
			{
				char * ret = GetRegisterInfo();
				if(ret!=NULL) MessageBox(NULL,ret,"",0);
			}
			break;
		case IDC_BUTTON10: // �ڴ�����/�� ѹ��/��ѹ����
			{
				unsigned char InBuf[32767];
				unsigned char OutBuf[10240];
				memset(OutBuf,0,10240);
				GetWindowText(GetDlgItem(hDlg, IDC_EDIT_MSG),(char *)InBuf,32767);
				if(InBuf[0]==0)
				{
					MessageBox(NULL,"pls type some word in edit control","note",0);
					return 0;
				}
				int ol = strlen((const char *)InBuf);
				int InBytes = strlen((const char *)InBuf);
				int OutBytes=0;

				// �ڴ�/��ѹ��
				Compress((int)InBuf,InBytes,(int)OutBuf,&OutBytes,"abcdefg");
				char * hx = ToHex(OutBytes,OutBuf);
				strcat((char *)InBuf,"\r\n");
				strcat((char *)InBuf,"\r\n\r\nѹ����Ĵ�:\r\n");
				strcat((char *)InBuf,hx);
				SetWindowText(GetDlgItem(hDlg, IDC_EDIT_MSG), (const char *)InBuf);

				char msg[260];
				wsprintf(msg,"ԭ����:%d ѹ���󴮳�:%d",ol,OutBytes);
				SetWindowText(GetDlgItem(hDlg, IDC_EDITINFO), msg);

				// �ڴ�/����ѹ
				memset(InBuf,0,32767);
				Decompress((int)OutBuf,OutBytes,(int)InBuf,&InBytes,"abcdefg");
				char * hx2 = ToHex(InBytes,InBuf);
				GetWindowText(GetDlgItem(hDlg, IDC_EDIT_MSG),(char *)OutBuf,10240);
				strcat((char *)OutBuf,"\r\n");
				strcat((char *)OutBuf,"\r\n\r\n��ѹ��Ĵ�:\r\n");
				strcat((char *)OutBuf,hx2);
				SetWindowText(GetDlgItem(hDlg, IDC_EDIT_MSG), (const char *)OutBuf);
			}
			break;
		case IDC_BUTTON3: // ɱ��ָ������
			{
				char ProcessName[MAX_PATH];
				GetWindowText(GetDlgItem(HwndDlg, IDC_EDIT1), ProcessName ,MAX_PATH); 
				if (ProcessName[0]==0) 
				{
					MessageBox(NULL,"����ָ��һ��������","",0);
					return 0;
				}
				if(KillProcess(ProcessName)) MessageBox(NULL,"�ɹ�","",0);
				else MessageBox(NULL,"ʧ��","",0);
			}
			break;
		case IDC_BUTTON4: // ȡ����ָ�����̵Ľ�ɱ
			{
				char ProcessName[MAX_PATH];
				GetWindowText(GetDlgItem(HwndDlg, IDC_EDIT2), ProcessName ,MAX_PATH); 
				if (ProcessName[0]==0) 
				{
					MessageBox(NULL,"����ָ��һ��������","",0);
					return 0;
				}
				if(NotKillProcess(ProcessName)) MessageBox(NULL,"�ɹ�","",0);
				else MessageBox(NULL,"ʧ��","",0);
			}
			break;
		}
		break;
		case WM_INITDIALOG:
			{
				HICON hIcon;
				hIcon = (HICON)LoadImage(g_hInst,
					MAKEINTRESOURCE(IDI_ICON1),
					IMAGE_ICON,
					GetSystemMetrics(SM_CXSMICON),
					GetSystemMetrics(SM_CYSMICON),
					0);

				if(hIcon) 
				{
					SendMessage(HwndDlg, WM_SETICON, ICON_SMALL, (LPARAM)hIcon);
				}
				int s=sizeof(P);
				P=(PUserRecord)malloc(s);
				GetRegisterHandle(g_hInst);
				if(RegisterHandle == NULL) // ����û�мӿ�
				{
					MessageBox(NULL,"����û�мӿǣ����ܲ���","",0);
					EnableWindow(GetDlgItem(HwndDlg, IDC_BUTTON1), FALSE);
					EnableWindow(GetDlgItem(HwndDlg, IDC_BUTTON2), FALSE);
					EnableWindow(GetDlgItem(HwndDlg, IDC_BUTTON3), FALSE);
					EnableWindow(GetDlgItem(HwndDlg, IDC_BUTTON4), FALSE);
					EnableWindow(GetDlgItem(HwndDlg, IDC_BUTTON5), FALSE);
					EnableWindow(GetDlgItem(HwndDlg, IDC_EDIT1), FALSE);
					EnableWindow(GetDlgItem(HwndDlg, IDC_EDIT2), FALSE);
					EnableWindow(GetDlgItem(HwndDlg, IDC_BUTTON6), FALSE);
					EnableWindow(GetDlgItem(HwndDlg, IDC_BUTTON7), FALSE);
					EnableWindow(GetDlgItem(HwndDlg, IDC_BUTTON8), FALSE);
					EnableWindow(GetDlgItem(HwndDlg, IDC_BUTTON9), FALSE);
					EnableWindow(GetDlgItem(HwndDlg, IDC_BUTTON10), FALSE);
					EnableWindow(GetDlgItem(HwndDlg, IDC_BUTTON11), FALSE);
					EnableWindow(GetDlgItem(HwndDlg, IDC_BUTTON12), FALSE);
					EnableWindow(GetDlgItem(HwndDlg, IDC_BUTTON13), FALSE);
					EnableWindow(GetDlgItem(HwndDlg, IDC_BUTTON14), FALSE);
					EnableWindow(GetDlgItem(HwndDlg, IDC_BUTTON15), FALSE);
					EnableWindow(GetDlgItem(HwndDlg, IDC_BUTTON16), FALSE);
					EnableWindow(GetDlgItem(HwndDlg, IDC_BUTTON17), FALSE);
					EnableWindow(GetDlgItem(HwndDlg, IDC_BUTTON18), FALSE);
					EnableWindow(GetDlgItem(HwndDlg, IDC_BUTTON19), FALSE);
				}
				else
				{
					EnableWindow(GetDlgItem(HwndDlg, IDC_BUTTON1), TRUE);
					EnableWindow(GetDlgItem(HwndDlg, IDC_BUTTON2), TRUE);
					EnableWindow(GetDlgItem(HwndDlg, IDC_BUTTON3), TRUE);
					EnableWindow(GetDlgItem(HwndDlg, IDC_BUTTON4), TRUE);
					EnableWindow(GetDlgItem(HwndDlg, IDC_BUTTON5), TRUE);
					EnableWindow(GetDlgItem(HwndDlg, IDC_EDIT1), TRUE);
					EnableWindow(GetDlgItem(HwndDlg, IDC_EDIT2), TRUE);
					EnableWindow(GetDlgItem(HwndDlg, IDC_BUTTON6), TRUE);
					EnableWindow(GetDlgItem(HwndDlg, IDC_BUTTON7), TRUE);
					EnableWindow(GetDlgItem(HwndDlg, IDC_BUTTON8), TRUE);
					EnableWindow(GetDlgItem(HwndDlg, IDC_BUTTON9), TRUE);
					EnableWindow(GetDlgItem(HwndDlg, IDC_BUTTON10), TRUE);
					EnableWindow(GetDlgItem(HwndDlg, IDC_BUTTON11), TRUE);
					EnableWindow(GetDlgItem(HwndDlg, IDC_BUTTON12), TRUE);
					EnableWindow(GetDlgItem(HwndDlg, IDC_BUTTON13), TRUE);
					EnableWindow(GetDlgItem(HwndDlg, IDC_BUTTON14), TRUE);
					EnableWindow(GetDlgItem(HwndDlg, IDC_BUTTON15), TRUE);
					EnableWindow(GetDlgItem(HwndDlg, IDC_BUTTON16), TRUE);
					EnableWindow(GetDlgItem(HwndDlg, IDC_BUTTON17), TRUE);
					EnableWindow(GetDlgItem(HwndDlg, IDC_BUTTON18), TRUE);
					EnableWindow(GetDlgItem(HwndDlg, IDC_BUTTON19), TRUE);
				}
				hDlg = HwndDlg;

				// ����Ĭ����Ϣ
				SetWindowText(GetDlgItem(hDlg, IDC_EDIT_MSG), text);
				SetWindowText(GetDlgItem(HwndDlg, IDC_EDIT3), "�Բ��������������ѵ�������ע�᱾�����");
				SetWindowText(GetDlgItem(HwndDlg, IDC_EDIT4), "www.yesite.com");
				SetWindowText(GetDlgItem(HwndDlg, IDC_EDIT5), "sales@yesite.com");
				SetWindowText(GetDlgItem(HwndDlg, IDC_EDIT6), "��������Ѿͷ");
				SetWindowText(GetDlgItem(HwndDlg, IDC_EDIT7), "�ؼҵĸо�");

				COMBOBOXEXITEM cbeItem;
				TCHAR szText[40];
				combo = GetDlgItem(HwndDlg, IDC_COMBOBOXEX1);
				
				// Add items to control
				cbeItem.mask = CBEIF_TEXT;
				cbeItem.iItem = -1;

				strcpy(szText,"�Ƿ�ע��");
				cbeItem.pszText = szText;
				cbeItem.cchTextMax = strlen(szText);
				SendMessage(combo,CBEM_INSERTITEM,0,(LPARAM)&cbeItem);
				strcpy(szText,"������Ϣ");
				cbeItem.pszText = szText;
				cbeItem.cchTextMax = strlen(szText);
				SendMessage(combo,CBEM_INSERTITEM,0,(LPARAM)&cbeItem);
				strcpy(szText,"ע���û�");
				cbeItem.pszText = szText;
				cbeItem.cchTextMax = strlen(szText);
				SendMessage(combo,CBEM_INSERTITEM,0,(LPARAM)&cbeItem);
				strcpy(szText,"ע����Ϣ");
				cbeItem.pszText = szText;
				cbeItem.cchTextMax = strlen(szText);
				SendMessage(combo,CBEM_INSERTITEM,0,(LPARAM)&cbeItem);
				strcpy(szText,"�������");
				cbeItem.pszText = szText;
				cbeItem.cchTextMax = strlen(szText);
				SendMessage(combo,CBEM_INSERTITEM,0,(LPARAM)&cbeItem);
				strcpy(szText,"���������ж��ٷ���");
				cbeItem.pszText = szText;
				cbeItem.cchTextMax = strlen(szText);
				SendMessage(combo,CBEM_INSERTITEM,0,(LPARAM)&cbeItem);
				strcpy(szText,"ÿ�����ٷ���Ҫ��ע��");
				cbeItem.pszText = szText;
				cbeItem.cchTextMax = strlen(szText);
				SendMessage(combo,CBEM_INSERTITEM,0,(LPARAM)&cbeItem);
				strcpy(szText,"ÿ���������ж��ٷ���");
				cbeItem.pszText = szText;
				cbeItem.cchTextMax = strlen(szText);
				SendMessage(combo,CBEM_INSERTITEM,0,(LPARAM)&cbeItem);
				strcpy(szText,"��һ���ڱ���ʹ�����������");
				cbeItem.pszText = szText;
				cbeItem.cchTextMax = strlen(szText);
				SendMessage(combo,CBEM_INSERTITEM,0,(LPARAM)&cbeItem);
				strcpy(szText,"������������");
				cbeItem.pszText = szText;
				cbeItem.cchTextMax = strlen(szText);
				SendMessage(combo,CBEM_INSERTITEM,0,(LPARAM)&cbeItem);
				strcpy(szText,"������������");
				cbeItem.pszText = szText;
				cbeItem.cchTextMax = strlen(szText);
				SendMessage(combo,CBEM_INSERTITEM,0,(LPARAM)&cbeItem);
				strcpy(szText,"�����д���");
				cbeItem.pszText = szText;
				cbeItem.cchTextMax = strlen(szText);
				SendMessage(combo,CBEM_INSERTITEM,0,(LPARAM)&cbeItem);
				strcpy(szText,"�������ô���");
				cbeItem.pszText = szText;
				cbeItem.cchTextMax = strlen(szText);
				SendMessage(combo,CBEM_INSERTITEM,0,(LPARAM)&cbeItem);
				strcpy(szText,"�ӿ�ʱ���õ���������ֵ");
				cbeItem.pszText = szText;
				cbeItem.cchTextMax = strlen(szText);
				SendMessage(combo,CBEM_INSERTITEM,0,(LPARAM)&cbeItem);


			}
			break;
		case WM_CLOSE:
			{
				if(P!=NULL) 
				{
					free(P);
					P=NULL;
				}
				DestroyWindow(HwndDlg);
			}
			break;
		case WM_DESTROY:
			{
				if(P!=NULL) 
				{
					free(P);
					P=NULL;
				}
				PostQuitMessage(0);
			}
			break;
		case WM_NOTIFY:
			break;
		case WM_CTLCOLORLISTBOX:
		case WM_CTLCOLOREDIT:
			{
				SetTextColor((HDC)wParam, cl);
				return (long)GetStockObject(DEFAULT_PALETTE);
			}
			break;
	}
	return FALSE;
}

void WINAPI test(int * Out)
{
	*Out = 200;
	return;
}

char * WINAPI ToHex(int nLength,unsigned char *buf)
{
	int m,n;
	int nLines;
	char tmp[65536];

	memset (str,0,32767);

	char* p = str;
	
	// ȷ������
	nLines = nLength/16;
	if (nLength % 16) nLines++;
	
	for (m = 0; m < nLines; m++)
	{
		// �����ַ
		wsprintf(tmp,"%08X  ", 16 * m);
		memcpy(p, tmp, 10);
		p += 10;
		
		// ��HEX����ʽ���
		for (n = 0; n < 16; n++)
		{
			if (m * 16 + n < nLength)
			{
				wsprintf(tmp,"%02X ", buf[m*16+n]);
			}
			else
			{
				wsprintf(tmp,"%s","   ");		// ����һ�У����
			}
			
			memcpy(p, tmp, 3);
			p += 3;
		}
		
		memcpy(p, "  ", 2);
		p += 2;
		
		// ���ַ���ʽ���
		for (n = 0; n < 16; n++)
		{
			if (m * 16 + n < nLength)
			{
				if (isprint(buf[m*16+n]) || (buf[m*16+n] >= 0xa1) && (n < 16 - 1))
				{
					wsprintf(tmp,"%c", buf[m*16+n]);		// �ɴ�ӡ�ַ�
				}
				else
				{
					wsprintf(tmp,"%s",".");		// ���ɴ�ӡ�ַ�����'.'����
				}
			}
			else
			{
				wsprintf(tmp,"%s"," ");		// ����һ�У����
			}
			memcpy(p, tmp, 1);
			p += 1;
		}
		memcpy(p, "\r\n", 2);
		p += 2;
	}
	*p = '\0';
	return str;
}