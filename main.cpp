//
// FileName : main.cpp
//
#include "systemclass.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR pScmdline, int iCmdshow)
{
	SystemClass* System;
	bool result;


	// system 객체 생성합니다.
	System = new SystemClass;
	if (!System)
	{
		return 0;
	}

	// system 객체 초기화 및 run을 호출합니다.
	result = System->Initialize();
	if (result)
	{
		System->Run();
	}

	// system 객체를 종료 후 메모리를 반환합니다.
	System->Shutdown();
	delete System;
	System = 0;

	return 0;
}