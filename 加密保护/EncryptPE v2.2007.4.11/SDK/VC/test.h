// EncryptPE.cpp : Defines the entry point for the application.
//

#include <windows.h>
#include <stdlib.h>
#include <malloc.h>

HWND RegisterHandle = NULL;
char RegisterStrings[4096];
char Result[4096];
char item[1024];
extern HWND hDlg;
typedef struct _UserRecord
{
    int Bz;
    int ValueSize;
    int ValueBuf;
    int PassSize;
    int PassBuf;
}UserRecord, * PUserRecord;

UserRecord UR;
PUserRecord P;


//////////////////////////////////////////////////////////
// ����ԭ��

// �ڵ��� SDK ֮ǰ��ȡ�����ͨ�ŵĴ��ھ����
// һ������������ĳ�ʼ����ɺ���ô˺���
void GetRegisterHandle(HINSTANCE hInstance);

// ȡ�ù� 15 ��ע�������Ϣ����INDEXֵ��
// 0 �Ƿ�ע��(Y/N)��
// 1 ������Ϣ��
// 2 ע���û���
// 3 ע����Ϣ��
// 4 ������ƣ�ע�ᴰ�ڱ��⣩
// 5 ���������ж��ٷ��ӣ�
// 6 ÿ�����ٷ���Ҫ��ע�ᣬ
// 7 ÿ���������ж��ٷ���
// 8 ��һ���ڱ���ʹ����������ڣ���ʽYYYYMMDD��
// 9 �����������ڣ���ʽYYYYMMDD
// 10 ��������������
// 11 �����д�����
// 12 �������ô�����
// 13 �ӿ�ʱ���õ���������ֵ��14Ϊ���������EPEHashֵ�������˶����ж��Ƿ��ƽ��
// ��������ָ���ͬʱȫ�������� RegisterStrings ��
char * GetRegisterInfo(UINT Index);

// ȡ��ע���û����ƣ�δע����Ϊ�գ�GetRegisterInfo(2)����δע��Ҳ��ֵ
char * GetRegisterUser();

// ��ʾע�ᴰ��
BOOL ShowRegisterForm();

// ��EncryptPE���ܳ������й����в�����ProcessNameָ���Ľ��̣�����.EXE�����У�
// ����������ε��øú����������ö��Ÿ������������
BOOL KillProcess(char * ProcessName);

// ȡ����ɱ���� KillProcess
BOOL NotKillProcess(char *ProcessName);

// ���üӿǽ����в�������ص�ģ�����������Զ��Ÿ������ģ����
bool KillDLL(char *DLLName);

// ��ȡָ���ִ���EPEHashֵ
char * EPEHash(char *SourceString);
//�ÿ�ȥִ�б��ӿǳ����ĳ��������������������ܶ���ִ�У����޲����޷���ֵ��
//Address�Ǻ�����ʵ��ַ�뱣�������HASHֵǰ��λ�������λ��ǰ��0��ת�����������Լ�������������������
bool RunFunction(DWORD Address);

////////////////////////////////////////////////////////////////////
//���º���Ҫ����˿���������
////////////////////////////////////////////////////////////////////

//��ȡ�ӿ�ʱ���õ������ļ������ݣ�����ָ���ӵڼ����ֽڿ�ʼ��ȡ�೤����
void * GetSavedData(unsigned short From, unsigned short Len);

// д��ע���û�����ע����Ϣ���� GetRegisterInfo ��Ͽ�������Ƹ���ע�ᴰ��
BOOL WINAPI SetRegisterInfo(char *User, char *Info);

// �ı�ע��ܿڵĽ�������Ԫ�أ�PLanguage ָ���ڴ棨�������ź�ʡ�Ժţ���
// һ���ֽ��ַ�����һ���ֽ������С���������ƣ�0���ַ���4��0���ַ���5��0��......���ַ���17��0
// ��һ���ַ�����#134#9'����'#0'����'#0'����δ֪����'��0......'ȡ��(&C)'#0
// �����û���д�����Գ���
BOOL SetLanguage(DWORD PLanguage);

// �ı�ע�ᴰ�ڵ���ʾ����վ��ҳ���ʼ���ַ����Ϣ��PHintָ���ڴ棨�������ţ�:
// ���ں��������ɫת���ɵ��ַ�����0����ʾ��Ϣ��0����ҳ��0�������ַ��0
// ��һ���ַ�����'$0000FF'#0'��ע�᱾���'#0'http://www.server.com'#0'mailto:someone@server.com'#0}
BOOL SetRegisterHint(int PHint);

