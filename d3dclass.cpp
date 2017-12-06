//
// FileName : d3dclass.cpp
//
#include "d3dclass.h"

//
// CLASS FUNCTION
//

// 생성자
D3DClass::D3DClass()
{
	m_swapChain = 0;
	m_device = 0;
	m_deviceContext = 0;
	m_renderTargetView = 0;
	m_depthStencilBuffer = 0;
	m_depthStencilState = 0;
	m_depthStencilView = 0;
	m_rasterState = 0;
}

// 복사 생성자
D3DClass::D3DClass(const D3DClass& other)
{
}

// 소멸자
D3DClass::~D3DClass()
{
}

// 생성
bool D3DClass::Initialize(int screenWidth, int screenHeight, bool vsync, HWND hwnd,
	bool fullscreen, float screenDepth, float screenNear)
{
	HRESULT result;
	IDXGIFactory* factory;
	IDXGIAdapter* adapter;
	IDXGIOutput* adapterOutput;
	unsigned int numModes, numerator, denominator, stringLength;
	DXGI_MODE_DESC* displayModeList;
	DXGI_ADAPTER_DESC adapterDesc;
	int error;
	DXGI_SWAP_CHAIN_DESC swapChainDesc;
	D3D_FEATURE_LEVEL featureLevel;
	ID3D11Texture2D* backBufferPtr;
	D3D11_TEXTURE2D_DESC depthBufferDesc;
	D3D11_DEPTH_STENCIL_DESC depthStencilDesc;
	D3D11_DEPTH_STENCIL_VIEW_DESC depthStencilViewDesc;
	D3D11_RASTERIZER_DESC rasterDesc;
	D3D11_VIEWPORT viewport;
	float fieldOfView, screenAspect;


	// vsync 설정을 저장
	m_vsync_enabled = vsync;

	// DirectX 그래픽 인터페이스 팩토리를 생성
	result = CreateDXGIFactory(__uuidof(IDXGIFactory), (void**)&factory);
	if (FAILED(result))
	{
		return false;
	}

	// 팩토리 객체를 사용하여 첫번째 그래픽 카드 인터페이스에 대한 아답터를 생성
	result = factory->EnumAdapters(0, &adapter);
	if (FAILED(result))
	{
		return false;
	}

	// 출력(모니터)에 대한 첫번째 아답터를 나열함
	result = adapter->EnumOutputs(0, &adapterOutput);
	if (FAILED(result))
	{
		return false;
	}

	// DXGI_FORMAT_R8G8B88A8_UNORM 모니터 출력 디스플레이 포맷에 맞는 모드의 개수를 구함
	result = adapterOutput->GetDisplayModeList(DXGI_FORMAT_B8G8R8A8_UNORM, DXGI_ENUM_MODES_INTERLACED, &numModes, displayModeList);
	if (FAILED(result))
	{
		return false;
	}

	// 모든 디스플레이 모드에 대해 화면 너비 / 높이에 맞는 디스플레이 모드를 찾음
	// 적합한 것을 찾으면 모니터의 새로고침 비율의 분모와 분자 값을 저장
	for (int i = 0; i < numModes; i++)
	{
		if (displayModeList[i].Width == (unsigned int)screenWidth)
		{
			if (displayModeList[i].Height == (unsigned int)screenHeight)
			{
				numerator = displayModeList[i].RefreshRate.Numerator;
				denominator = displayModeList[i].RefreshRate.Denominator;
			}
		}
	}

	// 아답터(그래픽카드)의 description을 가져옴
	result = adapter->GetDesc(&adapterDesc);
	if (FAILED(result))
	{
		return false;
	}

	// 현재 그래픽카드의 메모리 용량을 메가바이트 단위로 저장
	m_videoCardMemory = (int)(adapterDesc.DedicatedVideoMemory / 1024 / 1024);

	// 그래픽카드의 이름을 char형 문자열 배열로 바꾼 뒤 저장
	error = wcstombs_s(&stringLength, m_videoCardDescription, 128, adapterDesc.Description, 128);
	if (error != 0)
	{
		return false;
	}

	// 디스플레이 모드 리스트의 할당을 해제
	delete[] displayModeList;
	displayModeList = 0;

	// 출력 아답터를 할당 해제
	adapterOutput->Release();
	adapterOutput = 0;

	// 아답터를 할당 해제
	adapter->Release();
	adapter = 0;

	// 팩토리 객체를 할당 해제
	factory->Release();
	factory = 0;

	// 스왑 체인 decription을 초기화
	ZeroMemory(&swapChainDesc, sizeof(swapChainDesc));

	// 하나의 백버퍼만을 사용하도록 함
	swapChainDesc.BufferCount = 1;

	// 백버퍼의 너비와 높이를 설정함
	swapChainDesc.BufferDesc.Width = screenWidth;
	swapChainDesc.BufferDesc.Height = screenHeight;

	// 백버퍼로 일반적인 32bit의 서페이스를 지정함
	swapChainDesc.BufferDesc.Format = DXGI_FORMAT_G8R8_G8B8_UNORM;

	// 백버퍼의 새로고침 비율을 설정
	if (m_vsync_enabled)
	{
		swapChainDesc.BufferDesc.RefreshRate.Numerator = numerator;
		swapChainDesc.BufferDesc.RefreshRate.Denominator = denominator;
	}
	else
	{
		swapChainDesc.BufferDesc.RefreshRate.Numerator = 0;
		swapChainDesc.BufferDesc.RefreshRate.Denominator = 1;
	}

	// 백버퍼의 용도를 설정
	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;

	// 렌더링이 이루어질 윈도우의 핸들을 설정
	swapChainDesc.SampleDesc.Count = 1;
	swapChainDesc.SampleDesc.Quality = 0;

	// 윈도우 모드 또는 풀스크린 모드를 설정
	if (fullscreen)
	{
		swapChainDesc.Windowed = false;
	}
	else
	{
		swapChainDesc.Windowed = true;
	}

	// 스캔라인의 정렬과 스캔라이닝을 지정되지 않음으로(unspecified) 설정
	swapChainDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	swapChainDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;

	// 출력된 이후의 백버퍼의 내용을 버림
	swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

	// 추가 옵션 플래그를 사용하지 않음
	swapChainDesc.Flags = 0;

	// 피쳐 레벨을 DX11로 설정
	featureLevel = D3D_FEATURE_LEVEL_11_0;

	// 스왑 체인, Direct3D 디바이스, Direct3D 디바이스 컨텍스트를 생성
	result = D3D11CreateDeviceAndSwapChain(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, 0, &featureLevel,
		1, D3D11_SDK_VERSION, &swapChainDesc, &m_swapChain, &m_device, NULL, &m_deviceContext);
	
	// 백버퍼의 포인터를 가져옴
	result = m_swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&backBufferPtr);
	if (FAILED(result))
	{
		return false;
	}

	// 백버퍼의 포인터로 렌더타겟 뷰를 생성
	result = m_device->CreateRenderTargetView(backBufferPtr, NULL, &m_renderTargetView);
	if (FAILED(result))
	{
		return false;
	}

	// 백버퍼 포인터를 더이상 사용하지 않으므로 할당 해제
	backBufferPtr->Release();
	backBufferPtr = 0;

	// 깊이 버퍼의 decription을 초기화
	ZeroMemory(&depthBufferDesc, sizeof(depthBufferDesc));

	// 깊이 버퍼의 description을 작성
	depthBufferDesc.Width = screenWidth;
	depthBufferDesc.Height = screenHeight;
	depthBufferDesc.MipLevels = 1;
	depthBufferDesc.ArraySize = 1;
	depthBufferDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	depthBufferDesc.SampleDesc.Count = 1;
	depthBufferDesc.SampleDesc.Quality = 0;
	depthBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	depthBufferDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	depthBufferDesc.CPUAccessFlags = 0;
	depthBufferDesc.MiscFlags = 0;

	// description을 사용하여 깊이 버퍼의 텍스쳐를 생성
	result = m_device->CreateTexture2D(&depthBufferDesc, NULL, &m_depthStencilBuffer);
	if (FAILED(result))
	{
		return false;
	}

	// 스텐실 상태의 description을 초기화
	ZeroMemory(&depthStencilDesc, sizeof(depthStencilDesc));

	// 스텐실 상태의 description을 작성
	depthStencilDesc.DepthEnable = true;
	depthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	depthStencilDesc.DepthFunc = D3D11_COMPARISON_LESS;

	depthStencilDesc.StencilEnable = true;
	depthStencilDesc.StencilReadMask = 0xFF;
	depthStencilDesc.StencilWriteMask = 0xFF;

	// stencil operations if pixel is front-facing.
	depthStencilDesc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	depthStencilDesc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_KEEP;
	depthStencilDesc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	depthStencilDesc.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

	// 깊이-스텐실 상태를 생성
	result = m_device->CreateDepthStencilState(&depthStencilDesc, &m_depthStencilState);
	if (FAILED(result))
	{
		false;
	}

	// 렌더타겟 뷰와 깊이-스텐실 버퍼를 각각 출력 파이프라인에 바인딩
	m_deviceContext->OMSetRenderTargets(1, &m_renderTargetView, m_depthStencilView);

	// 어떤 도형을 어떻게 그릴 것인지 결정하는 래스터화기 description을 작성
	rasterDesc.AntialiasedLineEnable = false;
	rasterDesc.CullMode = D3D11_CULL_BACK;
	rasterDesc.DepthBias = 0;
	rasterDesc.DepthBiasClamp = 0.0f;
	rasterDesc.DepthClipEnable = true;
	rasterDesc.FillMode = D3D11_FILL_SOLID;
	rasterDesc.FrontCounterClockwise = false;
	rasterDesc.MultisampleEnable = false;
	rasterDesc.ScissorEnable = false;
	rasterDesc.SlopeScaledDepthBias = 0.0f;

	// 작성한 description으로 부터 래스터화기 상태를 생성
	result = m_device->CreateRasterizerState(&rasterDesc, &m_rasterState);
	if (FAILED(result))
	{
		return false;
	}

	// 래스터화기 상태를 설정
	m_deviceContext->RSSetState(m_rasterState);

	// 렌더링을 위한 뷰포트를 설정
	viewport.Width = (float)screenWidth;
	viewport.Height = (float)screenHeight;
	viewport.MinDepth = 0.0f;
	viewport.MaxDepth = 1.0f;
	viewport.TopLeftX = 0.0f;
	viewport.TopLeftY = 0.0f;

	// 뷰포트를 생성
	m_deviceContext->RSSetViewports(1, &viewport);

	// 투영 행렬을 설정
	fieldOfView = (float)D3DX_PI / 4.0f;
	screenAspect = (float)screenWidth / (float)screenHeight;

	// 3D 렌더링을 위한 투영 행렬을 생성
	D3DXMatrixPerspectiveFovLH(&m_projectionMatrix, fieldOfView, screenAspect, screenNear, screenDepth);

	// 월드 행렬을 단위 행렬로 초기화
	D3DXMatrixIdentity(&m_worldMatrix);

	// 2D 렌더링에 사용될 정사영 행렬을 생성
	D3DXMatrixOrthoLH(&m_orthoMatrix, (float)screenWidth, (float)screenHeight, screenNear, screenDepth);
	
	return true;
}

