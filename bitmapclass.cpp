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

	// ���� �ε��� ������ description�� �ۼ��մϴ�.
	indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	indexBufferDesc.ByteWidth = sizeof(unsigned long) * m_indexCount;
	indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	indexBufferDesc.CPUAccessFlags = 0;
	indexBufferDesc.MiscFlags = 0;
	indexBufferDesc.StructureByteStride = 0;

	// �ε��� �����Ϳ� ���� ���ҽ� ����ü�� �����͸� �ݴϴ�.
	indexData.pSysMem = indices;
	indexData.SysMemPitch = 0;
	indexData.SysMemSlicePitch = 0;

	// �ε��� ���۸� �����մϴ�.
	result = device->CreateBuffer(&indexBufferDesc, &indexData, &m_indexBuffer);
	if(FAILED(result))
	{
		return false;
	}

	// ����, �ε��� �迭�� �ð�����ǳ���� �����ϴ�.
	delete[] vertices;
	vertices = 0;

	delete[] indices;
	indices = 0;

	return true;
}

void BitmapClass::ShutdownBuffers()
{
	// �ε��� ���۸� �����մϴ�.
	if (m_indexBuffer)
	{
		m_indexBuffer->Release();
		m_indexBuffer = 0;
	}

	// ���� ���۸� �����մϴ�.
	if (m_vertexBuffer)
	{
		m_vertexBuffer->Release();
		m_vertexBuffer = 0;
	}

	return;
}

bool BitmapClass::UpdateBuffers(ID3D11DeviceContext* deviceContext, int positionX, int positionY)
{
	float left, right, top, bottom;
	VertexType* vertices;
	D3D11_MAPPED_SUBRESOURCE mappedResource;
	VertexType* verticesPtr;
	HRESULT result;


	// ���� ��Ʈ���� ������ ��ġ�� ������ �ʾҴٸ� ������ ���� �ʽ��ϴ�.
	if ((positionX == m_previousPosX) && (positionY == m_previousPosY))
	{
		return true;
	}

	// ���� ������ ��ġ�� ���Ͽ��ٸ� ���ο� ��ġ�� ����մϴ�.
	m_previousPosX = positionX;
	m_previousPosY = positionY;

	// ��Ʈ���� �����κ��� ȭ��� �����ϰ� ����մϴ�.
	left = (float)((m_screenWidth / 2) * -1) + (float)positionX;

	// ��Ʈ���� �����ʺκ��� ȭ��� �����ϰ� ����մϴ�.
	right = left + (float)m_bitmapWidth;

	// ��Ʈ���� ���ʺκ��� ȭ��� �����ϰ� ����մϴ�.
	top = (float)(m_screenHeight / 2) - (float)positionY;
	
	// ��Ʈ���� �Ʒ��ʺκ��� ȭ��� �����ϰ� ����մϴ�.
	bottom = top - (float)m_bitmapHeight;

	// ���� �迭�� �����մϴ�.
	vertices = new VertexType[m_vertexCount];
	if (!vertices)
	{
		return false;
	}

	// ���� �迭�� �ε��մϴ�.
	// ù��° �ﰢ��
	vertices[0].position = XMFLOAT3(left, top, 0.0f);  // Top left.
	vertices[0].texture = XMFLOAT2(0.0f, 0.0f);

	vertices[1].position = XMFLOAT3(right, bottom, 0.0f);  // Bottom right.
	vertices[1].texture = XMFLOAT2(1.0f, 1.0f);

	vertices[2].position = XMFLOAT3(left, bottom, 0.0f);  // Bottom left.
	vertices[2].texture = XMFLOAT2(0.0f, 1.0f);

	// �ι�° �ﰢ��
	vertices[3].position = XMFLOAT3(left, top, 0.0f);  // Top left.
	vertices[3].texture = XMFLOAT2(0.0f, 0.0f);

	vertices[4].position = XMFLOAT3(right, top, 0.0f);  // Top right.
	vertices[4].texture = XMFLOAT2(1.0f, 0.0f);

	vertices[5].position = XMFLOAT3(right, bottom, 0.0f);  // Bottom right.
	vertices[5].texture = XMFLOAT2(1.0f, 1.0f);

	// ���� ���۸� ���� ���� ��޴ϴ�.
	result = deviceContext->Map(m_vertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
	if (FAILED(result))
	{
		return false;
	}

	// ���� ������ �������� �����͸� �����ɴϴ�.
	verticesPtr = (VertexType*)mappedResource.pData;

	// ���� ������ �����͸� �����մϴ�.
	memcpy(verticesPtr, (void*)vertices, (sizeof(VertexType) * m_vertexCount));

	// ���� ���۸� ��� �����մϴ�.
	deviceContext->Unmap(m_vertexBuffer, 0);

	// ���� �迭�� �Ҵ��� �����մϴ�.
	delete[] vertices;
	vertices = 0;

	return true;
}

void BitmapClass::RenderBuffers(ID3D11DeviceContext* deviceContext)
{
	unsigned int stride;
	unsigned int offset;


	// ���� ������ ũ��� �������� �����մϴ�.
	stride = sizeof(VertexType);
	offset = 0;

	// ���� ���۰� Ȱ��ȭ �� �� �ֵ��� �Է� ��������� Ȱ�� ���·� �����մϴ�.
	deviceContext->IASetVertexBuffers(0, 1, &m_vertexBuffer, &stride, &offset);

	// �ε��� ���۰� Ȱ��ȭ �� �� �ֵ��� �Է� ��������� Ȱ�� ���·� �����մϴ�.
	deviceContext->IASetIndexBuffer(m_indexBuffer, DXGI_FORMAT_R32_UINT, 0);

	// �� ������ �ﰢ�� �ȿ� ���� ���۷κ��� ������ �ؾ��ϴ� ���� ������ �����մϴ�.
	deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	return;
}

bool BitmapClass::LoadTexture(ID3D11Device* device, WCHAR* filename)
{
	bool result;


	// �ؽ��� ������Ʈ�� �����մϴ�.
	m_Texture = new TextureClass;
	if (!m_Texture)
	{
		return false;
	}

	// �ؽ��� ������Ʈ�� �ʱ�ȭ�մϴ�.
	result = m_Texture->Initialize(device, filename);
	if (!result)
	{
		return false;
	}

	return true;
}

void BitmapClass::ReleaseTexture()
{
	// �ؽ��� ������Ʈ�� �Ҵ� �����մϴ�.
	if (m_Texture)
	{
		m_Texture->Shutdown();
		delete m_Texture;
		m_Texture = 0;
	}

	return;
}