// ��Indexȡֵ0��9�ֱ��Ӧ�������£�
// + - * div mod and or xor shl shr
// ����ֵΪĳһ�����Ľ��ֵ,+�����ڸ��˿�����
int EPECaclResult(int Value1, int Value2, char Index);

///////////////////////////////////////////////////
//���º���Ҫ����ҵרҵ������
///////////////////////////////////////////////////

// ���ط�Χ�� >=0 �� < Value ���������
int EPERandom(int Value);

// ��Indexȡֵ0��9�ֱ𷵻أ�
// ϵͳ�汾VER_PLATFORM_WIN32S(0) VER_PLATFORM_WIN32_WINDOWS(1) VER_PLATFORM_WIN32_NT(2),
// GetTickCount, GetCurrentProcess, GetCurrentProcessID, GetCurrentThread, GetCurrentThreadID,
// GetActiveWindow, GetFocus, GetForegroundWindow, GetDesktopWindow
WORD EPECustomValue(int Index);


//////////////////////////////////////////////////////
//���º���Ҫ����ҵ����������
//////////////////////////////////////////////////////

// ��Indexȡֵ0��9�Դ��ھ��aHwndִ�����WINDOW�����жϽ����
// IsWindow, IsWindowVisible, IsIconic, IsZoomed, ��ʾ����, ���ش���,
// ʹ���������û�����, ʹ���ڲ������û�����, IsWindowEnabled, CloseWindow, DestroyWindow
BOOL EPEWindowFunction(int Index, HWND aHwnd);

// ����Size��С�ڴ�ռ�
DWORD EPEGetMem(int Size);

// �ͷ��ڴ�
BOOL EPEFreeMem(DWORD Buf);

// ���һ���ڴ�
BOOL EPEZeroMemory(DWORD Buf, int Size);

// ��Fill�ֽ�ֵ���һ���ڴ�
BOOL EPEFillMemory(DWORD Buf,int Size,char Fill);

// �ڴ渴��
BOOL EPECopyMemory(DWORD Destination, DWORD Source,int Size);

// �ڴ��ƶ�
BOOL EPEMoveMemory(DWORD Destination, DWORD Source,int Size);

// ��Indexȡֵ0��5�ֱ��ã�
// GetCurrentDirectory, GetWindowsDirectory, GetSystemDirectory,
// GetTempPath, GetComputerName, GetUserName
char * EPESystemStr(int Index);

// �ڴ�����ѹ��
void WINAPI Compress(int InBuf,int InBytes,int OutBuf,int * OutBytes, char * Password);

// ѹ��������ݽ�ѹ��
void Decompress(int InBuf,int InBytes,int OutBuf,int * OutBytes,char * Password,int OutEstimate);

// �ַ���ѹ�������µ��ַ���
char * StringCompress(char * SourceString,char * Password,BOOL HFlag);

// ��ѹ�����ɵ��ַ�����ѹ����ԭ��ԭ�ַ���
char * StringDecompress(char *SourceString,char * Password,BOOL HFlag);

// ��һ���ڴ����ݽ��м���
void Encrypt(int InBuf,int InBytes,int OutBuf,int * OutBytes,char * Password);

// ���Ѽ������ݽ��н���
void Decrypt(int InBuf,int InBytes,int OutBuf,int * OutBytes,char * Password);

// ���ַ������м��������µ��ַ���
char * StringEncrypt(char *SourceString,char * Password,BOOL HFlag);

// ���������ɵ��ַ������ܻ�ԭ��ԭ�ַ���
char * StringDecrypt(char *SourceString,char * Password,BOOL HFlag);


// �ڲ�ʹ�ú���
BOOL IsLibrary(HINSTANCE hInstance);

