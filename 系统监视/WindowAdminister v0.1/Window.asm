;<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
;�������ƣ�WindowAdminister NO 0.1
;����ϵͳ��Win 9x/Me/NT/XP
;��    �ߣ�zhanshen[DFCG][RCT]
;�������ڣ�2006-04-05
;�����ܣ����ڹ�����
;ע���������ת�أ��뱣�ֱ�����İ汾��������Ϣ��
;<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

.386
.Model Flat, StdCall
Option Casemap :None

;-----------------------------------------------
;��������
Include windows.inc
Include user32.inc
Include kernel32.inc
Include Shell32.inc
Include Gdi32.inc

IncludeLib user32.lib
IncludeLib kernel32.lib
Includelib Shell32.lib
Includelib Gdi32.lib


;-----------------------------------------------
;�Զ��庯������
DlgProc proto :DWORD,:DWORD,:DWORD,:DWORD
AboutDlgProc proto :DWORD,:DWORD,:DWORD,:DWORD
UrlLinkProc proto :DWORD,:DWORD,:DWORD,:DWORD
_Wsprintf proto :DWORD,:DWORD,:DWORD

;-----------------------------------------------
;������
.const
	DLG_MAIN							EQU	100
	DLG_ABOUT_ME					EQU	101
	DLG_WINDOW_NAME_EDIT			EQU	1000
	DLG_MY_WINDOW_TOP				EQU	1001
	DLG_REJIGGER_TITLE			EQU	1002
	ABOUT_OK							EQU	1003
	DLG_WINDOW_EDIT_HWND			EQU	1004
	DLG_WINDOW_EDIT_ID			EQU	1005
	DLG_WINDOW_EDIT_SYTLE		EQU	1006
	DLG_WINDOW_EDIT_HINSTANCE	EQU	1007
	DLG_EDIT_WNDFUNCTION			EQU	1008
	DLG_WINDOW_EDIT_CLASS		EQU	1010
	DLG_WINDOW_NOTOP				EQU	1011
	DLG_WINDOW_TOP					EQU	1012
	DLG_WINDOW_MAXIMIZE			EQU	1013
	DLG_WINDOW_MINIMIZE			EQU	1014
	DLG_WINDOW_ENABLE				EQU	1015
	DLG_WINDOW_DISABLES			EQU	1016
	DLG_WINDOW_HIDE				EQU	1017
	DLG_WINDOW_SHOW				EQU	1018
	DLG_WINDOW_CLICK				EQU	1019
	DLG_WINDOW_CLOSE				EQU	1020
	DLG_WINDOW_NOTUSESHIFT		EQU	1021
	DLG_MY_WINDOW_EXIT			EQU	1022
	DLG_MY_WINDOW_ABOUT			EQU	1023
	ABOUT_LINK_WWW_PEDIY			EQU	1024
	ABOUT_LINK_BBS_PEDIY			EQU	1025
	ABOUT_LINK_DFCG				EQU	1026
	ABOUT_LINK_RCT					EQU	1027
	ABOUT_LINK_CHINADFORCE		EQU	1028
	DLG_TIMER_ID					EQU	1
	DLG_TIMER_ELAPSE				EQU	100
	DLG_CUR							EQU	2000
	DLG_ICON							EQU	100

;-----------------------------------------------
;�ѳ�ʼ��������
.data
	szTop					db	'WindowTop',0
	szNoTop				db	'WindowNoTop',0
	szUseShift			db	'UseShift',0
	szNotUseShift		db	'NotUseShift',0
	fShiftFlag			db	FALSE
	szFormat				db	'%X',0
	szLinkWwwPediy		db	'http://www.pediy.com',0
	szLinkBbsPediy		db	'http://bbs.pediy.com',0
	szLinkDfcg			db	'http://www.chinadfcg.com/woyao/index.php',0
	szLinkRct			db	'http://debugman.wintoolspro.com/index.php',0
	szLinkChinadforce	db	'http://www.chinadforce,com',0

;-----------------------------------------------
;δ��ʼ��������
.data?
	hInstance	HINSTANCE	?
	hWinWindow	HWND			?
	hLinkCur		HWND			?

