// Potato.h : Potato DLL ����ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CPotatoApp
// �йش���ʵ�ֵ���Ϣ������� Potato.cpp
//

class CPotatoApp : public CWinApp
{
public:
	CPotatoApp();

// ��д
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
