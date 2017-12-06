//
// FileName : systemclass.cpp
//
#include "systemclass.h"

//
// CLASS FUNCTION
//

// ������
SystemClass::SystemClass()
{
	m_Input = 0;
	m_Graphics = 0;
}

// ���� ������
SystemClass::SystemClass(const SystemClass& other)
{
}

// �Ҹ���
SystemClass::~SystemClass()
{
}

// ����
bool SystemClass::Initialize()
{
	int  screenWidth, screenHeight;
	bool result;


	// �Լ��� ���̿� �ʺ� �����ϱ� ���� ������ 0���� �ʱ�ȭ
	screenWidth = 0;
	screenHeight = 0;

	// �� API����Ͽ� �ʱ�ȭ
	InitiallzeWindows(screenWidth, screenHeight);

	// Input ��ü ����. �����κ��� ������ Ű���� �Է��� �ޱ� ���� ����
	m_Input = new InputClass;
	if (!m_Input)
	{
		return false;
	}

	// Input ��ü�� �ʱ�ȭ
	m_Input->Initialize();

	// graphics ��ü�� ����. �� ���ø����̼��� ��� �׷����� ó���ϱ� ���� ����
	m_Graphics = new GraphicsClass;
	if (!m_Graphics)
	{
		return false;
	}

	// Graphics ��ü�� �ʱ�ȭ
	result = m_Graphics->Initialize(screenWidth, screenHeight, m_hwnd);
	if (!result)
	{
		return false;
	}

	return true;
}

// ����
void SystemClass::Shutdown()
{
	// Graphics ��ü�� ��ȯ
	if (m_Graphics)
	{
		m_Graphics->Shutdown();
		delete m_Graphics;
		m_Graphics = 0;
	}

	// Input ��ü�� ��ȯ
	if (m_Input)
	{
		delete m_Input;
		m_Input = 0;
	}

	// â�� ����
	ShutdownWindows();

	return;
}

// ����
void SystemClass::Run()
{
	MSG msg;
	bool done, result;


	// �޼��� ����ü�� �ʱ�ȭ
	ZeroMemory(&msg, sizeof(MSG));

	// ������ ���� ���� �޼����� ���� �� ���� ����
	done = false;
	while (!done)
	{
		// ������ �޼����� ó��
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		// �����쿡�� ���ø����̼��� ���Ḧ ��û�ϴ� ��� ���� Ż��
		if (msg.message == WM_QUIT)
		{
			done = true;
		}
		else
		{
			result = Frame();
			if (!result)
			{
				done = true;
			}
		}
	}

	return;
}

// �� �����Ӹ��� ����
bool SystemClass::Frame()
{
	bool result;


	// ������ EscŰ������ ���ø����̼��� �����ϱ⸦ ���ϴ��� Ȯ��
	if (m_Input->IsKeyDown(VK_ESCAPE))
	{
		return false;
	}

	// graphics ��ü�� �۾��� ó��
	result = m_Graphics->Frame();
	if (!result)
	{
		return false;
	}

	return true;
}

// �޼��� ó����
LRESULT CALLBACK SystemClass::MessageHandler(HWND hwnd, UINT umsg, WPARAM wparam, LPARAM lparam)
{
	switch (umsg)
	{
		// Ű���尡 Ű�� ���ȴ��� Ȯ��
	case WM_KEYDOWN:
	{
		// Ű�� �������� input ��ü�� ������ �����Ͽ� ����ϵ��� ��
		m_Input->KeyDown((unsigned int)wparam);
		return 0;
	}

	// Ű������ ���� Ű�� ���������� Ȯ��
	case WM_KEYUP:
	{
		// Ű�� ���������� input ��ü�� ������ �����Ͽ� �� Ű�� �����ϵ��� ��
		m_Input->KeyUp((unsigned int)wparam);
		return 0;
	}

	// �ٸ� �޼������� ������� �����Ƿ� �⺻ �޼��� ó���⿡ ����
	default:
	{
		return DefWindowProc(hwnd, umsg, wparam, lparam);
	}
	}
}