;-----------------------------------------------
;�����
.CODE
;<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
START:
	invoke GetModuleHandle,NULL
	mov hInstance,eax
	invoke DialogBoxParam,hInstance,DLG_MAIN,0,offset DlgProc,0
	invoke ExitProcess,0

_Wsprintf proc szBuff,iBuffSize,Num
	invoke RtlZeroMemory,szBuff,iBuffSize
	invoke wsprintf,szBuff,addr szFormat,Num
	ret
_Wsprintf endp
;<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

;<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
;�Զ��庯��ִ����
;���������ص�����
DlgProc proc hWnd,uMsg,wParam,lParam
LOCAL @szWinBuff1[255],@szWinBuff2[255],@szWinBuff3[255]:Byte
LOCAL @point:POINT
.if uMsg==WM_INITDIALOG  ;���ڳ�ʼ����Ϣ
	invoke LoadIcon,hInstance,DLG_ICON
	invoke SendMessage,hWnd,WM_SETICON,ICON_SMALL,eax
	invoke LoadCursor,hInstance,DLG_CUR
	mov hLinkCur,eax
	invoke SendDlgItemMessage,hWnd,DLG_MY_WINDOW_TOP,BM_CLICK,NULL,NULL
	invoke SetTimer,hWnd,DLG_TIMER_ID,DLG_TIMER_ELAPSE,NULL
.elseif uMsg==WM_COMMAND  ;��ť�����Ϣ
	mov eax,wParam
	.if ax==DLG_MY_WINDOW_EXIT  ;�˳�����
		invoke SendMessage,hWnd,WM_CLOSE,NULL,NULL
	.elseif ax==DLG_MY_WINDOW_TOP  ;�����ö���ȡ���ö�
		invoke IsDlgButtonChecked,hWnd,DLG_MY_WINDOW_TOP
		.if eax==BST_CHECKED
			invoke SetDlgItemText,hWnd,DLG_MY_WINDOW_TOP,offset szTop
			invoke SetWindowPos,hWnd,HWND_TOPMOST,NULL,NULL,NULL,NULL,SWP_NOSIZE OR SWP_NOMOVE
		.elseif eax==BST_UNCHECKED
			invoke SetDlgItemText,hWnd,DLG_MY_WINDOW_TOP,offset szNoTop
			invoke SetWindowPos,hWnd,HWND_NOTOPMOST,NULL,NULL,NULL,NULL,SWP_NOSIZE OR SWP_NOMOVE
		.endif
	.elseif ax==DLG_REJIGGER_TITLE  ;���ĳ���Ĵ��ڱ���
		invoke GetDlgItemText,hWnd,DLG_WINDOW_NAME_EDIT,addr @szWinBuff1,sizeof @szWinBuff1
		.if ((hWinWindow!=NULL)&&(eax!=0))
			invoke SetWindowText,hWinWindow,addr @szWinBuff1
		.endif
	.elseif ax==DLG_WINDOW_NOTOP  ;�ö���ȡ���ڳ���
		.if hWinWindow!=NULL
			invoke SetWindowPos,hWinWindow,HWND_NOTOPMOST,NULL,NULL,NULL,NULL,SWP_NOSIZE OR SWP_NOMOVE
		.endif
	.elseif ax==DLG_WINDOW_TOP  ;ȡ���ö���ȡ���ڳ���
		.if hWinWindow!=NULL
			invoke SetWindowPos,hWinWindow,HWND_TOPMOST,NULL,NULL,NULL,NULL,SWP_NOSIZE OR SWP_NOMOVE
		.endif
	.elseif ax==DLG_WINDOW_MAXIMIZE  ;��ȡ�������
		.if hWinWindow!=NULL
			invoke ShowWindow,hWinWindow,SW_MAXIMIZE
		.endif
	.elseif ax==DLG_WINDOW_MINIMIZE  ;��ȡ������С��
		.if hWinWindow!=NULL
			invoke ShowWindow,hWinWindow,SW_MINIMIZE
		.endif
	.elseif ax==DLG_WINDOW_ENABLE  ;�����ȡ�Ĵ���
		.if hWinWindow!=NULL
			invoke EnableWindow,hWinWindow,TRUE
		.endif
	.elseif ax==DLG_WINDOW_DISABLES  ;��ֹ��ȡ�Ĵ���
		.if hWinWindow!=NULL
			invoke EnableWindow,hWinWindow,FALSE
		.endif
	.elseif ax==DLG_WINDOW_HIDE  ;���ػ�ȡ�Ĵ���
		.if hWinWindow!=NULL
			invoke ShowWindow,hWinWindow,SW_HIDE
		.endif
	.elseif ax==DLG_WINDOW_SHOW  ;��ʾ��ȡ�Ĵ���
		.if hWinWindow!=NULL
			invoke ShowWindow,hWinWindow,SW_SHOW
		.endif
	.elseif ax==DLG_WINDOW_CLICK  ;�����ȡ�Ĵ���
		.if hWinWindow!=NULL
			invoke SendMessage,hWinWindow,BM_CLICK,NULL,NULL
		.endif
	.elseif ax==DLG_WINDOW_CLOSE  ;�رջ�ȡ�Ĵ���
		.if hWinWindow!=NULL
			invoke SendMessage,hWinWindow,WM_SYSCOMMAND,SC_CLOSE,NULL
		.endif
	.elseif ax==DLG_WINDOW_NOTUSESHIFT  ;�Ƿ�ʹ��Shift������ȡ������Ϣ
		invoke IsDlgButtonChecked,hWnd,DLG_WINDOW_NOTUSESHIFT
		.if eax==BST_CHECKED
			invoke SetDlgItemText,hWnd,DLG_WINDOW_NOTUSESHIFT,offset szNotUseShift
			mov fShiftFlag,TRUE
		.elseif eax==BST_UNCHECKED
			invoke SetDlgItemText,hWnd,DLG_WINDOW_NOTUSESHIFT,offset szUseShift
			mov fShiftFlag,FALSE
		.endif
	.elseif ax==DLG_MY_WINDOW_ABOUT
		invoke DialogBoxParam,hInstance,DLG_ABOUT_ME,hWnd,offset AboutDlgProc,NULL
	.endif