// 종료
void D3DClass::Shutdown()
{
	// 종료 하기 전에 윈도우 모드로 바꾸지 않으면 스왑체인을 할당 해제할 때 예외 발생
	if (m_swapChain)
	{
		m_swapChain->SetFullscreenState(false, NULL);
	}

	if (m_rasterState)
	{
		m_rasterState->Release();
		m_rasterState = 0;
	}

	if (m_depthStencilView)
	{
		m_depthStencilView->Release();
		m_depthStencilView = 0;
	}

	if (m_depthStencilState)
	{
		m_depthStencilState->Release();
		m_depthStencilState = 0;
	}

	if (m_depthStencilBuffer)
	{
		m_depthStencilBuffer->Release();
		m_depthStencilBuffer - 0;
	}

	if (m_renderTargetView)
	{
		m_renderTargetView->Release();
		m_renderTargetView = 0;
	}

	if (m_deviceContext)
	{
		m_deviceContext->Release();
		m_deviceContext = 0;
	}

	if (m_device)
	{
		m_device->Release();
		m_device = 0;
	}

	if (m_swapChain)
	{
		m_swapChain->Release();
		m_swapChain = 0;
	}

	return;
}

// 씬을 시작
void D3DClass::BeginScene(float red, float green, float blue, float alpha)
{
	float color[4];


	// 버퍼를 어떤 색상으로 지울 것인지 설정
	color[0] = red;
	color[1] = green;
	color[2] = blue;
	color[3] = alpha;

	// 백버퍼의 내용을 지움
	m_deviceContext->ClearRenderTargetView(m_renderTargetView, color);

	// 깊이 버퍼를 지움
	m_deviceContext->ClearDepthStencilView(m_depthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0);

	return;
}

