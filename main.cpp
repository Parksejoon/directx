//
// FileName : main.cpp
//
#include "systemclass.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR pScmdline, int iCmdshow)
{
	SystemClass* System;
	bool result;


	// system ��ü �����մϴ�.
	System = new SystemClass;
	if (!System)
	{
		return 0;
	}

	// system ��ü �ʱ�ȭ �� run�� ȣ���մϴ�.
	result = System->Initialize();
	if (result)
	{
		System->Run();
	}

	// system ��ü�� ���� �� �޸𸮸� ��ȯ�մϴ�.
	System->Shutdown();
	delete System;
	System = 0;

	return 0;
}