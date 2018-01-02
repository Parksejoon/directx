//
// FileName : textclass.cpp
//
#include "textclass.h"


//
// CLASS FUNCTION
//
TextClass::TextClass()
{
	m_Font = 0;
	m_FontShader = 0;

	m_sentence1 = 0;
	m_sentence2 = 0;
}

TextClass::TextClass(const TextClass& other)
{
}

TextClass::~TextClass()
{
}

bool TextClass::Initialize(ID3D11Device* device, ID3D11DeviceContext* deviceContext, HWND hwnd, int screenWidth, int screenHeight,
	XMMATRIX baseViewMatrix)
{
	bool result;


	// 화면의 높이와 너비를 저장합니다.
	m_screenWidth = screenWidth;
	m_screenHeight = screenHeight;

	// 베이스 뷰 매트릭스를 저장합니다.
	m_baseViewMatrix = baseViewMatrix;

	// 폰트 오브젝트를 생성합니다.
	m_Font = new FontClass;
	if (!m_Font)
	{
		return false;
	}

	// 폰트 오브젝트를 초기화합니다.
	result = m_Font->Initiialize(device, "../Studying_DX/data/fontdata.txt", L"../Studying_DX/data/font.dds");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the font object.", L"Error", MB_OK);
		
		return false;
	}

	// 폰트 셰이더 오브젝트를 만듭니다.
	m_FontShader = new FontShaderClass;
	if (!m_FontShader)
	{
		return false;
	}

	// 폰트 셰이더 오브젝트를 초기화합니다.
	result = m_FontShader->Initialize(device, hwnd);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the font shader object.", L"Error", MB_OK);
		return false;
	}

	// 첫번째 문장을 초기화합니다.
	result = InitializeSentence(&m_sentence1, 16, device);
	if (!result)
	{
		return false;
	}

	// 문자열의 정보와 함께 문장 정점 버퍼를 갱신합니다.
	result = UpdateSentence(m_sentence1, "Hello", 100, 100, 1.0f, 1.0f, 1.0f, deviceContext);
	if (!result)
	{
		return false;
	}
	
	// 두번째 문장을 초기화합니다.
	result = InitializeSentence(&m_sentence2, 16, device);
	if(!result)
	{
		return false;
	}

	// 문자열의 정보와 함께 문장 정점 버퍼를 갱신합니다.
	result = UpdateSentence(m_sentence2, "Goodbye", 100, 200, 1.0f, 1.0f, 0.0f, deviceContext);
	if(!result)
	{
		return false;
	}

	return true;
}

void TextClass::Shutdown()
{
	// 첫번째 문장을 할당 해제합니다.
	ReleaseSentence(&m_sentence1);
	
	// 두번째 문장을 할당 해제합니다.
	ReleaseSentence(&m_sentence2);

	// 폰트 셰이더 오브젝트를 할당 해제합니다.
	if (m_FontShader)
	{
		m_FontShader->Shutdown();
		delete m_FontShader;
		m_FontShader = 0;
	}

	// 폰트 오브젝트를 할당 해제합니다.
	if (m_Font)
	{
		m_Font->Shutdown();
		delete m_Font;
		m_Font = 0;
	}

	return;
}

bool TextClass::Render(ID3D11DeviceContext* deviceContext, XMMATRIX worldMatrix, XMMATRIX orthoMatrix)
{
	bool result;


	// 첫번째 문장을 그립니다.
	result = RenderSentence(deviceContext, m_sentence1, worldMatrix, orthoMatrix);
	if (!result)
	{
		return false;
	}

	// 두번째 문장을 그립니다.
	result = RenderSentence(deviceContext, m_sentence2, worldMatrix, orthoMatrix);
	if (!result)
	{
		return false;
	}

	return true;
}

bool TextClass::InitializeSentence(SentenceType** sentence, int maxLength, ID3D11Device* device)
{
	VertexType* vertices;
	unsigned long* indices;
	D3D11_BUFFER_DESC vertexBufferDesc, indexBufferDesc;
	D3D11_SUBRESOURCE_DATA vertexData, indexData;
	HRESULT result;
	

	// 새로운 문장 오브젝트를 만듭니다.
	*sentence = new SentenceType;
	if (!*sentence)
	{
		return false;
	}

	// 문장 버퍼를 0으로 초기화합니다.
	(*sentence)->vertexBuffer = 0;
	(*sentence)->indexBuffer = 0;

	// 문장의 최대 길이를 설정합니다.
	(*sentence)->maxLength = maxLength;

	// 정점 배열의 정점 갯수를 설정합니다.
	(*sentence)->vertexCount = 6 * maxLength;

	// 인덱스 배열의 인덱스의 갯수를 설정합니다.
	(*sentence)->indexCount = (*sentence)->vertexCount;

	// 정점 배열을 생성합니다.
	vertices = new VertexType[(*sentence)->vertexCount];
	if (!vertices)
	{
		return false;
	}

	// 인덱스 배열을 생성합니다.
	indices = new unsigned long[(*sentence)->indexCount];
	if (!indices)
	{
		return false;
	}

	// 정점 배열을 0으로 초기화합니다.
	memset(vertices, 0, (sizeof(VertexType) * (*sentence)->vertexCount));

	// 인덱스 배열을 초기화합니다.
	for (int i = 0; i < (*sentence)->indexCount; i++)
	{
		indices[i] = i;
	}

	// 동적 정점 버퍼의 description을 작성합니다.
	vertexBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	vertexBufferDesc.ByteWidth = sizeof(VertexType) * (*sentence)->vertexCount;
	vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	vertexBufferDesc.MiscFlags = 0;
	vertexBufferDesc.StructureByteStride = 0;

	// 정점 데이터를 가르킬 서브리소스 구조체 포인터를 줍니다.
	vertexData.pSysMem = vertices;
	vertexData.SysMemPitch = 0;
	vertexData.SysMemSlicePitch = 0;

	// 정점 버퍼를 생성합니다.
	result = device->CreateBuffer(&vertexBufferDesc, &vertexData, &(*sentence)->vertexBuffer);
	if (FAILED(result))
	{
		return false;
	}

	// 정적 인덱스 버퍼의 description을 작성합니다.
	indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	indexBufferDesc.ByteWidth = sizeof(unsigned long) * (*sentence)->indexCount;
	indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	indexBufferDesc.CPUAccessFlags = 0;
	indexBufferDesc.MiscFlags = 0;
	indexBufferDesc.StructureByteStride = 0;

	// 인덱스 데이터를 가르킬 서브리소스 구조체 포인터를 줍니다.
	indexData.pSysMem = indices;
	indexData.SysMemPitch = 0;
	indexData.SysMemSlicePitch = 0;

	// 인덱스 버퍼를 생성합니다.
	result = device->CreateBuffer(&indexBufferDesc, &indexData, &(*sentence)->indexBuffer);
	if (FAILED(result))
	{
		return false;
	}

	// 더이상 필요 없는 것들을 할당 해제합니다.
	delete[] vertices;
	vertices = 0;

	delete[] indices;
	indices = 0;

	return true;
}