// 씬 종료
void D3DClass::EndScene()
{
	// 렌더링이 완료되었으므로 백버퍼의 내용을 화면에 표시
	// 수직 동기화 여부 확인
	if (m_vsync_enabled)
	{
		// 새로고침 비율을 고정
		m_swapChain->Present(1, 0);
	}
	else
	{
		// 가능한 빠르게 표시
		m_swapChain->Present(0, 0);
	}

	return;
}

// 디바이스의 포인터를 가져오는 함수
ID3D11Device* D3DClass::GetDevice()
{
	return m_device;
}

// 디바이스 컨텍스트의 포인터를 가져오는 함수
ID3D11DeviceContext* D3DClass::GetDeviceConstext()
{
	return m_deviceContext;
}

// 투영 행렬을 가져오는 함수
void D3DClass::GetProjectionMatrix(D3DXMATRIX& projectionMatrix)
{
	projectionMatrix = m_projectionMatrix;
	return;
}

// 월드 행렬을 가져오는 함수
void D3DClass::GetWorldMatrix(D3DXMATRIX& worldMatrix)
{
	worldMatrix = m_worldMatrix;
	return;
}

// 정사영 행렬을 가져오는 함수
void D3DClass::GetOrthoMatrix(D3DXMATRIX& orthoMatrix)
{
	orthoMatrix = m_orthoMatrix;
	return;
}

// 그래픽 카드의 정보를 가져오는 함수
void D3DClass::GetVideoCardInfo(char* cardName, int& memory)
{
	strcpy_s(cardName, 128, m_videoCardDescription);
	memory = m_videoCardMemory;
	return;
}