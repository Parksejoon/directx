//
// FileName : graphicsclass.cpp
//
#include "graphicsclass.h"

//
// CLASS FUNCTION
//

// 생성자
GraphicsClass::GraphicsClass()
{
	m_D3D = 0;
}

// 복사 생성자
GraphicsClass::GraphicsClass(const GraphicsClass& other)
{
}

// 소멸자
GraphicsClass::~GraphicsClass()
{
}

// 생성
bool GraphicsClass::Initialize(int screenWidth, int screenHeight, HWND hwnd)
{
	bool result;

	// Direct3D 객체를 생성
	m_D3D = new D3Dclass;
	if (!m_D3D)
	{
		return false;
	}

	// Direct3D 객체를 초기화
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
	// D3D 객체를 반환
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

	// 그래픽 렌더링을 수행
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
	// 씬 그리기를 시작하기 위해 버퍼의 내용을 지움
	m_D3D->BeginScene(0.5f, 0.5f, 0.5f, 1.0f);

	// 버퍼에 그려진 씬을 화면에 표시
	m_D3D->EndScene();

	return true;
}