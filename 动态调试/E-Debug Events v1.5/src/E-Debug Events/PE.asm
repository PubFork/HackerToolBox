GetImageBase proto Buffer:DWORD

.code
;���PE����Ч��
ValidPE proc Buffer:DWORD
        LOCAL l_PE:DWORD
	mov edi,Buffer
	invoke IsBadCodePtr,edi
	.if eax!=0
		jmp Error
	.endif
	assume edi:ptr IMAGE_DOS_HEADER
        .if [edi].e_magic==IMAGE_DOS_SIGNATURE 
                        add edi,[edi].e_lfanew
                        invoke IsBadCodePtr,edi
                        .if eax!=0
                        	jmp Error
                        .endif
                        assume edi:ptr  IMAGE_NT_HEADERS 
                        .if [edi].Signature==IMAGE_NT_SIGNATURE
                                 mov l_PE,TRUE
                        .else    
                                 mov l_PE,FALSE        
                        .endif
        .else
        Error:
                 mov l_PE,FALSE
        .endif
        mov eax,l_PE
	ret

ValidPE endp

;�����ṩRVA ȡ��ƫ��
GetRVASectionOffset proc uses edi esi edx ecx Buffer:DWORD,RVA:DWORD 
	   mov edi,Buffer
           mov esi,RVA
           assume edi:ptr IMAGE_DOS_HEADER
           add edi,[edi].e_lfanew
           add edi,IMAGE_NT_HEADERS.FileHeader
           assume edi:ptr IMAGE_FILE_HEADER
           movzx eax,[edi].NumberOfSections
           sub edi,IMAGE_NT_HEADERS.FileHeader
           add edi,size IMAGE_NT_HEADERS
           mov ecx,eax
Tsection:
           mov edx,edi
           mov eax,[edx+IMAGE_SECTION_HEADER.VirtualAddress]
           mov ebx,[edx+IMAGE_SECTION_HEADER.Misc.VirtualSize]
           add ebx,eax
           .if  esi>=eax
             .if esi<ebx
             	  jmp _Break
             .endif
        .endif
        add edi,size IMAGE_SECTION_HEADER
        loop Tsection
_Break:
         mov eax,[edx+IMAGE_SECTION_HEADER.PointerToRawData]
        mov ebx,[edx+IMAGE_SECTION_HEADER.VirtualAddress]
        sub ebx,eax
        mov eax,ebx
	ret

GetRVASectionOffset endp

;�����ṩoffset ȡ��ƫ��
GetSectionOffset proc uses edi esi edx ecx Buffer:DWORD,uOffset:DWORD
        mov edi,Buffer
        mov esi,uOffset
        assume edi:ptr IMAGE_DOS_HEADER
        add edi,[edi].e_lfanew
        add edi,IMAGE_NT_HEADERS.FileHeader
        assume edi:ptr IMAGE_FILE_HEADER
        movzx eax,[edi].NumberOfSections
        sub edi,IMAGE_NT_HEADERS.FileHeader
        add edi,size IMAGE_NT_HEADERS
        mov ecx,eax
        Tsection:
        mov edx,edi
        mov eax,[edx+IMAGE_SECTION_HEADER.PointerToRawData]
        mov ebx,[edx+IMAGE_SECTION_HEADER.SizeOfRawData]
        add ebx,eax
        .if  esi>=eax
             .if esi<ebx
             	  jmp _Break
             .endif
        .endif
        add edi,size IMAGE_SECTION_HEADER
        loop Tsection
_Break:
        mov eax,[edx+IMAGE_SECTION_HEADER.PointerToRawData]
        mov ebx,[edx+IMAGE_SECTION_HEADER.VirtualAddress]
        sub ebx,eax
        mov eax,ebx
        ret
GetSectionOffset endp

;�� RVA ת����ʵ�ʵ�����λ��
RVAToOffset PROC uses ebx edi esi edx ecx Buffer:DWORD,RVA:DWORD 
         invoke GetRVASectionOffset,Buffer,RVA
         mov ecx,eax
         mov eax,RVA
         sub eax,ecx
         ret
RVAToOffset endp 

;���ļ�ƫ��ת����RVA
OffsetToRVA PROC uses ebx edi esi edx ecx Buffer:DWORD,uOffset:DWORD 
	invoke GetSectionOffset,Buffer,uOffset
	mov ecx,eax
        mov eax,uOffset
        add eax,ecx
	ret

