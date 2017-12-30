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
	m_Text			= NULL;
	//m_TextureShader	= NULL;
	//m_Bitmap			= NULL;
	//m_Model		    = NULL;
	//m_LightShader		= NULL;
	//m_Light			= NULL;
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
	XMMATRIX baseViewMatrix;


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

	// 2d 유저 인터페이스를 렌더링하기 위해 카메라를 통해 베이스 뷰 매트릭스를 초기화합니다.
	m_Camera->SetPosition(0.0f, 0.0f, -1.0f);
	m_Camera->Render();
	m_Camera->GetViewMatrix(baseViewMatrix);

	// 텍스트 오브젝트를 생성합니다.
	m_Text = new TextClass;
	if (!m_Text)
	{
		return false;
	}

	// 텍스트 객체를 초기화합니다.
	result = m_Text->Initialize(m_D3D->GetDevice(), m_D3D->GetDeviceContext(), hwnd, screenWidth, screenHeight, baseViewMatrix);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the text object.", L"Error", MB_OK);

		return false;
	}

	//// 텍스쳐 셰이더 오브젝트를 생성합니다.
	//m_TextureShader = new TextureShaderClass;
	//if (!m_TextureShader)
	//{
	//	return false;
	//}

	//// 텍스쳐 셰이더 오브젝트를 초기화합니다.
	//result = m_TextureShader->Initialize(m_D3D->GetDevice(), hwnd);
	//if (!result)
	//{
	//	MessageBox(hwnd, L"Could not initialize the shader object.", L"Error", MB_OK);
	//	return false;
	//}

	//// 비트맵 오브젝트를 생성합니다.
	//m_Bitmap = new BitmapClass();
	//if (!m_Bitmap)
	//{
	//	return false;
	//}

	//// 비트맵 오브젝트를 초기화합니다.
	//result = m_Bitmap->Initialize(m_D3D->GetDevice(), screenWidth, screenHeight, L"../Studying_DX/data/seafloor.dds", 256, 256);
	//if(!result)
	//{
	//	MessageBox(hwnd, L"Could not initialize the bitmap object.", L"Error", MB_OK);
	//	return false;
	//}

	//// Model 객체를 생성합니다.
	//m_Model = new ModelClass;
	//if (!m_Model)
	//{
	//	return false;
	//}

	//// Model 객체를 초기화합니다.
	//result = m_Model->Initialize(m_D3D->GetDevice(), "../Studying_DX/data/model.txt", L"../Studying_DX/data/sap.dds");
	//if (!result)
	//{
	//	MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);

	//	return false;
	//}

	//// LightShader 객체를 생성합니다.
	//m_LightShader = new LightShaderClass;
	//if (!m_LightShader)
	//{
	//	return false;
	//}

	//// LightShader 객체를 초기화합니다.
	//result = m_LightShader->Initialize(m_D3D->GetDevice(), hwnd);
	//if (!result)
	//{
	//	MessageBox(hwnd, L"Could not initialize the light shader object.", L"Error", MB_OK);

	//	return false;
	//}

	//// light 객체를 생성합니다.
	//m_Light = new LightClass;
	//if (!m_Light)
	//{
	//	return false;
	//}

	//// light 객체를 초기화합니다.
	//m_Light->SetAmbientColor(0.15f, 0.15f, 0.15f, 1.0f);
	//m_Light->SetDiffuseColor(1.0f, 1.0f, 1.0f, 1.0f);
	//m_Light->SetDirection(0.0f, 0.0f, 1.0f);
	//m_Light->SetSpecularColor(1.0f, 0.0f, 0.0f, 1.0f);
	//m_Light->SetSpecularPower(32.0f);

	return true;
}

