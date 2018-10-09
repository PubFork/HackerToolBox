include shell32.inc
includelib shell32.lib
.const
WM_SHELLNOTIFY equ WM_USER+125
MAIN_ICO       equ 1

.data?
note NOTIFYICONDATA <?> 
.code

;���ô���ICOͼ��
SetMainICO proc hWin:HWND,IcoID:DWORD
	invoke GetModuleHandle,NULL
	invoke LoadIcon,eax,IcoID
	invoke SendMessage,hWin,WM_SETICON,ICON_BIG,eax
	ret

SetMainICO endp



;���ô��ڱ�������˵�λ�ã���ʹ����ͣ�á�(Stay on Top)
;uTop �Ƿ�������ǰ 1��True 0:False
TopMostWindow proc hWin:DWORD,uTop:DWORD
	
	mov eax,uTop
	.if eax==1
		invoke SetWindowPos,hWin, HWND_TOPMOST,0,0,0,0,SWP_NOMOVE or SWP_NOSIZE
	.else
		invoke SetWindowPos,hWin, HWND_NOTOPMOST,0,0,0,0,SWP_NOMOVE or SWP_NOSIZE
	.endif
	ret

TopMostWindow endp


;�϶�����(WM_DROPFILES)
;DragAcceptFiles �Ƿ�����϶�
;DragFinish �ͷ��Ϸ��ļ�ʱʹ�õ���Դ
;DragQueryFile ��ѯ�϶����ļ���

;ע���϶�����
DragAcceptFile proc hWin:HWND
          invoke DragAcceptFiles,hWin,TRUE
          ret
DragAcceptFile endp

;ȡ���������϶��ļ�������
DragFileNumber proc wParam:WPARAM
	invoke DragQueryFile,wParam,-1,NULL,NULL
	ret

DragFileNumber endp

;��ѯ��һ���ļ�
DragQueryFirstFile proc wParam:WPARAM,ulpFile:DWORD,uSize:DWORD
	invoke RtlZeroMemory,ulpFile,uSize
	invoke DragQueryFile,wParam,0,ulpFile,uSize
	ret

DragQueryFirstFile endp

;������ͼ��(WM_SHELLNOTIFY )
;WM_SHELLNOTIFY ������ΪWM_USER+5��ֻҪ��Ψһ��ֵ��������ν�Ƕ����ˣ�ֻҪ����WM_USER��
;��ʾ�ı�
SetTrayIcon proc hWnd:DWORD,TooltipText:DWORD,IcoID:DWORD
        mov note.cbSize,sizeof NOTIFYICONDATA 
        push hWnd
        pop note.hwnd 
        mov note.uID,0
        mov note.uFlags,NIF_ICON+NIF_MESSAGE+NIF_TIP 
        mov note.uCallbackMessage,WM_SHELLNOTIFY
        invoke GetModuleHandle,NULL
	invoke LoadIcon,eax,IcoID
        mov note.hIcon,eax
        invoke lstrcpy,addr note.szTip,TooltipText
        invoke Shell_NotifyIcon,NIM_ADD,addr note
        ret
SetTrayIcon endp

;ɾ��ͼ�ꡣ�ͷ�SetTrayIcon ���õ�ͼ��
DeleteTrayIcon proc
        invoke Shell_NotifyIcon,NIM_DELETE,addr note
        ret
DeleteTrayIcon endp


;Enable ������ָֹ���Ĵ���(EnableWindow HWND hWnd, BOOL bEnable)
;hDlg 
;nIDDlgItem �ؼ���ʶ��
;bEnable  TRUE ���� FALSE ��ֹ
Enable proc hDlg:DWORD,nIDDlgItem:DWORD,bEnable:DWORD
        invoke GetDlgItem,hDlg,nIDDlgItem
        invoke EnableWindow,eax,bEnable
        ret
Enable endp

