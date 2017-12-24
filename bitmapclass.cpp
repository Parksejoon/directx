//
// FileName : bitmapclass.cpp
//
#include "bitmapclass.h"


//
// CLASS FUNCTION
//
BitmapClass::BitmapClass()
{
	m_vertexBuffer = 0;
	m_indexBuffer = 0;
	m_Texture = 0;
}

BitmapClass::BitmapClass(const BitmapClass& other)
{
}

BitmapClass::~BitmapClass()
{
}

bool BitmapClass::Initialize(ID3D11Device* device, int screenWidth, int screenHeight, WCHAR* textureFilename, int bitmapWidth, int bitmapHeight)
{
	bool result;


	// ȭ���� ũ�⸦ �����մϴ�.
	m_screenWidth = screenWidth;
	m_screenHeight = screenHeight;

	// �̹����� ũ�⸦ �����մϴ�.
	m_bitmapWidth = bitmapWidth;
	m_bitmapHeight = bitmapHeight;

	// ���� ������ ��ġ ������ -1�� �ʱ�ȭ�մϴ�.
	m_previousPosX = -1;
	m_previousPosY = -1;

	// ����, �ε��� ���۸� �ʱ�ȭ�մϴ�.
	result = InitializeBuffers(device);
	if(!result)
	{
		return false;
	}

	// �� ���� �ؽ��ĸ� �ҷ��ɴϴ�.
	result = LoadTexture(device, textureFilename);
	if(!result)
	{
		return false;
	}

	return true;
}

void BitmapClass::Shutdown()
{
	// �� �ؽ��ĸ� ��ȯ�մϴ�.
	ReleaseTexture();

	// ����, �ε��� ���۸� ��ȯ�մϴ�.
	ShutdownBuffers();
	
	return;
}

bool BitmapClass::Render(ID3D11DeviceContext* deviceContext, int positionX, int positionY)
{
	bool result;


	// ȭ���� �ٸ� ��ġ�� �������� ���� �ϵ��� ���� ���� ���۸� �ٽ� �ۼ��մϴ�.
	result = UpdateBuffers(deviceContext, positionX, positionY);
	if (!result)
	{
		return false;
	}

	// ����, �ε��� ���۸� �׷��Ƚ� ���������ο� �ֽ��ϴ�.
	RenderBuffers(deviceContext);

	return true;
}

int BitmapClass::GetIndexCount()
{
	return m_indexCount;
}

ID3D11ShaderResourceView* BitmapClass::GetTexture()
{
	return m_Texture->GetTexture();
}

bool BitmapClass::InitializeBuffers(ID3D11Device* device)
{
	VertexType* vertices;
	unsigned long* indices;
	D3D11_BUFFER_DESC vertexBufferDesc, indexBufferDesc;
	D3D11_SUBRESOURCE_DATA vertexData, indexData;
	HRESULT result;


	// ���� �迭�� �ִ� ������ ������ �����մϴ�.
	m_vertexCount = 6;

	// �ε��� �迭�� �ִ� �ε����� ������ �����մϴ�.
	m_indexCount = m_vertexCount;

	// ���� �迭�� �����մϴ�.
	vertices = new VertexType[m_vertexCount];
	if (!vertices)
	{
		return false;
	}

	// �ε��� �迭�� �����մϴ�.
	indices = new unsigned long[m_indexCount];
	if (!indices)
	{
		return false;
	}

	// ���� �迭�� 0���� �ʱ�ȭ�մϴ�.
	memset(vertices, 0, (sizeof(VertexType) * m_vertexCount));

	// �����͸� ���� �ε��� �迭�� �ҷ��ɴϴ�.
	for (int i = 0; i < m_indexCount; i++)
	{
		indices[i] = i;
	}

	// ���� ���� ������ description�� �����մϴ�.
	vertexBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	vertexBufferDesc.ByteWidth = sizeof(VertexType) * m_vertexCount;
	vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	vertexBufferDesc.MiscFlags = 0;
	vertexBufferDesc.StructureByteStride = 0;

	// ���� �����Ϳ� ���� ���ҽ� ����ü�� �����͸� �ݴϴ�.
	vertexData.pSysMem = vertices;
	vertexData.SysMemPitch = 0;
	vertexData.SysMemSlicePitch = 0;

	// ���� ���۸� �����մϴ�.
	result = device->CreateBuffer(&vertexBufferDesc, &vertexData, &m_vertexBuffer);
	if(FAILED(result))
	{
		return false;
	}

}
