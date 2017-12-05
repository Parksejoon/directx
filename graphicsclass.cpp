//
// FileName : graphicsclass.cpp
//
#include "graphicsclass.h"

//
// CLASS FUNCTION
//

// ������
GraphicsClass::GraphicsClass()
{
	m_D3D = 0;
}

// ���� ������
GraphicsClass::GraphicsClass(const GraphicsClass& other)
{
}

// �Ҹ���
GraphicsClass::~GraphicsClass()
{
}

// ����
bool GraphicsClass::Initialize(int screenWidth, int screenHeight, HWND hwnd)
{
	bool result;

	// Direct3D ��ü�� ����
	m_D3D = new D3Dclass;
	if (!m_D3D)
	{
		return false;
	}

	// Direct3D ��ü�� �ʱ�ȭ
	result = m_D3D->Initialize(screenWidth, screenHeight, VSYNC_ENABLED, hwnd, FULL_SCREEN, SCREEN_DEPTH, SCREEN_NEAR);
	if (!result)
	{
		MessageBox(hwnd, L"Cloud not initialize Direct3D", L"Error", MB_OK);
		return false;
	}

	return true;
}

// ����
void GraphicsClass::Shutdown()
{
	// D3D ��ü�� ��ȯ
	if (m_D3D)
	{
		m_D3D->Shutdown();
		delete m_D3D;
		m_D3D = 0;
	}

	return;
}

// �� ������
bool GraphicsClass::Frame()
{
	bool result;

	// �׷��� �������� ����
	result = Render();
	if (!result)
	{
		return false;
	}

	return true;
}

// ������
bool GraphicsClass::Render()
{
	// �� �׸��⸦ �����ϱ� ���� ������ ������ ����
	m_D3D->BeginScene(0.5f, 0.5f, 0.5f, 1.0f);

	// ���ۿ� �׷��� ���� ȭ�鿡 ǥ��
	m_D3D->EndScene();

	return true;
}