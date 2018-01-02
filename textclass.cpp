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


	// ȭ���� ���̿� �ʺ� �����մϴ�.
	m_screenWidth = screenWidth;
	m_screenHeight = screenHeight;

	// ���̽� �� ��Ʈ������ �����մϴ�.
	m_baseViewMatrix = baseViewMatrix;

	// ��Ʈ ������Ʈ�� �����մϴ�.
	m_Font = new FontClass;
	if (!m_Font)
	{
		return false;
	}

	// ��Ʈ ������Ʈ�� �ʱ�ȭ�մϴ�.
	result = m_Font->Initiialize(device, "../Studying_DX/data/fontdata.txt", L"../Studying_DX/data/font.dds");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the font object.", L"Error", MB_OK);
		
		return false;
	}

	// ��Ʈ ���̴� ������Ʈ�� ����ϴ�.
	m_FontShader = new FontShaderClass;
	if (!m_FontShader)
	{
		return false;
	}

	// ��Ʈ ���̴� ������Ʈ�� �ʱ�ȭ�մϴ�.
	result = m_FontShader->Initialize(device, hwnd);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the font shader object.", L"Error", MB_OK);
		return false;
	}

	// ù��° ������ �ʱ�ȭ�մϴ�.
	result = InitializeSentence(&m_sentence1, 16, device);
	if (!result)
	{
		return false;
	}

	// ���ڿ��� ������ �Բ� ���� ���� ���۸� �����մϴ�.
	result = UpdateSentence(m_sentence1, "Hello", 100, 100, 1.0f, 1.0f, 1.0f, deviceContext);
	if (!result)
	{
		return false;
	}
	
	// �ι�° ������ �ʱ�ȭ�մϴ�.
	result = InitializeSentence(&m_sentence2, 16, device);
	if(!result)
	{
		return false;
	}

	// ���ڿ��� ������ �Բ� ���� ���� ���۸� �����մϴ�.
	result = UpdateSentence(m_sentence2, "Goodbye", 100, 200, 1.0f, 1.0f, 0.0f, deviceContext);
	if(!result)
	{
		return false;
	}

	return true;
}

