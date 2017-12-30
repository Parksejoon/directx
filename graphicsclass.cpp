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

	// 2d ���� �������̽��� �������ϱ� ���� ī�޶� ���� ���̽� �� ��Ʈ������ �ʱ�ȭ�մϴ�.
	m_Camera->SetPosition(0.0f, 0.0f, -1.0f);
	m_Camera->Render();
	m_Camera->GetViewMatrix(baseViewMatrix);

	// �ؽ�Ʈ ������Ʈ�� �����մϴ�.
	m_Text = new TextClass;
	if (!m_Text)
	{
		return false;
	}

	// �ؽ�Ʈ ��ü�� �ʱ�ȭ�մϴ�.
	result = m_Text->Initialize(m_D3D->GetDevice(), m_D3D->GetDeviceContext(), hwnd, screenWidth, screenHeight, baseViewMatrix);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the text object.", L"Error", MB_OK);

		return false;
	}

	//// �ؽ��� ���̴� ������Ʈ�� �����մϴ�.
	//m_TextureShader = new TextureShaderClass;
	//if (!m_TextureShader)
	//{
	//	return false;
	//}

	//// �ؽ��� ���̴� ������Ʈ�� �ʱ�ȭ�մϴ�.
	//result = m_TextureShader->Initialize(m_D3D->GetDevice(), hwnd);
	//if (!result)
	//{
	//	MessageBox(hwnd, L"Could not initialize the shader object.", L"Error", MB_OK);
	//	return false;
	//}

	//// ��Ʈ�� ������Ʈ�� �����մϴ�.
	//m_Bitmap = new BitmapClass();
	//if (!m_Bitmap)
	//{
	//	return false;
	//}

	//// ��Ʈ�� ������Ʈ�� �ʱ�ȭ�մϴ�.
	//result = m_Bitmap->Initialize(m_D3D->GetDevice(), screenWidth, screenHeight, L"../Studying_DX/data/seafloor.dds", 256, 256);
	//if(!result)
	//{
	//	MessageBox(hwnd, L"Could not initialize the bitmap object.", L"Error", MB_OK);
	//	return false;
	//}

	//// Model ��ü�� �����մϴ�.
	//m_Model = new ModelClass;
	//if (!m_Model)
	//{
	//	return false;
	//}

	//// Model ��ü�� �ʱ�ȭ�մϴ�.
	//result = m_Model->Initialize(m_D3D->GetDevice(), "../Studying_DX/data/model.txt", L"../Studying_DX/data/sap.dds");
	//if (!result)
	//{
	//	MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);

	//	return false;
	//}

	//// LightShader ��ü�� �����մϴ�.
	//m_LightShader = new LightShaderClass;
	//if (!m_LightShader)
	//{
	//	return false;
	//}

	//// LightShader ��ü�� �ʱ�ȭ�մϴ�.
	//result = m_LightShader->Initialize(m_D3D->GetDevice(), hwnd);
	//if (!result)
	//{
	//	MessageBox(hwnd, L"Could not initialize the light shader object.", L"Error", MB_OK);

	//	return false;
	//}

	//// light ��ü�� �����մϴ�.
	//m_Light = new LightClass;
	//if (!m_Light)
	//{
	//	return false;
	//}

	//// light ��ü�� �ʱ�ȭ�մϴ�.
	//m_Light->SetAmbientColor(0.15f, 0.15f, 0.15f, 1.0f);
	//m_Light->SetDiffuseColor(1.0f, 1.0f, 1.0f, 1.0f);
	//m_Light->SetDirection(0.0f, 0.0f, 1.0f);
	//m_Light->SetSpecularColor(1.0f, 0.0f, 0.0f, 1.0f);
	//m_Light->SetSpecularPower(32.0f);

	return true;
}

