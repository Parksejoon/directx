//
// FileName : lightshaderclass.h
//
#pragma once


//
// INCLUDES
//
#include <d3dcompiler.h>
#include <d3d11.h>
#include <DirectXMath.h>
#include <fstream>

using namespace DirectX;
using namespace std;


//
// Class Name : LightShaderClass
//
class LightShaderClass
{
private:
	struct MatrixBufferType
	{
		XMMATRIX world;
		XMMATRIX view;
		XMMATRIX projection;
	};

	struct LightBufferType
	{
		XMFLOAT4 ambientColor;
		XMFLOAT4 diffuseColor;
		XMFLOAT3 lightDirection;
		float padding;			// 버퍼를 생성할 때 16의 배수가 되어야 하므로 채워넣는 변수입니다.
	};

public:
	LightShaderClass();
	LightShaderClass(const LightShaderClass&);
	~LightShaderClass();

	bool Initialize(ID3D11Device*, HWND);													// 초기화
	void Shutdown();																		// 종료
	bool Render(ID3D11DeviceContext*, int, XMMATRIX, XMMATRIX, XMMATRIX,
				ID3D11ShaderResourceView*, XMFLOAT3, XMFLOAT4, XMFLOAT4);					// 렌더링
private:
	bool InitializeShader(ID3D11Device*, HWND, WCHAR*, WCHAR*);								// 셰이더 초기화
	void ShutdownShader();																	// 셰이더 종료
	void OutputShaderErrorMessage(ID3D10Blob*, HWND, WCHAR*);								// 셰이더 에러 메세지를 출력하는 함수

	bool SetShaderParameters(ID3D11DeviceContext*, XMMATRIX, XMMATRIX, 
				XMMATRIX, ID3D11ShaderResourceView*, XMFLOAT3, XMFLOAT4, XMFLOAT4);			// 셰이더의 인자를 입력하는 함수
	void RenderShader(ID3D11DeviceContext*, int);											// 셰이더를 렌더링하는 함수

private:
	ID3D11VertexShader* m_vertexShader;				// 정점 셰이더
	ID3D11PixelShader* m_pixelShader;				// 픽셀 셰이더
	ID3D11InputLayout* m_layout;					// 레이아웃
	ID3D11Buffer* m_matrixBuffer;					// 행렬 버퍼
	ID3D11SamplerState* m_sampleState;				// 샘플의 상태
	ID3D11Buffer* m_lightBuffer;					// 빛의 정보를 위한 버퍼
};