.elseif uMsg==WM_TIMER  ;��ʱ����Ϣ
	.if fShiftFlag
		jmp @f
	.endif
	invoke GetKeyState,VK_SHIFT
	test eax,80000000
	.if !ZERO?
@@:
		invoke GetCursorPos,addr @point
		invoke WindowFromPoint,@point.x,@point.y  ;ȡ�õ�ǰ��괰�ھ��
		mov hWinWindow,eax
		invoke _Wsprintf,addr @szWinBuff3,sizeof @szWinBuff3,hWinWindow
		invoke SetDlgItemText,hWnd,DLG_WINDOW_EDIT_HWND,addr @szWinBuff3
		invoke GetClassName,hWinWindow,addr @szWinBuff3,sizeof @szWinBuff3 ;��ȡ���ھ��
		invoke SetDlgItemText,hWnd,DLG_WINDOW_EDIT_CLASS,addr @szWinBuff3
		invoke GetWindowLong,hWinWindow,GWL_STYLE  ;��ȡ���ڷ��
		invoke _Wsprintf,addr @szWinBuff3,sizeof @szWinBuff3,eax
		invoke SetDlgItemText,hWnd,DLG_WINDOW_EDIT_SYTLE,addr @szWinBuff3
		invoke GetWindowLong,hWinWindow,GWL_ID  ;��ȡ����ID
		invoke _Wsprintf,addr @szWinBuff3,sizeof @szWinBuff3,eax
		invoke SetDlgItemText,hWnd,DLG_WINDOW_EDIT_ID,addr @szWinBuff3
		invoke GetWindowLong,hWinWindow,GWL_HINSTANCE  ;��ȡ����ģ��
		invoke _Wsprintf,addr @szWinBuff3,sizeof @szWinBuff3,eax
		invoke SetDlgItemText,hWnd,DLG_WINDOW_EDIT_HINSTANCE,addr @szWinBuff3
		invoke GetWindowLong,hWinWindow,GWL_WNDPROC  ;��ȡ���ڻص�����
		invoke _Wsprintf,addr @szWinBuff3,sizeof @szWinBuff3,eax
		invoke SetDlgItemText,hWnd,DLG_EDIT_WNDFUNCTION,addr @szWinBuff3
		invoke GetWindowText,hWinWindow,addr @szWinBuff2,sizeof @szWinBuff2
		invoke SetDlgItemText,hWnd,DLG_WINDOW_NAME_EDIT,addr @szWinBuff2
	.endif