void GraphicsClass::Shutdown()
{
	// 텍스트 오브젝트를 할당 해제합니다.
	if (m_Text)
	{
		m_Text->Shutdown();
		delete m_Text;
		m_Text = 0;
	}

	//// 비트맵 오브젝트를 할당 해제합니다.
	//if(m_Bitmap)
	//{
	//	m_Bitmap->Shutdown();
	//	delete m_Bitmap;
	//	m_Bitmap = 0;
	//}

	//// 텍스쳐 셰이더 오브젝트를 할당 해제합니다.
	//if(m_TextureShader)
	//{
	//	m_TextureShader->Shutdown();
	//	delete m_TextureShader;
	//	m_TextureShader = 0;
	//}

	//// LightShader 객체를 반환합니다.
	//if (m_LightShader)
	//{
	//	m_LightShader->Shutdown();
	//	delete m_LightShader;
	//	m_LightShader = 0;
	//}

	//// Light 객체를 반환합니다.
	//if (m_Light)
	//{
	//	delete m_Light;
	//	m_Light = 0;
	//}


	//// Model 객체를 반환합니다.
	//if (m_Model)
	//{
	//	m_Model->Shutdown();
	//	delete m_Model;
	//	m_Model = 0;
	//}

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
	rotation += (float)XM_PI * 0.05f;
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
	XMMATRIX worldMatrix, viewMatrix, projectionMatrix, orthoMatrix;
	bool result;


	// 씬 그리기를 시작하기 위해 버퍼의 내용을 지움니다.
	m_D3D->BeginScene(0.0f, 0.0f, 0.0f, 1.0f);

	// 카메라의 위치를 사용하여 뷰 행렬을 생성합니다.
	m_Camera->Render();

	// 사용할 행렬들을 불러옵니다.
	m_Camera->GetViewMatrix(viewMatrix);
	m_D3D->GetWorldMatrix(worldMatrix);
	m_D3D->GetProjectionMatrix(projectionMatrix);
	m_D3D->GetOrthoMatrix(orthoMatrix);
	
	// 2D 렌더링을 위해 Z버퍼를 끕니다.
	m_D3D->TurnZBufferOff();

	// 텍스트를 렌더링 하기 전에 알파 블렌딩을 켭니다.
	m_D3D->TurnOnAlphaBlending();

	// 텍스트 문자열을 렌더링합니다.
	result = m_Text->Render(m_D3D->GetDeviceContext(), worldMatrix, orthoMatrix);
	if (!result)
	{
		return false;
	}

	// 텍스트를 렌더링 한 후에 알파 블렌딩을 끕니다.
	m_D3D->TurnOffAlphaBlending();

	//// 비트맵 정점, 인덱스 버퍼를 그래픽스 파이프라인에 넣습니다.
	//result = m_Bitmap->Render(m_D3D->GetDeviceContext(), 100, 100);
	//if (!result)
	//{
	//	return false;
	//}

	//// 텍스쳐 셰이더를 사용해 비트맵을 렌더링합니다.
	//result = m_TextureShader->Render(m_D3D->GetDeviceContext(), m_Bitmap->GetIndexCount(), worldMatrix, viewMatrix, orthoMatrix, m_Bitmap->GetTexture());
	//if (!result)
	//{
	//	return false;
	//}

	// 2D 렌더링이 끝났으므로 Z버퍼를 원래대로 돌려둡니다.
	m_D3D->TurnZBufferOn();

	//// 월드 행렬을 회전합니다.
	//worldMatrix = XMMatrixRotationY(rotation);

	//// 그래픽 파이프라인에 모델의 정점버퍼와 인덱스버퍼를 넣어 그릴 준비를 합니다. 
	//m_Model->Render(m_D3D->GetDeviceContext());

	//// 라이트 셰이더를 사용하여 모델을 랜더링합니다.
	//result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_Model->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix, 
	//			       m_Model->GetTexture(), m_Light->GetDirection(), m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(), 
	//			       m_Camera->GetPosition(), m_Light->GetSpecularColor(), m_Light->GetSpecularPower());
	//if (!result)
	//{
	//	return false;
	//}

	// 버퍼에 그려진 씬을 화면에 표시합니다.
	m_D3D->EndScene();

	return true;
}