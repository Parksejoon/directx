//
// FileName : textureclass.cpp
//
#include "textureclass.h"


//
// CLASS FUCTION
//
TextureClass::TextureClass()
{
	m_texture = 0;
}

TextureClass::TextureClass(const TextureClass& other)
{
}

TextureClass::~TextureClass()
{
}

bool TextureClass::Initialize(ID3D11Device* device, WCHAR* filename)
{
	HRESULT result;
	ScratchImage image;


	// �ؽ��ĸ� �ε��մϴ�.
	result = LoadFromDDSFile(filename, DDS_FLAGS_NONE, nullptr, image);
	if (FAILED(result))
	{
		// ���� ���⼭ ��������
		return false;
	}

	result = CreateShaderResourceView(device, image.GetImages(), image.GetImageCount(), image.GetMetadata(), &m_texture);
	if (FAILED(result))
	{
		return false;
	}

	return true;
}

void TextureClass::Shutdown()
{
	// �ؽ��ĸ� ��ȯ�մϴ�.
	if (m_texture)
	{
		m_texture->Release();
		m_texture = 0;
	}

	return;
}

ID3D11ShaderResourceView* TextureClass::GetTexture()
{
	return m_texture;
}