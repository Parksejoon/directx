//
// FileName : graphicsclass.cpp
//
#include "graphicsclass.h"

//
// CLASS FUNCTION
//

GraphicsClass::GraphicsClass()
{
	m_D3D = NULL;
}

GraphicsClass::GraphicsClass(const GraphicsClass& other)
{
}

GraphicsClass::~GraphicsClass()
{
}

bool GraphicsClass::Initialize(int screenWidth, int screenHeight, HWND hwnd)
{
	bool result;


	// Direct3D 객체를 생성합니다.
	m_D3D = new D3DClass;
	if (!m_D3D)
	{
		return false;
	}

	// Direct3D 객체를 초기화합니다.
	result = m_D3D->Initialize(screenWidth, screenHeight, VSYNC_ENABLED, hwnd, FULL_SCREEN, SCREEN_DEPTH, SCREEN_NEAR);
	if (!result)
	{
		MessageBox(hwnd, L"Cloud not initialize Direct3D", L"Error", MB_OK);
		return false;
	}

	return true;
}

// 종료
void GraphicsClass::Shutdown()
{
	// D3D 객체를 반환합니다.
	if (m_D3D)
	{
		m_D3D->Shutdown();
		delete m_D3D;
		m_D3D = 0;
	}

	return;
}

// 매 프래임
bool GraphicsClass::Frame()
{
	bool result;


	// 그래픽 렌더링을 수행합니다.
	result = Render();
	if (!result)
	{
		return false;
	}

	return true;
}

// 랜더링
bool GraphicsClass::Render()
{
	// 씬 그리기를 시작하기 위해 버퍼의 내용을 지움니다.
	m_D3D->BeginScene(0.5f, 0.5f, 0.5f, 1.0f);

	// 버퍼에 그려진 씬을 화면에 표시합니다.
	m_D3D->EndScene();

	return true;
}