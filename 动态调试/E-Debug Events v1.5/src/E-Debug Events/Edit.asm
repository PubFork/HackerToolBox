include Numeric conversion.asm

HexProcEdit proto hWin:HWND,uMsg:UINT,wParam:WPARAM,lParam:LPARAM

.data
   szAllowedChar db '0123456789ABCDEFabcdef',08,22,03,0        ;08 �˸�� 22 Ctrl+V 03 Ctrl+C
    
.data?
    lpProcEdit   dd ?
.code

;�����ı�
AppendText proc hWnd:DWORD,pText:DWORD 
   invoke SendMessage,hWnd, EM_REPLACESEL,0,pText
   invoke SendMessage,hWnd,EM_SETSEL,-1,0
   ret 
AppendText endp 

;�����ı�,���Զ�����
AppendTextNewline proc uses edi hWnd:DWORD,pText:DWORD 
   LOCAL  l_Newline:DWORD
   invoke GlobalAlloc,GPTR,600
   mov l_Newline,eax
   invoke lstrcpy,l_Newline,pText
   invoke lstrlen,l_Newline
   mov edi,l_Newline
   add edi,eax
   mov WORD ptr ds:[edi],0A0DH
   invoke SendMessage,hWnd, EM_REPLACESEL,0,l_Newline
   invoke SendMessage,hWnd,EM_SETSEL,-1,0
   invoke GlobalFree,l_Newline
   ret 
AppendTextNewline endp 


;����ı�
ClearEdit proc hWnd:DWORD
	invoke SendMessage,hWnd,WM_SETTEXT,0,0
	ret

ClearEdit endp

;EM_SETLIMITTEXT ���ø�EditΪ�ı��������
SetMaximum proc hWnd:DWORD
	invoke  SendMessage,hWnd,EM_SETLIMITTEXT,0,0
	ret

SetMaximum endp

;����Edit����󳤶�
MaxLength proc hWnd:DWORD,Num:DWORD
        invoke SendMessage,hWnd,EM_LIMITTEXT,Num,0
	ret

MaxLength endp


;���ñ༭����ֻ������16����
HexEdit proc hWin:HWND
	invoke SetWindowLong,hWin,GWL_WNDPROC,addr HexProcEdit
        mov lpProcEdit,eax
	ret

HexEdit endp

HexProcEdit proc hWin:HWND,uMsg:UINT,wParam:WPARAM,lParam:LPARAM
	mov eax,uMsg
	.if eax==WM_CHAR
	        mov eax,wParam
	        mov edi,offset szAllowedChar
	        mov ecx,sizeof szAllowedChar
	        repnz scasb
	        .if   ZERO?
	               invoke CallWindowProc,lpProcEdit,hWin,uMsg,wParam,lParam
		       ret
	        .endif
	.else
		invoke CallWindowProc,lpProcEdit,hWin,uMsg,wParam,lParam
		ret
        .endif
	xor eax,eax
	ret

HexProcEdit endp

;ȡ�༭�������ת����16��������
GetHexEdit proc hWin:HWND
        LOCAL l_String:DWORD
        LOCAL l_Ret:DWORD
        invoke GlobalAlloc,GPTR,50000
        mov l_String,eax
	invoke GetWindowText,hWin,l_String,5000
	invoke StrToHex,l_String ;Numeric conversion.asm
	mov l_Ret,eax
	invoke GlobalFree,l_String
	mov eax,l_Ret
        ret
GetHexEdit endp

;�жϱ༭��������Ƿ�Ϊ�գ�Ϊ�շ���TURE�����򷵻�FASLE 
IsEditNULL proc hWin:HWND
        LOCAL l_String:DWORD
        LOCAL l_Ret:DWORD
        invoke GlobalAlloc,GPTR,50000
        mov l_String,eax
	invoke GetWindowText,hWin,l_String,5000
	.if eax==0
		mov l_Ret,TRUE
	.else
		mov l_Ret,FALSE
	.endif
	invoke GlobalFree,l_String
	mov eax,l_Ret
	ret

IsEditNULL endp