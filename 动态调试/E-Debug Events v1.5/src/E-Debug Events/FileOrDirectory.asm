;Slash  б��
include shlwapi.inc
includelib shlwapi.lib
include shell32.inc
includelib Shell32.lib

;GetSystemDirectory ȡϵͳĿ¼ C:\windows\system32

.data
szIEPath  db 'program files\Internet Explorer\IEXPLORE.EXE',0

.code
;GetWindowsToDisk ȡϵͳ�����ڵ�Ӳ�� ����:C ��  Slash:�Ƿ���б��
GetWindowsToDisk proc lpBuffer:DWORD,uSize:DWORD,Slash:DWORD
	invoke GetWindowsDirectory,lpBuffer,uSize
	mov eax,Slash
	.if eax!=0
		invoke lstrcpyn,lpBuffer,lpBuffer,4
	.else
		 invoke lstrcpyn,lpBuffer,lpBuffer,3
	.endif
	ret

GetWindowsToDisk endp

;GetIEName; ȡIE�ļ�·�� ����:
GetIEName proc proc lpBuffer:DWORD,uSize:DWORD
	invoke GetWindowsToDisk,lpBuffer,uSize,TRUE
	invoke lstrcat,lpBuffer,addr szIEPath
	ret

GetIEName endp

;ȡ����Ŀ¼
GetRunPath proc lpBuffer:DWORD,uSize:DWORD
	invoke GetModuleHandle,NULL
	invoke GetModuleFileName,eax,lpBuffer,uSize
        invoke PathRemoveFileSpec,lpBuffer
	ret

GetRunPath endp

;ȡ����Ŀ¼
GetDesktopPath proc lpBuffer:DWORD
        invoke SHGetSpecialFolderPath,NULL,lpBuffer,CSIDL_DESKTOP,FALSE
	ret

GetDesktopPath endp




