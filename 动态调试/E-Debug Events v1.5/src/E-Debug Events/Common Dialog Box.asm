include comdlg32.inc
includelib comdlg32.lib

.data
szExeFile db 'Executable Files (*.exe)',0,'*.exe',0,0
szExeFileAll db 'Executable Files (*.exe)',0,'*.exe',0
             db 'All Files(*.*)',0,'*.*',0,0  
.data?
strFile db 256 dup(?)  ;�����ļ���   
.code
;----------------------------------------------------------------
;lpstrFilter
;���ֶξ����˶Ի����С��ļ����͡�����ʽ�б���е����ݣ��ַ��������ɶ���������ɣ�ÿ�����һ��˵���ַ�����һ��ɸѡ�ַ������ַ��������������0��������������ַ��������б������ʾ�������ݣ�ѡ��ͬ��Ŀ��ʱ��ֱ��г���*.txt���ļ����������ļ���*.*����

;Text Files(*.txt)',0,'*.txt',0,'All Files(*.*)',0,'*.*',0,0

;ɸѡ�ַ�����Ҳ����ͬʱָ�������չ�����м��÷ֺŸ�������'*.txt;*.doc'��

;ʾ��:
;All Files(*.*)',0,'*.*',0,0     
;Text Files(*.txt)',0,'*.txt',0,,0
;"Executable Files (*.exe, *.dll)",0,"*.exe;*.dll",0,0
;"Executable Files (*.exe)",0,"*.exe",0,0
;----------------------------------------------------------------

;ѡ���ļ�����TRUE��δѡ�񷵻ؼ�
;���ļ��Ի���    lpstrFile �����ļ����Ļ����� ��СΪ 256 lpstrFilter ָ���ļ���ɸѡ�ַ��� ��Ϊ��
OpenFileName proc uses ecx edx lpstrFile:DWORD,lpstrFilter:DWORD
	LOCAL ofn:OPENFILENAME
	invoke RtlZeroMemory,lpstrFile,256
	invoke RtlZeroMemory,addr ofn,sizeof  OPENFILENAME
	mov ofn.lStructSize,sizeof OPENFILENAME
	mov eax,lpstrFile
	mov ofn.lpstrFile,eax
	mov ofn.nMaxFile,256
	mov eax,lpstrFilter
	.if eax!=0
		mov ofn.lpstrFilter,eax
	.endif
	mov ofn.Flags,OFN_FILEMUSTEXIST or OFN_HIDEREADONLY
	invoke GetOpenFileName,addr ofn
	ret

OpenFileName endp