void GetRegisterHandle(HINSTANCE hInstance)
{
	P = &UR;
	char TempStr[MAX_PATH];
	unsigned int i;
	HANDLE hFileMap;
	HANDLE TempP;
	RegisterHandle = 0;
	GetModuleFileName(hInstance,TempStr,MAX_PATH);
	
	for(i=0;i<strlen(TempStr);i++)
	{
		if(TempStr[i]==92) TempStr[i]=47;
	}
	
	DWORD ccid = GetCurrentProcessId();
	char t[4096];
	wsprintf(t,"%s%s%08X",TempStr, "/" ,ccid);

	hFileMap = OpenFileMapping(FILE_MAP_WRITE, false, t);
	
	if (hFileMap > 0)
	{
		TempP = MapViewOfFile(hFileMap, FILE_MAP_WRITE, 0, 0, 0);

		if (TempP != NULL)
		{
			CopyMemory (&RegisterHandle, TempP, 4);
			UnmapViewOfFile(TempP);
		}
		CloseHandle(hFileMap);
		memset(RegisterStrings,0,4096);
	}
}

char * GetRegisterInfo(UINT Index = 0)
{
	memset(Result,0,4096);
	memset(item,0,1024);

	int s=sizeof(P);
	memset(P,0,s);

	char * Re= Result;
	int i, MessageResult;
	char msg[1024];
	wsprintf (msg,"%d",Index);

	if (Index == 0) 
	{
		wsprintf(Result,"%s","N");
	}

	if (Index == 4 && !IsLibrary(NULL)) 
	{
		GetWindowText(GetDlgItem(hDlg, IDD_APP), Result,4096);
	}

	if (!IsWindow(RegisterHandle)) return Result;

	for (i = 1; i <= 100; i++)
	{
		MessageResult = SendMessage(RegisterHandle, WM_USER, 0, 1);
		if (MessageResult != -1 && MessageResult != 0)
		{
			Re = (char *)MessageResult;
			strcpy(RegisterStrings,Re);
			int index2=0,pos=0;
			for(int j=0;j<strlen(RegisterStrings);j++)
			{
				if(RegisterStrings[j]==13 && RegisterStrings[j+1]==10)
				{
					if(index2==Index)
					{
						CopyMemory(&item,&RegisterStrings[pos],j-pos);
						return item;
					}
					else
					{
						index2=index2+1;
						pos = j+2;
					}
				}
			}
		}
	}
	return Re;
}

char * GetRegisterUser()
{
	if (IsWindow(RegisterHandle))
	{
		if (GetRegisterInfo() == "Y") 
		{
			int index2=0,pos=0;
			for(int j=0;j<strlen(RegisterStrings);j++)
			{
				if(RegisterStrings[j]==13 && RegisterStrings[j+1]==10)
				{
					if(index2==2)
					{
						CopyMemory(&item,&RegisterStrings[pos],j-pos);
						return item;
					}
					else
					{
						index2=index2+1;
						pos = j+2;
					}
				}
			}
		}
		else return "";
	}
	return "";
}

BOOL ShowRegisterForm()
{
	int s=sizeof(P);
	memset(P,0,s);

	int i, MessageResult;
	if (!IsWindow(RegisterHandle)) return false;
	
	for (i = 1 ;i<=100;i++)
	{
		MessageResult = SendMessage(RegisterHandle, WM_USER, 0, 0);
		if (MessageResult == 1) return true;
	}
	return false;
}

BOOL KillProcess(char * ProcessName)
{
	int s=sizeof(P);
	memset(P,0,s);
	int i, MessageResult;
	
	if (ProcessName[0] == 0 || !IsWindow(RegisterHandle)) return false;

	for (i = 1; i <= 100; i++)
	{
		MessageResult = SendMessage(RegisterHandle, WM_USER, 88, (long)ProcessName);
		if (MessageResult == 1) return true;
	}
	return false;
}

BOOL NotKillProcess(char *ProcessName)
{
	int s=sizeof(P);
	memset(P,0,s);
	int i, MessageResult;
	
	if (ProcessName[0] == 0 || ! IsWindow(RegisterHandle)) return false;

	for (i = 1; i <= 100; i++)
	{
		MessageResult = SendMessage(RegisterHandle, WM_USER, 89, (long)ProcessName);
		if (MessageResult == 1) return true;
	}
	return false;
}

BOOL KillDLL(char *DLLName)
{
	int s=sizeof(P);
	memset(P,0,s);
	int i, MessageResult;
	
	if (! IsWindow(RegisterHandle)) return false;

	for (i = 1; i <= 100; i++)
	{
		MessageResult = SendMessage(RegisterHandle, WM_USER, 90, (long)DLLName);
		if (MessageResult == 1) return true;
	}
	return false;
}

