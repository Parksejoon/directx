////////////////////////////////////////////////////////////////////////////////
// Filename: fontshaderclass.h
////////////////////////////////////////////////////////////////////////////////
#pragma once


//////////////
// INCLUDES //
//////////////
#include <d3d11.h>
#include <DirectXMath.h>
#include <d3dcompiler.h>
#include <fstream>

using namespace DirectX;
using namespace std;


////////////////////////////////////////////////////////////////////////////////
// Class name: FontShaderClass
////////////////////////////////////////////////////////////////////////////////
class FontShaderClass
{
private:
	struct ConstantBufferType																						   // 행렬 버퍼 타입
	{
		XMMATRIX world;									 // 월드 행렬
		XMMATRIX view;									 // 뷰 행렬
		XMMATRIX projection;							 // 사영 행렬
	};

	struct PixelBufferType
	{
		XMFLOAT4 pixelColor;
	};

public:
	FontShaderClass();
	FontShaderClass(const FontShaderClass&);
	~FontShaderClass();

	bool Initialize(ID3D11Device*, HWND);																			// 초기화
	void Shutdown();																								// 종료
	bool Render(ID3D11DeviceContext*, int, XMMATRIX, XMMATRIX, XMMATRIX, ID3D11ShaderResourceView*, XMFLOAT4);		// 렌더링

private:
	bool InitializeShader(ID3D11Device*, HWND, WCHAR*, WCHAR*);														// 셰이더 초기화
	void ShutdownShader();																							// 셰이더 종료
	void OutputShaderErrorMessage(ID3D10Blob*, HWND, WCHAR*);														// 셰이더 에러

	bool SetShaderParameters(ID3D11DeviceContext*, XMMATRIX, XMMATRIX, XMMATRIX, ID3D11ShaderResourceView*, XMFLOAT4);		// 셰이더 인자 설정
	void RenderShader(ID3D11DeviceContext*, int);																	// 셰이더 렌더링

private:
	ID3D11VertexShader* m_vertexShader;																				// 정점 셰이더
	ID3D11PixelShader* m_pixelShader;																				// 픽셀 셰이더
	ID3D11InputLayout* m_layout;																					// 레이아웃
	ID3D11Buffer* m_constantBuffer;																					// 행렬 버퍼
	ID3D11SamplerState* m_sampleState;																				// 샘플 상태
	ID3D11Buffer* m_pixelBuffer;
};
