///////////////////////////////////////////////////////////////////
//-----------------------------------------------------------------
//                 Copyright (c) 2004 jfpan20000@sina.com
// 
//                         IceSwordЭ���� 1.06
// 
//                           pjf    USTC
//------------------------------------------------------------------
////////////////////////////////////////////////////////////////////
#ifndef __ICE_COOPERATOR_
#define __ICE_COOPERATOR_

#pragma comment(lib, "IceSword110.lib")

typedef LONG NTSTATUS;

//
////ָʾIsdOpenKey��RootDirectoryΪ��
//
#define NULL_ROOT_DIR_HANDLE     ((HANDLE)0xF000000F)
//
////��ʷԭ�򣬽��䶨��Ϊ2000����ʵֻ�õ�255�ֽ�
//
#define DATA_BUF_LEN                    2000

//
////IsdCreateFile���Դ������Ŀ¼��������ΪdwFlagsAndAttributesָ��FILE_FLAG_DIRECTORY��־
//
#define FILE_FLAG_DIRECTORY             0x00400000

//
////����IsdFindFile����Ӧ��WIN32_FIND_DATA����һ������
//
typedef struct _ISD_WIN32_FIND_DATA {
	DWORD         dwFileAttributes; 
	FILETIME      ftCreationTime; 
	FILETIME      ftLastAccessTime; 
	FILETIME      ftLastWriteTime; 
	LARGE_INTEGER nFileSize; 
	LARGE_INTEGER AllocationSize; 
	TCHAR         cAlternateFileName[ 14 ]; 
	TCHAR         cFileName[ DATA_BUF_LEN ]; 
} ISD_WIN32_FIND_DATA, *PISD_WIN32_FIND_DATA;

//
////����IsdSetInformationFile/IsdQueryInformationFile
//
typedef enum _FILE_INFORMATION_CLASS {
    FileDirectoryInformation         = 1,
    FileFullDirectoryInformation,   // 2
    FileBothDirectoryInformation,   // 3
    FileBasicInformation,           // 4  wdm
    FileStandardInformation,        // 5  wdm
    FileInternalInformation,        // 6
    FileEaInformation,              // 7
    FileAccessInformation,          // 8
    FileNameInformation,            // 9
    FileRenameInformation,          // 10
    FileLinkInformation,            // 11
    FileNamesInformation,           // 12
    FileDispositionInformation,     // 13
    FilePositionInformation,        // 14 wdm
    FileFullEaInformation,          // 15
    FileModeInformation,            // 16
    FileAlignmentInformation,       // 17
    FileAllInformation,             // 18
    FileAllocationInformation,      // 19
    FileEndOfFileInformation,       // 20 wdm
    FileAlternateNameInformation,   // 21
    FileStreamInformation,          // 22
    FilePipeInformation,            // 23
    FilePipeLocalInformation,       // 24
    FilePipeRemoteInformation,      // 25
    FileMailslotQueryInformation,   // 26
    FileMailslotSetInformation,     // 27
    FileCompressionInformation,     // 28
    FileObjectIdInformation,        // 29
    FileCompletionInformation,      // 30
    FileMoveClusterInformation,     // 31
    FileQuotaInformation,           // 32
    FileReparsePointInformation,    // 33
    FileNetworkOpenInformation,     // 34
    FileAttributeTagInformation,    // 35
    FileTrackingInformation,        // 36
    FileIdBothDirectoryInformation, // 37
    FileIdFullDirectoryInformation, // 38
    FileValidDataLengthInformation, // 39
    FileShortNameInformation,       // 40
    FileMaximumInformation
} FILE_INFORMATION_CLASS, *PFILE_INFORMATION_CLASS;

//
////ע����ѯ�����ṹ
//
typedef enum _KEY_INFORMATION_CLASS {
    KeyBasicInformation,
    KeyNodeInformation,
    KeyFullInformation,
    KeyNameInformation,
    KeyCachedInformation,
    KeyFlagsInformation
} KEY_INFORMATION_CLASS;

typedef struct _KEY_BASIC_INFORMATION {
  LARGE_INTEGER LastWriteTime;
  ULONG  TitleIndex;
  ULONG  NameLength;
  WCHAR  Name[1];  //  Variable-length string
} KEY_BASIC_INFORMATION, *PKEY_BASIC_INFORMATION;