OffsetToRVA endp

;���ļ�ƫ��ת����VA

OffsetToVA proc uses ebx edi esi edx ecx Buffer:DWORD,uOffset:DWORD 
	invoke OffsetToRVA,Buffer,uOffset
	mov ebx,eax
	invoke GetImageBase,Buffer
	add eax,ebx
	ret

OffsetToVA endp

;�� RVA ת�����ڴ��ַ
RVAToVA proc uses ebx edi esi edx ecx  Buffer:DWORD,RVA:DWORD
	invoke GetImageBase,Buffer
	mov ebx,RVA
	add eax,ebx
	ret

RVAToVA endp

;�� VA ת����RVA
VAToRVA proc uses edi esi edx ecx  Buffer:DWORD,VA:DWORD
        mov ebx,VA
        invoke GetImageBase,Buffer
        sub ebx,eax
        mov eax,ebx
        ret
VAToRVA endp

;�� VA ת���� Offset
VAToOffset proc uses ebx edi esi edx ecx  Buffer:DWORD,VA:DWORD
	invoke VAToRVA,Buffer,VA
	invoke RVAToOffset,Buffer,eax
	ret

VAToOffset endp

;��ȡװ�ػ���ַ
GetImageBase proc uses ebx edi esi edx ecx Buffer:DWORD
        mov edi,Buffer
	assume edi:ptr IMAGE_DOS_HEADER
	add edi,[edi].e_lfanew
	add edi,size IMAGE_NT_HEADERS.Signature
	add edi,size IMAGE_NT_HEADERS.FileHeader
	assume edi:ptr IMAGE_OPTIONAL_HEADER32
	mov eax,[edi].ImageBase
	
        ret
GetImageBase endp

;��ȡ�����ʵ�ʵ�����λ�� �ļ�û�е���� �򷵻�0 ���򷵻���ȷ�����ݵ�ַ
GetImportOffset proc Buffer:DWORD
	mov edi,Buffer
	assume edi:ptr IMAGE_DOS_HEADER
	add edi,[edi].e_lfanew
	assume edi:ptr IMAGE_NT_HEADERS 
	mov edi,[edi].OptionalHeader.DataDirectory[sizeof IMAGE_DATA_DIRECTORY].VirtualAddress
	.if edi!=0
		invoke RVAToOffset,Buffer,edi
	.else
		 mov eax,edi
	.endif
	
	ret

GetImportOffset endp


;��ȡ�����RVA λ��
GetImportRVA proc uses edi esi edx ecx Buffer:DWORD
	mov edi,Buffer
	assume edi:ptr IMAGE_DOS_HEADER
	add edi,[edi].e_lfanew
	assume edi:ptr IMAGE_NT_HEADERS 
	mov edi,[edi].OptionalHeader.DataDirectory[sizeof IMAGE_DATA_DIRECTORY].VirtualAddress
        mov eax,edi

	
	ret

GetImportRVA endp

;��ȡ������С
GetImportSize proc Buffer:DWORD
	mov edi,Buffer
	assume edi:ptr IMAGE_DOS_HEADER
	add edi,[edi].e_lfanew
	assume edi:ptr IMAGE_NT_HEADERS 
	mov edi,[edi].OptionalHeader.DataDirectory[sizeof IMAGE_DATA_DIRECTORY].isize
        mov eax,edi

	ret

GetImportSize endp

;��ȡ������RVA λ��
GetEmportRVA  proc uses edi esi edx ecx Buffer:DWORD
        mov edi,Buffer
	assume edi:ptr IMAGE_DOS_HEADER
	add edi,[edi].e_lfanew
	assume edi:ptr IMAGE_NT_HEADERS 
	mov edi,[edi].OptionalHeader.DataDirectory.VirtualAddress
        mov eax,edi
        ret
GetEmportRVA endp

;��ȡ������offset λ��
GetEmportOffset proc uses edi esi edx ecx Buffer:DWORD
        mov edi,Buffer
	assume edi:ptr IMAGE_DOS_HEADER
	add edi,[edi].e_lfanew
	assume edi:ptr IMAGE_NT_HEADERS 
	mov edi,[edi].OptionalHeader.DataDirectory.VirtualAddress
        .if edi!=0
		invoke RVAToOffset,Buffer,edi
	.else
		 mov eax,edi
	.endif
        ret
