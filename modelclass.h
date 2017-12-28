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
	struct VertexType								// ���� ������ ��Ÿ���� ����ü
	{
		XMFLOAT3 position;			// ������ ��ġ
		XMFLOAT2 texture;			// �ؽ���
		XMFLOAT3 normal;			// ���� ����
	};

	struct ModelType								// �� Ÿ��
	{
		float x, y, z;				// X, Y, Z ��ǥ
		float tu, tv;				// �ؽ��� UV
		float nx, ny, nz;			// �븻 ������ X, Y, Z ��ǥ
	};

public:
	ModelClass();
	ModelClass(const ModelClass&);
	~ModelClass();

	bool Initialize(ID3D11Device*, char*, WCHAR*);	// �ʱ�ȭ
	void Shutdown();								// ����
	void Render(ID3D11DeviceContext*);				// ������

	int GetIndexCount();							// �ε��� ������ ������ ������
	ID3D11ShaderResourceView* GetTexture();			// �ؽ��ĸ� ������

private:
	bool InitializeBuffer(ID3D11Device*);			// ���� �ʱ�ȭ
	void ShutdownBuffers();							// ���� ����
	void RenderBuffers(ID3D11DeviceContext*);		// �� ���۸� Ȱ��ȭ

	bool LoadTexture(ID3D11Device*, WCHAR*);		// �ؽ��ĸ� �ε�
	void ReleaseTexture();							// �ؽ��ĸ� �Ҵ� ����
	
	bool LoadModel(char*);							// ���� �ε�
	void ReleaseModel();							// ���� �Ҵ� ����

private:
	ID3D11Buffer *m_vertexBuffer, *m_indexBuffer;	// �������ۿ� �ε�������
	int m_vertexCount, m_indexCount;				// �� ������ ����
	TextureClass* m_Texture;						// �ؽ���
	ModelType* m_model;								// ��
};
