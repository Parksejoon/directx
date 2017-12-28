//
// FileName : modelclass.h
//
#pragma once


//
// INCLUDES
//
#include <d3d11.h>
#include <DirectXMath.h>
#include <fstream>

using namespace DirectX;
using namespace std;


//
// MY CLASS INCLUDES
//
#include "textureclass.h"


//
// Class Name : ModelClass
//
class ModelClass
{
private:
	struct VertexType								// 정점 종류를 나타내는 구조체
	{
		XMFLOAT3 position;			// 정점의 위치
		XMFLOAT2 texture;			// 텍스쳐
		XMFLOAT3 normal;			// 법선 벡터
	};

	struct ModelType								// 모델 타입
	{
		float x, y, z;				// X, Y, Z 좌표
		float tu, tv;				// 텍스쳐 UV
		float nx, ny, nz;			// 노말 벡터의 X, Y, Z 좌표
	};

public:
	ModelClass();
	ModelClass(const ModelClass&);
	~ModelClass();

	bool Initialize(ID3D11Device*, char*, WCHAR*);	// 초기화
	void Shutdown();								// 종료
	void Render(ID3D11DeviceContext*);				// 랜더링

	int GetIndexCount();							// 인덱스 버퍼의 개수를 가져옴
	ID3D11ShaderResourceView* GetTexture();			// 텍스쳐를 가져옴

private:
	bool InitializeBuffer(ID3D11Device*);			// 버퍼 초기화
	void ShutdownBuffers();							// 버퍼 종료
	void RenderBuffers(ID3D11DeviceContext*);		// 각 버퍼를 활성화

	bool LoadTexture(ID3D11Device*, WCHAR*);		// 텍스쳐를 로드
	void ReleaseTexture();							// 텍스쳐를 할당 해제
	
	bool LoadModel(char*);							// 모델을 로드
	void ReleaseModel();							// 모델을 할당 해제

private:
	ID3D11Buffer *m_vertexBuffer, *m_indexBuffer;	// 정점버퍼와 인덱스버퍼
	int m_vertexCount, m_indexCount;				// 각 버퍼의 개수
	TextureClass* m_Texture;						// 텍스쳐
	ModelType* m_model;								// 모델
};