.elseif uMsg==WM_CLOSE   ;�رճ���
	invoke KillTimer,hWnd,DLG_TIMER_ID
	invoke EndDialog,hWnd,FALSE
.else
	mov eax,FALSE
	ret
.endif
mov eax,TRUE
ret
DlgProc endp

;<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
;���ڶԻ���ص�����
AboutDlgProc proc uses edi esi hWnd,uMsg,wParam,lParam
LOCAL @hFontOut:DWORD
LOCAL @st_hFont:LOGFONT
	.if uMsg==WM_INITDIALOG
		invoke LoadIcon,hInstance,100
		invoke SendMessage,hWnd,WM_SETICON,ICON_SMALL,eax
		mov edi,1024
		.while edi <= 1028   ;���໯��������
			invoke GetDlgItem,hWnd,edi
			mov esi,eax
			invoke SetWindowLong,esi,GWL_WNDPROC,offset UrlLinkProc
			invoke SetWindowLong,esi,GWL_USERDATA,eax
			inc edi
		.endw
	.elseif uMsg==WM_CTLCOLORSTATIC  ;�ػ���������������ɫ��������ɫ
		invoke GetDlgCtrlID,lParam
		.if (eax>=1024) && (eax<=1028)
			invoke SendMessage,lParam,WM_GETFONT,NULL,NULL
			mov @hFontOut,eax
			invoke GetObject,@hFontOut,sizeof LOGFONT,addr @st_hFont
			mov @st_hFont.lfUnderline,NULL
			invoke CreateFontIndirect,addr @st_hFont
			mov @hFontOut,eax
			invoke SelectObject,wParam,eax
			invoke SetTextColor,wParam,0FF0000h
			invoke GetSysColor,15
			invoke SetBkColor,wParam,eax
			invoke DeleteObject,@hFontOut
			invoke GetStockObject,5
		.else
			xor eax,eax
			ret
		.endif
		ret
	.elseif uMsg==WM_COMMAND
		mov eax,wParam
		.if ax==ABOUT_OK
			invoke EndDialog,hWnd,FALSE
		.endif
	.elseif uMsg==WM_CLOSE
		invoke EndDialog,hWnd,FALSE
	.else
		xor eax,eax
		ret
	.endif
	mov eax,TRUE
	ret
AboutDlgProc endp

;<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
;Label�ؼ��ص��������໯����
UrlLinkProc proc hWnd,uMsg,wParam,lParam
	.if uMsg==WM_LBUTTONUP
		invoke GetDlgCtrlID,hWnd
		.if eax==ABOUT_LINK_WWW_PEDIY
			mov eax,offset szLinkWwwPediy
		.elseif eax==ABOUT_LINK_BBS_PEDIY
			mov eax,offset szLinkBbsPediy
		.elseif eax==ABOUT_LINK_DFCG
			mov eax,offset szLinkDfcg
		.elseif eax==ABOUT_LINK_RCT
			mov eax,offset szLinkRct
		.elseif eax==ABOUT_LINK_CHINADFORCE
			mov eax,offset szLinkChinadforce
		.endif
		invoke ShellExecute,NULL,NULL,eax,NULL,NULL,SW_SHOW
	.elseif uMsg==WM_NCHITTEST
		mov eax,TRUE
		ret
	.elseif uMsg==WM_SETCURSOR
		invoke SetCursor,hLinkCur
	.else
		invoke GetWindowLong,hWnd,GWL_USERDATA
		invoke CallWindowProc,eax,hWnd,uMsg,wParam,lParam
		ret
	.endif
	xor eax,eax
	ret
UrlLinkProc endp

END START