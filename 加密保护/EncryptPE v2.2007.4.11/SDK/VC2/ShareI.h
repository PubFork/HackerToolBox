/*
 *	
 */
#ifndef _SHARE_INTEFACE_H_
#define _SHARE_INTEFACE_H_

#include "windows.h"
#define  MAX_REGISTER_INFO_NUMBER  15

// {�ڵ���SDK֮ǰ��ȡ�����ͨ�ŵĴ��ھ��������Ԫinitialization�����Ѿ����øú���}

typedef struct _TUserRecord
{
    int Bz ;
    int ValueSize;
    void * ValueBuf;
    int PassSize;
    void * PassBuf;
}TUserRecord, *PTUserRecord ;

void GetRegisterHandle(HINSTANCE hInstance);
/***********  GetRegisterInfo
 *	ȡ�ù�15��ע�������Ϣ����INDEXֵ��
 *  0�Ƿ�ע��(Y/N)��
 *  1������Ϣ��
 *  2ע���û���
 *  3ע����Ϣ��
 *  4������ƣ�ע�ᴰ�ڱ��⣩
 *  5���������ж��ٷ��ӣ�
 *  6ÿ�����ٷ���Ҫ��ע�ᣬ
 *  7ÿ���������ж��ٷ���
 *  8��һ���ڱ���ʹ����������ڣ���ʽYYYYMMDD��
 *  9�����������ڣ���ʽYYYYMMDD
 *  10��������������
 *  11�����д�����
 *  12�������ô�����
 *  13�ӿ�ʱ���õ���������ֵ��14Ϊ���������EPEHashֵ�������˶����ж��Ƿ��ƽ��
 *  ��������ָ���ͬʱȫ��������RegisterStrings��
 *****************************************************************************/
char * GetRegisterInfo(unsigned int  Integer = 0);

/*************************** GetRegisterUser
 *  ȡ��ע���û����ƣ�
 *  δע����Ϊ�գ�
 *  GetRegisterInfo(2)����δע��Ҳ��ֵ
 *****************************************************************************/
char * GetRegisterUser();

/*************************** ShowRegisterForm
 * ��ʾע�ᴰ��
 ****************************************************************************/
BOOL ShowRegisterForm();

/***************************** KillProcess
 *  ��EncryptPE���ܳ������й����в�����ProcessNameָ���Ľ��̣�����.EXE�����У�
 *  ��  ���������ε��øú����������ö��Ÿ������������
 ***************************************************************************/
BOOL KillProcess(char* pszProcessName) ;

/***************************** NotKillProcess
 *  ȡ����ɱ����KillProcess
 ***************************************************************************/
BOOL NotKillProcess(char *pszProcessName);
/***************************** KillDLL
 *  ���üӿǽ����в�������ص�ģ�����������Զ��Ÿ������ģ����
 ***************************************************************************/
BOOL KillDLL(char *pszDLLName);
/***************************** EPEHash
 *  ��ȡָ���ִ���EPEHashֵ
 ***************************************************************************/
char * EPEHash(char *pszSourceString);
//�ÿ�ȥִ�б��ӿǳ����ĳ��������������������ܶ���ִ�У����޲����޷���ֵ��
//Address�Ǻ�����ʵ��ַ�뱣�������HASHֵǰ��λ�������λ��ǰ��0��ת�����������Լ�������������������
bool RunFunction(DWORD Address);



//���º���Ҫ����˿���������


//��ȡ�ӿ�ʱ���õ������ļ������ݣ�����ָ���ӵڼ����ֽڿ�ʼ��ȡ�೤����
void * GetSavedData(unsigned short From, unsigned short Len);
/***************************** SetRegisterInfo
 * д��ע���û�����ע����Ϣ����GetRegisterInfo��Ͽ�������Ƹ���ע�ᴰ��
 ***************************************************************************/
BOOL SetRegisterInfo(char *pszUser,char *pszInfo);

/******************************** SetLanguage
 *	�ı�ע�ᴰ�ڵĽ�������Ԫ�أ�pvLanguageָ���ڴ�(�������ź�ʡ�Ժ�)
 *  һ���ֽ��ַ�����һ���ֽ������С���������ƣ�0���ַ���4��0���ַ���5��0��......���ַ���17��0
 *  ��һ���ַ�����#134#9'����'#0'����'#0'����δ֪����'��0......'ȡ��(&C)'#0
 *  �����û���д�����Գ���
 * pvLuange -------> FontCharset     offset 0    1 byte
 *              ---> FontSize        offset 1    1 byte 
 *              ---> FontName        offset 2    strlen(FontName)
 *              ---> char * pInfo[14];
 *              4=����          5=����δ֪���� 6=��ʾ
 *  7=��ĳЩ���Ի���ӳ����ͻ!
 *  8=�����˳�ϵͳ...
 *  9=ע��
 *  10=δע��
 *  11=ע��
 *  12=�ѹ���
 *  13=������Ϣ(&T):
 *  14=ע���û�(&U):
 *  15=ע����Ϣ(&I):
 *  16=ȷ��(&O)
 *  17=ȡ��(&C)
 
 ****************************************************************************/
BOOL SetLanguage(void * pvLanguage);


