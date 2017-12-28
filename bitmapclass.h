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
	struct VertexType																 // ���� Ÿ��
	{
		XMFLOAT3 position;						// ��ġ
		XMFLOAT2 texture;						// �ش��ϴ� �ؽ��� UV
	};

public:
	BitmapClass();
	BitmapClass(const BitmapClass&);
	~BitmapClass();

	bool Initialize(ID3D11Device*, int, int, WCHAR*, int, int);						 // �ʱ�ȭ
	void Shutdown();																 // ����
	bool Render(ID3D11DeviceContext*, int, int);									 // ������
																					 
	int GetIndexCount();															 // �ε��� ������ �������� �Լ�
	ID3D11ShaderResourceView* GetTexture();											 // �ؽ��ĸ� �������� �Լ�
																					 
private:																			 
	bool InitializeBuffers(ID3D11Device*);											 // ���� �ʱ�ȭ
	void ShutdownBuffers();															 // ���� ����
	bool UpdateBuffers(ID3D11DeviceContext*, int, int);								 // ���� ������Ʈ
	void RenderBuffers(ID3D11DeviceContext*);										 // ���� ������ ������(���������� ���)
																					
	bool LoadTexture(ID3D11Device*, WCHAR*);										 // �ؽ��� �ε�
	void ReleaseTexture();															 // �ؽ��� �Ҵ� ����
																					
private:																			 
	ID3D11Buffer *m_vertexBuffer, *m_indexBuffer;									 // ����, �ε��� ����
	int m_vertexCount, m_indexCount;												 // ����, �ε��� ����
	TextureClass* m_Texture;														 // �ؽ���
	int m_screenWidth, m_screenHeight;												 // ȭ���� ����, ����
	int m_bitmapWidth, m_bitmapHeight;												 // ��Ʈ���� ����, ����
	int m_previousPosX, m_previousPosY;												 // ������ �������� ��ǥ
};