void GraphicsClass::Shutdown()
{
	// �ؽ�Ʈ ������Ʈ�� �Ҵ� �����մϴ�.
	if (m_Text)
	{
		m_Text->Shutdown();
		delete m_Text;
		m_Text = 0;
	}

	//// ��Ʈ�� ������Ʈ�� �Ҵ� �����մϴ�.
	//if(m_Bitmap)
	//{
	//	m_Bitmap->Shutdown();
	//	delete m_Bitmap;
	//	m_Bitmap = 0;
	//}

	//// �ؽ��� ���̴� ������Ʈ�� �Ҵ� �����մϴ�.
	//if(m_TextureShader)
	//{
	//	m_TextureShader->Shutdown();
	//	delete m_TextureShader;
	//	m_TextureShader = 0;
	//}

	//// LightShader ��ü�� ��ȯ�մϴ�.
	//if (m_LightShader)
	//{
	//	m_LightShader->Shutdown();
	//	delete m_LightShader;
	//	m_LightShader = 0;
	//}

	//// Light ��ü�� ��ȯ�մϴ�.
	//if (m_Light)
	//{
	//	delete m_Light;
	//	m_Light = 0;
	//}


	//// Model ��ü�� ��ȯ�մϴ�.
	//if (m_Model)
	//{
	//	m_Model->Shutdown();
	//	delete m_Model;
	//	m_Model = 0;
	//}

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
	rotation += (float)XM_PI * 0.05f;
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
	XMMATRIX worldMatrix, viewMatrix, projectionMatrix, orthoMatrix;
	bool result;


	// �� �׸��⸦ �����ϱ� ���� ������ ������ ����ϴ�.
	m_D3D->BeginScene(0.0f, 0.0f, 0.0f, 1.0f);

	// ī�޶��� ��ġ�� ����Ͽ� �� ����� �����մϴ�.
	m_Camera->Render();

	// ����� ��ĵ��� �ҷ��ɴϴ�.
	m_Camera->GetViewMatrix(viewMatrix);
	m_D3D->GetWorldMatrix(worldMatrix);
	m_D3D->GetProjectionMatrix(projectionMatrix);
	m_D3D->GetOrthoMatrix(orthoMatrix);
	
	// 2D �������� ���� Z���۸� ���ϴ�.
	m_D3D->TurnZBufferOff();

	// �ؽ�Ʈ�� ������ �ϱ� ���� ���� ������ �մϴ�.
	m_D3D->TurnOnAlphaBlending();

	// �ؽ�Ʈ ���ڿ��� �������մϴ�.
	result = m_Text->Render(m_D3D->GetDeviceContext(), worldMatrix, orthoMatrix);
	if (!result)
	{
		return false;
	}

	// �ؽ�Ʈ�� ������ �� �Ŀ� ���� ������ ���ϴ�.
	m_D3D->TurnOffAlphaBlending();

	//// ��Ʈ�� ����, �ε��� ���۸� �׷��Ƚ� ���������ο� �ֽ��ϴ�.
	//result = m_Bitmap->Render(m_D3D->GetDeviceContext(), 100, 100);
	//if (!result)
	//{
	//	return false;
	//}

	//// �ؽ��� ���̴��� ����� ��Ʈ���� �������մϴ�.
	//result = m_TextureShader->Render(m_D3D->GetDeviceContext(), m_Bitmap->GetIndexCount(), worldMatrix, viewMatrix, orthoMatrix, m_Bitmap->GetTexture());
	//if (!result)
	//{
	//	return false;
	//}

	// 2D �������� �������Ƿ� Z���۸� ������� �����Ӵϴ�.
	m_D3D->TurnZBufferOn();

	//// ���� ����� ȸ���մϴ�.
	//worldMatrix = XMMatrixRotationY(rotation);

	//// �׷��� ���������ο� ���� �������ۿ� �ε������۸� �־� �׸� �غ� �մϴ�. 
	//m_Model->Render(m_D3D->GetDeviceContext());

	//// ����Ʈ ���̴��� ����Ͽ� ���� �������մϴ�.
	//result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_Model->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix, 
	//			       m_Model->GetTexture(), m_Light->GetDirection(), m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(), 
	//			       m_Camera->GetPosition(), m_Light->GetSpecularColor(), m_Light->GetSpecularPower());
	//if (!result)
	//{
	//	return false;
	//}

	// ���ۿ� �׷��� ���� ȭ�鿡 ǥ���մϴ�.
	m_D3D->EndScene();

	return true;
}