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

	bool Initialize(int, int, bool, HWND, bool, float, float);	// �ʱ�ȭ
	void Shutdown();											// ����

	void BeginScene(float, float, float, float);				// ���� �׸��� ����
	void EndScene();											// ���� �� �׸�

	ID3D11Device* GetDevice();									// Device�� �����͸� �޾ƿ�
	ID3D11DeviceContext* GetDeviceContext();					// DeviceContext�� �����͸� �޾ƿ�

	void GetProjectionMatrix(XMMATRIX&);						// �翵 ����� ���۷����� �޾ƿ�
	void GetWorldMatrix(XMMATRIX&);								// ���� ����� ���۷����� �޾ƿ�
	void GetOrthoMatrix(XMMATRIX&);								// ���翵 ����� ���۷����� �޾ƿ�
	void GetVideoCardInfo(char*, int&);							// �׷���ī���� ������ �޾ƿ�
	
	void TurnZBufferOn();										// Z���۸� Ŵ
	void TurnZBufferOff();										// Z���۸� ��
	void TurnOnAlphaBlending();									// ������ Ŵ
	void TurnOffAlphaBlending();								// ������ ��

private:
	bool	m_vsync_enabled;									// ���� ����ȭ ����
	int		m_videoCardMemory;									// �׷���ī���� �޸�
	char	m_videoCardDescription[128];						// �׷���ī���� �ʱ�ȭ ���� 
	
	IDXGISwapChain*				m_swapChain;					// ���� ü��
	ID3D11Device*				m_device;						// ����̽�
	ID3D11DeviceContext*		m_deviceContext;				// ����̽� ���ؽ�Ʈ
	ID3D11RenderTargetView*		m_renderTargetView;				// ���� Ÿ�� ��
	ID3D11Texture2D*			m_depthStencilBuffer;			// ���ٽ� ����
	ID3D11DepthStencilState*	m_depthStencilState;			// ���ٽ� ���
	ID3D11DepthStencilView*		m_depthStencilView;				// ���ٽ� ��
	ID3D11RasterizerState*		m_rasterState;					// ������ ����
	
	XMMATRIX					m_projectionMatrix;				// �翵���
	XMMATRIX					m_worldMatrix;					// �������
	XMMATRIX					m_orthoMatrix;					// ���翵���
	
	ID3D11DepthStencilState*    m_depthDisabledStencilState;	// ���� ���ٽ� ����

	ID3D11BlendState*			m_alphaEnableBlendingState;		// ���� ���� ����
	ID3D11BlendState*			m_alphaDisableBlendingState;	// ���� ���� ����
};