char * EPEHash(char* SourceString)
{
    int i ,MessageResult ;
    char *pszReturn = NULL;
    if (::IsWindow(RegisterHandle) == false)
    {
        return pszReturn;
    }
    for(i = 1 ; i <= 100 ; i ++)
    {
        MessageResult = ::SendMessage(RegisterHandle,WM_USER, 99,(LPARAM)(SourceString));
        if ((MessageResult != -1)  && (MessageResult != 0))
        {
            pszReturn = (char *)MessageResult;
            break;
        }
    }
    return pszReturn;
}

bool RunFunction(DWORD Address);
{
    int i ,MessageResult ;
    bool bReturn = false;
    if (::IsWindow(RegisterHandle) == false)
    {
        return bReturn;
    }
    for(i = 1 ; i <= 100 ; i ++)
    {
        MessageResult = ::SendMessage(RegisterHandle,WM_USER, 66,(LPARAM)(Address));
        if (MessageResult == 1)
        {
            bReturn = true;
            break;
        }
    }
    return bReturn;
}

void * GetSavedData(unsigned short From, unsigned short Len);
{
    int i ,MessageResult ;
    void * vReturn = NULL;
    if (::IsWindow(RegisterHandle) == false)
    {
        return pszReturn;
    }
    for(i = 1 ; i <= 100 ; i ++)
    {
        MessageResult = ::SendMessage(RegisterHandle,WM_USER, 77,From << 16 + Len);
        if ((MessageResult != -1)  && (MessageResult != 0))
        {
            vReturn = (void *)MessageResult;
            break;
        }
    }
    return vReturn;
}

bool SetLanguage(DWORD PLanguage)
{
	int s=sizeof(P);
	memset(P,0,s);
	int i, MessageResult;
	if (PLanguage==NULL || !IsWindow(RegisterHandle)) return false;
	
	for (i = 1; i <= 100; i++)
	{
		MessageResult = SendMessage(RegisterHandle, WM_USER, 1000, (int)PLanguage);
		if (MessageResult == 1) return true;
	}
	return false;
}

BOOL SetRegisterHint(int PHint)
{
	int s=sizeof(P);
	memset(P,0,s);
	int i, MessageResult;
	
	if (PHint==NULL || !IsWindow(RegisterHandle)) return FALSE;
	
	for (i = 1; i <= 100; i++)
	{
		MessageResult = SendMessage(RegisterHandle, WM_USER, 10000, PHint);
		if (MessageResult == 1) return TRUE;
	}
	return FALSE;
}

int EPECaclResult(int Value1, int Value2, char Index)
{
	
	int s=sizeof(P);
	memset(P,0,s);
	int i, MessageResult;
	
	if (!IsWindow(RegisterHandle))
		return 0;
	P->Bz = Index;
	P->ValueSize = Value1;
	P->PassSize = Value2;

	for (i = 1; i <= 100; i++)
	{
		MessageResult = SendMessage(RegisterHandle, WM_USER, 5, (long)P);
		if (MessageResult == 1) return P->ValueSize;
	}
	return 0;
}

int EPERandom(int Value)
{
	int s=sizeof(P);
	memset(P,0,s);
	int i;
	
	int Result = 0;
	if (!IsWindow(RegisterHandle)) return 0;

	for (i = 1; i <= 100; i++)
	{
		Result = SendMessage(RegisterHandle, WM_USER, 15, Value);
		if (Result != -1) break;
	}
	return Result;
}

WORD EPECustomValue(int Index)
{
	int s=sizeof(P);
	memset(P,0,s);
	int i;
	
	WORD Result = 0;
	if (Index < 0 || Index > 9 || ! IsWindow(RegisterHandle)) return 0;
	
	for (i = 1; i <= 100; i++)
	{
		Result = (WORD) SendMessage(RegisterHandle, WM_USER, 25, Index);
		if (Result != -1) break;
		else if (Index == 2) break;
	}
	return Result;
}

BOOL EPEWindowFunction(int Index, HWND aHwnd)
{
	int s=sizeof(P);
	memset(P,0,s);
	int i, MessageResult;
	
	if (Index < 0 || Index > 10 || !IsWindow(aHwnd) || !IsWindow(RegisterHandle)) return false;

	for (i = 1; i <= 100; i++)
	{
		MessageResult = SendMessage(RegisterHandle, WM_USER, Index * 10 + 35, (WORD)aHwnd);
		if (MessageResult == 1) return true;
	}
	return false;
}

