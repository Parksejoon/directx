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
		float padding;			// ���۸� ������ �� 16�� ����� �Ǿ�� �ϹǷ� ä���ִ� �����Դϴ�.
	};

public:
	LightShaderClass();
	LightShaderClass(const LightShaderClass&);
	~LightShaderClass();

	bool Initialize(ID3D11Device*, HWND);													// �ʱ�ȭ
	void Shutdown();																		// ����
	bool Render(ID3D11DeviceContext*, int, XMMATRIX, XMMATRIX, XMMATRIX,
				ID3D11ShaderResourceView*, XMFLOAT3, XMFLOAT4, XMFLOAT4);					// ������
private:
	bool InitializeShader(ID3D11Device*, HWND, WCHAR*, WCHAR*);								// ���̴� �ʱ�ȭ
	void ShutdownShader();																	// ���̴� ����
	void OutputShaderErrorMessage(ID3D10Blob*, HWND, WCHAR*);								// ���̴� ���� �޼����� ����ϴ� �Լ�

	bool SetShaderParameters(ID3D11DeviceContext*, XMMATRIX, XMMATRIX, 
				XMMATRIX, ID3D11ShaderResourceView*, XMFLOAT3, XMFLOAT4, XMFLOAT4);			// ���̴��� ���ڸ� �Է��ϴ� �Լ�
	void RenderShader(ID3D11DeviceContext*, int);											// ���̴��� �������ϴ� �Լ�

private:
	ID3D11VertexShader* m_vertexShader;				// ���� ���̴�
	ID3D11PixelShader* m_pixelShader;				// �ȼ� ���̴�
	ID3D11InputLayout* m_layout;					// ���̾ƿ�
	ID3D11Buffer* m_matrixBuffer;					// ��� ����
	ID3D11SamplerState* m_sampleState;				// ������ ����
	ID3D11Buffer* m_lightBuffer;					// ���� ������ ���� ����
};