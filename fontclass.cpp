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


	// 폰트 데이터를 불러옵니다.
	result = LoadFontData(fontFilename);
	if (!result)
	{
		return false;
	}

	// 폰트 글자의 텍스쳐를 불러옵니다.
	result = LoadTexture(device, textureFilename);
	if (!result)
	{
		return false;
	}

	return true;
}

void FontClass::Shutdown()
{
	// 폰트 텍스쳐를 반환합니다.
	ReleaseTexture();

	// 폰트 데이터를 반환합니다.
	ReleaseFontData();

	return;
}

bool FontClass::LoadFontData(char* filename)
{
	ifstream fin;
	char temp;


	// 폰트 공간 버퍼를 만듭니다.
	m_Font = new FontType[95];
	if (!m_Font)
	{
		return false;
	}

	// 텍스트 파일을 엽니다.
	fin.open(filename);
	if (fin.fail())
	{
		return false;
	}

	// 95개의 문자들을 읽어옵니다.
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

	// 파일을 닫습니다.
	fin.close();

	return true;
}

void FontClass::ReleaseFontData()
{
	// 폰트 데이터 배열을 할당 해제합니다.
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


	// 텍스쳐 오브젝트를 생성합니다.
	m_Texture = new TextureClass;
	if (!m_Texture)
	{
		return false;
	}

	// 텍스쳐 오브젝트를 초기화합니다.
	result = m_Texture->Initialize(device, filename);
	if (!result)
	{
		return false;
	}

	return true;
}

void FontClass::ReleaseTexture()
{
	// 텍스쳐 오브젝트를 할당 해제합니다.
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


	// 강제로 입력된 정점들을 정점 타입의 구조체의 정점으로 바꿉니다.
	vertexPtr = (VertexType*)vertices;

	// 문장의 문자갯수를 셉니다.
	numLetters = (int)strlen(sentence);

	// 정점 배열의 인덱스를 초기화합니다.
	index = 0;

	// 각각의 문장을 사각형으로 만듭니다.
	for (int i = 0; i < numLetters; i++)
	{
		letter = ((int)sentence[i]) - 32;

		// 만약 문자가 공백이면 3픽셀을 옮깁니다.
		if (letter == 0)
		{
			drawX = drawX + 3.0f;
		}
		else
		{
			// 사각형의 첫번째 삼각형
			vertexPtr[index].position = XMFLOAT3(drawX, drawY, 0.0f);  // Top left.
			vertexPtr[index].texture = XMFLOAT2(m_Font[letter].left, 0.0f);
			index++;

			vertexPtr[index].position = XMFLOAT3((drawX + m_Font[letter].size), (drawY - 16), 0.0f);  // Bottom right.
			vertexPtr[index].texture = XMFLOAT2(m_Font[letter].right, 1.0f);
			index++;

			vertexPtr[index].position = XMFLOAT3(drawX, (drawY - 16), 0.0f);  // Bottom left.
			vertexPtr[index].texture = XMFLOAT2(m_Font[letter].left, 1.0f);
			index++;

			// 사각형의 두번째 삼각형
			vertexPtr[index].position = XMFLOAT3(drawX, drawY, 0.0f);  // Top left.
			vertexPtr[index].texture = XMFLOAT2(m_Font[letter].left, 0.0f);
			index++;

			vertexPtr[index].position = XMFLOAT3(drawX + m_Font[letter].size, drawY, 0.0f);  // Top right.
			vertexPtr[index].texture = XMFLOAT2(m_Font[letter].right, 0.0f);
			index++;

			vertexPtr[index].position = XMFLOAT3((drawX + m_Font[letter].size), (drawY - 16), 0.0f);  // Bottom right.
			vertexPtr[index].texture = XMFLOAT2(m_Font[letter].right, 1.0f);
			index++;

			// 문자의 크기와 하나의 픽셀을 그리기 위해 X축의 좌표를 갱신합니다.
			drawX = drawX + m_Font[letter].size + 1.0f;
		}
	}

	return;
}
