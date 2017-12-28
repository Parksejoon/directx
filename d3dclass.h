//
// FileName : d3dclass.h
//
#pragma once


//
// LINKING
//
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3d11.lib")


//
// INCLUDES
//
#include <dxgi.h>
#include <d3dcommon.h>
#include <d3d11.h>
#include <DirectXMath.h>

using namespace DirectX;


//
// Class Name : D3DClass
//
class D3DClass
{
public:
	D3DClass();
	D3DClass(const D3DClass&);
	~D3DClass();

	bool Initialize(int, int, bool, HWND, bool, float, float);	// 초기화
	void Shutdown();											// 종료

	void BeginScene(float, float, float, float);				// 씬을 그리기 시작
	void EndScene();											// 씬을 다 그림

	ID3D11Device* GetDevice();									// Device의 포인터를 받아옴
	ID3D11DeviceContext* GetDeviceContext();					// DeviceContext의 포인터를 받아옴

	void GetProjectionMatrix(XMMATRIX&);						// 사영 행렬을 레퍼런스로 받아옴
	void GetWorldMatrix(XMMATRIX&);								// 월드 행렬을 레퍼런스로 받아옴
	void GetOrthoMatrix(XMMATRIX&);								// 정사영 행렬을 레퍼런스로 받아옴
	void GetVideoCardInfo(char*, int&);							// 그래픽카드의 정보를 받아옴
	
	void TurnZBufferOn();										// Z버퍼를 킴
	void TurnZBufferOff();										// Z버퍼를 끔
	void TurnOnAlphaBlending();									// 블렌딩을 킴
	void TurnOffAlphaBlending();								// 블렌딩을 끔

private:
	bool	m_vsync_enabled;									// 수직 동기화 여부
	int		m_videoCardMemory;									// 그래픽카드의 메모리
	char	m_videoCardDescription[128];						// 그래픽카드의 초기화 설정 
	
	IDXGISwapChain*				m_swapChain;					// 스왑 체인
	ID3D11Device*				m_device;						// 디바이스
	ID3D11DeviceContext*		m_deviceContext;				// 디바이스 콘텍스트
	ID3D11RenderTargetView*		m_renderTargetView;				// 랜더 타겟 뷰
	ID3D11Texture2D*			m_depthStencilBuffer;			// 스텐실 버퍼
	ID3D11DepthStencilState*	m_depthStencilState;			// 스텐실 상대
	ID3D11DepthStencilView*		m_depthStencilView;				// 스텐실 뷰
	ID3D11RasterizerState*		m_rasterState;					// 레스터 상태
	
	XMMATRIX					m_projectionMatrix;				// 사영행렬
	XMMATRIX					m_worldMatrix;					// 월드행렬
	XMMATRIX					m_orthoMatrix;					// 정사영행렬
	
	ID3D11DepthStencilState*    m_depthDisabledStencilState;	// 깊이 스텐실 상태

	ID3D11BlendState*			m_alphaEnableBlendingState;		// 블렌딩 켜진 상태
	ID3D11BlendState*			m_alphaDisableBlendingState;	// 블렌딩 꺼진 상태
};
