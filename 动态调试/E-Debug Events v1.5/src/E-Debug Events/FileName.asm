include shlwapi.inc
includelib shlwapi.lib

;P ��ʾPath
;FileName ��ʾ�ļ��� ����: SectionDIY.exe
;----------------
;PathStripPath
;����:�Ƴ�pszPathָ����·����Ŀ¼�ļ�
;ʾ��:
;TCHAR szPath[] = _T("D:\\����С˵\\���ļ�.pdf");
;::PathStripPath( szPath );
;//szPathֵΪ:���ļ�.pdf)

;PathRemoveFileSpec
;ԭ��:BOOL PathRemoveFileSpec(  LPTSTR pszPath );
;����:�Ƴ�pszPathָ����·��ĩβ���ļ����ͷ�б�ܲ���(�������)
;ʾ��:
;TCHAR szPath[] = _T("D:\\����С˵\\���ļ�.pdf");
;PathRemoveFileSpec( szPath )
;//szPathֵΪ: D:\����С˵


.const
ReplacePszPath equ 1

.code

;����: �������ļ���
;pszPath ԭ·��
;lpPath  �ṩ�������������µ�·�� (ReplacePszPath ��ʹ�ô˲�����ֱ���滻pszPath)
;FileName �ļ���
;ʾ��: pszPath : C:\Text.exe lpPath: ReplacePszPath  FileName: Rt.exe
; ִ�к�:   pszPath: C:\Rt.exe
PRenameFileName proc pszPath:DWORD,lpPath:DWORD,FileName:DWORD
	
        .if lpPath==ReplacePszPath
                invoke PathRemoveFileSpec,pszPath
	        invoke PathAddBackslash,pszPath
	        invoke lstrcat,pszPath,FileName
	.else
		invoke lstrcpy,lpPath,pszPath
		invoke PathRemoveFileSpec,lpPath
	        invoke PathAddBackslash,lpPath
	        invoke lstrcat,lpPath,FileName
        .endif
	ret

PRenameFileName endp

;����: ���ļ����в����ַ���
;String ������ַ���
;ʾ��: pszPath : C:\Text.exe lpPath: ReplacePszPath  FileName: _
; ִ�к�:   pszPath: C:\Text_.exe
PRenameInsertFileName  proc uses ecx ebx pszPath:DWORD,lpPath:DWORD,String:DWORD
         LOCAL l_File[256]:byte
        invoke RtlZeroMemory,addr l_File,256
        invoke PathFindExtension,pszPath
        mov ebx,eax
        mov ecx,pszPath
        sub eax,ecx
        inc eax
        invoke lstrcpyn,addr l_File,pszPath,eax
        invoke lstrcat,addr l_File,String
        invoke lstrcat,addr l_File,ebx
        .if lpPath==ReplacePszPath
               invoke lstrcpy,pszPath,addr l_File
	.else
		invoke lstrcpy,lpPath,addr l_File
        .endif
	ret

PRenameInsertFileName endp


;GetDirectoryLenȡ�ļ�����Ŀ¼���ȷ������ļ���c:\cektop\file.ext��ʱ�����ｫ����9(c:\cektop)��
GetDirectoryLen proc String:DWORD
	mov eax,String
	invoke lstrlen,eax
	mov ecx,eax
	mov eax,String
	add eax,ecx
	mov edi,eax
	dec edi
	xor eax,eax
	.while  ecx!=0
		mov al,byte ptr ss:[edi]
		.if eax==5CH
			mov eax,ecx
			dec eax
			.break
		.endif
		dec ecx
		dec edi
		xor eax,eax
	.endw
	ret

GetDirectoryLen endp

;GetDirectory ȡ�ļ�����Ŀ¼ szFile:�ļ��� lpBuffer:����Ŀ¼�Ļ����� ����:szFile c:\cektop\file.ext lpBuffer=c:\cektop
GetDirectory proc  szFile:DWORD,lpBuffer:DWORD
        push edi
	mov eax,szFile
	;invoke RtlZeroMemory,eax,nMaxCount
	invoke GetDirectoryLen,eax
	.if eax!=0
		inc eax
	.endif
	invoke lstrcpyn,lpBuffer,szFile,eax
	pop edi
	ret

