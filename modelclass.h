//
// FileName : modelclass.h
//
#pragma once


//
// INCLUDES
//
#include <d3d11.h>
#include <DirectXMath.h>

using namespace DirectX;


//
// Class Name : ModelClass
//
class ModelClass
{
private:
	struct VertexType				// 정점 종류를 나타내는 구조체
	{
		XMFLOAT3 position;	// 정점의 위치
		XMFLOAT4 color;		// 정점의 색
	};

public:
	ModelClass();
	ModelClass(const ModelClass&);
	~ModelClass();

	bool Initialize(ID3D11Device*);			// 초기화
	void Shutdown();						// 종료
	void Render(ID3D11DeviceContext*);		// 랜더링

	int GetIndexCount();					// 인덱스 버퍼의 개수를 가져옴

private:
	bool InitializeBuffer(ID3D11Device*);			// 버퍼 초기화
	void ShutdownBuffers();							// 버퍼 종료
	void RenderBuffers(ID3D11DeviceContext*);		// 각 버퍼를 활성화

private:
	ID3D11Buffer *m_vertexBuffer, *m_indexBuffer;	// 정점버퍼와 인덱스버퍼
	int m_vertexCount, m_indexCount;				// 각 버퍼의 개수
};