// ������ ����
void SystemClass::InitiallzeWindows(int& screenWidth, int& screenHeight)
{
	WNDCLASSEX wc;
	DEVMODE dmScreenSettings;
	int posX, posY;


	// �ܺ� �����͸� �� ��ü�� ����
	ApplicationHandle = this;

	// �� ���ø����̼��� �ν��Ͻ��� ������
	m_hinstance = GetModuleHandle(NULL);

	// ���ø����̼��� �̸��� ����
	m_applicationName = L"Engine";

	// ������ Ŭ������ �⺻ �������� ����
	wc.style		 = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
 	wc.lpfnWndProc	 = WndProc; wc.cbClsExtra = 0;
	wc.cbWndExtra	 = 0; wc.hInstance = m_hinstance;
	wc.hIcon		 = LoadIcon(NULL, IDI_WINLOGO);
	wc.hIconSm		 = wc.hIcon; wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wc.lpszMenuName	 = NULL; wc.lpszClassName = m_applicationName;
	wc.cbSize		 = sizeof(WNDCLASSEX);
	
	// ������ Ŭ������ ���
	RegisterClassEx(&wc);

	// ����� ȭ���� �ػ󵵸� ���ؿ�
	screenWidth  = GetSystemMetrics(SM_CXSCREEN);
	screenHeight = GetSystemMetrics(SM_CYSCREEN);

	// Ǯ ��ũ�� ��� ������ ���� ���� ȭ�� ����
	if (FULL_SCREEN)
	{
		// ���� Ǯ��ũ�� ����� ȭ�� ũ�⸦ ����� ũ�⿡ ���߰� ������ 32bit����
		memset(&dmScreenSettings, 0, sizeof(dmScreenSettings));
		dmScreenSettings.dmSize		  = sizeof(dmScreenSettings);
		dmScreenSettings.dmPelsWidth  = (unsigned long)screenWidth;
		dmScreenSettings.dmPelsHeight = (unsigned long)screenHeight;
		dmScreenSettings.dmBitsPerPel = 32;
		dmScreenSettings.dmFields	  = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;
	
		// Ǯ ��ũ���� �´� ���÷��� ������ ����
		ChangeDisplaySettings(&dmScreenSettings, CDS_FULLSCREEN);

		// �������� ��ġ�� ȭ���� ���� ���� ����
		posX = posY = 0;;
	}
	else
	{
		screenWidth  = 800;
		screenHeight = 600;

		posX = (GetSystemMetrics(SM_CXSCREEN) - screenWidth) / 2;
		posY = (GetSystemMetrics(SM_CYSCREEN) - screenHeight) / 2;
	}

	// ������ ���� ������ â�� ����� �� �ڵ��� ������
	m_hwnd = CreateWindowEx(WS_EX_APPWINDOW, m_applicationName, m_applicationName,
		WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_POPUP,
		posX, posY, screenWidth, screenHeight, NULL, NULL, m_hinstance, NULL);

	// �����츦 ȭ�鿡 ǥ���ϰ� ��Ŀ���� ��
	ShowWindow(m_hwnd, SW_SHOW);
	SetForegroundWindow(m_hwnd);
	SetFocus(m_hwnd);

	// ���콺 Ŀ���� ǥ������ ����
	ShowCursor(false);

	return;
}

// ������ â ����
void SystemClass::ShutdownWindows()
{
	// ���콺 Ŀ���� ǥ��
	ShowCursor(true);

	// Ǯ��ũ�� ��带 �������� �� ���÷��� ���� ����
	if (FULL_SCREEN)
	{
		ChangeDisplaySettings(NULL, 0);
	}

	// â�� ����
	DestroyWindow(m_hwnd);
	m_hwnd = NULL;
	
	// ���ø����̼� �ν��Ͻ��� ����
	UnregisterClass(m_applicationName, m_hinstance);
	m_hinstance = NULL;

	// �� Ŭ������ ���� �ܺ� ������ ������ ����
	ApplicationHandle = NULL;

	return;
}

// 
// FUNCTION PROTOTYPES
// 

//  SystemClass���� �������� �޼����� ����ä�� ����
LRESULT CALLBACK WndProc(HWND hwnd, UINT umessage, WPARAM wparam, LPARAM lparam)
{
	switch (umessage)
	{
		// �����찡 ���ŵǾ����� Ȯ��
		case WM_DESTROY:
		{
			PostQuitMessage(0);
			return 0;
		}

		// �����찡 �������� Ȯ��
		case WM_CLOSE:
		{
			PostQuitMessage(0);
			return 0;
		}

		// �ٸ� ��� �޼������� system Ŭ������ �޼��� ó���⿡ ����
		default:
		{
			return ApplicationHandle->MessageHandler(hwnd, umessage, wparam, lparam);
		}
	}
}