GetDirectory endp

;GetFilName ����FileName���ڴ��ַ String:�ļ���  ����: String c:\cektop\file.ext  �򷵻�file.ext���ڴ��ַ
GetFilName proc String:DWORD
        push edi
        mov eax,String
	invoke lstrlen,eax
	mov ecx,eax
	mov eax,String
	add eax,ecx
	mov edi,eax
	dec edi
	xor eax,eax
	.while  ecx!=0
		mov al,byte ptr ss:[edi]
		.if eax==5CH
			mov eax,edi
			inc eax
			.break
		.endif
		dec ecx
		dec edi
		xor eax,eax
	.endw
	pop edi
        ret
         
GetFilName endp



;GetDefExt ����DefExt���ڴ��ַ String:�ļ���  ����: String c:\cektop\file.ext  �򷵻�ext���ڴ��ַ
GetDefExt proc String:DWORD
        push edi
        mov eax,String
	invoke lstrlen,eax
	mov ecx,eax
	mov eax,String
	add eax,ecx
	mov edi,eax
	dec edi
	xor eax,eax
	.while  ecx!=0
		mov al,byte ptr ss:[edi]
		.if eax==2eH
			mov eax,edi
			inc eax
			.break
		.endif
		dec ecx
		dec edi
		xor eax,eax
	.endw
	pop edi
        ret
GetDefExt endp

;GetFilNameUDefExt ȡ�ļ���������׺ szFile:�ļ��� lpBuffer:����Ŀ¼�Ļ����� ����:szFile c:\cektop\file.ext lpBuffer=cektop
GetFilNameUDefExt proc szFile:DWORD,lpBuffer:DWORD
        LOCAL  Temp:DWORD
        invoke GetFilName,szFile
        mov Temp,eax
        invoke GetDefExt,szFile
        mov ecx,Temp
        sub eax,ecx
        .if eax>=0
        	invoke lstrcpyn,lpBuffer,Temp,eax
        .endif
        ret
GetFilNameUDefExt endp


;CatFilNameUDefExt ׷��FilNameUDefExt szFile:�ļ��� AppStr:׷�ӵ��ı� ����: szFile c:\cektop\file.ext  AppStr: _cn ��szFileΪ c:\cektop\file_cn.ext
CatFilNameUDefExt proc szFile:DWORD,AppStr:DWORD
        LOCAL hMem:DWORD
        LOCAL hMemUDefExt:DWORD
        LOCAL  Temp:DWORD
        invoke GlobalAlloc,GPTR,256
        mov hMem,eax
        .if eax!=0
        	invoke GetDirectory,szFile,eax
        	.if eax!=0
        	       mov Temp,eax
        	       invoke lstrlen,eax
        	       mov ebx,Temp
        	       add eax,ebx     	       
        	       mov byte ptr ss:[eax],5cH
        	       invoke GlobalAlloc,GPTR,256
        	       .if eax!=0
        	       	      mov hMemUDefExt,eax
        	       	      invoke GetFilNameUDefExt,szFile,eax
        	       	      mov eax,hMemUDefExt
        	       	      invoke lstrcat,eax,AppStr
        	       	      invoke GetDefExt,szFile
        	       	      dec eax
        	       	      mov ebx,hMemUDefExt
        	       	      invoke lstrcat,ebx,eax
        	       	      mov eax,hMem
        	       	      mov ebx,hMemUDefExt
        	       	      invoke lstrcat,eax,ebx
        	       	      mov eax,hMem
        	       	      invoke lstrcpy,szFile,eax
        	       .endif
        	       
        	.endif
        	invoke GlobalFree,hMem
        	invoke GlobalFree,hMemUDefExt
        .endif
        mov eax,szFile
        ret
CatFilNameUDefExt endp