typedef enum _KEY_VALUE_INFORMATION_CLASS {
    KeyValueBasicInformation,
    KeyValueFullInformation,
    KeyValuePartialInformation,
    KeyValueFullInformationAlign64,
    KeyValuePartialInformationAlign64
} KEY_VALUE_INFORMATION_CLASS;

typedef struct _KEY_VALUE_BASIC_INFORMATION {
    ULONG   TitleIndex;
    ULONG   Type;
    ULONG   NameLength;
    WCHAR   Name[1];            // Variable size
} KEY_VALUE_BASIC_INFORMATION, *PKEY_VALUE_BASIC_INFORMATION;

typedef struct _KEY_VALUE_PARTIAL_INFORMATION {
	ULONG  TitleIndex;
	ULONG  Type;
	ULONG  DataLength;
	UCHAR  Data[1];  //  Variable size
} KEY_VALUE_PARTIAL_INFORMATION, *PKEY_VALUE_PARTIAL_INFORMATION;

typedef struct _KEY_FULL_INFORMATION {
	LARGE_INTEGER  LastWriteTime;
	ULONG  TitleIndex;
	ULONG  ClassOffset;
	ULONG  ClassLength;
	ULONG  SubKeys;
	ULONG  MaxNameLen;
	ULONG  MaxClassLen;
	ULONG  Values;
	ULONG  MaxValueNameLen;
	ULONG  MaxValueDataLen;
	WCHAR  Class[1];
} KEY_FULL_INFORMATION, *PKEY_FULL_INFORMATION;

typedef struct _KEY_VALUE_FULL_INFORMATION {
	ULONG  TitleIndex;
	ULONG  Type;
	ULONG  DataOffset;
	ULONG  DataLength;
	ULONG  NameLength;
	WCHAR  Name[1];  //  Variable size
} KEY_VALUE_FULL_INFORMATION, *PKEY_VALUE_FULL_INFORMATION;

//
////��������
//

/////////////////////////////////////////////////////////////////////
////IsdGetVersion
//
//Ŀ�ģ���ȡ�����е�Icesword����汾
//
//������
//  Version 
//    [out] �ɹ��󷵻ذ汾�ţ���1.06��ͷ���0x106. 
//
//����ֵ���ɹ��򷵻�TRUE.
/////////////////////////////////////////////////////////////////////
extern "C" __declspec(dllimport) BOOL IsdGetVersion(DWORD *Version);

/////////////////////////////////////////////////////////////////////
////IsdGetIceProcId
//
//Ŀ�ģ���ȡ�����е�Icesword����PID
//
//�������� 
//
//����ֵ���ɹ��򷵻�PID.
/////////////////////////////////////////////////////////////////////
extern "C" __declspec(dllimport) DWORD IsdGetIceProcId();

/////////////////////////////////////////////////////////////////////
////IsConnectServer
//
//Ŀ�ģ��Ƿ��Ѿ����ӵ�IceSword����
//
//�������� 
//
//����ֵ���������򷵻�TRUE.
/////////////////////////////////////////////////////////////////////
extern "C" __declspec(dllimport) BOOL IsConnectServer();

/////////////////////////////////////////////////////////////////////
////ConnectAndCall
//
//Ŀ�ģ�����IceSword���̲���ȡ��ʼ����
//
//�������� 
//
//����ֵ���ɹ��򷵻�TRUE.
/////////////////////////////////////////////////////////////////////
extern "C" __declspec(dllimport) BOOL ConnectAndCall();

/////////////////////////////////////////////////////////////////////
////IsdEnumProcesses
//
//Ŀ�ģ�ö�ٽ���
//
//������
//  lpidProcess
//    [out] ���ڱ��淵��ֵ�Ļ���. 
//  cb
//    [in] �����С.
//  cbNeeded
//    [out] ʵ�ʷ��ػ����С.
//
//����ֵ���ɹ��򷵻�TRUE.
//
//��ע��1������ϵͳPSAPI��EnumProcesses����һ��ʹ�ã��Ͳ���˵��.
//      ע����Ϊ0��Idle����ʼ�ղ��䣬����ֵ��ʡ���ˣ����Խ�������
//      Ӧ�ü�һ.
//      2�������ص�PID����״̬Deleting�Ľ��̣�����IsProcessDeleting
//      �ж��ǲ��Ǹ�״̬������TRUE���ǣ�.
/////////////////////////////////////////////////////////////////////
extern "C" __declspec(dllimport) BOOL IsdEnumProcesses(
                                            DWORD *lpidProcess, 
                                            DWORD cb, 
                                            DWORD *cbNeeded);