GetEmportOffset endp


;��ȡ������С
GetEmportSize proc Buffer:DWORD
	mov edi,Buffer
	assume edi:ptr IMAGE_DOS_HEADER
	add edi,[edi].e_lfanew
	assume edi:ptr IMAGE_NT_HEADERS 
	mov edi,[edi].OptionalHeader.DataDirectory.isize
        mov eax,edi
	
	ret

GetEmportSize endp

;����RVA ȡ�����ڵ����� ���� ������
GetRVASection proc uses edi esi edx ecx Buffer:DWORD,RVA:DWORD 
	   mov edi,Buffer
           mov esi,RVA
           assume edi:ptr IMAGE_DOS_HEADER
           add edi,[edi].e_lfanew
           add edi,IMAGE_NT_HEADERS.FileHeader
           assume edi:ptr IMAGE_FILE_HEADER
           movzx eax,[edi].NumberOfSections
           sub edi,IMAGE_NT_HEADERS.FileHeader
           add edi,size IMAGE_NT_HEADERS
           mov ecx,eax
Tsection:
           mov edx,edi
           mov eax,[edx+IMAGE_SECTION_HEADER.VirtualAddress]
           mov ebx,[edx+IMAGE_SECTION_HEADER.Misc.VirtualSize]
           add ebx,eax
           .if  esi>=eax
             .if esi<ebx
             	  jmp _Break
             .endif
        .endif
        add edi,size IMAGE_SECTION_HEADER
        loop Tsection
_Break:
        mov eax,edx
        add eax,IMAGE_SECTION_HEADER.Name1
        ret
GetRVASection endp

;����Offset ȡ�����ڵ����δ�С
GetOffsetSectionSize proc uses edi esi edx ecx Buffer:DWORD,uOffset:DWORD 
	mov edi,Buffer
	mov esi,uOffset
	assume edi:ptr IMAGE_DOS_HEADER
	add edi,[edi].e_lfanew
	add edi,IMAGE_NT_HEADERS.FileHeader
	assume edi:ptr IMAGE_FILE_HEADER
	movzx eax,[edi].NumberOfSections
	sub edi,IMAGE_NT_HEADERS.FileHeader
	add edi,size IMAGE_NT_HEADERS
	mov ecx,eax
Tsection:
           mov edx,edi
           mov eax,[edx+IMAGE_SECTION_HEADER.PointerToRawData]
           mov ebx,[edx+IMAGE_SECTION_HEADER.SizeOfRawData]
           add ebx,eax
           .if  esi>=eax
             .if esi<ebx
             	  jmp _Break
             .endif
        .endif
        add edi,size IMAGE_SECTION_HEADER
        loop Tsection
_Break:
        mov eax,edx
        add eax,IMAGE_SECTION_HEADER.SizeOfRawData
        mov eax,dword ptr ds:[eax]
        ret
GetOffsetSectionSize endp

;����Offset ȡ�����ڵ����ε���һ�����ε���ʼλ��(Offset)
GetPriorOffset proc uses edi esi edx ecx Buffer:DWORD,uOffset:DWORD 
        mov edi,Buffer
	mov esi,uOffset
	assume edi:ptr IMAGE_DOS_HEADER
	add edi,[edi].e_lfanew
	add edi,IMAGE_NT_HEADERS.FileHeader
	assume edi:ptr IMAGE_FILE_HEADER
	movzx eax,[edi].NumberOfSections
	sub edi,IMAGE_NT_HEADERS.FileHeader
	add edi,size IMAGE_NT_HEADERS
	mov ecx,eax
Tsection:
           mov edx,edi
           mov eax,[edx+IMAGE_SECTION_HEADER.PointerToRawData]
           mov ebx,[edx+IMAGE_SECTION_HEADER.SizeOfRawData]
           add ebx,eax
           .if  esi>=eax
             .if esi<ebx
             	  jmp _Break
             .endif
        .endif
        add edi,size IMAGE_SECTION_HEADER
        loop Tsection
_Break:
        mov eax,edx
        sub eax,size IMAGE_SECTION_HEADER
        add eax,IMAGE_SECTION_HEADER.PointerToRawData
        mov eax,dword ptr ds:[eax]
        ret
GetPriorOffset endp