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
	m_TextureShader = NULL;
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
	m_Camera->SetPosition(0.0f, 0.0f, -10.0f);

	// Model ��ü�� �����մϴ�.
	m_Model = new ModelClass;
	if (!m_Model)
	{
		return false;
	}

	// Model ��ü�� �ʱ�ȭ�մϴ�.
	result = m_Model->Initialize(m_D3D->GetDevice(), L"../Studying_DX/data/seafloor.dds");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);

		return false;
	}

	// ColorShader ��ü�� �����մϴ�.
	m_TextureShader = new TextureShaderClass;
	if (!m_TextureShader)
	{
		return false;
	}

	// ColorShader ��ü�� �ʱ�ȭ�մϴ�.
	result = m_TextureShader->Initialize(m_D3D->GetDevice(), hwnd);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the color shader object.", L"Error", MB_OK);

		return false;
	}

	return true;
}

void GraphicsClass::Shutdown()
{
	// ColorShader ��ü�� ��ȯ�մϴ�.
	if (m_TextureShader)
	{
		m_TextureShader->Shutdown();
		delete m_TextureShader;
		m_TextureShader = 0;
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


	// �׷��� �������� �����մϴ�.
	result = Render();
	if (!result)
	{
		return false;
	}

	return true;
}

bool GraphicsClass::Render()
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

	// �׷��� ���������ο� ���� �������ۿ� �ε������۸� �־� �׸� �غ� �մϴ�. 
	m_Model->Render(m_D3D->GetDeviceContext());

	// colorshader�� ����Ͽ� ���� �������մϴ�.
	result = m_TextureShader->Render(m_D3D->GetDeviceContext(), m_Model->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix, m_Model->GetTexture());
	if (!result)
	{
		return false;
	}

	// ���ۿ� �׷��� ���� ȭ�鿡 ǥ���մϴ�.
	m_D3D->EndScene();

	return true;
}