/////////////////////////////////////////////////////////////////////
////IsProcessDeleting
//
//Ŀ�ģ��жϽ���״̬�Ƿ�ΪDeleting
//
//������
//  Pid
//    [in] ���ڱ��淵��ֵ�Ļ���. 
//
//����ֵ����Deleting״̬�����򷵻�TRUE.
//
/////////////////////////////////////////////////////////////////////
extern "C" __declspec(dllimport) BOOL IsProcessDeleting(DWORD Pid);

/////////////////////////////////////////////////////////////////////
////IsdEnumProcessModules
//
//Ŀ�ģ�ö�ٽ���ģ��
//
//������
//  Pid
//    [in] ����PID
//  lphModule
//    [out] ���ڱ��淵��ֵ�Ļ���. 
//  cb
//    [in] �����С.
//  lpcbNeeded
//    [out] ʵ�ʷ��ػ����С.
//
//����ֵ���ɹ��򷵻�TRUE.
//
//��ע������ϵͳPSAPI��EnumProcessModules����һ��ʹ�ã�ע���һ����
//      ����ͬ��������Pid.
/////////////////////////////////////////////////////////////////////
extern "C" __declspec(dllimport) BOOL IsdEnumProcessModules(
                                            DWORD Pid, 
                                            HMODULE *lphModule, 
                                            DWORD cb, 
                                            LPDWORD lpcbNeeded);

/////////////////////////////////////////////////////////////////////
////IsdQueryProcessFileName
//
//Ŀ�ģ��ɽ���PID��ȡ�����ļ�·����
//
//������
//  Pid
//    [in] ����PID
//  FileName
//    [out] ���ڱ��淵��ֵ�Ļ��壬���ַ���. 
//  len
//    [in] �����С.
//
//����ֵ���ɹ��򷵻�TRUE.
//
//��ע��
/////////////////////////////////////////////////////////////////////
extern "C" __declspec(dllimport) BOOL IsdQueryProcessFileName(
                                            DWORD Pid, 
                                            char *FileName, 
                                            int len);

/////////////////////////////////////////////////////////////////////
////IsdGetModuleFileName
//
//Ŀ�ģ���ȡָ�����̵�ָ��ģ����ļ�·����
//
//������
//  Pid
//    [in] ����PID
//  hModule
//    [in] ģ����
//  lpFilename
//    [out] ���ڱ��淵��ֵ�Ļ��壬���ַ���. 
//  nSize
//    [in] �����С.
//
//����ֵ���ɹ��򷵻�TRUE.
//
//��ע��
/////////////////////////////////////////////////////////////////////
extern "C" __declspec(dllimport) BOOL IsdGetModuleFileName(
                                            DWORD Pid, 
                                            HMODULE hModule, 
                                            LPTSTR lpFilename, 
                                            DWORD nSize);

/////////////////////////////////////////////////////////////////////
////IsdCreateFile
//
//Ŀ�ģ���������ļ�(Ŀ¼Ҳ��������ļ�)
//
//������
//  lpFileName
//    [in] �ļ�·��ȫ��. 
//  dwDesiredAccess
//    [in] �ļ�����Ȩ��.
//  dwShareMode
//    [in] ����ģʽ.
//  lpSecurityAttributes
//    [in] ʼ��ΪNULL.
//  dwCreationDisposition
//    [in] �����򿪲���.
//  dwFlagsAndAttributes
//    [in] ��־����.
//  hTemplateFile
//    [in] ʼ��ΪNULL.
//
//����ֵ���ɹ��򷵻ش򿪾�������򷵻�INVALID_HANDLE_VALUE.
//
//��ע������ϵͳAPI CreateFile���Ӽ���ʹ���ϲ�࣬��Ҫע����ǣ�
//    1��lpSecurityAttributes��hTemplateFile��֧�֣�Ӧ����NULL.
//    2��ֻ���������������Ӳ���ļ�.
//    3��������˵�ļ�����Ȩ��dwDesiredAccess��ʵû��ʲô���壬Ĭ��
//       �������е�Ȩ�ޣ�һ�㴫��0�ͺ�.
//    4�����صľ������IceSwordά���ģ�������windows�ں˾��������
//       ������ʹ��ϵͳapi.
//    6��IceSword������ÿ��Э�����̵ľ�����С���ļ���ע�����ɴ�
//       ��1000�����.
//    5��һ��Ҫ�����ļ�·��ȫ��.
/////////////////////////////////////////////////////////////////////
extern "C" __declspec(dllimport) HANDLE IsdCreateFile(
                                            LPCSTR lpFileName,
                                            ULONG dwDesiredAccess,
                                            ULONG dwShareMode,
                                            PVOID lpSecurityAttributes,
                                            ULONG dwCreationDisposition,
                                            ULONG dwFlagsAndAttributes,
                                            HANDLE hTemplateFile);