bool TextClass::UpdateSentence(SentenceType* sentence, char* text, int positionX, int positionY, float red, float green, float blue,
	ID3D11DeviceContext* deviceContext)
{
	int numLetters;
	VertexType* vertices;
	float drawX, drawY;
	HRESULT result;
	D3D11_MAPPED_SUBRESOURCE mappedResource;
	VertexType* verticesPtr;


	// 문장의 색을 저장합니다.
	sentence->red = red;
	sentence->green = green;
	sentence->blue = blue;

	// 문장의 문자의 갯수를 가져옵니다.
	numLetters = (int)strlen(text);

	// 버퍼의 오버플로우 여부를 확인합니다.
	if (numLetters > sentence->maxLength)
	{
		return false;
	}

	// 정점 배열을 생성합니다.
	vertices = new VertexType[sentence->vertexCount];
	if (!vertices)
	{
		return false;
	}

	// 정점 배열을 0으로 초기화합니다.
	memset(vertices, 0, (sizeof(VertexType) * sentence->vertexCount));

	// X와 Y픽셀 좌표를 계산합니다.
	drawX = (float)(((m_screenWidth / 2) * -1) + positionX);
	drawY = (float)((m_screenHeight / 2) - positionY);

	// 텍스트와 문장 위치를 정점 배열에 넣습니다.
	m_Font->BuildVertexArray((void*)vertices, text, drawX, drawY);
	
	// 정점 버퍼를 쓰기 위해 잠급니다.
	result = deviceContext->Map(sentence->vertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
	if (FAILED(result))
	{
		return false;
	}

	// 정점 버퍼 안에 데이터를 가르킬 포인터를 가져옵니다.
	verticesPtr = (VertexType*)mappedResource.pData;

	// 정점 버퍼 안에 데이터를 복사합니다.
	memcpy(verticesPtr, (void*)vertices, (sizeof(VertexType) * sentence->vertexCount));

	// 정점 버퍼의 잠금을 풉니다.
	deviceContext->Unmap(sentence->vertexBuffer, 0);

	// 정점 배열을 할당 해제합니다.
	delete[] vertices;
	vertices = 0;

	return true;
}

void TextClass::ReleaseSentence(SentenceType** sentence)
{
	if (*sentence)
	{
		// 문장 정점 버퍼를 할당 해제합니다.
		if ((*sentence)->vertexBuffer)
		{
			(*sentence)->vertexBuffer->Release();
			(*sentence)->vertexBuffer = 0;
		}

		// 문장 인덱스 버퍼를 할당 해제합니다.
		if ((*sentence)->indexBuffer)
		{
			(*sentence)->indexBuffer->Release();
			(*sentence)->indexBuffer = 0;
		}

		// 문장을 할당 해제합니다.
		delete *sentence;
		*sentence = 0;
	}

	return;
}

bool TextClass::RenderSentence(ID3D11DeviceContext* deviceContext, SentenceType* sentence, XMMATRIX worldMatrix,
	XMMATRIX orthoMatrix)
{
	unsigned int stride, offset;
	XMFLOAT4 pixelColor;
	bool result;


	// 정점 버퍼의 크기와 오프셋을 정합니다.
	stride = sizeof(VertexType);
	offset = 0;

	// 정점 버퍼가 렌더링 될 수 있도록 입력 어셈블러에서 활성 상태로 설정합니다.
	deviceContext->IASetVertexBuffers(0, 1, &sentence->vertexBuffer, &stride, &offset);

	// 인덱스 버퍼가 렌더링 될 수 있도록 입력 어셈블러에서 활성 상태로 설정합니다.
	deviceContext->IASetIndexBuffer(sentence->indexBuffer, DXGI_FORMAT_R32_UINT, 0);

	// 이 삼각형 안에 정점이 렌더링 되도록 원시 타입을 설정합니다.
	deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	// 입력 문장 색으로 색 벡터를 생성합니다.
	pixelColor = XMFLOAT4(sentence->red, sentence->green, sentence->blue, 1.0f);

	// 폰트 셰이더를 사용해서 텍스트를 렌더링합니다.
	result = m_FontShader->Render(deviceContext, sentence->indexCount, worldMatrix, m_baseViewMatrix, orthoMatrix, m_Font->GetTexture(),
		pixelColor);
	if (!result)
	{
		false;
	}

	return true;
}