/********************************* SetRegisterHint
 * �ı�ע�ᴰ�ڵ���ʾ����վ��ҳ���ʼ���ַ����Ϣ��PHintָ���ڴ棨�������ţ�:
 * ���ں��������ɫת���ɵ��ַ�����0����ʾ��Ϣ��0����ҳ��0�������ַ��0
 * ��һ���ַ�����'$0000FF'#0'��ע�᱾���'#0'http://www.server.com'#0'mailto:someone@server.com'#0
 ***************************************************************************************************/
BOOL SetRegisterHint(void * pvPHint);

/************************ EPECaclResult
 * ��Indexȡֵ0��9�ֱ��Ӧ�������£�
 * '+ - * div mod and or xor shl shr'
 * ��   �� ֵΪĳһ�����Ľ��ֵ,+�����ڸ��˿�����
 ************************************************************/
int EPECaclResult(int nValue1,int nValue2, BYTE Index);


//���º���Ҫ����ҵרҵ������

/***************** EPERandom
 *	���ط�Χ�� >=0 �� < Value ���������
 **********************************************/
int EPERandom(int nValue);


DWORD EPECustomValue(int Index);

//���º���Ҫ����ҵ����������

typedef enum  _WIN_OPERATION_CODE
{
    EPE_WIN_OPERATION_IS_WINDOW = 0,
    EPE_WIN_OPERATION_IS_WINDOW_VISIBLE,
    EPE_WIN_OPERATION_IS_ICONIC,
    EPE_WIN_OPERATION_IS_ZOOM,
    EPE_WIN_OPERATION_SHOW_WINDOW,
    EPE_WIN_OPERATION_HIDE_WINDOW,
    EPE_WIN_OPERATION_DISABLE_WINDOW,
    EPE_WIN_OPERATION_ENABLE_WINDOW,
    EPE_WIN_OPERATION_IS_WINDOW_ENABLE,
    EPE_WIN_OPERATION_CLOSE_WINDOW,
    EPE_WIN_OPERATION_DESTROY_WINDOW     
}WIN_OPERATION_CODE;

BOOL EPEWindowFunction(int Index , HWND aHwnd );


/*************************** EPEGetMem
 *  ����Size��С�ڴ�ռ�	
 **************************************************/
char *  EPEGetMem(int nSize);

/*************************** EPEFreeMem
 *  �ͷ��ڴ�
 **************************************************/
BOOL EPEFreeMem(void * pBuf);

/*************************** EPEZeroMemory
 *  ���һ���ڴ�
 **************************************************/
BOOL EPEZeroMemory(void * pBuf, int nSize);

/*************************** EPEFillMemory
 *  ���һ���ڴ�����
 **************************************************/
BOOL EPEFillMemory(void * pBuf ,int nSize , BYTE byFill);

/************************************ EPECopyMemory
 *  �ڴ渴��
 **************************************************************/
BOOL EPECopyMemory(void * pvDestination, void *pvSource, int nSize);
/************************** EPEMoveMemory
 *	�ڴ��ƶ�
 *******************************************************************/
BOOL  EPEMoveMemory(void * pvDestination, void * pvSource , int nSize);
/********************************** EPESystemStr
 * ��Indexȡֵ0��5�ֱ��ã�
 * GetCurrentDirectory, GetWindowsDirectory, GetSystemDirectory,
 * GetTempPath, GetComputerName, GetUserName}
 **********************************************************/
 char * EPESystemStr(int nIndex);
 
/******************************** Compress
 *	�ڴ�����ѹ��
 ***********************************************************************/
void  Compress(void *pvInBuf, int nInBytes, void *& pvOutBuf, int&   nOutBytes , char *  pzPassword= NULL);
/******************************* Decompress
 *	ѹ��������ݽ�ѹ��
 ****************************************************************/
 void  Decompress(void * pvInBuf, int nInBytes, void* &pvOutBuf, 
 int &  nOutBytes, char *pzPassword= NULL, int nOutEstimate = 0);

/******************************* StringCompress
 *	�ַ���ѹ�������µ��ַ���
 ******************************************************************/
char * StringCompress(char *pszSourceString ,char * pszPassword= NULL, BOOL bHFlag = TRUE);

/********************************* StringDecompress
 *	��ѹ�����ɵ��ַ�����ѹ����ԭ��ԭ�ַ���
 ******************************************************************/

char * StringDecompress(char *pszSourceString, char *pszPassword= NULL, BOOL bHFlag = TRUE);
/******************************************** Encrypt
 *	 ���ڴ��е�һ�����ݽ��м���
 ********************************************************************/
void  Encrypt(void * pvInBuf , int nInBytes,void * *pvOutBuf, int & nOutBytes,  char *pszPassword= NULL);

/******************** Decrypt
 * ���Ѽ������ݽ��н���	
 *************************************************************************/

void Decrypt(void *pvInBuf , int nInBytes, void* *pvPointer, int& nOutBytes,  char * pszPassword );

/*************************************** StringEncrypt
 *���ַ������м��������µ��ַ���
 **************************************************************************/
char * StringEncrypt(char* pszSourceString,  char *pszPassword= NULL, BOOL bHFlag = TRUE);
/************************************* StringDecrypt
 * ���������ɵ��ַ������ܻ�ԭ��ԭ�ַ���
 ********************************************************************************/
char * StringDecrypt(char* pszSourceString , char * pszPassword= NULL,BOOL bHFlag = TRUE);

#endif