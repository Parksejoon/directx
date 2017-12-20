//
// FileName : systemclass.h
//
#pragma once


//
// PRE-PROCESSING DIRECTIVES
//
#define WIN32_LEAN_AND_MEAN


//
// INCLUDES
//
#include <windows.h>


//
// MY CLASS INCLUDES
//
#include "inputclass.h"
#include "graphicsclass.h"


//
// Class Name : SystemClass
//
class SystemClass
{
public:
	SystemClass();
	SystemClass(const SystemClass&);
	~SystemClass();

	bool Initialize();						// 초기화
	void Shutdown();						// 종료
	void Run();								// 실행

	LRESULT CALLBACK MessageHandler(HWND, UINT, WPARAM, LPARAM);		// 메세지 처리 핸들러

private:
	bool Frame();							// 매 루프마다 실행
	void InitiallzeWindows(int&, int&);		// 초기화 작업
	void ShutdownWindows();					// 윈도우 종료

private:
	LPCWSTR			m_applicationName;		// 어플리케이션의 이름
	HINSTANCE		m_hinstance;			// 어플리케이션의 인스턴스
	HWND			m_hwnd;					// 창의 핸들

	InputClass*		m_Input;				// 사용자의 입력 처리
	GraphicsClass*  m_Graphics;				// 그래픽 출력 처리
};


//
// FUNCTION PROTOTYPES
//
static LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);			// 이건 모르겠는데요


//
// GLOBALS
//
static SystemClass* ApplicationHandle = 0;								// 애플리케이션의 핸들(시스템의 핸들)