DWORD EPEGetMem(int Size)
{
	int s=sizeof(P);
	memset(P,0,s);
	int i, MessageResult;
	
	if (Size <= 0 || !IsWindow(RegisterHandle)) return NULL;

	for (i = 1; i <= 100; i++)
	{
		MessageResult = SendMessage(RegisterHandle, WM_USER, 145, Size);
		if (MessageResult != -1 && MessageResult != 0) return (DWORD)MessageResult;
	}
	return NULL;
}

BOOL EPEFreeMem(DWORD Buf)
{
	int s=sizeof(P);
	memset(P,0,s);
	int i, MessageResult;
	
	if ( Buf==NULL || !IsWindow(RegisterHandle)) return false;

	for (i = 1; i <= 100; i++)
	{
		MessageResult = SendMessage(RegisterHandle, WM_USER, 155, (int)Buf);
		if (MessageResult == 1) return true;
	}
	return false;
}

BOOL EPEZeroMemory(DWORD Buf, int Size)
{
	
	int s=sizeof(P);
	memset(P,0,s);
	int i, MessageResult;
	
	if (Buf==NULL || Size <= 0 || ! IsWindow(RegisterHandle)) return false;

	P->Bz = 0;
	P->ValueSize = Size;
	P->ValueBuf = Buf;

	for (i = 1; i <= 100; i++)
	{
		MessageResult = SendMessage(RegisterHandle, WM_USER, 165, (long)P);
		if (MessageResult == 1) return true;
	}
	return false;
}

BOOL EPEFillMemory(DWORD Buf,int Size,char Fill)
{
	
	int s=sizeof(P);
	memset(P,0,s);
	int i, MessageResult;
	
	if (Buf==NULL || Size <= 0 || !IsWindow(RegisterHandle))
		return false;
	P->Bz = 1;
	P->ValueSize = Size;
	P->ValueBuf = Buf;
	P->PassSize = Fill;

	for (i = 1; i <= 100; i++)
	{
		MessageResult = SendMessage(RegisterHandle, WM_USER, 165, (long)P);
		if (MessageResult == 1) return true;
	}
	return false;
}

BOOL EPECopyMemory(DWORD Destination, DWORD Source,int Size)
{
	
	int s=sizeof(P);
	memset(P,0,s);
	int i, MessageResult;
	
	if (Destination==NULL || Source==NULL || Size <= 0 || !IsWindow(RegisterHandle)) return false;

	P->Bz = 2;
	P->PassBuf = Destination;
	P->ValueBuf = Source;
	P->ValueSize = Size;
	for (i = 1; i <= 100; i++)
	{
		MessageResult = SendMessage(RegisterHandle, WM_USER, 165, (long)P);
		if (MessageResult == 1) return true;
	}
	return false;
}

BOOL EPEMoveMemory(DWORD Destination, DWORD Source,int Size)
{
	
	int s=sizeof(P);
	memset(P,0,s);
	int i, MessageResult;
	
	if (Destination==NULL || Source==NULL || Size <= 0 || !IsWindow(RegisterHandle)) return false;
	P->Bz = 3;
	P->PassBuf = Destination;
	P->ValueBuf = Source;
	P->ValueSize = Size;

	for (i = 1; i <= 100; i++)
	{
		MessageResult = SendMessage(RegisterHandle, WM_USER, 165, (long)P);
		if (MessageResult == 1) return true;
	}
	return false;
}

char * EPESystemStr(int Index)
{
	int s=sizeof(P);
	memset(P,0,s);
	int i, MessageResult;
	
	if (Index < 0 || Index > 5 || ! IsWindow(RegisterHandle)) return "";

	for (i = 1; i <= 100; i++)
	{
		MessageResult = SendMessage(RegisterHandle, WM_USER, 175, Index);
		if (MessageResult != -1 && MessageResult != 0) return (char *)MessageResult;
	}
	return "";
}

BOOL WINAPI SetRegisterInfo(char *User, char *Info)
{
	int s=sizeof(P);
	memset(P,0,s);
	int i, MessageResult;
	if (!IsWindow(RegisterHandle)) return FALSE;

	P->Bz = 0xff;
	P->ValueSize = strlen(User);

	if (P->ValueSize > 0) P->ValueBuf = (int)User;
	else P->ValueBuf = NULL;

	P->PassSize = strlen(Info);

	if (P->PassSize > 0) P->PassBuf = (int)Info;
	else P->PassBuf = NULL;
	
	for (i = 1; i <= 100; i++)
	{
		MessageResult = SendMessage(RegisterHandle, WM_USER, 100, (long)P);
		if (MessageResult == 1) return TRUE;
	}
	return FALSE;

}

