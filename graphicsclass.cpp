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


	// Direct3D ��ü�� �����մϴ�.
	m_D3D = new D3DClass;
	if (!m_D3D)
	{
		return false;
	}

	// Direct3D ��ü�� �ʱ�ȭ�մϴ�.
	result = m_D3D->Initialize(screenWidth, screenHeight, VSYNC_ENABLED, hwnd, FULL_SCREEN, SCREEN_DEPTH, SCREEN_NEAR);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize Direct3D", L"Error", MB_OK);

		return false;
	}

	// Camera ��ü�� �����մϴ�.
	m_Camera = new CameraClass;
	if (!m_Camera)
	{
		return false;
	}

	// Camera�� ��ġ�� �����մϴ�.
	m_Camera->SetPosition(0.0f, 55.0f, -230.0f);

	// Model ��ü�� �����մϴ�.
	m_Model = new ModelClass;
	if (!m_Model)
	{
		return false;
	}

	// Model ��ü�� �ʱ�ȭ�մϴ�.
	result = m_Model->Initialize(m_D3D->GetDevice(), "../Studying_DX/data/model.txt", L"../Studying_DX/data/seafloor.dds");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);

		return false;
	}

	// LightShader ��ü�� �����մϴ�.
	m_LightShader = new LightShaderClass;
	if (!m_LightShader)
	{
		return false;
	}

	// LightShader ��ü�� �ʱ�ȭ�մϴ�.
	result = m_LightShader->Initialize(m_D3D->GetDevice(), hwnd);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the light shader object.", L"Error", MB_OK);

		return false;
	}

	// light ��ü�� �����մϴ�.
	m_Light = new LightClass;
	if (!m_Light)
	{
		return false;
	}

	// light ��ü�� �ʱ�ȭ�մϴ�.
	m_Light->SetAmbientColor(0.15f, 0.15f, 0.15f, 1.0f);
	m_Light->SetDiffuseColor(1.0f, 1.0f, 1.0f, 1.0f);
	m_Light->SetDirection(0.0f, 0.0f, 1.0f);

	return true;
}

void GraphicsClass::Shutdown()
{
	// LightShader ��ü�� ��ȯ�մϴ�.
	if (m_LightShader)
	{
		m_LightShader->Shutdown();
		delete m_LightShader;
		m_LightShader = 0;
	}

	// Light ��ü�� ��ȯ�մϴ�.
	if (m_Light)
	{
		delete m_Light;
		m_Light = 0;
	}


	// Model ��ü�� ��ȯ�մϴ�.
	if (m_Model)
	{
		m_Model->Shutdown();
		delete m_Model;
		m_Model = 0;
	}

	// Camera ��ü�� ��ȯ�մϴ�.
	if (m_Camera)
	{
		delete m_Camera;
		m_Camera = 0;
	}

	// D3D ��ü�� ��ȯ�մϴ�.
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

	// �� �����Ӹ��� ������ �����մϴ�.
	rotation += (float)XM_PI * 0.1f;
	if (rotation > 360.0f)
	{
		rotation -= 360.0f;
	}

	// �׷��� �������� �����մϴ�.
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


	// �� �׸��⸦ �����ϱ� ���� ������ ������ ����ϴ�.
	m_D3D->BeginScene(0.0f, 0.0f, 0.0f, 1.0f);

	// ī�޶��� ��ġ�� ����Ͽ� �� ����� �����մϴ�.
	m_Camera->Render();

	// ����� ��ĵ��� �ҷ��ɴϴ�.
	m_Camera->GetViewMatrix(viewMatrix);
	m_D3D->GetWorldMatrix(worldMatrix);
	m_D3D->GetProjectionMatrix(projectionMatrix);

	// ���� ����� ȸ���մϴ�.
	worldMatrix = XMMatrixRotationY(rotation);

	// �׷��� ���������ο� ���� �������ۿ� �ε������۸� �־� �׸� �غ� �մϴ�. 
	m_Model->Render(m_D3D->GetDeviceContext());


	// colorshader�� ����Ͽ� ���� �������մϴ�.
	result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_Model->GetIndexCount(), worldMatrix,
		viewMatrix, projectionMatrix, m_Model->GetTexture(), m_Light->GetDirection(), m_Light->GetAmbientColor(), m_Light->GetDiffuseColor());
	if (!result)
	{
		return false;
	}

	// ���ۿ� �׷��� ���� ȭ�鿡 ǥ���մϴ�.
	m_D3D->EndScene();

	return true;
}