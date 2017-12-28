//
// FileName : bitmapclass.h
//
#pragma once


//
// INCLUDES
//
#include <d3d11.h>
#include <DirectXMath.h>


//
// MY CLASS INCLUDES
//
#include "textureclass.h"


//
// Class Name : BitmapClass
//
class BitmapClass
{
private:
	struct VertexType																 // 정점 타입
	{
		XMFLOAT3 position;						// 위치
		XMFLOAT2 texture;						// 해당하는 텍스쳐 UV
	};

public:
	BitmapClass();
	BitmapClass(const BitmapClass&);
	~BitmapClass();

	bool Initialize(ID3D11Device*, int, int, WCHAR*, int, int);						 // 초기화
	void Shutdown();																 // 종료
	bool Render(ID3D11DeviceContext*, int, int);									 // 렌더링
																					 
	int GetIndexCount();															 // 인덱스 갯수를 가져오는 함수
	ID3D11ShaderResourceView* GetTexture();											 // 텍스쳐를 가져오는 함수
																					 
private:																			 
	bool InitializeBuffers(ID3D11Device*);											 // 버퍼 초기화
	void ShutdownBuffers();															 // 버퍼 종료
	bool UpdateBuffers(ID3D11DeviceContext*, int, int);								 // 버퍼 업데이트
	void RenderBuffers(ID3D11DeviceContext*);										 // 버퍼 내용을 렌더링(파이프라인 등록)
																					
	bool LoadTexture(ID3D11Device*, WCHAR*);										 // 텍스쳐 로드
	void ReleaseTexture();															 // 텍스쳐 할당 해제
																					
private:																			 
	ID3D11Buffer *m_vertexBuffer, *m_indexBuffer;									 // 정점, 인덱스 버퍼
	int m_vertexCount, m_indexCount;												 // 정점, 인덱스 갯수
	TextureClass* m_Texture;														 // 텍스쳐
	int m_screenWidth, m_screenHeight;												 // 화면의 가로, 세로
	int m_bitmapWidth, m_bitmapHeight;												 // 비트맵의 가로, 세로
	int m_previousPosX, m_previousPosY;												 // 이전에 렌더링된 좌표
};