void WINAPI Compress(int InBuf,int InBytes,int OutBuf,int * OB, char * Password)
{
	int s=sizeof(P);
	memset(P,0,s);
	int i, MessageResult;
	memset(P,0,sizeof(P));
	if ( InBuf==NULL || InBytes <= 0 || ! IsWindow(RegisterHandle)) return ;

	P->Bz = 0;
	P->ValueSize = InBytes;
	P->ValueBuf = (int)InBuf;
	P->PassSize = strlen(Password);
	if (Password!=NULL) P->PassBuf = (int)Password;
	else P->PassBuf = NULL;

	for (i = 1; i <= 100; i++)
	{
		MessageResult = SendMessage(RegisterHandle, WM_USER, (WPARAM)2147483647, (long)P);
		if (MessageResult == 1)
		{
			try
			{
				CopyMemory((void *)OutBuf, (void *)P->ValueBuf, P->ValueSize);
				*OB = P->ValueSize;
				return ;
			}
			catch(...)
			{
				return ;
			}
		}
	}
}

void Decompress(int InBuf,int InBytes,int OutBuf,int * OutBytes,char * Password,int OutEstimate = 0)
{

	int i, MessageResult;
	memset(P,0,sizeof(P));
	if ( InBuf==NULL || InBytes <= 0 || ! IsWindow(RegisterHandle))
		return;
	P->Bz = 1;
	P->ValueSize = InBytes;
	P->ValueBuf = (int)InBuf;
	P->PassSize = strlen(Password);

	if (Password!=NULL) P->PassBuf = (int)Password;
	else P->PassBuf = NULL;

	for (i = 1; i <= 100; i++)
	{
		MessageResult = SendMessage(RegisterHandle, WM_USER, 2147483647, (long)P);
		if (MessageResult == 1)
		{
			try
			{
				*OutBytes = P->ValueSize;
				CopyMemory((void *)OutBuf, (void *)P->ValueBuf, P->ValueSize);
				return ;
			}
			catch(...)
			{
				return ;
			}
		}
	}
}

char * StringCompress(char *SourceString,char * Password,BOOL HFlag = true)
{
	
	int s=sizeof(P);
	memset(P,0,s);
	int i, MessageResult;
	
	if (SourceString[0] ==0 || ! IsWindow(RegisterHandle)) return "";

	if (HFlag) P->Bz = 10;
	else P->Bz = 20;
	P->ValueSize = strlen(SourceString);
	P->ValueBuf = *SourceString;
	P->PassSize = strlen(Password);
	
	if (Password!=NULL) P->PassBuf = (int)Password;
	else P->PassBuf = NULL;

	for (i = 1; i <= 100; i++)
	{
		MessageResult = SendMessage(RegisterHandle, WM_USER, 2147483647, (long)P);
		if (MessageResult == 1)
		{
			try
			{
				//SetLength(Result, P->ValueSize);
				CopyMemory(&Result, &P->ValueBuf, P->ValueSize);
			}
			catch(...)
			{
				return "";
			}
		}
		return Result;
	}
	return "";
}

char * StringDecompress(char *SourceString,char * Password,BOOL HFlag= true)
{
	
	int s=sizeof(P);
	memset(P,0,s);
	int i, MessageResult;
	
	if (SourceString[0] = 0 || ! IsWindow(RegisterHandle)) return "";

	if (HFlag) P->Bz = 11;
	else P->Bz = 21;
	P->ValueSize = strlen(SourceString);
	P->ValueBuf = (int)SourceString;
	P->PassSize = strlen(Password);

	if (Password!=NULL) P->PassBuf = (int)Password;
	else P->PassBuf = NULL;

	for (i = 1; i <= 100; i++)
	{
		MessageResult = SendMessage(RegisterHandle, WM_USER, 2147483647, (long)P);
		if (MessageResult == 1)
		{
			try
			{
				CopyMemory((void *)Result, &P->ValueBuf, P->ValueSize);
			}
			catch(...)
			{
				return "";
			}
		}
		return Result;
	}
	return "";
}