/////////////////////////////////////////////////////////////////////
////IsdFindFile
//
//Ŀ�ģ�ö��Ŀ¼
//
//������
//  hFile
//    [in] Ŀ¼�������IsdCreateFile����. 
//  lpFindFileData
//    [out] ISD_WIN32_FIND_DATA�ṹָ��.
//  ReSet
//    [in] ����.
//
//����ֵ���ɹ��򷵻�TRUE.
//
//��ע������ϵͳAPI FindFirstFile��FindNextFile���ܼ�����һ��
//    1��ReSetΪTRUE��ӵ�һ���ļ���ͷö��.
//    2����ReSetΪFALSE�ظ�����IsdFindFile���ö��hFile��ָĿ¼����
//       ���ļ����뿴ʾ��.
/////////////////////////////////////////////////////////////////////
extern "C" __declspec(dllimport) BOOL IsdFindFile(
                                            HANDLE hFile,
                                            PISD_WIN32_FIND_DATA lpFindFileData,
                                            BOOL ReSet);

/////////////////////////////////////////////////////////////////////
////IsdCloseHandle
//
//Ŀ�ģ��رվ��
//
//������
//  hFile 
//    [in] �ļ���Ŀ¼���. 
//
//����ֵ���ɹ��򷵻�TRUE.
/////////////////////////////////////////////////////////////////////
extern "C" __declspec(dllimport) BOOL IsdCloseHandle(HANDLE hFile);

/////////////////////////////////////////////////////////////////////
////IsdReadFile
//
//Ŀ�ģ����ļ�
//
//������
//  hFile
//    [in] �ļ����. 
//  lpBuffer
//    [out] ������.
//  nNumberOfBytesToRead
//    [in] ��Ҫ��ȡ�Ĵ�С.
//  lpNumberOfBytesRead
//    [out] �ɹ��󷵻�ʵ�ʶ�ȡ��С.
//  lpOverlapped
//    [in] ʼ��ΪNULL.
//
//����ֵ���ɹ��򷵻�TRUE.
//
//��ע������ϵͳAPI ReadFile���Ӽ���ʹ���ϲ�࣬��Ҫע����ǣ�
//    1��lpOverlapped��֧�֣�Ӧ����NULL.
/////////////////////////////////////////////////////////////////////
extern "C" __declspec(dllimport) BOOL IsdReadFile(
                                            HANDLE hFile,
                                            PVOID lpBuffer,
                                            ULONG nNumberOfBytesToRead,
                                            PULONG lpNumberOfBytesRead,
                                            LPOVERLAPPED lpOverlapped);

/////////////////////////////////////////////////////////////////////
////IsdWriteFile
//
//Ŀ�ģ����ļ�
//
//������
//  hFile
//    [in] �ļ����. 
//  lpBuffer
//    [out] д����.
//  nNumberOfBytesToWrite
//    [in] ��Ҫд��Ĵ�С.
//  lpNumberOfBytesWritten
//    [out] �ɹ��󷵻�ʵ��д���С.
//  lpOverlapped
//    [in] ʼ��ΪNULL.
//
//����ֵ���ɹ��򷵻�TRUE.
//
//��ע������ϵͳAPI WriteFile���Ӽ���ʹ���ϲ�࣬��Ҫע����ǣ�
//    1��lpOverlapped��֧�֣�Ӧ����NULL.
/////////////////////////////////////////////////////////////////////
extern "C" __declspec(dllimport) BOOL IsdWriteFile(
                                            HANDLE hFile,
                                            PVOID lpBuffer,
                                            ULONG nNumberOfBytesToWrite,
                                            PULONG lpNumberOfBytesWritten,
                                            LPOVERLAPPED lpOverlapped);

