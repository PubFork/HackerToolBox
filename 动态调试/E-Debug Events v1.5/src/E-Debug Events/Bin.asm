.code

;Ѱ���ֽڼ�(����һ�ֽڼ�����һ�ֽڼ������ȳ��ֵ�λ�ã�λ��ֵ�� 1 ��ʼ�����δ�ҵ������� -1��)
;byBin ����Ѱ���ֽڼ�
;uSize ��С
;Bin   ����Ѱ���ֽڼ�
;ubSize ��С
;Start ��ʼ��Ѱλ��
FindBin proc uses edx ebx ecx edi esi byBin:DWORD,uSize:DWORD,Bin:DWORD,ubSize:DWORD,Start:DWORD
       LOCAL l_Len:DWORD
	mov eax,ubSize
	mov l_Len,eax
	xor esi,esi
	mov edi,byBin
	mov ecx,Start
	.if Start!=1
	     add edi,ecx
	.endif
	mov ecx,uSize
	xor eax,eax
	mov ebx,Bin
	mov al,byte ptr ds:[ebx]
	repne scasb
	.while ZERO?
	       push eax
	       mov eax,uSize
	       .if ecx>=eax
		   .break
	       .endif
	       pop eax
	       mov ecx,l_Len
	       sub ecx,1
	       xor edx,edx
	       xor esi,esi
	       inc esi
	       inc ebx
	       .while ecx>0
	              mov al,byte ptr ds:[ebx]
	              mov dl,byte ptr ds:[edi+esi-1]
	              .if al==dl
	              	  inc esi
	              .else
	              	   .break
	              .endif
	              inc ebx
	       	      dec ecx
	       .endw
	       mov ecx,l_Len
	       .if ecx==esi
	             .break
	       .endif
	       mov ebx,Bin
	       mov al,byte ptr ds:[ebx]
	       mov ecx,byBin
	       mov edx,edi
	       sub edx,ecx
	       mov ecx,uSize
	       sub ecx,edx
	       .if ecx==0
	       	   .break
	       .endif
	       repne scasb
	.endw
	mov ecx,l_Len
	.if esi==ecx
	       mov eax,edi
	       mov ecx,byBin
	       sub eax,ecx
	       sub eax,1
	.else
		mov eax,-1
	.endif
	
	
	ret

FindBin endp

;�ֽڼ��滻(�������п��ܵ��滻����Ҫ���ڻ�ָ���������)
;byBin ����Ѱ���ֽڼ�
;uSize ��С
;Bin   ;�����滻���ֽڼ�
;RepBin :�����滻���ֽڼ�
;ubSize ��С
;����  �����滻�Ĵ�����ʧ�ܷ���-1
RpBin proc uses edx ebx ecx edi esi byBin:DWORD,uSize:DWORD,Bin:DWORD,RepBin:DWORD,ubSize:DWORD
        LOCAL l_S:DWORD
	mov ecx,0
	mov l_S,1
	invoke FindBin,byBin,uSize,Bin,ubSize,l_S
	.while eax!=-1
		inc ecx
		mov l_S,eax
		push ecx
		mov ecx,byBin
		add eax,ecx
		mov edi,eax
		mov ecx,ubSize
		mov esi,RepBin
		rep movsb
		pop ecx
		mov eax,l_S
		inc eax
		mov l_S,eax
		invoke FindBin,byBin,uSize,Bin,ubSize,l_S
	.endw
	.if ecx!=0
	       mov eax,ecx
	.endif
	ret
	
RpBin endp