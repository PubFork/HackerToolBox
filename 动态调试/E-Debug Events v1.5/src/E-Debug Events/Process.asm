;P ��Process�ļ�д
;C ��Create�ļ�д

include psapi.inc
includelib psapi.lib

PROCESS_MEMORY_COUNTERS struct
    cb dd ?
    PageFaultCount dd ?
    PeakWorkingSetSize dd ?
    WorkingSetSize dd ?
    QuotaPeakPagedPoolUsage dd ?
    QuotaPagedPoolUsage dd ?
    QuotaPeakNonPagedPoolUsage dd ?
    QuotaNonPagedPoolUsage dd ?
    PagefileUsage dd ?
    PeakPagefileUsage dd ?
PROCESS_MEMORY_COUNTERS ENDS

.data
szMemoryUsage db 20 dup(?)
.data?
ThreadID       dd ?
hBaseSize      dd ?
hmodBaseAddr   dd ?
pi    PROCESS_INFORMATION<>

.code


;�������� 
;lpApplicationName:ָ����ִ���ļ���
;Flags�� ��־
;lpProcessInformation:ָ��һ��PROCESS_INFORMATION�ṹ������ṹ���������������½����̵������Ϣ��
;�������ִ�гɹ�������ֵ�Ƿ�0ֵ������������0��
CreateP proc lpApplicationName:DWORD,Flags:DWORD,lpProcessInformation:DWORD
	LOCAL stStartUp:STARTUPINFO
	invoke GetStartupInfo,addr stStartUp
	invoke CreateProcess,lpApplicationName,NULL,NULL,NULL,FALSE,Flags,NULL,NULL,addr stStartUp,lpProcessInformation
	ret

CreateP endp

;д�ڴ�
WritePMemory proc hProcess:DWORD,lpBaseAddress:DWORD,lpBuffer:DWORD,nSize:DWORD 
       LOCAL l_BytesWritten:DWORD
       invoke WriteProcessMemory,hProcess,lpBaseAddress,lpBuffer,nSize,addr l_BytesWritten
       ret
WritePMemory endp

;���ڴ�
ReadPMemory proc hProcess:DWORD,lpBaseAddress:DWORD,lpBuffer:DWORD,nSize:DWORD 
       LOCAL l_BytesWritten:DWORD
       invoke ReadProcessMemory,hProcess,lpBaseAddress,lpBuffer,nSize,addr l_BytesWritten
       ret
ReadPMemory endp

;��ȡָ�����̵������ڴ�,���ش�С
ReadPWholeMemory proc ProcessID:DWORD
       LOCAL l_ModuleSnap:DWORD
       LOCAL l_me32:MODULEENTRY32
       invoke CreateToolhelp32Snapshot,TH32CS_SNAPMODULE,ProcessID 
       mov l_ModuleSnap,eax
       invoke Module32First,l_ModuleSnap,addr l_me32
       mov eax,l_me32.modBaseAddr
       mov hmodBaseAddr,eax
       mov eax,l_me32.modBaseSize
       mov hBaseSize,eax
       ret
ReadPWholeMemory endp

;��ֹ����
TerminateP proc hProcess:DWORD
	invoke TerminateProcess,hProcess,NULL
	ret

TerminateP endp

;�����߳�(ThreadProc proc uses ecx Param:DWORD)
CThread proc StartFunction:DWORD
        invoke CreateThread,NULL,NULL,StartFunction,NULL,0,addr ThreadID
        invoke CloseHandle,eax
        ret

CThread endp

;ȡ�õ�ǰ���̵��ڴ�ʹ�ô�С �����ַ���
;����: 2808KB
GetMemoryUsage proc uses ecx
         LOCAL l_hP:DWORD
         LOCAL l_PM:PROCESS_MEMORY_COUNTERS
         LOCAL l_Fm[10]:BYTE

         invoke RtlZeroMemory,addr szMemoryUsage,20
         invoke RtlZeroMemory,addr l_hP,4
         invoke RtlZeroMemory,addr l_PM,sizeof PROCESS_MEMORY_COUNTERS
         invoke RtlZeroMemory,addr l_Fm,10
         invoke GetCurrentProcessId
         invoke OpenProcess,PROCESS_ALL_ACCESS,FALSE,eax
         mov l_hP,eax
         invoke GetProcessMemoryInfo,l_hP,addr l_PM,sizeof PROCESS_MEMORY_COUNTERS
         .if eax==TRUE
         	mov eax,l_PM.WorkingSetSize
         	cdq
         	mov ecx,1024
         	idiv ecx
         	lea ecx,l_Fm
         	mov byte ptr ds:[ecx],'%'
         	mov byte ptr ds:[ecx+1],'d'
         	mov byte ptr ds:[ecx+2],'K'
         	mov byte ptr ds:[ecx+3],'B'
         	invoke wsprintf,addr szMemoryUsage,ecx,eax
         .endif
         invoke CloseHandle,l_hP
         lea eax,szMemoryUsage
         ret
GetMemoryUsage endp