/////////////////////////////////////////////////////////////////////
////IsdSetFilePointerEx
//
//Ŀ�ģ����ô��ļ���ָ��λ��
//
//��ע������ϵͳAPI SetFilePointerEx�÷���ͬ����׸��.
/////////////////////////////////////////////////////////////////////
extern "C" __declspec(dllimport) BOOL IsdSetFilePointerEx(
                                            HANDLE hFile,
                                            LARGE_INTEGER liDistanceToMove,
                                            PLARGE_INTEGER lpNewFilePointer,
                                            ULONG dwMoveMethod);

/////////////////////////////////////////////////////////////////////
////IsdGetFileSizeEx
//
//Ŀ�ģ����ô��ļ���ָ��λ��
//
//��ע������ϵͳAPI GetFileSizeEx�÷���ͬ����׸��.
/////////////////////////////////////////////////////////////////////
extern "C" __declspec(dllimport) BOOL IsdGetFileSizeEx(
                                            HANDLE hFile,
                                            PLARGE_INTEGER lpFileSize);

/////////////////////////////////////////////////////////////////////
////IsdGetFileTime
//
//Ŀ�ģ����ô��ļ���ָ��λ��
//
//��ע������ϵͳAPI GetFileTime�÷���ͬ����׸��.
/////////////////////////////////////////////////////////////////////
extern "C" __declspec(dllimport) BOOL IsdGetFileTime(
                                            HANDLE hFile,
                                            LPFILETIME lpCreationTime,
                                            LPFILETIME lpLastAccessTime,
                                            LPFILETIME lpLastWriteTime);

/////////////////////////////////////////////////////////////////////
////IsdSetFileTime
//
//Ŀ�ģ����ô��ļ���ָ��λ��
//
//��ע������ϵͳAPI SetFileTime�÷���ͬ����׸������ע���������3��ָ
//      �붼����Ϊ��.
/////////////////////////////////////////////////////////////////////
extern "C" __declspec(dllimport) BOOL IsdSetFileTime(
                                            HANDLE hFile,
                                            const FILETIME *lpCreationTime,
                                            const FILETIME *lpLastAccessTime,
                                            const FILETIME *lpLastWriteTime);

extern "C" __declspec(dllimport) LONG IsdSetInformationFile(
                                            HANDLE hFile,
                                            PVOID  FileInformation,
                                            ULONG  Length,
                                            FILE_INFORMATION_CLASS  FileInformationClass);

extern "C" __declspec(dllimport) LONG IsdQueryInformationFile(
                                            HANDLE hFile,
                                            PVOID  FileInformation,
                                            ULONG  Length,
                                            FILE_INFORMATION_CLASS  FileInformationClass);

extern "C" __declspec(dllimport) INT IsdReadProcessMemory(
                                            DWORD pid, 
                                            PVOID BaseAddress, 
                                            PVOID Buf, 
                                            UINT Len);

extern "C" __declspec(dllimport) INT IsdWriteProcessMemory(
                                            DWORD pid, 
                                            PVOID BaseAddress, 
                                            PVOID Buf, 
                                            UINT Len);

//
////ʹ��IsdOpenKey�򿪵ľ��ҲӦʹ��IsdCloseHandle�رա���ע��� Э��dll����ʱֻ�����⼸��������:)
////ʹ���ϱȽ��鷳���ο�����
//
extern "C" __declspec(dllimport) BOOL IsdOpenKey(
                                            OUT PHANDLE KeyHandle,
                                            IN ACCESS_MASK DesiredAccess,
                                            IN HANDLE RootDirectory,
                                            IN PWCHAR KeyName);

extern "C" __declspec(dllimport) NTSTATUS IsdEnumerateKey(
                                            IN HANDLE KeyHandle,
                                            IN ULONG Index,
                                            IN KEY_INFORMATION_CLASS KeyInformationClass,
                                            OUT PVOID KeyInformation,
                                            IN ULONG Length,
                                            IN PULONG ResultLength);

extern "C" __declspec(dllimport) NTSTATUS IsdEnumerateValueKey(
                                            IN HANDLE KeyHandle,
                                            IN ULONG Index,
                                            IN KEY_VALUE_INFORMATION_CLASS KeyInformationClass,
                                            OUT PVOID KeyInformation,
                                            IN ULONG Length,
                                            IN PULONG ResultLength);

#endif
