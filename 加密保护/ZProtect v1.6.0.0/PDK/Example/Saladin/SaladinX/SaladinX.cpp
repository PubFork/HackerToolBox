// SaladinX.cpp : ���� DLL Ӧ�ó������ڵ㡣
//

#include "stdafx.h"

#pragma comment(linker,"/merge:.rdata=.data")
#pragma comment(linker,"/merge:.data=.text")


BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
					 )
{
    return TRUE;
}

