// Saladin.cpp : ���� DLL Ӧ�ó������ڵ㡣
//

#include "stdafx.h"


BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
					 )
{
    return TRUE;
}

void	__stdcall ZPCP_GetPluginInfo(PPARG_GETINFO pArgInfo)
{
	strcpy(pArgInfo->m_lpName,"���������");
	strcpy(pArgInfo->m_lpVer,"v0.1");
	strcpy(pArgInfo->m_lpAuthor,"Lifeengines");
	strcpy(pArgInfo->m_lpDesc,"�����ʾ������֤�����ȶ���");
}

void	__stdcall ZPCP_Init(void*)
{
	int pV = ZPPC_GetCfgIntValue("abcTest");
	pV = 3;
}

void	__stdcall ZPCP_Exit(void*)
{
	ZPPC_SetCfgIntValue("abcTest",2);
}