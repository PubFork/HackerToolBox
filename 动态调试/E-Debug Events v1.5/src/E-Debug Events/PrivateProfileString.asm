.code

;��������
;lpAppName:������
;lpKeyName:����������
;lpDefault:Ĭ���ı�
;lpReturnedString: ����ָ�������ļ���ָ����Ŀ���ı����ݡ�
;nSize:��С
;lpFileName:�����ļ���

GetKeyText proc lpAppName:DWORD,lpKeyName:DWORD,lpDefault:DWORD,lpReturnedString:DWORD,nSize:DWORD,lpFileName:DWORD
     invoke GetPrivateProfileString,lpAppName,lpKeyName,lpDefault,lpReturnedString,nSize,lpFileName
     ret
     
GetKeyText endp

;д������
;lpString:��д��ֵ

SetKeyText proc lpAppName:DWORD,lpKeyName:DWORD,lpString:DWORD,lpFileName:DWORD
	invoke WritePrivateProfileString,lpAppName,lpKeyName,lpString,lpFileName
	
	ret

SetKeyText endp