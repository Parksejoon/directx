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


	// 화면의 크기를 저장합니다.
	m_screenWidth = screenWidth;
	m_screenHeight = screenHeight;

	// 이미지의 크기를 저장합니다.
	m_bitmapWidth = bitmapWidth;
	m_bitmapHeight = bitmapHeight;

	// 이전 렌더링 위치 변수를 -1로 초기화합니다.
	m_previousPosX = -1;
	m_previousPosY = -1;

	// 정점, 인덱스 버퍼를 초기화합니다.
	result = InitializeBuffers(device);
	if(!result)
	{
		return false;
	}

	// 이 모델의 텍스쳐를 불러옵니다.
	result = LoadTexture(device, textureFilename);
	if(!result)
	{
		return false;
	}

	return true;
}

void BitmapClass::Shutdown()
{
	// 모델 텍스쳐를 반환합니다.
	ReleaseTexture();

	// 정점, 인덱스 버퍼를 반환합니다.
	ShutdownBuffers();
	
	return;
}

bool BitmapClass::Render(ID3D11DeviceContext* deviceContext, int positionX, int positionY)
{
	bool result;


	// 화면의 다른 위치에 렌더링이 가능 하도록 동적 정점 버퍼를 다시 작성합니다.
	result = UpdateBuffers(deviceContext, positionX, positionY);
	if (!result)
	{
		return false;
	}

	// 정점, 인덱스 버퍼를 그래픽스 파이프라인에 넣습니다.
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


	// 정점 배열에 있는 정점의 갯수를 설정합니다.
	m_vertexCount = 6;

	// 인덱스 배열에 있는 인덱스의 갯수를 설정합니다.
	m_indexCount = m_vertexCount;

	// 정점 배열을 생성합니다.
	vertices = new VertexType[m_vertexCount];
	if (!vertices)
	{
		return false;
	}

	// 인덱스 배열을 생성합니다.
	indices = new unsigned long[m_indexCount];
	if (!indices)
	{
		return false;
	}

	// 정점 배열을 0으로 초기화합니다.
	memset(vertices, 0, (sizeof(VertexType) * m_vertexCount));

	// 데이터를 통해 인덱스 배열을 불러옵니다.
	for (int i = 0; i < m_indexCount; i++)
	{
		indices[i] = i;
	}

	// 정적 정점 버퍼의 description을 설정합니다.
	vertexBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	vertexBufferDesc.ByteWidth = sizeof(VertexType) * m_vertexCount;
	vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	vertexBufferDesc.MiscFlags = 0;
	vertexBufferDesc.StructureByteStride = 0;

	// 정점 데이터에 서브 리소스 구조체의 포인터를 줍니다.
	vertexData.pSysMem = vertices;
	vertexData.SysMemPitch = 0;
	vertexData.SysMemSlicePitch = 0;

	// 정점 버퍼를 생성합니다.
	result = device->CreateBuffer(&vertexBufferDesc, &vertexData, &m_vertexBuffer);
	if(FAILED(result))
	{
		return false;
	}

}