void Encrypt(int InBuf,int InBytes,int OutBuf,int * OutBytes,char * Password)
{
	
	int s=sizeof(P);
	memset(P,0,s);
	int i, MessageResult;

//	if ( InBuf==NULL || InBytes <= 0 || ! IsWindow(RegisterHandle)) return;
	P->Bz = 100;
	P->ValueSize = InBytes;
	P->ValueBuf = (int)InBuf;
	P->PassSize = strlen(Password);

	if (Password!=NULL) P->PassBuf = (int)Password;
	else P->PassBuf = NULL;

	for (i = 1; i <= 100; i++)
	{
		MessageResult = SendMessage(RegisterHandle, WM_USER, (WPARAM)2147483647, (long)P);
		if (MessageResult == 1)
		{
			try
			{
				//OutBuf = (int)malloc(P->ValueSize);
				CopyMemory((void *)OutBuf, (void *)P->ValueBuf, P->ValueSize);
				*OutBytes = P->ValueSize;
			}
			catch(...)
			{
				//			
			}
		}
		break;
	}
}

void Decrypt(int InBuf,int InBytes,int OutBuf,int * OutBytes,char * Password)
{
	
	int s=sizeof(P);
	memset(P,0,s);
	int i, MessageResult;
	
	if ( InBuf==NULL || InBytes <= 0 || ! IsWindow(RegisterHandle)) return;

	P->Bz = 101;
	P->ValueSize = InBytes;
	P->ValueBuf = (int)InBuf;
	P->PassSize = strlen(Password);
	
	if (Password!=NULL) P->PassBuf = (int)Password;
	else P->PassBuf = NULL;

	for (i = 1; i <= 100; i++)
	{
		MessageResult = SendMessage(RegisterHandle, WM_USER, (WPARAM)2147483647, (long)P);
		
		if (MessageResult == 1)
		{
			try
			{
				//OutBuf = (int)malloc(P->ValueSize);
				CopyMemory((void *)OutBuf, (void *)P->ValueBuf, P->ValueSize);
				*OutBytes = P->ValueSize;
			}
			catch(...)
			{
				//
			}
		}
		break;
	}
}

char * StringEncrypt(char *SourceString,char * Password,BOOL HFlag = true)
{
	
	int s=sizeof(P);
	memset(P,0,s);
	int i, MessageResult;
	
	if (SourceString[0] == 0 || ! IsWindow(RegisterHandle)) return "";

	if (HFlag) P->Bz = 110;
	else P->Bz = 120;

	P->ValueSize = strlen(SourceString);
	P->ValueBuf = (int)SourceString;
	P->PassSize = strlen(Password);

	if (Password!=NULL) P->PassBuf = (int)Password;
	else P->PassBuf = NULL;

	for (i = 1; i <= 100; i++)
	{
		MessageResult = SendMessage(RegisterHandle, WM_USER, 2147483647, (long)P);
		if (MessageResult == 1)
		{
			try
			{
				CopyMemory(&Result, &P->ValueBuf, P->ValueSize);
			}
			catch(...)
			{
				return "";
			}
		}
		return Result;
	}
	return "";
}

char * StringDecrypt(char *SourceString,char * Password,BOOL HFlag= true)
{
	
	int s=sizeof(P);
	memset(P,0,s);
	int i, MessageResult;
	
	if (SourceString[0] == 0 || ! IsWindow(RegisterHandle)) return "";

	if (HFlag) P->Bz = 111;
	else P->Bz = 121;
	P->ValueSize = strlen(SourceString);
	P->ValueBuf = (int)SourceString;
	P->PassSize = strlen(Password);

	if (Password!=NULL) P->PassBuf = (int)Password;
	else P->PassBuf = NULL;

	for (i = 1; i <= 100; i++)
	{
		MessageResult = SendMessage(RegisterHandle, WM_USER, 2147483647, (long)P);
		if (MessageResult == 1)
		{
			try
			{
				CopyMemory(&Result, &P->ValueBuf, P->ValueSize);
			}
			catch(...)
			{
				return "";
			}
		}
		return Result;
	}
	return "";
}

BOOL IsLibrary(HINSTANCE hInstance)
{
	char sPath[MAX_PATH];
	char * ss;
	char ext[MAX_PATH];
	
	GetModuleFileName(NULL,sPath,MAX_PATH);	
	ss=_strlwr(sPath);
	_splitpath( ss, NULL, NULL, NULL, ext );
	
    if(strcmp(ext,".dll")==0) return TRUE;
	else return FALSE;
}
