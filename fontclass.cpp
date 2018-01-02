//
// FileName : fontclass.cpp
//
#include "fontclass.h"


//
// CLASS FUNCTION
//
FontClass::FontClass()
{
	m_Font = 0;
	m_Texture = 0;
}

FontClass::FontClass(const FontClass& other)
{
}

FontClass::~FontClass()
{
}

bool FontClass::Initiialize(ID3D11Device* device, char* fontFilename, WCHAR* textureFilename)
{
	bool result;


	// ��Ʈ �����͸� �ҷ��ɴϴ�.
	result = LoadFontData(fontFilename);
	if (!result)
	{
		return false;
	}

	// ��Ʈ ������ �ؽ��ĸ� �ҷ��ɴϴ�.
	result = LoadTexture(device, textureFilename);
	if (!result)
	{
		return false;
	}

	return true;
}

void FontClass::Shutdown()
{
	// ��Ʈ �ؽ��ĸ� ��ȯ�մϴ�.
	ReleaseTexture();

	// ��Ʈ �����͸� ��ȯ�մϴ�.
	ReleaseFontData();

	return;
}

bool FontClass::LoadFontData(char* filename)
{
	ifstream fin;
	char temp;


	// ��Ʈ ���� ���۸� ����ϴ�.
	m_Font = new FontType[95];
	if (!m_Font)
	{
		return false;
	}

	// �ؽ�Ʈ ������ ���ϴ�.
	fin.open(filename);
	if (fin.fail())
	{
		return false;
	}

	// 95���� ���ڵ��� �о�ɴϴ�.
	for (int i = 0; i < 95; i++)
	{
		fin.get(temp);
		while (temp != ' ')
		{
			fin.get(temp);
		}

		fin.get(temp);
		while (temp != ' ')
		{
			fin.get(temp);
		}

		fin >> m_Font[i].left;
		fin >> m_Font[i].right;
		fin >> m_Font[i].size;
	}

	// ������ �ݽ��ϴ�.
	fin.close();

	return true;
}

void FontClass::ReleaseFontData()
{
	// ��Ʈ ������ �迭�� �Ҵ� �����մϴ�.
	if (m_Font)
	{
		delete[] m_Font;
		m_Font = 0;
	}

	return;
}

bool FontClass::LoadTexture(ID3D11Device* device, WCHAR* filename)
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

void FontClass::ReleaseTexture()
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

ID3D11ShaderResourceView* FontClass::GetTexture()
{
	return m_Texture->GetTexture();
}

void FontClass::BuildVertexArray(void* vertices, char* sentence, float drawX, float drawY)
{
	VertexType* vertexPtr;
	int numLetters, index, letter;


	// ������ �Էµ� �������� ���� Ÿ���� ����ü�� �������� �ٲߴϴ�.
	vertexPtr = (VertexType*)vertices;

	// ������ ���ڰ����� ���ϴ�.
	numLetters = (int)strlen(sentence);

	// ���� �迭�� �ε����� �ʱ�ȭ�մϴ�.
	index = 0;

	// ������ ������ �簢������ ����ϴ�.
	for (int i = 0; i < numLetters; i++)
	{
		letter = ((int)sentence[i]) - 32;

		// ���� ���ڰ� �����̸� 3�ȼ��� �ű�ϴ�.
		if (letter == 0)
		{
			drawX = drawX + 3.0f;
		}
		else
		{
			// �簢���� ù��° �ﰢ��
			vertexPtr[index].position = XMFLOAT3(drawX, drawY, 0.0f);  // Top left.
			vertexPtr[index].texture = XMFLOAT2(m_Font[letter].left, 0.0f);
			index++;

			vertexPtr[index].position = XMFLOAT3((drawX + m_Font[letter].size), (drawY - 16), 0.0f);  // Bottom right.
			vertexPtr[index].texture = XMFLOAT2(m_Font[letter].right, 1.0f);
			index++;

			vertexPtr[index].position = XMFLOAT3(drawX, (drawY - 16), 0.0f);  // Bottom left.
			vertexPtr[index].texture = XMFLOAT2(m_Font[letter].left, 1.0f);
			index++;

			// �簢���� �ι�° �ﰢ��
			vertexPtr[index].position = XMFLOAT3(drawX, drawY, 0.0f);  // Top left.
			vertexPtr[index].texture = XMFLOAT2(m_Font[letter].left, 0.0f);
			index++;

			vertexPtr[index].position = XMFLOAT3(drawX + m_Font[letter].size, drawY, 0.0f);  // Top right.
			vertexPtr[index].texture = XMFLOAT2(m_Font[letter].right, 0.0f);
			index++;

			vertexPtr[index].position = XMFLOAT3((drawX + m_Font[letter].size), (drawY - 16), 0.0f);  // Bottom right.
			vertexPtr[index].texture = XMFLOAT2(m_Font[letter].right, 1.0f);
			index++;

			// ������ ũ��� �ϳ��� �ȼ��� �׸��� ���� X���� ��ǥ�� �����մϴ�.
			drawX = drawX + m_Font[letter].size + 1.0f;
		}
	}

	return;
}
