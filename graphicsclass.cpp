//
// FileName : graphicsclass.cpp
//
#include "graphicsclass.h"


//
// CLASS FUNCTION
//
GraphicsClass::GraphicsClass()
{
	m_D3D		    = NULL;
	m_Camera	    = NULL;
	m_Model		    = NULL;
	m_LightShader	= NULL;
	m_Light			= NULL;
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
		MessageBox(hwnd, L"Could not initialize Direct3D", L"Error", MB_OK);

		return false;
	}

	// Camera 객체를 생성합니다.
	m_Camera = new CameraClass;
	if (!m_Camera)
	{
		return false;
	}

	// Camera의 위치를 설정합니다.
	m_Camera->SetPosition(0.0f, 55.0f, -230.0f);

	// Model 객체를 생성합니다.
	m_Model = new ModelClass;
	if (!m_Model)
	{
		return false;
	}

	// Model 객체를 초기화합니다.
	result = m_Model->Initialize(m_D3D->GetDevice(), "../Studying_DX/data/model.txt", L"../Studying_DX/data/seafloor.dds");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);

		return false;
	}

	// LightShader 객체를 생성합니다.
	m_LightShader = new LightShaderClass;
	if (!m_LightShader)
	{
		return false;
	}

	// LightShader 객체를 초기화합니다.
	result = m_LightShader->Initialize(m_D3D->GetDevice(), hwnd);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the light shader object.", L"Error", MB_OK);

		return false;
	}

	// light 객체를 생성합니다.
	m_Light = new LightClass;
	if (!m_Light)
	{
		return false;
	}

	// light 객체를 초기화합니다.
	m_Light->SetAmbientColor(0.15f, 0.15f, 0.15f, 1.0f);
	m_Light->SetDiffuseColor(1.0f, 1.0f, 1.0f, 1.0f);
	m_Light->SetDirection(0.0f, 0.0f, 1.0f);

	return true;
}

void GraphicsClass::Shutdown()
{
	// LightShader 객체를 반환합니다.
	if (m_LightShader)
	{
		m_LightShader->Shutdown();
		delete m_LightShader;
		m_LightShader = 0;
	}

	// Light 객체를 반환합니다.
	if (m_Light)
	{
		delete m_Light;
		m_Light = 0;
	}


	// Model 객체를 반환합니다.
	if (m_Model)
	{
		m_Model->Shutdown();
		delete m_Model;
		m_Model = 0;
	}

	// Camera 객체를 반환합니다.
	if (m_Camera)
	{
		delete m_Camera;
		m_Camera = 0;
	}

	// D3D 객체를 반환합니다.
	if (m_D3D)
	{
		m_D3D->Shutdown();
		delete m_D3D;
		m_D3D = 0;
	}

	return;
}

bool GraphicsClass::Frame()
{
	bool result;
	static float rotation = 0.0f;

	// 매 프래임마다 각도를 갱신합니다.
	rotation += (float)XM_PI * 0.1f;
	if (rotation > 360.0f)
	{
		rotation -= 360.0f;
	}

	// 그래픽 렌더링을 수행합니다.
	result = Render(rotation);
	if (!result)
	{
		return false;
	}

	return true;
}

bool GraphicsClass::Render(float rotation)
{
	XMMATRIX worldMatrix, viewMatrix, projectionMatrix;
	bool result;


	// 씬 그리기를 시작하기 위해 버퍼의 내용을 지움니다.
	m_D3D->BeginScene(0.0f, 0.0f, 0.0f, 1.0f);

	// 카메라의 위치를 사용하여 뷰 행렬을 생성합니다.
	m_Camera->Render();

	// 사용할 행렬들을 불러옵니다.
	m_Camera->GetViewMatrix(viewMatrix);
	m_D3D->GetWorldMatrix(worldMatrix);
	m_D3D->GetProjectionMatrix(projectionMatrix);

	// 월드 행렬을 회전합니다.
	worldMatrix = XMMatrixRotationY(rotation);

	// 그래픽 파이프라인에 모델의 정점버퍼와 인덱스버퍼를 넣어 그릴 준비를 합니다. 
	m_Model->Render(m_D3D->GetDeviceContext());


	// colorshader를 사용하여 모델을 랜더링합니다.
	result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_Model->GetIndexCount(), worldMatrix,
		viewMatrix, projectionMatrix, m_Model->GetTexture(), m_Light->GetDirection(), m_Light->GetAmbientColor(), m_Light->GetDiffuseColor());
	if (!result)
	{
		return false;
	}

	// 버퍼에 그려진 씬을 화면에 표시합니다.
	m_D3D->EndScene();

	return true;
}