void TextClass::Shutdown()
{
	// ù��° ������ �Ҵ� �����մϴ�.
	ReleaseSentence(&m_sentence1);
	
	// �ι�° ������ �Ҵ� �����մϴ�.
	ReleaseSentence(&m_sentence2);

	// ��Ʈ ���̴� ������Ʈ�� �Ҵ� �����մϴ�.
	if (m_FontShader)
	{
		m_FontShader->Shutdown();
		delete m_FontShader;
		m_FontShader = 0;
	}

	// ��Ʈ ������Ʈ�� �Ҵ� �����մϴ�.
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


	// ù��° ������ �׸��ϴ�.
	result = RenderSentence(deviceContext, m_sentence1, worldMatrix, orthoMatrix);
	if (!result)
	{
		return false;
	}

	// �ι�° ������ �׸��ϴ�.
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
	

	// ���ο� ���� ������Ʈ�� ����ϴ�.
	*sentence = new SentenceType;
	if (!*sentence)
	{
		return false;
	}

	// ���� ���۸� 0���� �ʱ�ȭ�մϴ�.
	(*sentence)->vertexBuffer = 0;
	(*sentence)->indexBuffer = 0;

	// ������ �ִ� ���̸� �����մϴ�.
	(*sentence)->maxLength = maxLength;

	// ���� �迭�� ���� ������ �����մϴ�.
	(*sentence)->vertexCount = 6 * maxLength;

	// �ε��� �迭�� �ε����� ������ �����մϴ�.
	(*sentence)->indexCount = (*sentence)->vertexCount;

	// ���� �迭�� �����մϴ�.
	vertices = new VertexType[(*sentence)->vertexCount];
	if (!vertices)
	{
		return false;
	}

	// �ε��� �迭�� �����մϴ�.
	indices = new unsigned long[(*sentence)->indexCount];
	if (!indices)
	{
		return false;
	}

	// ���� �迭�� 0���� �ʱ�ȭ�մϴ�.
	memset(vertices, 0, (sizeof(VertexType) * (*sentence)->vertexCount));

	// �ε��� �迭�� �ʱ�ȭ�մϴ�.
	for (int i = 0; i < (*sentence)->indexCount; i++)
	{
		indices[i] = i;
	}

	// ���� ���� ������ description�� �ۼ��մϴ�.
	vertexBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	vertexBufferDesc.ByteWidth = sizeof(VertexType) * (*sentence)->vertexCount;
	vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	vertexBufferDesc.MiscFlags = 0;
	vertexBufferDesc.StructureByteStride = 0;

	// ���� �����͸� ����ų ���긮�ҽ� ����ü �����͸� �ݴϴ�.
	vertexData.pSysMem = vertices;
	vertexData.SysMemPitch = 0;
	vertexData.SysMemSlicePitch = 0;

	// ���� ���۸� �����մϴ�.
	result = device->CreateBuffer(&vertexBufferDesc, &vertexData, &(*sentence)->vertexBuffer);
	if (FAILED(result))
	{
		return false;
	}

	// ���� �ε��� ������ description�� �ۼ��մϴ�.
	indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	indexBufferDesc.ByteWidth = sizeof(unsigned long) * (*sentence)->indexCount;
	indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	indexBufferDesc.CPUAccessFlags = 0;
	indexBufferDesc.MiscFlags = 0;
	indexBufferDesc.StructureByteStride = 0;

	// �ε��� �����͸� ����ų ���긮�ҽ� ����ü �����͸� �ݴϴ�.
	indexData.pSysMem = indices;
	indexData.SysMemPitch = 0;
	indexData.SysMemSlicePitch = 0;

	// �ε��� ���۸� �����մϴ�.
	result = device->CreateBuffer(&indexBufferDesc, &indexData, &(*sentence)->indexBuffer);
	if (FAILED(result))
	{
		return false;
	}

	// ���̻� �ʿ� ���� �͵��� �Ҵ� �����մϴ�.
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


	// ������ ���� �����մϴ�.
	sentence->red = red;
	sentence->green = green;
	sentence->blue = blue;

	// ������ ������ ������ �����ɴϴ�.
	numLetters = (int)strlen(text);

	// ������ �����÷ο� ���θ� Ȯ���մϴ�.
	if (numLetters > sentence->maxLength)
	{
		return false;
	}

	// ���� �迭�� �����մϴ�.
	vertices = new VertexType[sentence->vertexCount];
	if (!vertices)
	{
		return false;
	}

	// ���� �迭�� 0���� �ʱ�ȭ�մϴ�.
	memset(vertices, 0, (sizeof(VertexType) * sentence->vertexCount));

	// X�� Y�ȼ� ��ǥ�� ����մϴ�.
	drawX = (float)(((m_screenWidth / 2) * -1) + positionX);
	drawY = (float)((m_screenHeight / 2) - positionY);

	// �ؽ�Ʈ�� ���� ��ġ�� ���� �迭�� �ֽ��ϴ�.
	m_Font->BuildVertexArray((void*)vertices, text, drawX, drawY);
	
	// ���� ���۸� ���� ���� ��޴ϴ�.
	result = deviceContext->Map(sentence->vertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
	if (FAILED(result))
	{
		return false;
	}

	// ���� ���� �ȿ� �����͸� ����ų �����͸� �����ɴϴ�.
	verticesPtr = (VertexType*)mappedResource.pData;

	// ���� ���� �ȿ� �����͸� �����մϴ�.
	memcpy(verticesPtr, (void*)vertices, (sizeof(VertexType) * sentence->vertexCount));

	// ���� ������ ����� Ǳ�ϴ�.
	deviceContext->Unmap(sentence->vertexBuffer, 0);

	// ���� �迭�� �Ҵ� �����մϴ�.
	delete[] vertices;
	vertices = 0;

	return true;
}

void TextClass::ReleaseSentence(SentenceType** sentence)
{
	if (*sentence)
	{
		// ���� ���� ���۸� �Ҵ� �����մϴ�.
		if ((*sentence)->vertexBuffer)
		{
			(*sentence)->vertexBuffer->Release();
			(*sentence)->vertexBuffer = 0;
		}

		// ���� �ε��� ���۸� �Ҵ� �����մϴ�.
		if ((*sentence)->indexBuffer)
		{
			(*sentence)->indexBuffer->Release();
			(*sentence)->indexBuffer = 0;
		}

		// ������ �Ҵ� �����մϴ�.
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


	// ���� ������ ũ��� �������� ���մϴ�.
	stride = sizeof(VertexType);
	offset = 0;

	// ���� ���۰� ������ �� �� �ֵ��� �Է� ��������� Ȱ�� ���·� �����մϴ�.
	deviceContext->IASetVertexBuffers(0, 1, &sentence->vertexBuffer, &stride, &offset);

	// �ε��� ���۰� ������ �� �� �ֵ��� �Է� ��������� Ȱ�� ���·� �����մϴ�.
	deviceContext->IASetIndexBuffer(sentence->indexBuffer, DXGI_FORMAT_R32_UINT, 0);

	// �� �ﰢ�� �ȿ� ������ ������ �ǵ��� ���� Ÿ���� �����մϴ�.
	deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	// �Է� ���� ������ �� ���͸� �����մϴ�.
	pixelColor = XMFLOAT4(sentence->red, sentence->green, sentence->blue, 1.0f);

	// ��Ʈ ���̴��� ����ؼ� �ؽ�Ʈ�� �������մϴ�.
	result = m_FontShader->Render(deviceContext, sentence->indexCount, worldMatrix, m_baseViewMatrix, orthoMatrix, m_Font->GetTexture(),
		pixelColor);
	if (!result)
	{
		false;
	}

	return true;
}
