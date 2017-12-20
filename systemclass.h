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

	bool Initialize();						// �ʱ�ȭ
	void Shutdown();						// ����
	void Run();								// ����

	LRESULT CALLBACK MessageHandler(HWND, UINT, WPARAM, LPARAM);		// �޼��� ó�� �ڵ鷯

private:
	bool Frame();							// �� �������� ����
	void InitiallzeWindows(int&, int&);		// �ʱ�ȭ �۾�
	void ShutdownWindows();					// ������ ����

private:
	LPCWSTR			m_applicationName;		// ���ø����̼��� �̸�
	HINSTANCE		m_hinstance;			// ���ø����̼��� �ν��Ͻ�
	HWND			m_hwnd;					// â�� �ڵ�

	InputClass*		m_Input;				// ������� �Է� ó��
	GraphicsClass*  m_Graphics;				// �׷��� ��� ó��
};


//
// FUNCTION PROTOTYPES
//
static LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);			// �̰� �𸣰ڴµ���


//
// GLOBALS
//
static SystemClass* ApplicationHandle = 0;								// ���ø����̼��� �ڵ�(�ý����� �ڵ�)
