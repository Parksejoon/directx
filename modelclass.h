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
	struct VertexType				// ���� ������ ��Ÿ���� ����ü
	{
		XMFLOAT3 position;	// ������ ��ġ
		XMFLOAT4 color;		// ������ ��
	};

public:
	ModelClass();
	ModelClass(const ModelClass&);
	~ModelClass();

	bool Initialize(ID3D11Device*);			// �ʱ�ȭ
	void Shutdown();						// ����
	void Render(ID3D11DeviceContext*);		// ������

	int GetIndexCount();					// �ε��� ������ ������ ������

private:
	bool InitializeBuffer(ID3D11Device*);			// ���� �ʱ�ȭ
	void ShutdownBuffers();							// ���� ����
	void RenderBuffers(ID3D11DeviceContext*);		// �� ���۸� Ȱ��ȭ

private:
	ID3D11Buffer *m_vertexBuffer, *m_indexBuffer;	// �������ۿ� �ε�������
	int m_vertexCount, m_indexCount;				// �� ������ ����
};
